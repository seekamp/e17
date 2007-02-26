/*
 * Copyright (C) 2000-2007 Carsten Haitzler, Geoff Harrison and various contributors
 * Copyright (C) 2004-2007 Kim Woelders
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies of the Software, its documentation and marketing & publicity
 * materials, and acknowledgment shall be given in the documentation, materials
 * and software packages that this Software was used.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "E.h"
#include "borders.h"
#include "desktops.h"
#include "dialog.h"
#include "e16-ecore_list.h"
#include "eimage.h"
#include "emodule.h"
#include "eobj.h"
#include "ewins.h"
#include "file.h"
#include "grabs.h"
#include "hints.h"
#include "iclass.h"
#include "menus.h"
#include "screen.h"
#include "settings.h"
#include "tclass.h"
#include "timers.h"
#include "tooltips.h"
#include "xwin.h"
#include <time.h>
#include <X11/keysym.h>

#define DEBUG_MENU_EVENTS 0

static struct
{
   Menu               *first;
   Menu               *active;
   EWin               *context_ewin;
   EObj               *cover_win;
   char                just_shown;
} Mode_menus;

struct _menustyle
{
   char               *name;
   TextClass          *tclass;
   ImageClass         *bg_iclass;
   ImageClass         *item_iclass;
   ImageClass         *sub_iclass;
   char                use_item_bg;
   char                iconpos;
   int                 maxx;
   int                 maxy;
   char               *border_name;
   unsigned int        ref_count;
};

struct _menuitem
{
   Menu               *menu;
   ImageClass         *icon_iclass;
   char               *text;
   char               *params;
   Menu               *child;
   char                state;
   PmapMask            pmm[3];
   Win                 win;
   Win                 icon_win;
   short               icon_w;
   short               icon_h;
   short               text_w;
   short               text_h;
   short               text_x;
   short               text_y;
};

struct _menu
{
   EWin               *ewin;
   Win                 win;
   PmapMask            pmm;
   int                 w, h;
   char               *name;
   char               *title;
   char               *alias;
   MenuStyle          *style;
   MenuLoader         *loader;
   int                 num;
   MenuItem          **items;
   int                 icon_size;
   char                internal;	/* Don't destroy when reloading */
   char                dynamic;	/* May be emptied on close */
   char                shown;
   char                stuck;
   char                redraw;
   Menu               *parent;
   Menu               *child;
   MenuItem           *sel_item;
   time_t              last_change;
   time_t              last_access;
   void               *data;
   unsigned int        ref_count;
};

#define MENU_ITEM_EVENT_MASK \
	KeyPressMask | KeyReleaseMask | \
	ButtonPressMask | ButtonReleaseMask | \
	EnterWindowMask | LeaveWindowMask	/* | PointerMotionMask */

static void         MenuRedraw(Menu * m);
static void         MenuRealize(Menu * m);
static void         MenuActivateItem(Menu * m, MenuItem * mi);
static void         MenuDrawItem(Menu * m, MenuItem * mi, char shape,
				 int state);

static void         MenuHandleEvents(Win win, XEvent * ev, void *m);
static void         MenuItemHandleEvents(Win win, XEvent * ev, void *mi);
static void         MenuMaskerHandleEvents(Win win, XEvent * ev, void *prm);

static void         MenusHide(void);

static Ecore_List  *menu_list = NULL;
static Ecore_List  *menu_style_list = NULL;

static MenuItem    *
MenuFindItemByChild(Menu * m, Menu * mc)
{
   int                 i;

   if (!mc)
      return (m->num) ? m->items[0] : NULL;

   for (i = 0; i < m->num; i++)
     {
	if (mc == m->items[i]->child)
	   return m->items[i];
     }

   return NULL;
}

static void
MenuHideChildren(Menu * m)
{
   if (!m->child)
      return;

   MenuHide(m->child);
   m->child = NULL;
}

void
MenuHide(Menu * m)
{
   EWin               *ewin;

   if (!m)
      return;

   if (m->sel_item)
      MenuDrawItem(m, m->sel_item, 1, STATE_NORMAL);
   m->sel_item = NULL;

   ewin = m->ewin;
   if (ewin)
     {
	EUnmapWindow(m->win);
	EReparentWindow(m->win, VRoot.win, ewin->client.x, ewin->client.y);
	EwinHide(ewin);
     }
   m->ewin = NULL;

   m->stuck = 0;
   m->shown = 0;
   m->parent = NULL;
   m->last_access = time(0);
   MenuHideChildren(m);
   if (m->dynamic)
      MenuEmpty(m, 0);
}

static void
MenuEwinMoveResize(EWin * ewin, int resize __UNUSED__)
{
   Menu               *m = (Menu *) ewin->data;

   if (!m)
      return;

   if (Mode.mode != MODE_NONE && !m->redraw)
      return;

   if (TransparencyUpdateNeeded())
      m->redraw = 1;

   if ((!m->style->use_item_bg && m->pmm.pmap == 0) || m->redraw)
      MenuRedraw(m);
}

static void
MenuEwinClose(EWin * ewin)
{
   if ((Menu *) (ewin->data) == Mode_menus.active)
     {
	GrabKeyboardRelease();
	Mode_menus.active = NULL;
     }

   ewin->data = NULL;
}

static const EWinOps MenuEwinOps = {
   NULL,
   MenuEwinMoveResize,
   MenuEwinClose,
};

static void
MenuEwinInit(EWin * ewin, void *ptr)
{
   Menu               *m = (Menu *) ptr;

   ewin->data = ptr;
   ewin->ops = &MenuEwinOps;

   ewin->props.skip_ext_task = 1;
   ewin->props.skip_ext_pager = 1;
   ewin->props.no_actions = 1;
   ewin->props.skip_focuslist = 1;
   ewin->props.skip_winlist = 1;
   ewin->props.ignorearrange = 1;
   EwinInhSetWM(ewin, focus, 1);
   ewin->client.grav = StaticGravity;

   ICCCM_SetSizeConstraints(ewin, m->w, m->h, m->w, m->h, 0, 0, 1, 1,
			    0.0, 65535.0);

   EoSetLayer(ewin, 12);
   ewin->ewmh.opacity = OpacityFromPercent(Conf.opacity.menus);
}

static void         MenuShowMasker(Menu * m);

int
MenuLoad(Menu * m)
{
   if (!m || !m->loader)
      return 0;

   return m->loader(m);
}

static void
MenuShow(Menu * m, char noshow)
{
   EWin               *ewin;
   int                 x, y;
   int                 wx = 0, wy = 0;	/* wx, wy added to stop menus */
   int                 w, h, mw, mh;	/* from appearing offscreen */
   int                 head_num = 0;

   if (m->shown || !m->style)
      return;

   if (MenuLoad(m))
      MenuRealize(m);

   if (m->num <= 0)
      return;

   if (!m->win)
      MenuRealize(m);

   ewin = m->ewin;
   if (ewin)
     {
#if 0				/* ??? */
	EwinRaise(ewin);
	EwinShow(ewin);
	return;
#else
	MenuHide(m);
#endif
     }

   EGetGeometry(m->items[0]->win, NULL, &x, &y, &w, &h, NULL, NULL);
   mw = m->w;
   mh = m->h;

   wx = Mode.events.x - EoGetX(DesksGetCurrent()) - x - (w / 2);
   wy = Mode.events.y - EoGetY(DesksGetCurrent()) - y - (h / 2);
   if (Conf.menus.onscreen)
     {
	Border             *b;

	b = BorderFind(m->style->border_name);
	if (b)
	  {
	     int                 width;
	     int                 height;
	     int                 x_origin;
	     int                 y_origin;

	     head_num =
		GetPointerScreenGeometry(&x_origin, &y_origin, &width, &height);

	     if (wx > x_origin + width - mw - b->border.right)
		wx = x_origin + width - mw - b->border.right;
	     if (wx < x_origin + b->border.left)
		wx = x_origin + b->border.left;

	     if (wy > y_origin + height - mh - b->border.bottom)
		wy = y_origin + height - mh - b->border.bottom;
	     if (wy < y_origin + b->border.top)
		wy = y_origin + b->border.top;
	  }
     }

   EMoveWindow(m->win, wx, wy);

   ewin = AddInternalToFamily(m->win, m->style->border_name, EWIN_TYPE_MENU, m,
			      MenuEwinInit);
   m->ewin = ewin;
   if (ewin)
     {
	ewin->client.event_mask |= KeyPressMask;
	ESelectInput(m->win, ewin->client.event_mask);

	ewin->head = head_num;

	EwinMoveToDesktop(ewin, EoGetDesk(ewin));
	EwinResize(ewin, ewin->client.w, ewin->client.h);

	if (Conf.menus.animate)
	   EwinInstantShade(ewin, 0);

	if (!noshow)
	  {
	     ICCCM_Cmap(NULL);
	     EwinOpFloatAt(ewin, OPSRC_NA, EoGetX(ewin), EoGetY(ewin));
	     EwinShow(ewin);
	     if (Conf.menus.animate)
		EwinUnShade(ewin);
	  }
     }

   m->stuck = 0;
   m->shown = 1;
   m->last_access = time(0);
   Mode_menus.just_shown = 1;

   if (!Mode_menus.first)
     {
	Mode_menus.context_ewin = GetContextEwin();
#if 0
	Eprintf("Mode_menus.context_ewin set %s\n",
		EwinGetTitle(Mode_menus.context_ewin));
#endif
	ESync();
	Mode_menus.first = m;
	MenuShowMasker(m);
	TooltipsEnable(0);
	GrabKeyboardSet(m->win);
     }
   m->ref_count++;
}

static void
MenuStyleSetName(MenuStyle * ms, const char *name)
{
   if (ms->name)
      Efree(ms->name);
   ms->name = Estrdup(name);
}

static MenuStyle   *
MenuStyleCreate(const char *name)
{
   MenuStyle          *ms;

   ms = ECALLOC(MenuStyle, 1);
   if (!ms)
      return NULL;

   if (!menu_style_list)
      menu_style_list = ecore_list_new();
   ecore_list_prepend(menu_style_list, ms);

   ms->iconpos = ICON_LEFT;
   MenuStyleSetName(ms, name);

   return ms;
}

MenuItem           *
MenuItemCreate(const char *text, ImageClass * iclass,
	       const char *action_params, Menu * child)
{
   MenuItem           *mi;

   mi = ECALLOC(MenuItem, 1);

   mi->icon_iclass = iclass;
   if (iclass)
      ImageclassIncRefcount(iclass);

   mi->text = (text) ? Estrdup((text[0]) ? text : "?!?") : NULL;
   mi->params = Estrdup(action_params);
   mi->child = child;
   mi->state = STATE_NORMAL;

   return mi;
}

static int
_MenuStyleMatchName(const void *data, const void *match)
{
   return strcmp(((const MenuStyle *)data)->name, (const char *)match);
}

MenuStyle          *
MenuStyleFind(const char *name)
{
   return (MenuStyle *) ecore_list_find(menu_style_list, _MenuStyleMatchName,
					name);
}

void
MenuSetInternal(Menu * m)
{
   m->internal = 1;
}

void
MenuSetDynamic(Menu * m)
{
   m->dynamic = 1;
}

void
MenuSetName(Menu * m, const char *name)
{
   _EFDUP(m->name, name);

   if (!menu_list)
      menu_list = ecore_list_new();
   ecore_list_prepend(menu_list, m);
}

void
MenuSetAlias(Menu * m, const char *alias)
{
   _EFDUP(m->alias, alias);
}

void
MenuSetTitle(Menu * m, const char *title)
{
   _EFDUP(m->title, title);
}

void
MenuSetIconSize(Menu * m, int size)
{
   if (size > 48)
      size = 48;
   m->icon_size = size;
}

void
MenuSetData(Menu * m, char *data)
{
   if (m->data)
      Efree(m->data);
   m->data = data;
}

void
MenuSetLoader(Menu * m, MenuLoader * loader)
{
   m->loader = loader;
}

void
MenuSetTimestamp(Menu * m, time_t t)
{
   m->last_change = t;
}

const char         *
MenuGetName(const Menu * m)
{
   return m->name;
}

const char         *
MenuGetData(const Menu * m)
{
   return (const char *)m->data;
}

time_t
MenuGetTimestamp(const Menu * m)
{
   return m->last_change;
}

void
MenuSetStyle(Menu * m, MenuStyle * ms)
{
   if (m->style)
      m->style->ref_count--;
   if (!ms && m->parent)
      ms = m->parent->style;
   if (!ms)
      ms = MenuStyleFind("DEFAULT");
   m->style = ms;
   if (ms)
      ms->ref_count++;
}

Menu               *
MenuCreate(const char *name, const char *title, Menu * parent, MenuStyle * ms)
{
   Menu               *m;

   m = ECALLOC(Menu, 1);
   if (!m)
      return m;

   m->parent = parent;
   MenuSetName(m, name);
   MenuSetTitle(m, title);
   MenuSetStyle(m, ms);
   m->icon_size = -1;		/* Use image size */

   return m;
}

void
MenuDestroy(Menu * m)
{
   if (!m)
      return;

   m = (Menu *) ecore_list_remove_node(menu_list, m);
   if (!m)
      return;

   MenuHide(m);

   if (m->win)
      EDestroyWindow(m->win);

   MenuEmpty(m, 1);

   if (m->name)
      Efree(m->name);
   if (m->alias)
      Efree(m->alias);
   if (m->title)
      Efree(m->title);
   if (m->data)
      Efree(m->data);
   FreePmapMask(&m->pmm);

   Efree(m);
}

/* NB - this doesnt free imageclasses if we created them for the menu
 * FIXME: so it will leak if we create new imageclasses and stop using
 * old ones for menu icons. we need to add some ref counting in menu icon
 * imageclasses to knw to free them when not used
 */
void
MenuEmpty(Menu * m, int destroying)
{
   int                 i, j;

   for (i = 0; i < m->num; i++)
     {
	if (m->items[i])
	  {
	     if (m->items[i]->child)
		MenuDestroy(m->items[i]->child);
	     if (m->items[i]->text)
		Efree(m->items[i]->text);
	     if (m->items[i]->params)
		Efree(m->items[i]->params);
	     for (j = 0; j < 3; j++)
		FreePmapMask(&(m->items[i]->pmm[j]));
	     if (!destroying && m->items[i]->win)
		EDestroyWindow(m->items[i]->win);
	     if (m->items[i]->icon_iclass)
		ImageclassDecRefcount(m->items[i]->icon_iclass);
	     if (m->items[i])
		Efree(m->items[i]);
	  }
     }
   if (m->items)
      Efree(m->items);
   m->items = NULL;
   m->num = 0;
   m->sel_item = NULL;
}

void
MenuRepack(Menu * m)
{
   EWin               *ewin;

   m->redraw = 1;
   if (m->win)
      MenuRealize(m);

   ewin = m->ewin;
   if (!ewin)
      return;

   ICCCM_SetSizeConstraints(ewin, m->w, m->h, m->w, m->h, 0, 0, 1, 1,
			    0.0, 65535.0);
   EwinResize(ewin, m->w, m->h);
   EwinRaise(ewin);
}

void
MenuAddItem(Menu * m, MenuItem * item)
{
   if (!item)
      return;
   m->num++;
   m->items = EREALLOC(MenuItem *, m->items, m->num);
   m->items[m->num - 1] = item;
}

static void
MenuRealize(Menu * m)
{
   int                 i, maxh, maxw, nmaxy;
   int                 maxx1, maxx2, w, h, x, y, r, mmw, mmh;
   int                 iw, ih;
   EImage             *im;
   EImageBorder       *pad, *pad_item, *pad_sub;
   char                has_i, has_s;

   if (!m->style)
      return;

   if (!m->win)
     {
	m->win = ECreateClientWindow(VRoot.win, 0, 0, 1, 1);
	EventCallbackRegister(m->win, 0, MenuHandleEvents, m);
	if (m->title)
	   HintsSetWindowName(m->win, _(m->title));
	HintsSetWindowClass(m->win, m->name, "Enlightenment_Menu");
     }

   maxh = maxw = 0;
   maxx1 = 0;
   maxx2 = 0;
   has_i = 0;
   has_s = 0;

   for (i = 0; i < m->num; i++)
     {
	m->items[i]->menu = m;

	if (m->items[i]->child)
	   has_s = 1;
	else
	   has_i = 1;

	m->items[i]->win = ECreateWindow(m->win, 0, 0, 1, 1, 0);
	EventCallbackRegister(m->items[i]->win, 0, MenuItemHandleEvents,
			      m->items[i]);
	ESelectInput(m->items[i]->win, MENU_ITEM_EVENT_MASK);
	EMapWindow(m->items[i]->win);

	if ((m->style) && (m->style->tclass) && (m->items[i]->text))
	  {
	     TextSize(m->style->tclass, 0, 0, 0, _(m->items[i]->text), &w, &h,
		      17);
	     if (h > maxh)
		maxh = h;
	     if (w > maxx1)
		maxx1 = w;
	     m->items[i]->text_w = w;
	     m->items[i]->text_h = h;
	  }
	if (m->items[i]->icon_iclass && Conf.menus.show_icons)
	  {
	     im = ImageclassGetImage(m->items[i]->icon_iclass, 0, 0, 0);
	     if (im)
	       {
		  w = h = 0;
		  if (m->icon_size > 0)
		     w = h = m->icon_size;
		  else if (m->icon_size == 0)
		     w = h = Conf.menus.icon_size;
		  if (w <= 0 || h <= 0)
		    {
		       EImageGetSize(im, &w, &h);
		       EImageFree(im);
		    }
		  m->items[i]->icon_w = w;
		  m->items[i]->icon_h = h;
		  m->items[i]->icon_win =
		     ECreateWindow(m->items[i]->win, 0, 0, w, h, 0);
		  EMapWindow(m->items[i]->icon_win);
		  if (h > maxh)
		     maxh = h;
		  if (w > maxx2)
		     maxx2 = w;
	       }
	     else
		m->items[i]->icon_iclass = NULL;
	  }
     }

   pad = ImageclassGetPadding(m->style->bg_iclass);
   pad_item = ImageclassGetPadding(m->style->item_iclass);
   pad_sub = ImageclassGetPadding(m->style->sub_iclass);
   if (((has_i) && (has_s)) || ((!has_i) && (!has_s)))
     {
	if (pad_item->top > pad_sub->top)
	   maxh += pad_item->top;
	else
	   maxh += pad_sub->top;
	if (pad_item->bottom > pad_sub->bottom)
	   maxh += pad_item->bottom;
	else
	   maxh += pad_sub->bottom;
	maxw = maxx1 + maxx2;
	if (pad_item->left > pad_sub->left)
	   maxw += pad_item->left;
	else
	   maxw += pad_sub->left;
	if (pad_item->right > pad_sub->right)
	   maxw += pad_item->right;
	else
	   maxw += pad_sub->right;
     }
   else if (has_i)
     {
	maxh += pad_item->top;
	maxh += pad_item->bottom;
	maxw = maxx1 + maxx2;
	maxw += pad_item->left;
	maxw += pad_item->right;
     }
   else if (has_s)
     {
	maxh += pad_sub->top;
	maxh += pad_sub->bottom;
	maxw = maxx1 + maxx2;
	maxw += pad_sub->left;
	maxw += pad_sub->right;
     }

   mmw = 0;
   mmh = 0;

   nmaxy = 3 * VRoot.h / (4 * maxh + 1);
   if (m->style->maxy && nmaxy > m->style->maxy)
      nmaxy = m->style->maxy;

   r = 0;
   x = 0;
   y = 0;
   for (i = 0; i < m->num; i++)
     {
	if (r == 0 && (m->style->bg_iclass) && (!m->style->use_item_bg))
	  {
	     x += pad->left;
	     y += pad->top;
	  }
	EMoveResizeWindow(m->items[i]->win, x, y, maxw, maxh);
	if (m->style->iconpos == ICON_LEFT)
	  {
	     m->items[i]->text_x = pad_item->left + maxx2;
	     m->items[i]->text_w = maxx1;
	     m->items[i]->text_y = (maxh - m->items[i]->text_h) / 2;
	     if (m->items[i]->icon_win)
		EMoveWindow(m->items[i]->icon_win,
			    pad_item->left +
			    ((maxx2 - m->items[i]->icon_w) / 2),
			    ((maxh - m->items[i]->icon_h) / 2));
	  }
	else
	  {
	     m->items[i]->text_x = pad_item->left;
	     m->items[i]->text_w = maxx1;
	     m->items[i]->text_y = (maxh - m->items[i]->text_h) / 2;
	     if (m->items[i]->icon_win)
		EMoveWindow(m->items[i]->icon_win,
			    maxw - pad_item->right - maxx2 +
			    ((maxx2 - m->items[i]->icon_w) / 2),
			    ((maxh - m->items[i]->icon_h) / 2));
	  }
	if (m->items[i]->icon_iclass && Conf.menus.show_icons)
	  {
	     iw = 0;
	     ih = 0;
	     EGetGeometry(m->items[i]->icon_win, NULL, NULL, NULL, &iw, &ih,
			  NULL, NULL);
	     ImageclassApply(m->items[i]->icon_iclass, m->items[i]->icon_win,
			     iw, ih, 0, 0, STATE_NORMAL, ST_MENU_ITEM);
	  }
	if (x + maxw > mmw)
	   mmw = x + maxw;
	if (y + maxh > mmh)
	   mmh = y + maxh;
	if ((m->style->maxx) || (nmaxy))
	  {
	     if (nmaxy)
	       {
		  y += maxh;
		  r++;
		  if (r >= nmaxy)
		    {
		       r = 0;
		       x += maxw;
		       y = 0;
		    }
	       }
	     else
	       {
		  x += maxw;
		  r++;
		  if (r >= m->style->maxx)
		    {
		       r = 0;
		       y += maxh;
		       x = 0;
		    }
	       }
	  }
	else
	   y += maxh;
     }

   if ((m->style->bg_iclass) && (!m->style->use_item_bg))
     {
	mmw += pad->right;
	mmh += pad->bottom;
     }

   m->redraw = 1;
   m->w = mmw;
   m->h = mmh;
   EResizeWindow(m->win, mmw, mmh);
}

static void
MenuRedraw(Menu * m)
{
   int                 i, j, w, h;

   if (m->redraw)
     {
	for (i = 0; i < m->num; i++)
	  {
	     for (j = 0; j < 3; j++)
		FreePmapMask(&(m->items[i]->pmm[j]));

	  }
	m->redraw = 0;
     }

   if (!m->style->use_item_bg)
     {
	w = m->w;
	h = m->h;
	FreePmapMask(&m->pmm);
	ImageclassApplyCopy(m->style->bg_iclass, m->win, w, h, 0,
			    0, STATE_NORMAL, &m->pmm, 1, ST_MENU);
	ESetWindowBackgroundPixmap(m->win, m->pmm.pmap);
	EShapeCombineMask(m->win, ShapeBounding, 0, 0, m->pmm.mask, ShapeSet);
	EClearWindow(m->win);
	for (i = 0; i < m->num; i++)
	   MenuDrawItem(m, m->items[i], 0, -1);
     }
   else
     {
	for (i = 0; i < m->num; i++)
	   MenuDrawItem(m, m->items[i], 0, -1);
	EShapePropagate(m->win);
     }
}

static void
MenuDrawItem(Menu * m, MenuItem * mi, char shape, int state)
{
   PmapMask           *mi_pmm;

   if (state >= 0)
      mi->state = state;
   mi_pmm = &(mi->pmm[(int)(mi->state)]);

   if (!mi_pmm->pmap)
     {
	GC                  gc;
	int                 x, y, w, h;
	int                 item_type;
	ImageClass         *ic;

	EGetGeometry(mi->win, NULL, &x, &y, &w, &h, NULL, NULL);

	mi_pmm->type = 0;
	mi_pmm->pmap = ECreatePixmap(mi->win, w, h, 0);
	mi_pmm->mask = None;

	ic = (mi->child) ? m->style->sub_iclass : m->style->item_iclass;
	item_type = (mi->state != STATE_NORMAL) ? ST_MENU_ITEM : ST_MENU;

	if (!m->style->use_item_bg)
	  {
	     gc = EXCreateGC(m->pmm.pmap, 0, NULL);
	     XCopyArea(disp, m->pmm.pmap, mi_pmm->pmap, gc, x, y, w, h, 0, 0);
	     if ((mi->state != STATE_NORMAL) || (mi->child))
	       {
		  PmapMask            pmm;

		  ImageclassApplyCopy(ic, mi->win, w, h, 0, 0,
				      mi->state, &pmm, 1, item_type);
		  if (pmm.mask)
		    {
		       XSetClipMask(disp, gc, pmm.mask);
		       XSetClipOrigin(disp, gc, 0, 0);
		    }
		  XCopyArea(disp, pmm.pmap, mi_pmm->pmap, gc, 0, 0, w, h, 0, 0);
		  FreePmapMask(&pmm);
	       }
	     EXFreeGC(gc);
	  }
	else
	  {
	     ImageclassApplyCopy(ic, mi->win, w, h, 0, 0, mi->state,
				 mi_pmm, 1, item_type);
	  }

	if (mi->text)
	  {
	     TextDraw(m->style->tclass, mi->win, mi_pmm->pmap, 0, 0, mi->state,
		      _(mi->text), mi->text_x, mi->text_y, mi->text_w,
		      mi->text_h, 17,
		      TextclassGetJustification(m->style->tclass));
	  }
     }

   ESetWindowBackgroundPixmap(mi->win, mi_pmm->pmap);
   EShapeCombineMask(mi->win, ShapeBounding, 0, 0, mi_pmm->mask, ShapeSet);
   EClearWindow(mi->win);

   if ((shape) && (m->style->use_item_bg))
      EShapePropagate(m->win);
}

static void
MenuShowMasker(Menu * m __UNUSED__)
{
   EObj               *eo = Mode_menus.cover_win;

   if (!eo)
     {
	eo = EobjWindowCreate(EOBJ_TYPE_EVENT, 0, 0, VRoot.w, VRoot.h, 0,
			      "Masker");
	if (!eo)
	   return;

	EobjReparent(eo, EoObj(DesksGetCurrent()), 0, 0);
	EobjSetLayer(eo, 11);
	ESelectInput(eo->win, ButtonPressMask | ButtonReleaseMask |
		     EnterWindowMask | LeaveWindowMask);
	EventCallbackRegister(eo->win, 0, MenuMaskerHandleEvents, NULL);

	Mode_menus.cover_win = eo;
     }

   EobjMap(eo, 0);
}

static void
MenuHideMasker(void)
{
   EObj               *eo = Mode_menus.cover_win;

   if (!eo)
      return;

   EventCallbackUnregister(eo->win, 0, MenuMaskerHandleEvents, NULL);
   EobjWindowDestroy(eo);
   Mode_menus.cover_win = NULL;
}

static void
MenusDestroyLoaded(void)
{
   Menu               *m;
   int                 found_one;

   MenusHide();

   /* Free all menustyles first (gulp) */
   do
     {
	found_one = 0;
	ECORE_LIST_FOR_EACH(menu_list, m)
	{
	   if (m->internal)
	      continue;

	   MenuDestroy(m);
	   /* Destroying a menu may result in sub-menus being
	    * destroyed too, so we have to re-find all menus
	    * afterwards. Inefficient yes, but it works...
	    */
	   found_one = 1;
	   break;
	}
     }
   while (found_one);
}

static int
_MenuMatchName(const void *data, const void *match)
{
   const Menu         *m = (const Menu *)data;

   if ((m->name && !strcmp((const char *)match, m->name)) ||
       (m->alias && !strcmp((const char *)match, m->alias)))
      return 0;

   return 1;
}

Menu               *
MenuFind(const char *name)
{
   Menu               *m;

   m = (Menu *) ecore_list_find(menu_list, _MenuMatchName, name);
   if (m)
      return (m);

   /* Not in list - try if we can load internal */
   m = MenusCreateInternal(name, name, NULL, NULL);

   return m;
}

static void
MenusShowNamed(const char *name)
{
   Menu               *m;

   /* Hide any menus currently up */
   if (MenusActive())
      MenusHide();

   m = MenuFind(name);
   if (!m)
      return;

   if (!m->ewin)		/* Don't show if already shown */
      MenuShow(m, 0);
}

int
MenusActive(void)
{
   return Mode_menus.first != NULL;
}

static void
MenusHide(void)
{
   RemoveTimerEvent("SUBMENU_SHOW");

   MenuHide(Mode_menus.first);
   Mode_menus.first = NULL;
   MenuHideMasker();
   TooltipsEnable(1);
}

static void
MenusTouch(void)
{
   Menu               *m;

   ECORE_LIST_FOR_EACH(menu_list, m) m->redraw = 1;
}

/*
 * Menu event handlers
 */

static MenuItem    *
MenuFindNextItem(Menu * m, MenuItem * mi, int inc)
{
   int                 i;

   if (mi == NULL)
     {
	if (m->num > 0)
	   return m->items[0];
	else
	   return NULL;
     }

   for (i = 0; i < m->num; i++)
      if (m->items[i] == mi)
	{
	   i = (i + inc + m->num) % m->num;
	   return m->items[i];
	}

   return NULL;
}

static              KeySym
MenuKeyPressConversion(KeySym key)
{
   if (key == Conf.menus.key.left)
      return XK_Left;
   if (key == Conf.menus.key.right)
      return XK_Right;
   if (key == Conf.menus.key.up)
      return XK_Up;
   if (key == Conf.menus.key.down)
      return XK_Down;
   if (key == Conf.menus.key.escape)
      return XK_Escape;
   if (key == Conf.menus.key.ret)
      return XK_Return;

   /* The key does not correspond to any set, use the default behavior 
    * associated to the key */
   return key;
}

static void
MenuEventKeyPress(Menu * m, XEvent * ev)
{
   KeySym              key;
   MenuItem           *mi;
   EWin               *ewin;

   mi = NULL;
   if (Mode_menus.active)
     {
	m = Mode_menus.active;
	mi = m->sel_item;
     }

   /* NB! m != NULL */

   key = XLookupKeysym(&ev->xkey, 0);
   switch (MenuKeyPressConversion(key))
     {
     case XK_Escape:
	MenusHide();
	break;

     case XK_Down:
      check_next:
	mi = MenuFindNextItem(m, mi, 1);
	goto check_activate;

     case XK_Up:
	mi = MenuFindNextItem(m, mi, -1);
	goto check_activate;

     case XK_Left:
	m = m->parent;
	if (!m)
	   break;
	mi = m->sel_item;
	goto check_activate;

     case XK_Right:
	if (mi == NULL)
	   goto check_next;
	m = mi->child;
	if (!m || m->num <= 0)
	   break;
	ewin = m->ewin;
	if (ewin == NULL || !EwinIsMapped(ewin))
	   break;
	mi = MenuFindItemByChild(m, m->child);
	goto check_activate;

      check_activate:
	if (!mi)
	   break;
	MenuActivateItem(m, mi);
	break;

     case XK_Return:
	if (!mi)
	   break;
	if (!mi->params)
	   break;
	EFuncDefer(Mode_menus.context_ewin, mi->params);
	MenusHide();
	EobjsRepaint();
	break;
     }
}

static void
MenuItemEventMouseDown(MenuItem * mi, XEvent * ev __UNUSED__)
{
   Menu               *m;

   Mode_menus.just_shown = 0;

   m = mi->menu;
   MenuDrawItem(m, mi, 1, STATE_CLICKED);
}

static void
MenuItemEventMouseUp(MenuItem * mi, XEvent * ev __UNUSED__)
{
   Menu               *m;

   if (Mode_menus.just_shown)
     {
	Mode_menus.just_shown = 0;
	if (ev->xbutton.time - Mode.events.last_btime < 250)
	   return;
     }

   m = mi->menu;

   if ((m) && (mi->state))
     {
	MenuDrawItem(m, mi, 1, STATE_HILITED);
	if ((mi->params) /* && (!Mode_menus.just_shown) */ )
	  {
	     EFuncDefer(Mode_menus.context_ewin, mi->params);
	     MenusHide();
	     EobjsRepaint();
	  }
     }
}

#if 0				/* Was in HandleMotion() */
void
MenusHandleMotion(void)
{
#define SCROLL_RATIO 2/3
   if ((MenusActive() || (Mode_menus.clicked)))
     {
	int                 i, offx = 0, offy = 0, xdist = 0, ydist = 0;
	EWin               *ewin;
	EWin               *menus[256];
	int                 fx[256];
	int                 fy[256];
	int                 tx[256];
	int                 ty[256];
	static int          menu_scroll_dist = 4;
	int                 my_width, my_height, x_org, y_org, head_num = 0;

	head_num =
	   ScreenGetGeometry(Mode.events.x, Mode.events.y, &x_org, &y_org,
			     &my_width, &my_height);

	if (Mode.events.x > ((x_org + my_width) - (menu_scroll_dist + 1)))
	  {
	     xdist = -(menu_scroll_dist + (Mode.events.x - (x_org + my_width)));
	  }
	else if (Mode.events.x < (menu_scroll_dist + x_org))
	  {
	     xdist = x_org + menu_scroll_dist - (Mode.events.x);
	  }

	if (Mode.events.y > (VRoot.h - (menu_scroll_dist + 1)))
	  {
	     ydist =
		-(menu_scroll_dist + (Mode.events.y - (y_org + my_height)));
	  }
	else if (Mode.events.y < (menu_scroll_dist + y_org))
	  {
	     ydist = y_org + menu_scroll_dist - (Mode.events.y);
	  }

	/* That's a hack to avoid unwanted events:
	 * If the user entered the border area, he has to
	 * leave it first, before he can scroll menus again ...
	 */
	if ((xdist != 0) || (ydist != 0) || Mode.doingslide)
	  {
	     /* -10 has no meaning, only makes sure that the if's */
	     /* above can't be fulfilled ... */
	     menu_scroll_dist = -10;
	  }
	else
	  {
	     menu_scroll_dist = 13;
	  }

	if (Mode_menus.current_depth > 0)
	  {
	     int                 x1, y1, x2, y2;

	     x1 = x_org + my_width;
	     x2 = x_org - 1;
	     y1 = y_org + my_height;
	     y2 = y_org - 1;
	     /* work out the minimum and maximum extents of our */
	     /* currently active menus */
	     for (i = 0; i < Mode_menus.current_depth; i++)
	       {
		  if (Mode_menus.list[i])
		    {
		       ewin = Mode_menus.list[i]->ewin;
		       if (ewin)
			 {
			    if (EoGetX(ewin) < x1)
			       x1 = EoGetX(ewin);
			    if (EoGetY(ewin) < y1)
			       y1 = EoGetY(ewin);
			    if ((EoGetX(ewin) + EoGetW(ewin) - 1) > x2)
			       x2 = EoGetX(ewin) + EoGetW(ewin) - 1;
			    if ((EoGetY(ewin) + EoGetH(ewin) - 1) > y2)
			       y2 = EoGetY(ewin) + EoGetH(ewin) - 1;
			 }
		    }
	       }

	     if (xdist < 0)
	       {
		  offx = (x_org + my_width) - x2;
	       }
	     else if (xdist > 0)
	       {
		  offx = x_org - x1;
	       }
	     if (ydist < 0)
	       {
		  offy = (y_org + my_height) - y2;
	       }
	     else if (ydist > 0)
	       {
		  offy = y_org - y1;
	       }

	     if ((xdist < 0) && (offx <= 0))
		xdist = offx;
	     if ((xdist > 0) && (offx >= 0))
		xdist = offx;
	     if ((ydist < 0) && (offy <= 0))
		ydist = offy;
	     if ((ydist > 0) && (offy >= 0))
		ydist = offy;

	     /* only if any active menus are partially off screen then scroll */
	     if ((((xdist > 0) && (x1 < x_org))
		  || ((xdist < 0) && (x2 >= (x_org + my_width))))
		 || (((ydist > 0) && (y1 < y_org))
		     || ((ydist < 0) && (y2 >= (y_org + my_height)))))
	       {
		  /* If we would scroll too far, limit scrolling to 2/3s of screen */
		  if (ydist < -my_width)
		     ydist = -my_width * SCROLL_RATIO;
		  if (ydist > my_width)
		     ydist = my_width * SCROLL_RATIO;

		  if (xdist < -my_height)
		     xdist = -my_height * SCROLL_RATIO;
		  if (xdist > my_height)
		     xdist = my_height * SCROLL_RATIO;

		  if (Mode_menus.current_depth)
		    {
#ifdef HAVE_XINERAMA
		       ewin = Mode_menus.list[0]->ewin;
		       if (ewin->head == head_num)
			 {
#endif
			    for (i = 0; i < Mode_menus.current_depth; i++)
			      {
				 menus[i] = NULL;
				 if (Mode_menus.list[i])
				   {
				      ewin = Mode_menus.list[i]->ewin;
				      if (ewin)
					{
					   menus[i] = ewin;
					   fx[i] = EoGetX(ewin);
					   fy[i] = EoGetY(ewin);
					   tx[i] = EoGetX(ewin) + xdist;
					   ty[i] = EoGetY(ewin) + ydist;
					}
				   }
			      }
			    SlideEwinsTo(menus, fx, fy, tx, ty,
					 Mode_menus.current_depth,
					 Conf.shadespeed);
			    if (((xdist != 0) || (ydist != 0))
				&& (Conf.menus.warp))
			       EXWarpPointer(None, xdist, ydist);
#ifdef HAVE_XINERAMA
			 }
#endif
		    }
	       }
	  }
     }
}
#endif

struct _mdata
{
   Menu               *m;
   MenuItem           *mi;
};

static void
MenusSetEvents(int on)
{
   int                 i;
   Menu               *m;
   long                event_mask;

   event_mask = (on) ? MENU_ITEM_EVENT_MASK : 0;

   for (m = Mode_menus.first; m; m = m->child)
     {
	for (i = 0; i < m->num; i++)
	   ESelectInput(m->items[i]->win, event_mask);
     }
}

static void
MenuSelectItem(Menu * m, MenuItem * mi, int focus)
{
   if (mi && focus)
     {
	if (Mode_menus.active != m)
	  {
	     Mode_menus.active = m;
	     GrabKeyboardRelease();
	     GrabKeyboardSet(m->win);
	  }
     }

   if (mi == m->sel_item)
      return;

   if (m->sel_item)
      MenuDrawItem(m, m->sel_item, 1, STATE_NORMAL);

   if (mi)
      MenuDrawItem(m, mi, 1, STATE_HILITED);

   m->sel_item = mi;
}

static void
MenuSelectItemByChild(Menu * m, Menu * mc)
{
   MenuItem           *mi;

   mi = MenuFindItemByChild(m, mc);
   if (!mi)
      return;

   MenuSelectItem(m, mi, 0);
}

static void
SubmenuShowTimeout(int val __UNUSED__, void *dat)
{
   int                 mx, my, my2, xo, yo, mw;
   Menu               *m;
   MenuItem           *mi;
   EWin               *ewin2, *ewin;
   struct _mdata      *data;
   int                 bl1, br1, bt1, bb1;
   int                 bl2, br2, bt2, bb2;

   data = (struct _mdata *)dat;
   if (!data)
      return;
   if (!data->m)
      return;

   m = data->m;
   ewin = m->ewin;
   if (!ewin || !EwinFindByPtr(ewin))
      return;
   if (!EoIsShown(ewin))
      return;

   mi = data->mi;
   if (!mi)
      return;

   if (mi->child != m->child)
      MenuHide(m->child);
   m->child = mi->child;
   if (!mi->child)
      return;

   mi->child->parent = m;
   MenuShow(mi->child, 1);
   ewin2 = mi->child->ewin;
   if (!ewin2 || !EwinFindByPtr(ewin2))
      return;

   EGetGeometry(mi->win, NULL, &mx, &my, &mw, NULL, NULL, NULL);
   my2 = 0;
   if (mi->child->num > 0 && mi->child->items[0])
      EGetGeometry(mi->child->items[0]->win, NULL, NULL, &my2, NULL, NULL, NULL,
		   NULL);

   /* Sub-menu offsets relative to parent menu origin */
   EwinBorderGetSize(ewin, &bl1, &br1, &bt1, &bb1);
   EwinBorderGetSize(ewin2, &bl2, &br2, &bt2, &bb2);
   xo = bl1 + mx + mw;
   yo = bt1 + my - (bt2 + my2);

   if (Conf.menus.onscreen)
     {
	EWin               *menus[256], *etmp;
	int                 fx[256], fy[256], tx[256], ty[256];
	int                 i, ww, hh;
	int                 xdist = 0, ydist = 0;

	/* Size of new submenu (may be shaded atm.) */
	ww = mi->child->w + bl2 + br2;
	hh = mi->child->h + bt2 + bb2;

	if (EoGetX(ewin) + xo + ww > VRoot.w)
	   xdist = VRoot.w - (EoGetX(ewin) + xo + ww);
	if (EoGetY(ewin) + yo + hh > VRoot.h)
	   ydist = VRoot.h - (EoGetY(ewin) + yo + hh);

	if ((xdist != 0) || (ydist != 0))
	  {
	     i = 0;
	     for (m = Mode_menus.first; m; m = m->child)
	       {
		  etmp = m->ewin;
		  if (!etmp || etmp == ewin2)
		     break;
		  menus[i] = etmp;
		  fx[i] = EoGetX(etmp);
		  fy[i] = EoGetY(etmp);
		  tx[i] = EoGetX(etmp) + xdist;
		  ty[i] = EoGetY(etmp) + ydist;
		  i++;
	       }

	     /* Disable menu item events while sliding */
	     MenusSetEvents(0);
	     SlideEwinsTo(menus, fx, fy, tx, ty, i, Conf.shading.speed);
	     MenusSetEvents(1);

	     if (Conf.menus.warp)
		EXWarpPointer(WinGetXwin(mi->win), mi->text_w / 2,
			      mi->text_h / 2);
	  }
     }

   Mode.move.check = 0;		/* Bypass on-screen checks */
   EwinMove(ewin2, EoGetX(ewin) + xo, EoGetY(ewin) + yo);
   Mode.move.check = 1;
   EwinOpFloatAt(ewin2, OPSRC_NA, EoGetX(ewin2), EoGetY(ewin2));
   EwinRaise(ewin2);
   EwinShow(ewin2);

   if (Conf.menus.animate)
      EwinUnShade(ewin2);
}

static void
MenuActivateItem(Menu * m, MenuItem * mi)
{
   static struct _mdata mdata;
   MenuItem           *mi_prev;

   mi_prev = m->sel_item;

   if (m->child)
      MenuSelectItem(m->child, NULL, 0);
   MenuSelectItem(m, mi, 1);
   if (m->parent)
      MenuSelectItemByChild(m->parent, m);

   if (mi == mi_prev)
      return;

   if (mi && !mi->child && mi_prev && !mi_prev->child)
      return;

   RemoveTimerEvent("SUBMENU_SHOW");

   if ((mi && mi->child && !mi->child->shown) || (mi && mi->child != m->child))
     {
	mdata.m = m;
	mdata.mi = mi;
	DoIn("SUBMENU_SHOW", 0.2, SubmenuShowTimeout, 0, &mdata);
     }
}

static void
MenuItemEventMouseIn(MenuItem * mi, XEvent * ev)
{
   if (ev->xcrossing.detail == NotifyInferior)
      return;

   MenuActivateItem(mi->menu, mi);
}

static void
MenuItemEventMouseOut(MenuItem * mi, XEvent * ev)
{
   if (ev->xcrossing.detail == NotifyInferior)
      return;

   if (!mi->child)
      MenuSelectItem(mi->menu, NULL, 0);
}

static void
MenuHandleEvents(Win win __UNUSED__, XEvent * ev, void *prm)
{
   Menu               *m = (Menu *) prm;

#if DEBUG_MENU_EVENTS
   Eprintf("MenuHandleEvents %d\n", ev->type);
#endif
   switch (ev->type)
     {
     case KeyPress:
	MenuEventKeyPress(m, ev);
	break;
     case ButtonRelease:
	break;
     case EnterNotify:
	GrabKeyboardSet(m->win);
	break;
     }
}

static void
MenuItemHandleEvents(Win win __UNUSED__, XEvent * ev, void *prm)
{
   MenuItem           *mi = (MenuItem *) prm;

#if DEBUG_MENU_EVENTS
   Eprintf("MenuItemHandleEvents %d\n", ev->type);
#endif
   switch (ev->type)
     {
     case ButtonPress:
	MenuItemEventMouseDown(mi, ev);
	break;
     case ButtonRelease:
	MenuItemEventMouseUp(mi, ev);
	break;
     case EnterNotify:
	MenuItemEventMouseIn(mi, ev);
	break;
     case LeaveNotify:
	MenuItemEventMouseOut(mi, ev);
	break;
     }
}

static void
MenuMaskerHandleEvents(Win win __UNUSED__, XEvent * ev, void *prm __UNUSED__)
{
#if DEBUG_MENU_EVENTS
   Eprintf("MenuMaskerHandleEvents %d\n", ev->type);
#endif
   switch (ev->type)
     {
     case ButtonRelease:
	MenusHide();
	break;
     }
}

/*
 * Configuration load/save
 */
#include "conf.h"

int
MenuStyleConfigLoad(FILE * ConfigFile)
{
   int                 err = 0;
   char                s[FILEPATH_LEN_MAX];
   char                s2[FILEPATH_LEN_MAX];
   int                 i1;
   MenuStyle          *ms = NULL;
   int                 fields;

   while (GetLine(s, sizeof(s), ConfigFile))
     {
	s2[0] = 0;
	i1 = CONFIG_INVALID;
	fields = sscanf(s, "%i %4000s", &i1, s2);

	if (fields < 1)
	  {
	     i1 = CONFIG_INVALID;
	  }
	else if (i1 == CONFIG_CLOSE)
	  {
	     if (fields != 1)
		Alert(_("CONFIG: ignoring extra data in \"%s\"\n"), s);
	  }
	else if (i1 != CONFIG_INVALID)
	  {
	     if (fields != 2)
		Alert(_("CONFIG: missing required data in \"%s\"\n"), s);
	  }

	switch (i1)
	  {
	  case CONFIG_CLOSE:
	     goto done;
	  case CONFIG_CLASSNAME:
	     ms = MenuStyleCreate(s2);
	     break;
	  case CONFIG_TEXT:
	     ms->tclass = TextclassFind(s2, 1);
	     if (ms->tclass)
		TextclassIncRefcount(ms->tclass);
	     break;
	  case MENU_BG_ICLASS:
	     ms->bg_iclass = ImageclassFind(s2, 0);
	     if (ms->bg_iclass)
		ImageclassIncRefcount(ms->bg_iclass);
	     break;
	  case MENU_ITEM_ICLASS:
	     ms->item_iclass = ImageclassFind(s2, 0);
	     if (ms->item_iclass)
		ImageclassIncRefcount(ms->item_iclass);
	     break;
	  case MENU_SUBMENU_ICLASS:
	     ms->sub_iclass = ImageclassFind(s2, 0);
	     if (ms->sub_iclass)
		ImageclassIncRefcount(ms->sub_iclass);
	     break;
	  case MENU_USE_ITEM_BACKGROUND:
	     ms->use_item_bg = atoi(s2);
	     if (ms->use_item_bg)
	       {
		  if (ms->bg_iclass)
		    {
		       ImageclassDecRefcount(ms->bg_iclass);
		       ms->bg_iclass = NULL;
		    }
	       }
	     break;
	  case MENU_MAX_COLUMNS:
	     ms->maxx = atoi(s2);
	     break;
	  case MENU_MAX_ROWS:
	     ms->maxy = atoi(s2);
	     break;
	  case CONFIG_BORDER:
	     {
		/* FIXME!!!  I don't think this file is loaded in the
		 * right order!
		 */
		Border             *b;

		if (ms->border_name)
		   Efree(ms->border_name);

		ms->border_name = Estrdup(s2);

		b = BorderFind(ms->border_name);
		if (b)
		   BorderIncRefcount(b);
	     }
	     break;
	  default:
	     break;
	  }
     }
   err = -1;

 done:
   return err;
}

int
MenuConfigLoad(FILE * fs)
{
   int                 err = 0;
   char                s[FILEPATH_LEN_MAX];
   char                s2[FILEPATH_LEN_MAX];
   char                s3[FILEPATH_LEN_MAX];
   char                s4[FILEPATH_LEN_MAX];
   char                s5[FILEPATH_LEN_MAX];
   char               *txt = NULL;
   const char         *params;
   int                 i1, i2;
   Menu               *m = NULL, *mm;
   MenuItem           *mi;
   MenuStyle          *ms;
   ImageClass         *ic = NULL;
   int                 fields, len2, len;

   while (GetLine(s, sizeof(s), fs))
     {
	s2[0] = 0;
	i1 = CONFIG_INVALID;
	len = 0;
	fields = sscanf(s, "%i %n%4000s %n", &i1, &len2, s2, &len);

	if (fields < 1)
	  {
	     i1 = CONFIG_INVALID;
	  }
	else if (i1 == CONFIG_CLOSE)
	  {
	     if (fields != 1)
		Alert(_("CONFIG: ignoring extra data in \"%s\"\n"), s);
	  }
	else if (i1 != CONFIG_INVALID)
	  {
	     if (fields != 2)
	       {
		  Alert(_("CONFIG: missing required data in \"%s\"\n"), s);
		  continue;
	       }
	  }

	switch (i1)
	  {
	  case CONFIG_MENU:
	     err = -1;
	     i2 = atoi(s2);
	     if (i2 != CONFIG_OPEN)
		goto done;
	     m = NULL;
	     ic = NULL;
	     _EFREE(txt);
	     break;
	  case CONFIG_CLOSE:
	     err = 0;
	     break;

	  case MENU_PREBUILT:
	     sscanf(s, "%i %4000s %4000s %4000s %4000s", &i1, s2, s3, s4, s5);
	     m = MenusCreateInternal(s4, s2, s3, s5);
	     break;
	  case CONFIG_CLASSNAME:
	     if (!m)
		m = MenuCreate(s2, NULL, NULL, NULL);
	     else
		MenuSetName(m, s2);
	     break;
	  case MENU_USE_STYLE:
	     ms = MenuStyleFind(s2);
	     if (ms)
		MenuSetStyle(m, ms);
	     break;
	  case MENU_TITLE:
	     if (m)
		MenuSetTitle(m, s + len2);
	     break;
	  case MENU_ITEM:
#if 0				/* FIXME - Why ? */
	     if ((txt) || (ic))
	       {
		  mi = MenuItemCreate(txt, ic, NULL, NULL);
		  MenuAddItem(m, mi);
	       }
#endif
	     ic = NULL;
	     if (strcmp("NULL", s2))
		ic = ImageclassFind(s2, 0);
	     params = s + len;
	     _EFDUP(txt, params);
	     break;
	  case MENU_ACTION:
	     if ((txt) || (ic))
	       {
		  char                ok = 1;

		  /* if its an execute line then check to see if the exec is 
		   * on your system before adding the menu entry */
		  if (!strcmp(s2, "exec"))
		    {
		       sscanf(s + len, "%1000s", s3);
		       ok = path_canexec(s3);
		    }
		  if (ok)
		    {
		       params = s + len2;
		       mi = MenuItemCreate(txt, ic, params, NULL);
		       MenuAddItem(m, mi);
		    }
		  ic = NULL;
		  _EFREE(txt);
	       }
	     break;
	  case MENU_SUBMENU:
	     len2 = 0;
	     sscanf(s + len, "%4000s %n", s3, &len2);
	     ic = NULL;
	     if (strcmp("NULL", s3))
		ic = ImageclassFind(s3, 0);
	     mm = MenuFind(s2);
#if 0				/* FIXME - Remove? */
	     /* if submenu empty - dont put it in - only if menu found */
	     if (MenuIsEmpty(mm))
		break;
#endif
	     mi = MenuItemCreate(s + len + len2, ic, NULL, mm);
	     MenuAddItem(m, mi);
	     break;
	  default:
	     break;
	  }
     }

 done:
   if (err)
      ConfigAlertLoad("Menu");
   _EFREE(txt);

   return err;
}

static void
MenusTimeout(int val __UNUSED__, void *data __UNUSED__)
{
   Menu               *m;
   time_t              ts;

   /* Unload contents if loadable and no access in > 5 min */
   ts = time(0);
   ECORE_LIST_FOR_EACH(menu_list, m)
   {
      if (!m->loader || m->shown || m->num == 0 || ts - m->last_access < 300)
	 continue;

      MenuEmpty(m, 0);
      m->last_change = 0;
   }

   DoIn("MenusCheck", 300.0, MenusTimeout, 0, NULL);
}

/*
 * Menus Module
 */

static void
MenusSighan(int sig, void *prm __UNUSED__)
{
   switch (sig)
     {
     case ESIGNAL_CONFIGURE:
	ConfigFileLoad("menus.cfg", NULL, MenuConfigLoad, 1);
	break;

     case ESIGNAL_START:
	DoIn("MenusCheck", 300.0, MenusTimeout, 0, NULL);
	break;

     case ESIGNAL_AREA_SWITCH_START:
     case ESIGNAL_DESK_SWITCH_START:
	MenusHide();
	break;

     case ESIGNAL_EWIN_UNMAP:
	if ((EWin *) prm == Mode_menus.context_ewin)
	   MenusHide();
	break;

     case ESIGNAL_THEME_TRANS_CHANGE:
	MenusTouch();
	break;
     }
}

/*
 * Configuration dialog
 */

static char         tmp_warpmenus;
static char         tmp_animated_menus;
static char         tmp_menusonscreen;

static void
CB_ConfigureMenus(Dialog * d __UNUSED__, int val, void *data __UNUSED__)
{
   if (val < 2)
     {
	Conf.menus.warp = tmp_warpmenus;
	Conf.menus.animate = tmp_animated_menus;
	Conf.menus.onscreen = tmp_menusonscreen;
     }
   autosave();
}

static void
_DlgFillMenus(Dialog * d __UNUSED__, DItem * table, void *data __UNUSED__)
{
   DItem              *di;

   tmp_warpmenus = Conf.menus.warp;
   tmp_animated_menus = Conf.menus.animate;
   tmp_menusonscreen = Conf.menus.onscreen;

   DialogItemTableSetOptions(table, 3, 0, 0, 0);

   di = DialogAddItem(table, DITEM_CHECKBUTTON);
   DialogItemSetColSpan(di, 3);
   DialogItemSetText(di, _("Animated display of menus"));
   DialogItemCheckButtonSetPtr(di, &tmp_animated_menus);

   di = DialogAddItem(table, DITEM_CHECKBUTTON);
   DialogItemSetColSpan(di, 3);
   DialogItemSetText(di, _("Always pop up menus on screen"));
   DialogItemCheckButtonSetPtr(di, &tmp_menusonscreen);

   di = DialogAddItem(table, DITEM_CHECKBUTTON);
   DialogItemSetColSpan(di, 3);
   DialogItemSetText(di, _("Warp pointer after moving menus"));
   DialogItemCheckButtonSetPtr(di, &tmp_warpmenus);
}

const DialogDef     DlgMenus = {
   "CONFIGURE_MENUS",
   N_("Menus"),
   N_("Menu Settings"),
   "SOUND_SETTINGS_MENUS",
   "pix/place.png",
   N_("Enlightenment Menu\n" "Settings Dialog\n"),
   _DlgFillMenus,
   DLG_OAC, CB_ConfigureMenus,
};

static void
MenusIpc(const char *params, Client * c __UNUSED__)
{
   const char         *p;
   char                cmd[128], prm[4096];
   int                 len;
   Menu               *m;

   cmd[0] = prm[0] = '\0';
   p = params;
   if (p)
     {
	len = 0;
	sscanf(p, "%100s %4000s %n", cmd, prm, &len);
	p += len;
     }

   if (!p || cmd[0] == '?')
     {
	IpcPrintf("Menus - active=%d\n", MenusActive());
     }
   else if (!strncmp(cmd, "cfg", 2))
     {
	DialogShowSimple(&DlgMenus, NULL);
     }
   else if (!strncmp(cmd, "list", 2))
     {
	ECORE_LIST_FOR_EACH(menu_list, m) IpcPrintf("%s\n", m->name);
     }
   else if (!strncmp(cmd, "reload", 2))
     {
	MenusDestroyLoaded();
	ConfigFileLoad("menus.cfg", NULL, MenuConfigLoad, 1);
     }
   else if (!strncmp(cmd, "show", 2))
     {
	if (strcmp(prm, "named"))
	   p = prm;
	SoundPlay("SOUND_MENU_SHOW");
	MenusShowNamed(p);
     }
}

static const IpcItem MenusIpcArray[] = {
   {
    MenusIpc,
    "menus", "mnu",
    "Menu functions",
    "  menus list               Show existing menus\n"
    "  menus reload             Reload menus.cfg without restarting\n"
    "  menus show <name>        Show named menu\n"}
   ,
};
#define N_IPC_FUNCS (sizeof(MenusIpcArray)/sizeof(IpcItem))

static const CfgItem MenusCfgItems[] = {
   CFG_ITEM_BOOL(Conf.menus, animate, 0),
   CFG_ITEM_BOOL(Conf.menus, onscreen, 1),
   CFG_ITEM_BOOL(Conf.menus, warp, 1),
   CFG_ITEM_BOOL(Conf.menus, show_icons, 1),
   CFG_ITEM_INT(Conf.menus, icon_size, 16),
   CFG_ITEM_HEX(Conf.menus, key.left, XK_Left),
   CFG_ITEM_HEX(Conf.menus, key.right, XK_Right),
   CFG_ITEM_HEX(Conf.menus, key.up, XK_Up),
   CFG_ITEM_HEX(Conf.menus, key.down, XK_Down),
   CFG_ITEM_HEX(Conf.menus, key.escape, XK_Escape),
   CFG_ITEM_HEX(Conf.menus, key.ret, XK_Return),
};
#define N_CFG_ITEMS (sizeof(MenusCfgItems)/sizeof(CfgItem))

/*
 * Module descriptor
 */
extern const EModule ModMenus;
const EModule       ModMenus = {
   "menus", "menu",
   MenusSighan,
   {N_IPC_FUNCS, MenusIpcArray},
   {N_CFG_ITEMS, MenusCfgItems}
};
