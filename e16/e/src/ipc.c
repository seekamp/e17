#include "E.h"
#include "timestamp.h"

/* IPC array member function declarations */

/* this is needed for the IPC array below to not give us any warnings
 * during compiletime.  Since we don't use these anywhere else and I
 * don't expect us to ever, we're not going to bother putting them in
 * E.h
 * --Mandrake
 */

void                IPC_Help(char *params, Client * c);
void                IPC_Version(char *params, Client * c);
void                IPC_Copyright(char *params, Client * c);
void                IPC_AutoSave(char *params, Client * c);
void                IPC_DefaultTheme(char *params, Client * c);
void                IPC_Restart(char *params, Client * c);
void                IPC_RestartWM(char *params, Client * c);
void                IPC_RestartTheme(char *params, Client * c);
void                IPC_Exit(char *params, Client * c);
void                IPC_ForceSave(char *params, Client * c);
void                IPC_SMFile(char *params, Client * c);
void                IPC_ListThemes(char *params, Client * c);
void                IPC_GotoDesktop(char *params, Client * c);
void                IPC_ShowIcons(char *params, Client * c);
void                IPC_FocusMode(char *params, Client * c);
void                IPC_AdvancedFocus(char *params, Client * c);
void                IPC_NumDesks(char *params, Client * c);
void                IPC_NumAreas(char *params, Client * c);
void                IPC_WinOps(char *params, Client * c);
void                IPC_WinList(char *params, Client * c);
void                IPC_GotoArea(char *params, Client * c);
void                IPC_ButtonShow(char *params, Client * c);
void                IPC_ActiveNetwork(char *params, Client * c);
void                IPC_FX(char *params, Client * c);
void                IPC_MoveMode(char *params, Client * c);
void                IPC_ResizeMode(char *params, Client * c);
void                IPC_Pager(char *params, Client * c);
void                IPC_InternalList(char *params, Client * c);
void                IPC_SetFocus(char *params, Client * c);
void                IPC_DialogOK(char *params, Client * c);
void                IPC_SoundClass(char *params, Client * c);
void                IPC_ImageClass(char *params, Client * c);
void                IPC_ActionClass(char *params, Client * c);
void                IPC_ColorModifierClass(char *params, Client * c);
void                IPC_TextClass(char *params, Client * c);
void                IPC_Border(char *params, Client * c);
void                IPC_Button(char *params, Client * c);
void                IPC_Background(char *params, Client * c);
void                IPC_Cursor(char *params, Client * c);
void                IPC_PlaySoundClass(char *params, Client * c);
void                IPC_ListClassMembers(char *params, Client * c);
void                IPC_GeneralInfo(char *params, Client * c);
void                IPC_Modules(char *params, Client * c);
void                IPC_DockPosition(char *params, Client * c);

/* the IPC Array */

/* the format of an IPC member of the IPC array is as follows:
 * {
 *    NameOfMyFunction,
 *    "command_name",
 *    "quick-help explanation",
 *    "extended help data"
 *    "may go on for several lines, be sure\n"
 *    "to add line feeds when you need them and to \"quote\"\n"
 *    "properly"
 * }
 *
 * when you add a function into this array, make sure you also add it into
 * the declarations above and also put the function in this file.  PLEASE
 * if you add a new function in, add help to it also.  since my end goal
 * is going to be to have this whole IPC usable by an end-user or to your
 * scripter, it should be easy to learn to use without having to crack
 * open the source code.
 * --Mandrake
 */

IPCStruct           IPCArray[] =
{
   {
      IPC_Help,
      "help",
      "gives you this help screen",
      "Additional parameters will retreive help on many topics - "
      "\"help <command>\".\nuse \"help all\" for a list of commands."
   },
   {
      IPC_Version,
      "version",
      "displays the current version of Enlightenment running",
      NULL
   },
   {
      IPC_Copyright,
      "copyright",
      "displays copyright information for Enlightenment",
      NULL
   },
   {
      IPC_AutoSave,
      "autosave",
      "toggle the Automatic Saving Feature",
      "Use \"autosave ?\" to list the current status\n"
      "use \"autosave on\" or \"autosave off\" to toggle the status"
   },
   {
      IPC_DefaultTheme,
      "default_theme",
      "toggle the default theme",
      "Use \"default_theme ?\" to get the current default theme\n"
      "use \"default_theme /path/to/theme\"\n"
      "you can retrieve a list of available themes from the "
      "\"list_themes\" command"
   },
   {
      IPC_Restart,
      "restart",
      "Restart Enlightenment",
      NULL
   },
   {
      IPC_RestartWM,
      "restart_wm",
      "Restart another window manager",
      "Use \"restart_wm <wmname>\" to start another window manager.\n"
      "Example: \"restart_wm fvwm\""
   },
   {
      IPC_RestartTheme,
      "restart_theme",
      "Restart with another theme",
      "Use \"restart_theme <themename>\" to restart enlightenment "
      "with another theme\nExample: \"restart_theme icE\""
   },
   {
      IPC_Exit,
      "exit",
      "Exit Enlightenment",
      NULL
   },
   {
      IPC_ForceSave,
      "save_config",
      "Force Enlightenment to save settings now",
      NULL
   },
   {
      IPC_SMFile,
      "sm_file",
      "Change the default prefix used for session saves",
      "Average users are encouraged not to touch this setting.\n"
      "Use \"sm_file ?\" to retreive the current session management "
      "file prefix\nUse \"sm_file /path/to/prefix/filenameprefix\" "
      "to change."
   },
   {
      IPC_ListThemes,
      "list_themes",
      "List currently available themes",
      NULL
   },
   {
      IPC_GotoDesktop,
      "goto_desktop",
      "Change currently active destkop",
      "Use \"goto_desktop num\" to go to a specific desktop.\n"
      "Use \"goto_desktop next\" and \"goto_desktop prev\" to go to "
      "the next and\n     previous desktop\n"
      "Use \"goto_desktop ?\" to find out what desktop you are "
      "currently on"
   },
   {
      IPC_GotoArea,
      "goto_area",
      "Change currently active area",
      "Use \"goto_area <horiz> <vert>\" to go to a specific desktop.\n"
      "Use \"goto_desktop next <vert/horiz>\" and \"goto_desktop "
      "prev <vert/horiz>\" to go to the next and\n     "
      "previous areas\nUse \"goto_area ?\" to find out what area "
      "you are currently on"
   },
   {
      IPC_ShowIcons,
      "show_icons",
      "Toggle the display of icons on the desktop",
      "Use \"show_icons on\" and \"show_icons off\" to change this setting\n"
      "Use \"show_icons ?\" to retrieve the current setting"
   },
   {
      IPC_FocusMode,
      "focus_mode",
      "Change the current focus mode setting",
      "Use \"focus_mode <mode>\" to change the focus mode.\n"
      "Use \"focus_mode ?\" to retrieve the current setting\n"
      "Focus Types:\n"
      "click: This is the traditional click-to-focus mode.\n"
      "clicknograb: This is a similar focus mode, but without the "
      "grabbing of the click\n    "
      "(you cannot click anywhere in a window to focus it)\n"
      "pointer: The focus will follow the mouse pointer\n"
      "sloppy: in sloppy-focus, the focus follows the mouse, "
      "but when over\n    "
      "the desktop background the last window does not lose the focus"
   },
   {
      IPC_AdvancedFocus,
      "advanced_focus",
      "Toggle Advanced Focus Settings",
      "use \"advanced_focus <option> <on/off/?>\" to change.\n"
      "the options you may set are:\n"
      "new_window_focus : all new windows get the keyboard focus\n"
      "new_popup_window_focus : all new transient windows get focus\n"
      "new_popup_of_owner_focus : transient windows from apps that have\n"
      "   focus already may receive focus\n"
      "raise_on_keyboard_focus_switch: Raise windows when switching focus\n"
      "   with the keyboard\n"
      "raise_after_keyboard_focus_switch: Raise windows after switching "
      "focus\n"
      "   with the keyboard\n"
      "pointer_to_keyboard_focus_window: Send the pointer to the focused\n"
      "   window when changing focus with the keyboard\n"
      "pointer_after_keyboard_focus_window: Send the pointer to the "
      "focused\n"
      "   window after changing focus with the keyboard\n"
      "transients_follow_leader: popup windows appear together with the\n"
      "   window that created them.\n"
      "switch_to_popup_location: switch to where a popup window appears\n"
      "focus_list: display and use focus list (requires XKB)\n"
      "manual_placement: place all new windows by hand"
   },
   {
      IPC_NumDesks,
      "num_desks",
      "Change the number of available desktops",
      "Use \"num_desks <num>\" to change the available number of desktops.\n"
      "Use \"num_desks ?\" to retrieve the current setting"
   },
   {
      IPC_NumAreas,
      "num_areas",
      "Change the size of the virtual desktop",
      "Use \"num_areas <width> <height>\" to change the size of the "
      "virtual desktop.\nExample: \"num_areas 2 2\" makes 2x2 "
      "virtual destkops\nUse \"num_areas ?\" to retrieve the "
      "current setting"
   },
   {
      IPC_WinOps,
      "win_op",
      "Change a property of a specific window",
      "Use \"win_op <windowid> <property> <value>\" to change the "
      "property of a window\nYou can use the \"window_list\" "
      "command to retreive a list of available windows\n"
      "You can use ? after most of these commands to receive the current\n"
      "status of that flag\n"
      "available win_op commands are:\n  win_op <windowid> close\n  "
      "win_op <windowid> annihilate\n  win_op <windowid> iconify\n  "
      "win_op <windowid> shade\n  win_op <windowid> stick\n  "
      "win_op <windowid> toggle_<width/height/size> "
      "<conservative/available>\n          (or none for absolute)\n  "
      "win_op <windowid> border <BORDERNAME>\n  win_op <windowid> "
      "desk <desktochangeto/next/prev>\n  win_op <windowid> "
      "area <x> <y>\n  win_op <windowid> <raise/lower>\n  "
      "win_op <windowid> <move/resize> <x> <y>\n  "
      "(you can use ? and ?? to retreive client and frame locations)\n  "
      "win_op <windowid> focus\n  "
      "win_op <windowid> title <title>"
   },
   {
      IPC_WinList,
      "window_list",
      "Get a list of currently open windows and their Titles",
      "the list will be returned in the following "
      "format - \"window_id : title\""
   },
   {
      IPC_ButtonShow,
      "button_show",
      "Show or Hide buttons on desktop",
      "use \"button_show <button/buttons/all_buttons_except/all> "
      "<BUTTON_STRING>\"\nexamples: \"button_show buttons all\" "
      "(removes all buttons and the dragbar)\n\"button_show\" "
      "(removes all buttons)\n \"button_show buttons CONFIG*\" "
      "(removes all buttons with CONFIG in the start)"
   },
   {
      IPC_ActiveNetwork,
      "active_network",
      "Enable or disable networking",
      "use \"active_network <on/off>\" to toggle\n"
      "use \"active_network ?\" to test status"
   },
   {
      IPC_FX,
      "fx",
      "Toggle various effects on/off",
      "Use \"fx <effect> <mode>\" to set the mode of a particular effect\n"
      "Use \"fx <effect> ?\" to get the current mode\n"
      "the following effects are available\n"
      "ripples <on/off> (ripples that act as a water effect on the screen)\n"
      "deskslide <on/off> (slide in desktops on desktop change)\n"
      "mapslide <on/off> (slide in new windows)\n"
      "raindrops <on/off> (raindrops will appear across your desktop)\n"
      "menu_animate <on/off> (toggles the animation of menus "
      "as they appear)\n"
    "animate_win_shading <on/off> (toggles the animation of window shading)\n"
      "window_shade_speed <#> (number of pixels/sec to shade a window)\n"
      "dragbar <on/off/left/right/top/bottom> (changes "
      "location of dragbar)\n"
      "tooltips <on/off/#> (changes state of tooltips and "
      "seconds till popup)\n"
      "autoraise <on/off/#> (changes state of autoraise and "
      "seconds till raise)\n"
      "edge_resistance <#/?/off> (changes the amount (in 1/100 seconds)\n"
      "   of time to push for resistance to give)\n"
      "edge_snap_resistance <#/?> (changes the number of pixels that "
      "a window will\n   resist moving against another window\n"
      "audio <on/off> (changes state of audio)\n"
      "-  seconds for tooltips and autoraise can have less than one second\n"
      "   (i.e. 0.5) or greater (1.3, 3.5, etc)"
   },
   {
      IPC_DockPosition,
      "dock",
      "Change Data about the Dock Position and Direction",
      "use \"dock direction <up/down/left/right/?>\" to set or "
      "test direction\n"
      "use \"dock start_pos ?\" to test the starting x y coords\n"
      "use \"dock start_pos x y\" to set the starting x y coords"
   },
   {
      IPC_MoveMode,
      "move_mode",
      "Toggle the Window move mode",
      "use \"move_mode <opaque/lined/box/shaded/semi-solid/translucent>\" "
      "to set\nuse \"move_mode ?\" to get the current mode"
   },
   {
      IPC_ResizeMode,
      "resize_mode",
      "Toggle the Window resize mode",
      "use \"resize_mode <opaque/lined/box/shaded/semi-solid>\" "
      "to set\nuse \"resize_mode ?\" to get the current mode"
   },
   {
      IPC_Pager,
      "pager",
      "Toggle the status of the Pager and various pager settings",
      "use \"pager <on/off>\" to set the current mode\nuse \"pager ?\" "
      "to get the current mode\n"
      "use \"pager <#> <on/off/?>\" to toggle or test any desktop's pager\n"
      "use \"pager hiq <on/off>\" to toggle high quality pager\n"
      "use \"pager snap <on/off>\" to toggle snapshotting in the pager\n"
      "use \"pager zoom <on/off>\" to toggle zooming in the pager\n"
      "use \"pager title <on/off>\" to toggle title display in the pager\n"
      "use \"pager scanrate <#>\" to toggle number of line update "
      "per second"
   },
   {
      IPC_InternalList,
      "internal_list",
      "Retreive a list of internal items",
      "use \"internal_list <pagers/menus/dialogs/internal_ewin>\"\n"
      "to retrieve a list of various internal window types.\n"
      "(note that listing internal_ewin  doesn't retreive "
      "dialogs currently)\n"
   },
   {
      IPC_SetFocus,
      "set_focus",
      "Set/Retrieve focused window",
      "use \"set_focus <win_id>\" to focus a new window\n"
      "use \"set_focus ?\" to retreive the currently focused window"
   },
   {
      IPC_DialogOK,
      "dialog_ok",
      "Pop up a dialog box with an OK button",
      "use \"dialog_ok <message>\" to pop up a dialog box."
   },
   {
      IPC_ListClassMembers,
      "list_class",
      "List all members of a class",
      "use \"list_class <classname>\" to get back a list of class members\n"
      "available classes are:\n"
      "sounds\n"
      "actions\n"
      "backgrounds\n"
      "borders\n"
      "text\n"
      "images\n"
      "cursors\n"
      "buttons"
   },
   {
      IPC_PlaySoundClass,
      "play_sound",
      "Plays a soundclass via E",
      "use \"play_sound <soundclass>\" to play a sound.\n"
      "use \"list_class sounds\" to get a list of available sounds"
   },
   {
      IPC_SoundClass,
      "soundclass",
      "Create/Delete soundclasses",
      "use \"soundclass create <classname> <filename>\" to create\n"
      "use \"soundclass delete <classname>\" to delete"
   },
   {
      IPC_ImageClass,
      "imageclass",
      "Create/delete/modify/apply an ImageClass",
      "This doesn't do anything yet."
   },
   {
      IPC_ActionClass,
      "actionclass",
      "Create/Delete/Modify an ActionClass",
      "This doesn't do anything yet."
   },
   {
      IPC_ColorModifierClass,
      "colormod",
      "Create/Delete/Modify a ColorModifierClass",
      "This doesn't do anything yet."
   },
   {
      IPC_TextClass,
      "textclass",
      "Create/Delete/Modify a TextClass",
      "This doesn't do anything yet."
   },
   {
      IPC_Background,
      "background",
      "Create/Delete/Modify a Background",
      "use \"background\" to list all defined backgrounds.\n"
      "use \"background <name>\" to delete a background.\n"
      "use \"background <name> ?\" to show current values.\n"
      "use \"background <name> <type> <value> to create / modify.\n"
      "(get available types from \"background <name> ?\"."
   },
   {
      IPC_Border,
      "border",
      "Create/Delete/Modify a Border",
      "This doesn't do anything yet."
   },
   {
      IPC_Cursor,
      "cursor",
      "Create/Delete/Modify a Cursor",
      "This doesn't do anything yet."
   },
   {
      IPC_Button,
      "button",
      "Create/Delete/Modify a Button",
      "This doesn't do anything yet."
   },
   {
      IPC_GeneralInfo,
      "general_info",
      "Retreive some general information",
      "use \"general_info <info>\" to retreive information\n"
      "available info is: screen_size"
   },
   {
      IPC_Modules,
      "module",
      "Load/Unload/List Modules",
      NULL
   }
};

/* the functions */

/* below here are all the functions that belong to the IPC.
 * If you're going to add a function to the IPC system don't forget to
 * add the prototype at the top of the file and also to add it into the
 * IPC array just above.
 * - Mandrake
 */

void
IPC_Modules(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];

	word(params, 1, param1);
	word(params, 2, param2);
	if (!strcmp(param1, "load"))
	  {
	     if (!param2)
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no module specified\n");
	       }
	     else
	       {
		  int                 returncode = 0;

		  if ((returncode = LoadModule(param2)))
		    {
		       strcat(buf, ModuleErrorCodeToString(returncode));
		    }
	       }
	  }
	else if (!strcmp(param1, "unload"))
	  {
	     if (!param2)
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no module specified\n");
	       }
	     else
	       {
		  int                 returncode = 0;

		  if ((returncode = UnloadModule(param2)))
		    {
		       strcat(buf, ModuleErrorCodeToString(returncode));
		       if (!buf[0])
			 {
			    Esnprintf(buf, sizeof(buf), "\n");
			 }
		    }
	       }
	  }
	else if (!strcmp(param1, "list"))
	  {
	     strcat(buf, ModuleListAsString());
	     if (!buf[0])
	       {
		  Esnprintf(buf, sizeof(buf), "no modules loaded\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf),
		       "Error: unknown module operation specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no module operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_DockPosition(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);

	if (!strcmp(param1, "start_pos"))
	  {
	     if (param2)
	       {
		  if (!strcmp(param2, "?"))
		    {
		       Esnprintf(buf, sizeof(buf), "dock_startposition: %d %d\n",
				 mode.dockstartx, mode.dockstarty);
		    }
		  else
		    {
		       word(params, 3, param3);
		       if (param3[0])
			 {
			    mode.dockstartx = atoi(param2);
			    mode.dockstarty = atoi(param3);
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf), "Error: no y coordinate\n");

			 }
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
	       }
	  }
	else if (!strcmp(param1, "direction"))
	  {
	     if (param2)
	       {
		  if (!strcmp(param2, "?"))
		    {
		       if (mode.dockdirmode == DOCK_LEFT)
			 {
			    Esnprintf(buf, sizeof(buf), "dock_dir: left\n");
			 }
		       else if (mode.dockdirmode == DOCK_RIGHT)
			 {
			    Esnprintf(buf, sizeof(buf), "dock_dir: right\n");
			 }
		       else if (mode.dockdirmode == DOCK_UP)
			 {
			    Esnprintf(buf, sizeof(buf), "dock_dir: up\n");
			 }
		       else if (mode.dockdirmode == DOCK_DOWN)
			 {
			    Esnprintf(buf, sizeof(buf), "dock_dir: down\n");
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf), "Error: I have NO "
				      "idea what direction "
				      "this thing is going\n");
			 }
		    }
		  else if (!strcmp(param2, "left"))
		    {
		       mode.dockdirmode = DOCK_LEFT;
		    }
		  else if (!strcmp(param2, "right"))
		    {
		       mode.dockdirmode = DOCK_RIGHT;
		    }
		  else if (!strcmp(param2, "up"))
		    {
		       mode.dockdirmode = DOCK_UP;
		    }
		  else if (!strcmp(param2, "down"))
		    {
		       mode.dockdirmode = DOCK_DOWN;
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "Error: unknown direction "
				 "specified\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown mode\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no mode given\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_GeneralInfo(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	if (!strcmp(params, "screen_size"))
	  {
	     Esnprintf(buf, sizeof(buf), "screen_size: %d %d\n", root.w, root.h);
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown info requested\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no info requested\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_Button(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param2, "create"))
	       {
	       }
	     else if (!strcmp(param2, "delete"))
	       {
		  Button             *b;

		  b = (Button *) FindItem(param1, 0, LIST_FINDBY_NAME,
					  LIST_TYPE_BUTTON);
		  if (b)
		     DestroyButton(b);
	       }
	     else if (!strcmp(param2, "modify"))
	       {
	       }
	     else if (!strcmp(param2, "ref_count"))
	       {
		  Button             *b;

		  b = (Button *) FindItem(param1, 0, LIST_FINDBY_NAME,
					  LIST_TYPE_BUTTON);
		  if (b)
		     Esnprintf(buf, sizeof(buf), "%u references remain\n",
			       b->ref_count);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no cursor specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf),
		       "Error: unknown operation specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_Background(char *params, Client * c)
{
   char                buf[FILEPATH_LEN_MAX];
   char                name[FILEPATH_LEN_MAX];
   char                type[FILEPATH_LEN_MAX];
   char                valu[FILEPATH_LEN_MAX];
   Background         *bg = NULL;

   buf[0] = 0;

   name[0] = 0;
   type[0] = 0;
   valu[0] = 0;

   word(params, 1, name);
   word(params, 2, type);

   if (params)
     {
	if (type[0])
	  {
	     if (!strcmp(type, "?"))
	       {
		  /* query background values */

		  bg = (Background *) FindItem(name, 0, LIST_FINDBY_NAME, LIST_TYPE_BACKGROUND);

		  if (bg)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "%s ref_count %u\n"
				 " bg.solid\t %i %i %i \n"
				 " bg.file\t %s \ttop.file\t %s \n"
				 " bg.tile\t %i \n"
			      " bg.keep_aspect\t %i \ttop.keep_aspect\t %i \n"
				 " bg.xjust\t %i \ttop.xjust\t %i \n"
				 " bg.yjust\t %i \ttop.yjust\t %i \n"
				 " bg.xperc\t %i \ttop.xperc\t %i \n"
				 " bg.yperc\t %i \ttop.yperc\t %i \n",
				 bg->name, bg->ref_count,
			       bg->bg.solid.r, bg->bg.solid.g, bg->bg.solid.b,
				 bg->bg.file, bg->top.file,
				 bg->bg.tile,
				 bg->bg.keep_aspect, bg->top.keep_aspect,
				 bg->bg.xjust, bg->top.xjust,
				 bg->bg.yjust, bg->top.yjust,
				 bg->bg.xperc, bg->top.xperc,
				 bg->bg.yperc, bg->top.yperc);
		    }
		  else
		     Esnprintf(buf, sizeof(buf), "Error: background '%s' does not exist.", name);
	       }
	     else
	       {
		  /* create / modify background */

		  bg = (Background *) FindItem(name, 0, LIST_FINDBY_NAME, LIST_TYPE_BACKGROUND);

		  if (!bg)
		     bg = CreateDesktopBG(strdup(name), NULL, NULL, 0, 0, 0, 0, 0, 0, NULL, 0, 0, 0, 0, 0);

		  if (!bg)
		     Esnprintf(buf, sizeof(buf), "Error: could not create background '%s'.\n", name);
		  else
		    {
		       word(params, 3, valu);
		       if (!strcmp(type, "bg.solid"))
			 {
			    char                R[3], G[3], B[3];

			    R[0] = 0;
			    G[0] = 0;
			    B[0] = 0;

			    word(params, 3, R);
			    word(params, 4, G);
			    word(params, 5, B);

			    bg->bg.solid.r = atoi(R);
			    bg->bg.solid.g = atoi(G);
			    bg->bg.solid.b = atoi(B);
			 }
		       else if (!strcmp(type, "bg.file"))
			 {
			    if (bg->bg.file)
			       Efree(bg->bg.file);
			    bg->bg.file = strdup(valu);
			 }
		       else if (!strcmp(type, "bg.tile"))
			  bg->bg.tile = atoi(valu);
		       else if (!strcmp(type, "bg.keep_aspect"))
			  bg->bg.keep_aspect = atoi(valu);
		       else if (!strcmp(type, "bg.xjust"))
			  bg->bg.xjust = atoi(valu);
		       else if (!strcmp(type, "bg.yjust"))
			  bg->bg.yjust = atoi(valu);
		       else if (!strcmp(type, "bg.xperc"))
			  bg->bg.xperc = atoi(valu);
		       else if (!strcmp(type, "bg.yperc"))
			  bg->bg.yperc = atoi(valu);
		       else if (!strcmp(type, "top.file"))
			 {
			    if (bg->top.file)
			       Efree(bg->top.file);
			    bg->top.file = strdup(valu);
			 }
		       else if (!strcmp(type, "top.keep_aspect"))
			  bg->top.keep_aspect = atoi(valu);
		       else if (!strcmp(type, "top.xjust"))
			  bg->top.xjust = atoi(valu);
		       else if (!strcmp(type, "top.yjust"))
			  bg->top.yjust = atoi(valu);
		       else if (!strcmp(type, "top.xperc"))
			  bg->top.xperc = atoi(valu);
		       else if (!strcmp(type, "top.yperc"))
			  bg->top.yperc = atoi(valu);
		       else
			  Esnprintf(buf, sizeof(buf), "Error: unknow background value type '%s'.", type);
		    }

		  AddItem(bg, bg->name, 0, LIST_TYPE_BACKGROUND);
	       }
	  }
	else
	  {
	     /* delete background */

	     bg = (Background *) FindItem(name, 0, LIST_FINDBY_NAME, LIST_TYPE_BACKGROUND);

	     if (bg)
	       {
		  if (bg->ref_count == 0)
		    {
		       RemoveItem(name, 0, LIST_FINDBY_NAME, LIST_TYPE_BACKGROUND);
		       FreeDesktopBG(bg);
		    }
		  else
		     Esnprintf(buf, sizeof(buf), "Error: ref_count for background '%s' is %u.", name, bg->ref_count);
	       }
	     else
		Esnprintf(buf, sizeof(buf), "Error: background '%s' does not exist.", name);
	  }
     }
   else
     {
	/* show all backgrounds */

	Background        **lst;
	char                buf2[FILEPATH_LEN_MAX];
	int                 num, i;

	buf2[0] = 0;

	lst = (Background **) ListItemType(&num, LIST_TYPE_BACKGROUND);

	for (i = 0; i < num; i++)
	  {
	     buf2[0] = 0;
	     Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
	     strcat(buf, buf2);
	  }
	if (lst)
	   Efree(lst);
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_Border(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param2, "create"))
	       {
	       }
	     else if (!strcmp(param2, "delete"))
	       {
		  Border             *b;

		  b = (Border *) FindItem(param1, 0, LIST_FINDBY_NAME,
					  LIST_TYPE_BORDER);
		  if (b)
		     FreeBorder(b);
	       }
	     else if (!strcmp(param2, "modify"))
	       {
	       }
	     else if (!strcmp(param2, "ref_count"))
	       {
		  Border             *b;

		  b = (Border *) FindItem(param1, 0, LIST_FINDBY_NAME,
					  LIST_TYPE_BORDER);
		  if (b)
		     Esnprintf(buf, sizeof(buf), "%u references remain\n",
			       b->ref_count);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no cursor specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf),
		       "Error: unknown operation specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_Cursor(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param2, "create"))
	       {
	       }
	     else if (!strcmp(param2, "delete"))
	       {
		  ECursor            *ec;

		  ec = (ECursor *) FindItem(param1, 0, LIST_FINDBY_NAME,
					    LIST_TYPE_ECURSOR);
		  if (ec)
		     FreeECursor(ec);
	       }
	     else if (!strcmp(param2, "modify"))
	       {
	       }
	     else if (!strcmp(param2, "ref_count"))
	       {
		  ECursor            *ec;

		  ec = (ECursor *) FindItem(param1, 0, LIST_FINDBY_NAME,
					    LIST_TYPE_ECURSOR);
		  if (ec)
		     Esnprintf(buf, sizeof(buf), "%u references remain\n",
			       ec->ref_count);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no cursor specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf),
		       "Error: unknown operation specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_TextClass(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param2, "create"))
	       {
	       }
	     else if (!strcmp(param2, "delete"))
	       {
		  TextClass          *t;

		  t = (TextClass *) FindItem(param1, 0, LIST_FINDBY_NAME,
					     LIST_TYPE_TCLASS);
		  if (t)
		     DeleteTclass(t);
	       }
	     else if (!strcmp(param2, "modify"))
	       {
	       }
	     else if (!strcmp(param2, "ref_count"))
	       {
		  TextClass          *t;

		  t = (TextClass *) FindItem(param1, 0, LIST_FINDBY_NAME,
					     LIST_TYPE_TCLASS);
		  if (t)
		     Esnprintf(buf, sizeof(buf), "%u references remain.\n",
			       t->ref_count);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown operation specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: no class specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_ColorModifierClass(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param1, "create"))
	       {
	       }
	     else if (!strcmp(param2, "delete"))
	       {
		  ColorModifierClass *cm;

		  cm = (ColorModifierClass *) FindItem(param1, 0,
				   LIST_FINDBY_NAME, LIST_TYPE_COLORMODIFIER);
		  if (cm)
		     FreeCMClass(cm);
	       }
	     else if (!strcmp(param2, "modify"))
	       {
	       }
	     else if (!strcmp(param2, "ref_count"))
	       {
		  ColorModifierClass *cm;

		  cm = (ColorModifierClass *) FindItem(param1, 0,
				   LIST_FINDBY_NAME, LIST_TYPE_COLORMODIFIER);
		  if (cm)
		     Esnprintf(buf, sizeof(buf), "%u references remain.\n",
			       cm->ref_count);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown operation specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: no class specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_ActionClass(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param1, "create"))
	       {
	       }
	     else if (!strcmp(param2, "delete"))
	       {
		  ActionClass        *a;

		  a = (ActionClass *) FindItem(param1, 0, LIST_FINDBY_NAME,
					       LIST_TYPE_ACLASS);
		  if (a)
		     RemoveActionClass(a);
	       }
	     else if (!strcmp(param2, "modify"))
	       {
	       }
	     else if (!strcmp(param2, "ref_count"))
	       {
		  ActionClass        *a;

		  a = (ActionClass *) FindItem(param1, 0, LIST_FINDBY_NAME,
					       LIST_TYPE_ACLASS);
		  if (a)
		     Esnprintf(buf, sizeof(buf), "%u references remain.\n",
			       a->ref_count);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown operation specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: no class specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_ImageClass(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param1, "create"))
	       {
	       }
	     else if (!strcmp(param2, "delete"))
	       {
		  ImageClass         *i;

		  i = (ImageClass *) FindItem(param1, 0, LIST_FINDBY_NAME,
					      LIST_TYPE_ICLASS);
		  if (i)
		     FreeImageClass(i);
	       }
	     else if (!strcmp(param2, "modify"))
	       {
	       }
	     else if (!strcmp(param2, "apply"))
	       {
		  ImageClass         *iclass;

		  iclass = (ImageClass *) FindItem(param1, 0, LIST_FINDBY_NAME, LIST_TYPE_ICLASS);
		  if (iclass)
		    {
		       Window              win;
		       char               *winptr, *hptr, state[20];
		       int                 st, w = 0, h = 0;

		       winptr = atword(params, 3);
		       word(params, 4, state);
		       win = (Window) strtol(winptr, (char **)NULL, 0);
		       if (!strcasecmp(state, "hilited"))
			 {
			    st = STATE_HILITED;
			 }
		       else if (!strcasecmp(state, "clicked"))
			 {
			    st = STATE_CLICKED;
			 }
		       else if (!strcasecmp(state, "disabled"))
			 {
			    st = STATE_DISABLED;
			 }
		       else
			 {
			    st = STATE_NORMAL;
			 }
		       if ((hptr = atword(winptr, 3)))
			 {
			    w = (int)strtol(atword(winptr, 2), (char **)NULL, 0);
			    h = (int)strtol(hptr, (char **)NULL, 0);
			 }
		       IclassApply(iclass, win, w, h, 0, 0, st, 0);
		       FreeImageClass(iclass);
		    }
	       }
	     else if (!strcmp(param2, "ref_count"))
	       {
		  ImageClass         *i;

		  i = (ImageClass *) FindItem(param1, 0, LIST_FINDBY_NAME,
					      LIST_TYPE_ICLASS);
		  if (i)
		     Esnprintf(buf, sizeof(buf), "%u references remain.\n",
			       i->ref_count);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown operation specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: no class specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_SoundClass(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];
	char                param3[FILEPATH_LEN_MAX];
	SoundClass         *sc;

	param1[0] = 0;
	param2[0] = 0;
	param3[0] = 0;

	word(params, 1, param1);
	word(params, 2, param2);
	if (param2[0])
	  {
	     if (!strcmp(param1, "create"))
	       {
		  word(params, 3, param3);
		  if (param3[0])
		    {
		       sc = CreateSoundClass(param1, param2);
		       if (sc)
			  AddItem(sc, sc->name, 0, LIST_TYPE_SCLASS);
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "Error: no file specified\n");
		    }
	       }
	     else if (!strcmp(param1, "delete"))
	       {
		  DestroySclass(RemoveItem(param2, 0, LIST_FINDBY_NAME,
					   LIST_TYPE_SCLASS));
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown operation specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: no class specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_PlaySoundClass(char *params, Client * c)
{
   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	SoundClass         *soundtoplay;

	soundtoplay = FindItem(params, 0, LIST_FINDBY_NAME, LIST_TYPE_SCLASS);
	if (soundtoplay)
	   ApplySclass(soundtoplay);
	else
	   Esnprintf(buf, sizeof(buf), "Error: unknown soundclass selected\n");
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no soundclass selected\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_ListClassMembers(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];
   char                buf2[FILEPATH_LEN_MAX];
   int                 num, i;

   buf[0] = 0;

   if (params)
     {
	if (!strcmp(params, "backgrounds"))
	  {

	     Background        **lst;

	     lst = (Background **) ListItemType(&num, LIST_TYPE_BACKGROUND);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else if (!strcmp(params, "actions"))
	  {
	     ActionClass       **lst;

	     lst = (ActionClass **) ListItemType(&num, LIST_TYPE_ACLASS);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else if (!strcmp(params, "sounds"))
	  {
	     SoundClass        **lst;

	     lst = (SoundClass **) ListItemType(&num, LIST_TYPE_SCLASS);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else if (!strcmp(params, "cursors"))
	  {
	     ECursor           **lst;

	     lst = (ECursor **) ListItemType(&num, LIST_TYPE_ECURSOR);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else if (!strcmp(params, "borders"))
	  {
	     Border            **lst;

	     lst = (Border **) ListItemType(&num, LIST_TYPE_BORDER);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else if (!strcmp(params, "text"))
	  {
	     TextClass         **lst;

	     lst = (TextClass **) ListItemType(&num, LIST_TYPE_TCLASS);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else if (!strcmp(params, "images"))
	  {
	     ImageClass        **lst;

	     lst = (ImageClass **) ListItemType(&num, LIST_TYPE_ICLASS);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else if (!strcmp(params, "buttons"))
	  {
	     Button            **lst;

	     lst = (Button **) ListItemType(&num, LIST_TYPE_BUTTON);
	     for (i = 0; i < num; i++)
	       {
		  buf2[0] = 0;
		  Esnprintf(buf2, sizeof(buf2), "%s\n", lst[i]->name);
		  strcat(buf, buf2);
	       }
	     if (lst)
		Efree(lst);
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown class selected\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no class selected\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_DialogOK(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	DIALOG_OK("Message", params);
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: No text for dialog specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_SetFocus(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	EWin               *my_focused_win;

	if (!strcmp(params, "?"))
	  {
	     my_focused_win = GetFocusEwin();
	     if (my_focused_win)
	       {
		  Esnprintf(buf, sizeof(buf), "focused: %8x\n",
			    my_focused_win->client.win);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "focused: none\n");
	       }
	  }
	else
	  {
	     unsigned int        win;

	     sscanf(params, "%8x", &win);
	     my_focused_win = FindEwinByChildren(win);
	     if (my_focused_win)
		FocusToEWin(my_focused_win);
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no window selected\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_AdvancedFocus(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	char                param1[FILEPATH_LEN_MAX];
	char                param2[FILEPATH_LEN_MAX];

	param1[0] = 0;
	param2[0] = 0;
	word(params, 1, param1);
	word(params, 2, param2);
	if (!strcmp(param1, "new_window_focus"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.all_new_windows_get_focus = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.all_new_windows_get_focus = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.all_new_windows_get_focus)
		    {
		       Esnprintf(buf, sizeof(buf), "new_window_focus: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "new_window_focus: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "focus_list"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.display_warp = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.display_warp = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.display_warp)
		    {
		       Esnprintf(buf, sizeof(buf), "focus_list: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "focus_list: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "new_popup_window_focus"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.new_transients_get_focus = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.new_transients_get_focus = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.new_transients_get_focus)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "new_popup_window_focus: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "new_popup_window_focus: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "new_popup_of_owner_focus"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.new_transients_get_focus_if_group_focused = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.new_transients_get_focus_if_group_focused = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.new_transients_get_focus_if_group_focused)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "new_popup_of_owner_focus: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "new_popup_of_owner_focus: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "raise_on_keyboard_focus_switch"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.raise_on_next_focus = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.raise_on_next_focus = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.raise_on_next_focus)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "raise_on_keyboard_focus_switch: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "raise_on_keyboard_focus_switch: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "raise_after_keyboard_focus_switch"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.raise_after_next_focus = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.raise_after_next_focus = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.raise_after_next_focus)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "raise_after_keyboard_focus_switch: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "raise_after_keyboard_focus_switch: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "display_warp"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.display_warp = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.display_warp = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.display_warp)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "display_warp: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "display_warp: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "pointer_to_keyboard_focus_window"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.warp_on_next_focus = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.warp_on_next_focus = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.warp_on_next_focus)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "pointer_to_keyboard_focus_window: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "pointer_to_keyboard_focus_window: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "pointer_after_keyboard_focus_window"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.warp_after_next_focus = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.warp_after_next_focus = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.warp_after_next_focus)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "pointer_after_keyboard_focus_window: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "pointer_after_keyboard_focus_window: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "transients_follow_leader"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.transientsfollowleader = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.transientsfollowleader = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.transientsfollowleader)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "transients_follow_leader: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "transients_follow_leader: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "switch_to_popup_location"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.switchfortransientmap = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.switchfortransientmap = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.switchfortransientmap)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "switch_to_popup_location: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "switch_to_popup_location: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "manual_placement"))
	  {
	     if (!strcmp(param2, "on"))
	       {
		  mode.manual_placement = 1;
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  mode.manual_placement = 0;
	       }
	     else if (!strcmp(param2, "?"))
	       {
		  if (mode.manual_placement)
		    {
		       Esnprintf(buf, sizeof(buf),
				 "manual_placement: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "manual_placement: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no mode selected\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_InternalList(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];
   char                buf2[FILEPATH_LEN_MAX];

   buf[0] = 0;
   buf2[0] = 0;

   if (params)
     {
	EWin              **lst;
	int                 num, i;

	lst = (EWin **) ListItemType(&num, LIST_TYPE_EWIN);
	if (!strcmp(params, "pagers"))
	  {
	     for (i = 0; i < num; i++)
	       {
		  if (lst[i]->pager)
		    {
		       Esnprintf(buf2, sizeof(buf2),
				 "%8x\n", lst[i]->client.win);
		       strcat(buf, buf2);
		    }
	       }
	  }
	else if (!strcmp(params, "menus"))
	  {
	     for (i = 0; i < num; i++)
	       {
		  if (lst[i]->menu)
		    {
		       Esnprintf(buf2, sizeof(buf2),
				 "%8x\n", lst[i]->client.win);
		       strcat(buf, buf2);
		    }
	       }
	  }
	else if (!strcmp(params, "dialogs"))
	  {
	     for (i = 0; i < num; i++)
	       {
		  if (lst[i]->dialog)
		    {
		       Esnprintf(buf2, sizeof(buf2),
				 "%8x\n", lst[i]->client.win);
		       strcat(buf, buf2);
		    }
	       }
	  }
	else if (!strcmp(params, "internal_ewin"))
	  {
	     for (i = 0; i < num; i++)
	       {
		  if (lst[i]->internal)
		    {
		       Esnprintf(buf2, sizeof(buf2),
				 "%8x\n", lst[i]->client.win);
		       strcat(buf, buf2);
		    }
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf),
		       "Error: unknown internal list specified\n");
	  }

	if (lst)
	   Efree(lst);
     }
   if (buf[0])
      CommsSend(c, buf);
   else
      CommsSend(c, "");

   return;

}

void
IPC_Pager(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];
   char                param1[FILEPATH_LEN_MAX];
   char                param2[FILEPATH_LEN_MAX];

   buf[0] = 0;
   param1[0] = 0;
   param2[0] = 0;

   if (params)
     {
	word(params, 1, param1);
	if (!strcmp(param1, "on"))
	  {
	     EnableAllPagers();
	  }
	else if (!strcmp(param1, "off"))
	  {
	     DisableAllPagers();
	  }
	else if (!strcmp(param1, "?"))
	  {
	     if (mode.show_pagers)
	       {
		  Esnprintf(buf, sizeof(buf), "pager: on\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "pager: off\n");
	       }
	  }
	else if (!strcmp(param1, "hiq"))
	  {
	     word(params, 2, param2);
	     if (!strcmp(param2, "?"))
	       {
		  if (mode.pager_hiq)
		    {
		       Esnprintf(buf, sizeof(buf), "pager_hiq: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "pager_hiq: off\n");
		    }
	       }
	     else if (!strcmp(param2, "on"))
	       {
		  PagerSetHiQ(1);
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  PagerSetHiQ(0);
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown mode selected\n");

	       }
	  }
	else if (!strcmp(param1, "zoom"))
	  {
	     word(params, 2, param2);
	     if (param2)
	       {
		  if (!strcmp(param2, "on"))
		    {
		       mode.pager_zoom = 1;
		    }
		  else if (!strcmp(param2, "off"))
		    {
		       mode.pager_zoom = 0;
		    }
		  else if (!strcmp(param2, "?"))
		    {
		       if (mode.pager_zoom)
			 {
			    CommsSend(c, "pager_zoom: on\n");
			 }
		       else
			 {
			    CommsSend(c, "pager_zoom: off\n");
			 }
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "Error: unknown mode selected\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no mode selected\n");
	       }
	  }
	else if (!strcmp(param1, "title"))
	  {
	     word(params, 2, param2);
	     if (param2)
	       {
		  if (!strcmp(param2, "on"))
		    {
		       mode.pager_title = 1;
		    }
		  else if (!strcmp(param2, "off"))
		    {
		       mode.pager_title = 0;
		    }
		  else if (!strcmp(param2, "?"))
		    {
		       if (mode.pager_title)
			 {
			    CommsSend(c, "pager_title: on\n");
			 }
		       else
			 {
			    CommsSend(c, "pager_title: off\n");
			 }
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "Error: no mode selected\n");
		    }
	       }
	  }
	else if (!strcmp(param1, "scanrate"))
	  {
	     word(params, 2, param2);
	     if (param2)
	       {
		  if (!strcmp(param2, "?"))
		    {
		       Esnprintf(buf, sizeof(buf),
				 "pager_scanrate: %d\n", mode.pager_scanspeed);
		    }
		  else
		    {
		       mode.pager_scanspeed = atoi(param2);
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no scanrate specified.\n");
	       }
	  }
	else if (!strcmp(param1, "snap"))
	  {
	     word(params, 2, param2);
	     if (!strcmp(param2, "?"))
	       {
		  if (mode.pager_hiq)
		    {
		       Esnprintf(buf, sizeof(buf), "pager_snap: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "pager_snap: off\n");
		    }
	       }
	     else if (!strcmp(param2, "on"))
	       {
		  PagerSetSnap(1);
	       }
	     else if (!strcmp(param2, "off"))
	       {
		  PagerSetSnap(0);
	       }
	  }
	else if (!strcmp(param1, "desk"))
	  {
	     char                param3[FILEPATH_LEN_MAX];

	     param3[0] = 0;

	     word(params, 2, param2);
	     word(params, 3, param3);
	     if (param3[0])
	       {
		  if (!strcmp(param3, "on"))
		    {
		       EnableSinglePagerForDesktop(atoi(param2));
		    }
		  else if (!strcmp(param3, "new"))
		    {
		       NewPagerForDesktop(atoi(param2));
		    }
		  else if (!strcmp(param3, "off"))
		    {
		       DisablePagersForDesktop(atoi(param2));
		    }
		  else if (!strcmp(param3, "?"))
		    {
		       Esnprintf(buf, sizeof(buf), "Desk %s: %i pagers\n", param2,
				 PagerForDesktop(atoi(param2)));
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "Error: unknown mode specified\n");
		    }
	       }
	     else
	       {
		  if (param2[0])
		    {
		       Esnprintf(buf, sizeof(buf), "Error: no mode specified\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "Error: no desk specified\n");
		    }
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown mode specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no mode specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_MoveMode(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	if (!strcmp(params, "opaque"))
	  {
	     mode.movemode = 0;
	  }
	else if (!strcmp(params, "lined"))
	  {
	     mode.movemode = 1;
	  }
	else if (!strcmp(params, "box"))
	  {
	     mode.movemode = 2;
	  }
	else if (!strcmp(params, "shaded"))
	  {
	     mode.movemode = 3;
	  }
	else if (!strcmp(params, "semi-solid"))
	  {
	     mode.movemode = 4;
	  }
	else if (!strcmp(params, "translucent"))
	  {
	     mode.movemode = 5;
	  }
	else if (!strcmp(params, "?"))
	  {
	     if (mode.movemode)
	       {
		  if (mode.movemode == 1)
		     Esnprintf(buf, sizeof(buf), "movemode: lined\n");
		  else if (mode.movemode == 2)
		     Esnprintf(buf, sizeof(buf), "movemode: box\n");
		  else if (mode.movemode == 3)
		     Esnprintf(buf, sizeof(buf), "movemode: shaded\n");
		  else if (mode.movemode == 4)
		     Esnprintf(buf, sizeof(buf), "movemode: semi-solid\n");
		  else if (mode.movemode == 5)
		     Esnprintf(buf, sizeof(buf), "movemode: translucent\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "movemode: opaque\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown mode specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no mode specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_ResizeMode(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	if (!strcmp(params, "opaque"))
	  {
	     mode.resizemode = 0;
	  }
	else if (!strcmp(params, "lined"))
	  {
	     mode.resizemode = 1;
	  }
	else if (!strcmp(params, "box"))
	  {
	     mode.resizemode = 2;
	  }
	else if (!strcmp(params, "shaded"))
	  {
	     mode.resizemode = 3;
	  }
	else if (!strcmp(params, "semi-solid"))
	  {
	     mode.resizemode = 4;
	  }
	else if (!strcmp(params, "?"))
	  {
	     if (mode.resizemode)
	       {
		  if (mode.resizemode == 1)
		     Esnprintf(buf, sizeof(buf), "resizemode: lined\n");
		  else if (mode.resizemode == 2)
		     Esnprintf(buf, sizeof(buf), "resizemode: box\n");
		  else if (mode.resizemode == 3)
		     Esnprintf(buf, sizeof(buf), "resizemode: shaded\n");
		  else if (mode.resizemode == 4)
		     Esnprintf(buf, sizeof(buf), "resizemode: semi-solid\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "resizemode: opaque\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown mode specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no mode specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_FX(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {

	char                word1[FILEPATH_LEN_MAX];
	char                word2[FILEPATH_LEN_MAX];

	word(params, 1, word1);
	if (!strcmp(word1, "ripples"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  if (!FX_IsOn("ripples"))
		     FX_Activate("ripples");
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  if (FX_IsOn("ripples"))
		     FX_Deactivate("ripples");
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (FX_IsOn("ripples"))
		     Esnprintf(buf, sizeof(buf), "ripples: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "ripples: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else if (!strcmp(word1, "deskslide"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  desks.slidein = 1;
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  desks.slidein = 0;
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (desks.slidein)
		     Esnprintf(buf, sizeof(buf), "deskslide: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "deskslide: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else if (!strcmp(word1, "mapslide"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  mode.mapslide = 1;
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  mode.mapslide = 0;
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (mode.mapslide)
		     Esnprintf(buf, sizeof(buf), "mapslide: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "mapslide: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else if (!strcmp(word1, "raindrops"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  if (!FX_IsOn("raindrops"))
		     FX_Activate("raindrops");
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  if (FX_IsOn("raindrops"))
		     FX_Deactivate("raindrops");
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (FX_IsOn("raindrops"))
		     Esnprintf(buf, sizeof(buf), "raindrops: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "raindrops: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else if (!strcmp(word1, "menu_animate"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  mode.menuslide = 1;
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  mode.menuslide = 0;
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (mode.menuslide)
		     Esnprintf(buf, sizeof(buf), "menu_animate: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "menu_animate: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else if (!strcmp(word1, "waves"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  if (!FX_IsOn("waves"))
		     FX_Activate("waves");
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  if (FX_IsOn("waves"))
		     FX_Deactivate("waves");
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (FX_IsOn("waves"))
		     Esnprintf(buf, sizeof(buf), "waves: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "waves: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else if (!strcmp(word1, "animate_win_shading"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  mode.animate_shading = 1;
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  mode.animate_shading = 0;
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (mode.animate_shading)
		     Esnprintf(buf, sizeof(buf), "animate_win_shading: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "animate_win_shading: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else if (!strcmp(word1, "window_shade_speed"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "?"))
	       {
		  if (mode.animate_shading)
		    {
		       Esnprintf(buf, sizeof(buf), "shadespeed: %d seconds\n",
				 mode.shadespeed);
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "shadespeed: off\n");
		    }
	       }
	     else
	       {
		  mode.shadespeed = atoi(word2);
	       }
	  }
	else if (!strcmp(word1, "dragbar"))
	  {

	     char                move;

	     word(params, 2, word2);
	     move = 0;
	     if (!strcmp(word2, "off"))
	       {
		  desks.dragbar_width = 0;
		  move = 1;
	       }
	     else if (!strcmp(word2, "on"))
	       {
		  desks.dragbar_width = 16;
		  move = 1;
	       }
	     else if (!strcmp(word2, "bottom"))
	       {
		  desks.dragbar_width = 16;
		  desks.dragdir = 3;
		  move = 1;
	       }
	     else if (!strcmp(word2, "right"))
	       {
		  desks.dragbar_width = 16;
		  desks.dragdir = 1;
		  move = 1;
	       }
	     else if (!strcmp(word2, "left"))
	       {
		  desks.dragbar_width = 16;
		  desks.dragdir = 0;
		  move = 1;
	       }
	     else if (!strcmp(word2, "top"))
	       {
		  desks.dragbar_width = 16;
		  desks.dragdir = 2;
		  move = 1;
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (desks.dragbar_width)
		    {
		       if (desks.dragdir == 1)
			 {
			    Esnprintf(buf, sizeof(buf), "Dragbar: right\n");
			 }
		       else if (desks.dragdir == 2)
			 {
			    Esnprintf(buf, sizeof(buf), "Dragbar: top\n");
			 }
		       else if (desks.dragdir == 3)
			 {
			    Esnprintf(buf, sizeof(buf), "Dragbar: bottom\n");
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf), "Dragbar: left\n");
			 }
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "Dragbar: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }

	     if (move)
	       {

		  Button             *b;
		  int                 i;

		  GotoDesktop(desks.current);
		  for (i = 0; i < ENLIGHTENMENT_CONF_NUM_DESKTOPS; i++)
		     MoveDesktop(i, 0, 0);
		  while ((b = RemoveItem("_DESKTOP_DRAG_CONTROL",
				      0, LIST_FINDBY_NAME, LIST_TYPE_BUTTON)))
		     DestroyButton(b);
		  while ((b = RemoveItem("_DESKTOP_DESKRAY_DRAG_CONTROL",
				      0, LIST_FINDBY_NAME, LIST_TYPE_BUTTON)))
		     DestroyButton(b);
		  InitDesktopControls();
		  ShowDesktopControls();
	       }
	  }
	else if (!strcmp(word1, "tooltips"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "off"))
	       {
		  mode.tooltips = 0;
	       }
	     else if (!strcmp(word2, "on"))
	       {
		  mode.tooltips = 1;
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (mode.tooltips)
		    {
		       Esnprintf(buf, sizeof(buf), "tooltips: %f seconds\n",
				 mode.tiptime);
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "tooltips: off\n");
		    }
	       }
	     else
	       {
		  mode.tiptime = atof(word2);
		  if (!mode.tiptime)
		     mode.tooltips = 0;
		  else
		     mode.tooltips = 1;
	       }
	  }
	else if (!strcmp(word1, "edge_resistance"))
	  {
	     word(params, 2, word2);
	     if (word2[0])
	       {
		  if (!strcmp(word2, "off"))
		    {
		       mode.edge_flip_resistance = -1;
		    }
		  else if (!strcmp(word2, "?"))
		    {
		       if (mode.edge_flip_resistance >= 0)
			 {
			    Esnprintf(buf, sizeof(buf),
				      "edge_resistance: %d / 100 seconds\n",
				      mode.edge_flip_resistance);
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf), "edge_resistance: off\n");
			 }
		    }
		  else
		    {
		       mode.edge_flip_resistance = atoi(word2);
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no time given\n");
	       }
	  }
	else if (!strcmp(word1, "edge_snap_distance"))
	  {
	     word(params, 2, word2);
	     if (word2[0])
	       {
		  if (!strcmp(word2, "?"))
		    {
		       Esnprintf(buf, sizeof(buf),
			     "edge_snap_distance: %d\n", mode.edge_snap_dist);
		    }
		  else
		    {
		       mode.edge_snap_dist = atoi(word2);
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: no pixel distance given\n");
	       }
	  }
	else if (!strcmp(word1, "autoraise"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "off"))
	       {
		  mode.autoraise = 0;
	       }
	     else if (!strcmp(word2, "on"))
	       {
		  mode.autoraise = 1;
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (mode.autoraise)
		    {
		       Esnprintf(buf, sizeof(buf), "autoraise: %f seconds\n",
				 mode.autoraisetime);
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "autoraise: off\n");
		    }
	       }
	     else
	       {
		  mode.autoraisetime = atof(word2);
		  if (!mode.autoraisetime)
		     mode.autoraise = 0;
		  else
		     mode.autoraise = 1;
	       }
	  }
	else if (!strcmp(word1, "audio"))
	  {
	     word(params, 2, word2);
	     if (!strcmp(word2, "on"))
	       {
		  if (!mode.sound)
		    {
		       mode.sound = 1;
		       SoundInit();
		    }
	       }
	     else if (!strcmp(word2, "off"))
	       {
		  if (mode.sound)
		    {

		       SoundClass        **lst;
		       int                 num, i;

		       mode.sound = 0;

		       lst = (SoundClass **) ListItemType(&num,
							  LIST_TYPE_SCLASS);
		       if (lst)
			 {
			    for (i = 0; i < num; i++)
			      {
				 if (lst[i]->sample)
				    DestroySample(lst[i]->sample);
				 lst[i]->sample = NULL;
			      }
			    Efree(lst);
			 }
		       close(sound_fd);
		       sound_fd = -1;
		    }
	       }
	     else if (!strcmp(word2, "?"))
	       {
		  if (mode.sound)
		     Esnprintf(buf, sizeof(buf), "audio: on\n");
		  else
		     Esnprintf(buf, sizeof(buf), "audio: off\n");
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf),
			    "Error: unknown mode specified\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown effect specified\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no effect specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_ActiveNetwork(char *params, Client * c)
{
   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
#ifdef AUTOUPGRADE
	if (!strcmp(params, "on"))
	  {
	     if (!mode.activenetwork)
	       {
		  mode.activenetwork = 1;
		  DoIn("MOTD_CHECK", 5.0, CheckForNewMOTD, 0, NULL);
	       }
	  }
	else if (!strcmp(params, "off"))
	  {
	     if (mode.activenetwork)
	       {
		  mode.activenetwork = 0;
		  RemoveTimerEvent("MOTD_CHECK");
		  RemoveTimerEvent("UPDATE_CHECK");
	       }
	     else if (!strcmp(params, "?"))
	       {
		  if (mode.activenetwork)
		    {
		       Esnprintf(buf, sizeof(buf), "Active network: on\n");
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf), "Active network: off\n");
		    }
	       }
	     else
	       {
		  Esnprintf(buf, sizeof(buf), "Error: unknown state.\n");
	       }
	  }
#else
	Esnprintf(buf, sizeof(buf),
		  "Active Network not compiled into this version of E\n");
#endif
     }
   else
      Esnprintf(buf, sizeof(buf), "Error: no state specified\n");

   if (buf[0])
      CommsSend(c, buf);
   return;
}

void
IPC_ButtonShow(char *params, Client * c)
{
   c = NULL;
   if (params)
     {
	doHideShowButton(params);
     }
   else
     {
	doHideShowButton(NULL);
     }
   return;
}

void
IPC_WinList(char *params, Client * c)
{

   char               *ret = NULL;
   char                buf[FILEPATH_LEN_MAX];
   EWin              **lst;
   int                 num, i;
   char                none[] = "-NONE-";

   params = NULL;
   lst = (EWin **) ListItemType(&num, LIST_TYPE_EWIN);
   if (lst)
     {
	for (i = 0; i < num; i++)
	  {
	     if (!lst[i]->client.title)
		lst[i]->client.title = none;
	     Esnprintf(buf, sizeof(buf), "%8x : %s\n", lst[i]->client.win,
		       lst[i]->client.title);
	     if (!ret)
	       {
		  ret = Emalloc(strlen(buf) + 1);
		  ret[0] = 0;
	       }
	     else
	       {
		  ret = Erealloc(ret, strlen(ret) + strlen(buf) + 1);
	       }
	     strcat(ret, buf);
	  }
     }
   if (ret)
     {
	CommsSend(c, ret);
	Efree(ret);
     }
   else
     {
	CommsSend(c, "");
     }
   if (lst)
      Efree(lst);

}

void
IPC_GotoArea(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];
   char                param1[FILEPATH_LEN_MAX];
   char                param2[FILEPATH_LEN_MAX];

   buf[0] = 0;
   param1[0] = 0;
   param2[0] = 0;

   if (!params)
     {
	Esnprintf(buf, sizeof(buf), "Error: no area specified\n");
     }
   else
     {
	int                 a, b;

	word(params, 1, param1);
	if (!strcmp(param1, "next"))
	  {
	     GetCurrentArea(&a, &b);
	     word(params, 2, param2);
	     if ((param2) && (!strcmp(param2, "horiz")))
	       {
		  a++;
	       }
	     else if ((param2) && (!strcmp(param2, "vert")))
	       {
		  b++;
	       }
	     else
	       {
		  a++;
		  b++;
	       }
	     SetCurrentArea(a, b);
	  }
	else if (!strcmp(param1, "prev"))
	  {
	     GetCurrentArea(&a, &b);
	     word(params, 2, param2);
	     if ((param2) && (!strcmp(param2, "horiz")))
	       {
		  a--;
	       }
	     else if ((param2) && (!strcmp(param2, "vert")))
	       {
		  b--;
	       }
	     else
	       {
		  a--;
		  b--;
	       }
	     SetCurrentArea(a, b);
	  }
	else if (!strcmp(param1, "?"))
	  {
	     GetCurrentArea(&a, &b);
	     Esnprintf(buf, sizeof(buf), "Current Area: %d %d\n", a, b);
	  }
	else
	  {
	     sscanf(params, "%i %i", &a, &b);
	     SetCurrentArea(a, b);
	  }
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_WinOps(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;
   if (params)
     {

	char                windowid[FILEPATH_LEN_MAX];
	char                operation[FILEPATH_LEN_MAX];
	char                param1[FILEPATH_LEN_MAX];
	unsigned int        win;

	windowid[0] = 0;
	operation[0] = 0;
	param1[0] = 0;
	word(params, 1, windowid);
	sscanf(windowid, "%8x", &win);
	word(params, 2, operation);
	if (!operation)
	  {
	     Esnprintf(buf, sizeof(buf), "Error: no operation specified\n");
	  }
	else
	  {
	     EWin               *ewin;

	     ewin = FindEwinByChildren(win);
	     if (!ewin)
	       {
		  Esnprintf(buf, sizeof(buf), "Error: no such window: %8x\n",
			    win);
	       }
	     else
	       {
		  if (!strcmp(operation, "close"))
		    {
		       ICCCM_Delete(ewin);
		       ApplySclass(FindItem("SOUND_WINDOW_CLOSE", 0,
					 LIST_FINDBY_NAME, LIST_TYPE_SCLASS));
		    }
		  else if (!strcmp(operation, "annihiliate"))
		    {
		       EDestroyWindow(disp, ewin->client.win);
		       ApplySclass(FindItem("SOUND_WINDOW_CLOSE", 0,
					 LIST_FINDBY_NAME, LIST_TYPE_SCLASS));
		    }
		  else if (!strcmp(operation, "iconify"))
		    {
		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "on"))
			      {
				 if (!ewin->iconified)
				    IconifyEwin(ewin);
			      }
			    else if (!strcmp(param1, "off"))
			      {
				 if (ewin->iconified)
				    DeIconifyEwin(ewin);
			      }
			    else if (!strcmp(param1, "?"))
			      {
				 if (ewin->iconified)
				    Esnprintf(buf, sizeof(buf),
					      "window iconified: yes\n");
				 else
				    Esnprintf(buf, sizeof(buf),
					      "window iconified: no\n");
			      }
			    else
			      {
				 Esnprintf(buf, sizeof(buf),
					   "Error: unknown mode specified");
			      }
			 }
		       else
			 {
			    if (ewin->iconified)
			       DeIconifyEwin(ewin);
			    else
			       IconifyEwin(ewin);
			 }
		    }
		  else if (!strcmp(operation, "shade"))
		    {
		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "on"))
			      {
				 if (!ewin->shaded)
				    ShadeEwin(ewin);
			      }
			    else if (!strcmp(param1, "off"))
			      {
				 if (ewin->shaded)
				    UnShadeEwin(ewin);
			      }
			    else if (!strcmp(param1, "?"))
			      {
				 if (ewin->shaded)
				    Esnprintf(buf, sizeof(buf),
					      "window shaded: yes\n");
				 else
				    Esnprintf(buf, sizeof(buf),
					      "window shaded: no\n");
			      }
			    else
			      {
				 Esnprintf(buf, sizeof(buf),
					   "Error: unknown mode specified");
			      }
			 }
		       else
			 {
			    if (ewin->shaded)
			       UnShadeEwin(ewin);
			    else
			       ShadeEwin(ewin);
			 }
		    }
		  else if (!strcmp(operation, "stick"))
		    {
		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "on"))
			      {
				 if (!ewin->sticky)
				    MakeWindowSticky(ewin);
			      }
			    else if (!strcmp(param1, "off"))
			      {
				 if (ewin->sticky)
				    MakeWindowUnSticky(ewin);
			      }
			    else if (!strcmp(param1, "?"))
			      {
				 if (ewin->sticky)
				    Esnprintf(buf, sizeof(buf),
					      "window sticky: yes\n");
				 else
				    Esnprintf(buf, sizeof(buf),
					      "window sticky: no\n");
			      }
			    else
			      {
				 Esnprintf(buf, sizeof(buf),
					   "Error: unknown mode specified");
			      }
			 }
		       else
			 {
			    if (ewin->sticky)
			       MakeWindowUnSticky(ewin);
			    else
			       MakeWindowSticky(ewin);
			 }
		    }
		  else if (!strcmp(operation, "title"))
		    {
		       char               *ptr = strstr(params, "title");

		       if (ptr)
			  ptr += strlen("title");
		       if (ptr)
			 {
			    while (*ptr == ' ')
			       ptr++;
			    if (strlen(ptr))
			      {
				 if (!strncmp(ptr, "?", 1))
				   {
				      /* return the window title */
				      Esnprintf(buf, sizeof(buf),
						"window title: %s\n", ewin->client.title);
				   }
				 else
				   {
				      /* set the new title */
				      if (ewin->client.title)
					 Efree(ewin->client.title);
				      ewin->client.title = Emalloc((strlen(ptr) + 1) *
								sizeof(char));

				      strcpy(ewin->client.title, ptr);
				      DrawEwin(ewin);
				   }
			      }
			    else
			      {
				 /* error */
				 Esnprintf(buf, sizeof(buf),
					   "Error: no title specified\n");
			      }
			 }
		    }
		  else if (!strcmp(operation, "toggle_width"))
		    {
		       word(params, 3, param1);
		       MaxWidth(ewin, param1);
		    }
		  else if (!strcmp(operation, "toggle_height"))
		    {
		       word(params, 3, param1);
		       MaxHeight(ewin, param1);
		    }
		  else if (!strcmp(operation, "toggle_size"))
		    {
		       word(params, 3, param1);
		       MaxSize(ewin, param1);
		    }
		  else if (!strcmp(operation, "border"))
		    {
		       Border             *b;

		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "?"))
			      {
				 if (ewin->border)
				   {
				      if (ewin->border->name)
					{
					   Esnprintf(buf, sizeof(buf),
						     "window border: %s\n",
						     ewin->border->name);
					}
				   }
			      }
			    else
			      {
				 b = (Border *) FindItem(param1, 0,
					  LIST_FINDBY_NAME, LIST_TYPE_BORDER);
				 if ((b) && (b != ewin->border))
				   {
				      ewin->border_new = 1;
				      SetEwinToBorder(ewin, b);
				      ICCCM_MatchSize(ewin);
				      MoveResizeEwin(ewin, ewin->x, ewin->y,
					      ewin->client.w, ewin->client.h);
				   }
			      }
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf),
				      "Error: no border specified\n");
			 }
		    }
		  else if (!strcmp(operation, "desk"))
		    {
		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "next"))
			      {
				 DesktopRemoveEwin(ewin);
				 MoveEwinToDesktop(ewin, ewin->desktop + 1);
				 RaiseEwin(ewin);
				 ICCCM_Configure(ewin);
				 ewin->sticky = 0;
			      }
			    else if (!strcmp(param1, "prev"))
			      {
				 DesktopRemoveEwin(ewin);
				 MoveEwinToDesktop(ewin, ewin->desktop - 1);
				 RaiseEwin(ewin);
				 ICCCM_Configure(ewin);
				 ewin->sticky = 0;
			      }
			    else if (!strcmp(param1, "?"))
			      {
				 Esnprintf(buf, sizeof(buf),
					   "window desk: %d\n", ewin->desktop);
			      }
			    else
			      {
				 DesktopRemoveEwin(ewin);
				 MoveEwinToDesktop(ewin, atoi(param1));
				 RaiseEwin(ewin);
				 ICCCM_Configure(ewin);
				 ewin->sticky = 0;
			      }
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf),
				      "Error: no desktop supplied\n");
			 }
		    }
		  else if (!strcmp(operation, "area"))
		    {
		       int                 a, b;

		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "?"))
			      {
				 Esnprintf(buf, sizeof(buf),
					 "window area: %d %d\n", ewin->area_x,
					   ewin->area_y);
			      }
			    else
			      {
				 sscanf(params, "%*s %*s %i %i", &a, &b);
				 MoveEwinToArea(ewin, a, b);
			      }
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf),
				      "Error: no area supplied\n");
			 }
		    }
		  else if (!strcmp(operation, "raise"))
		    {
		       RaiseEwin(ewin);
		    }
		  else if (!strcmp(operation, "lower"))
		    {
		       LowerEwin(ewin);
		    }
		  else if (!strcmp(operation, "move"))
		    {
		       int                 a, b;

		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "?"))
			      {
				 Esnprintf(buf, sizeof(buf),
					   "window location: %d %d\n", ewin->x,
					   ewin->y);
			      }
			    else if (!strcmp(param1, "??"))
			      {
				 Esnprintf(buf, sizeof(buf),
					   "client location: %d %d\n",
					   ewin->x + ewin->border->border.left,
					   ewin->y + ewin->border->border.top);
			      }
			    else
			      {
				 sscanf(params, "%*s %*s %i %i", &a, &b);
				 MoveResizeEwin(ewin, a, b, ewin->client.w,
						ewin->client.h);
			      }
			 }
		       else
			 {
			    Esnprintf(buf, sizeof(buf),
				      "Error: no coords supplied\n");
			 }
		    }
		  else if (!strcmp(operation, "resize"))
		    {
		       int                 a, b;

		       word(params, 3, param1);
		       if (param1[0])
			 {
			    if (!strcmp(param1, "?"))
			      {
				 Esnprintf(buf, sizeof(buf),
				       "window size: %d %d\n", ewin->client.w,
					   ewin->client.h);
			      }
			    else if (!strcmp(param1, "??"))
			      {
				 Esnprintf(buf, sizeof(buf),
				     "frame size: %d %d\n", ewin->w, ewin->h);
			      }
			    else
			      {
				 sscanf(params, "%*s %*s %i %i", &a, &b);
				 MoveResizeEwin(ewin, ewin->x, ewin->y, a, b);
			      }
			 }
		    }
		  else if (!strcmp(operation, "move_relative"))
		    {
		       int                 a, b;

		       word(params, 3, param1);
		       if (param1[0])
			 {
			    sscanf(params, "%*s %*s %i %i", &a, &b);
			    a += ewin->x;
			    b += ewin->y;
			    MoveResizeEwin(ewin, a, b, ewin->client.w,
					   ewin->client.h);
			 }
		    }
		  else if (!strcmp(operation, "resize_relative"))
		    {
		       int                 a, b;

		       word(params, 3, param1);
		       if (param1[0])
			 {
			    sscanf(params, "%*s %*s %i %i", &a, &b);
			    a += ewin->client.w;
			    b += ewin->client.h;
			    MoveResizeEwin(ewin, ewin->x, ewin->y, a, b);
			 }
		    }
		  else if (!strcmp(operation, "focus"))
		    {
		       word(params, 3, param1);
		       if (!strcmp(param1, "?"))
			 {
			    if (ewin == GetFocusEwin())
			      {
				 Esnprintf(buf, sizeof(buf), "focused: yes\n");
			      }
			    else
			      {
				 Esnprintf(buf, sizeof(buf), "focused: no\n");
			      }
			 }
		       else
			 {
			    FocusToEWin(ewin);
			 }
		    }
		  else
		    {
		       Esnprintf(buf, sizeof(buf),
				 "Error: unknown operation\n");
		    }
	       }
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no window specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_NumAreas(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;
   if (params)
     {
	if (!strcmp(params, "?"))
	  {
	     int                 ax, ay;

	     GetAreaSize(&ax, &ay);
	     Esnprintf(buf, sizeof(buf), "Number of Areas: %d %d\n",
		       ax, ay);
	  }
	else
	  {
	     char                ax[128], ay[128];

	     word(params, 1, ax);
	     word(params, 2, ay);
	     SetNewAreaSize(atoi(ax), atoi(ay));
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: number of areas not given\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_NumDesks(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;
   if (params)
     {
	if (!strcmp(params, "?"))
	  {
	     Esnprintf(buf, sizeof(buf), "Number of Desks: %d\n",
		       mode.numdesktops);
	  }
	else
	  {
	     ChangeNumberOfDesktops(atoi(params));
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: number of desks not given\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_FocusMode(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;
   if (params)
     {
	if (!strcmp(params, "click"))
	  {
	     mode.focusmode = 2;
	     mode.click_focus_grabbed = 1;
	  }
	else if (!strcmp(params, "pointer"))
	  {
	     mode.focusmode = 0;
	  }
	else if (!strcmp(params, "sloppy"))
	  {
	     mode.focusmode = 1;
	  }
	else if (!strcmp(params, "clicknograb"))
	  {
	     mode.focusmode = 2;
	     mode.click_focus_grabbed = 0;
	  }
	else if (!strcmp(params, "?"))
	  {
	     Esnprintf(buf, sizeof(buf), "Focus Mode: ");
	     if (mode.focusmode == 2)
	       {
		  if (mode.click_focus_grabbed)
		    {
		       strcat(buf, "click\n");
		    }
		  else
		    {
		       strcat(buf, "clicknograb\n");
		    }
	       }
	     else if (mode.focusmode == 1)
	       {
		  strcat(buf, "sloppy\n");
	       }
	     else if (mode.focusmode == 0)
	       {
		  strcat(buf, "pointer\n");
	       }
	     else
	       {
		  strcat(buf, "unknown\n");
	       }
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown focus type\n");
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no focus type given\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_ShowIcons(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;
   if (params)
     {
	if (!strcmp(params, "on"))
	  {
	     mode.showicons = 1;
	     ShowIcons();
	  }
	else if (!strcmp(params, "off"))
	  {
	     mode.showicons = 0;
	     HideIcons();
	  }
	else if (!strcmp(params, "?"))
	  {
	     Esnprintf(buf, sizeof(buf), "Icons: ");
	     if (mode.showicons)
		strcat(buf, "on\n");
	     else
		strcat(buf, "off\n");
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Error: unknown icon statee: %s\n",
		       params);
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no icon state specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_GotoDesktop(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;
   if (!params)
     {
	Esnprintf(buf, sizeof(buf), "Error: no desktop selected\n");
     }
   else
     {
	if (!strcmp(params, "next"))
	  {
	     doNextDesktop(NULL);
	  }
	else if (!strcmp(params, "prev"))
	  {
	     doPrevDesktop(NULL);
	  }
	else if (!strcmp(params, "?"))
	  {
	     Esnprintf(buf, sizeof(buf), "Current Desktop: %d\n",
		       desks.current);
	  }
	else
	  {
	     GotoDesktop(atoi(params));
	  }
     }

   if (buf[0])
      CommsSend(c, buf);

   return;
}

void
IPC_ListThemes(char *params, Client * c)
{

   char              **list, *buf = NULL;
   int                 i, num;

   params = NULL;
   list = ListThemes(&num);
   for (i = 0; i < num; i++)
     {
	if (buf)
	  {
	     buf = Erealloc(buf, strlen(buf) + strlen(list[i]) + 2);
	  }
	else
	  {
	     buf = Emalloc(strlen(list[i]) + 2);
	     buf[0] = 0;
	  }
	strcat(buf, list[i]);
	strcat(buf, "\n");
     }

   if (list)
      freestrlist(list, num);

   if (buf)
     {
	CommsSend(c, buf);
	Efree(buf);
     }
   else
     {
	CommsSend(c, "");
     }

   return;

}

void
IPC_SMFile(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (params)
     {
	if (!strcmp(params, "?"))
	  {
	     Esnprintf(buf, sizeof(buf), GetSMFile());
	  }
	else
	  {
	     SetSMFile(params);
	  }
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no file prefix specified\n");
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_ForceSave(char *params, Client * c)
{

   c = NULL;
   params = NULL;

   if (mode.autosave)
/*    SaveUserControlConfig(fopen(GetSMFile(), "w")); */
      SaveUserControlConfig(fopen(GetGenericSMFile(), "w"));
   else
/*    rm(GetSMFile()); */
      rm(GetGenericSMFile());
   return;
}

void
IPC_Restart(char *params, Client * c)
{

   c = NULL;
   params = NULL;

   doExit("restart");

}

void
IPC_RestartWM(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   if (params)
     {
	Esnprintf(buf, sizeof(buf), "restart_wm %s", params);
	params = NULL;
	doExit(buf);
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no window manager specified\n");
	CommsSend(c, buf);
     }

   return;

}

void
IPC_RestartTheme(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   if (params)
     {
	Esnprintf(buf, sizeof(buf), "restart_theme %s", params);
	params = NULL;
	doExit(buf);
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Error: no theme specified\n");
	CommsSend(c, buf);
     }
   return;
}

void
IPC_Exit(char *params, Client * c)
{

   c = NULL;

   if (params)
      doExit("quit");
   else
      doExit("logout");
   return;

}

void
IPC_DefaultTheme(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (!params)
      return;

   if (!strcmp(params, "?"))
     {
	Esnprintf(buf, sizeof(buf), "%s\n", GetDefaultTheme());
     }
   else
     {
	if (exists(params))
	  {
	     char                restartcommand[FILEPATH_LEN_MAX];

	     SetDefaultTheme(params);
	     Esnprintf(restartcommand, sizeof(restartcommand),
		       "restart_theme %s", params);
	     doExit(restartcommand);
	  }
	else
	  {
	     Esnprintf(buf, sizeof(buf), "Could not find theme: %s\n",
		       GetDefaultTheme());
	  }
     }

   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_AutoSave(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   buf[0] = 0;

   if (!params)
      return;

   if (!strcmp(params, "?"))
     {
	if (mode.autosave)
	   Esnprintf(buf, sizeof(buf), "Autosave : on\n");
	else
	   Esnprintf(buf, sizeof(buf), "Autosave : off\n");
     }
   else if (!strcmp(params, "on"))
     {
	mode.autosave = 1;
     }
   else if (!strcmp(params, "off"))
     {
	mode.autosave = 0;
     }
   else
     {
	Esnprintf(buf, sizeof(buf), "Unknown autosave state: %s\n", params);
     }
   if (buf[0])
      CommsSend(c, buf);

   return;

}

void
IPC_Help(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];
   char                buf2[FILEPATH_LEN_MAX];
   int                 i, j, numIPC;
   unsigned int        k;
   char              **commandname_list;

   buf[0] = 0;
   buf2[0] = 0;
   numIPC = sizeof(IPCArray) / sizeof(IPCStruct);
   Esnprintf(buf, sizeof(buf), "Enlightenment IPC Commands Help");

   if (!params)
     {
	strcat(buf, "\ncommands currently available:\n");
	strcat(buf, "use \"help all\" for descriptions of each command\n"
	       "use \"help <command>\" for an individual description\n\n");

	commandname_list = Emalloc(numIPC * sizeof(char *));

	for (i = 0; i < numIPC; i++)
	   commandname_list[i] = IPCArray[i].commandname;

	Quicksort((void **)commandname_list, 0, numIPC - 1,
		  (int (*)(void *, void *))&strcmp);

	i = 0;
	while (i < numIPC)
	  {
	     for (j = 0; j < 3; j++)
	       {
		  strcat(buf2, commandname_list[i]);

		  /* suggest some parens here */
		  for (k = 0; k < 3 - strlen(commandname_list[i]) / 8; k++)
		     strcat(buf2, "\t");

		  if (++i >= numIPC)
		     break;
	       }

	     strcat(buf, buf2);
	     strcat(buf, "\n");
	     buf2[0] = 0;
	  }

	Efree(commandname_list);
     }
   else
     {
	if (!strcmp(params, "all"))
	  {
	     strcat(buf, "\ncommands currently available:\n");
	     strcat(buf, "use \"help <command>\" "
		    "for an individual description\n");
	     strcat(buf, "<command> : <description>\n");
	     for (i = 0; i < numIPC; i++)
	       {
		  strcat(buf, IPCArray[i].commandname);
		  strcat(buf, " : ");
		  strcat(buf, IPCArray[i].help_text);
		  strcat(buf, "\n");
	       }
	  }
	else
	  {
	     int                 found = 0;

	     for (i = 0; i < numIPC; i++)
	       {
		  if (!strcmp(IPCArray[i].commandname, params))
		    {
		       found = 1;
		       strcat(buf, " : ");
		       strcat(buf, IPCArray[i].commandname);
		       strcat(buf, "\n--------------------------------\n");
		       strcat(buf, IPCArray[i].help_text);
		       strcat(buf, "\n");
		       if (IPCArray[i].extended_help_text)
			 {
			    strcat(buf, IPCArray[i].extended_help_text);
			    strcat(buf, "\n");
			 }
		    }
	       }
	  }
     }

   if (buf)
      CommsSend(c, buf);

   return;
}

void
IPC_Copyright(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   params = NULL;
   Esnprintf(buf, sizeof(buf),
	     "Copyright (C) 1999 Carsten Haitzler and Geoff Harrison,\n"
	     "with various contributors (Isaac Richards, Sung-Hyun Nam, "
	     "Kimball Thurston,\n"
	     "Michael Kellen, Frederic Devernay, Felix Bellaby, "
	     "Michael Jennings,\n"
	     "Christian Kreibich, Peter Kjellerstedt and others)\n\n"
	     "Permission is hereby granted, free of charge, to "
	     "any person obtaining a copy\n"
	     "of this software and associated documentation files "
	     "(the \"Software\"), to\n"
	     "deal in the Software without restriction, including "
	     "without limitation the\n"
	     "rights to use, copy, modify, merge, publish, distribute, "
	     "sub-license, and/or\n"
	     "sell copies of the Software, and to permit persons to "
	     "whom the Software is\n"
	     "furnished to do so, subject to the following conditions:\n\n"
	     "The above copyright notice and this permission notice "
	     "shall be included in\n"
	     "all copies or substantial portions of the Software.\n\n"
	     "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF "
	     "ANY KIND, EXPRESS OR\n"
	     "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF "
	     "MERCHANTABILITY,\n"
	     "FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. "
	     "IN NO EVENT SHALL\n"
	     "THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
	     "LIABILITY, WHETHER\n"
	     "IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
	     "OUT OF OR IN\n"
	     "CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS "
	     "IN THE SOFTWARE.\n"
      );

   if (buf)
      CommsSend(c, buf);

   return;

}

void
IPC_Version(char *params, Client * c)
{

   char                buf[FILEPATH_LEN_MAX];

   params = NULL;

   buf[0] = 0;

   Esnprintf(buf, sizeof(buf),
	     "Enlightenment Version : %s\n"
	     "code is current to    : %s\n",
	     ENLIGHTENMENT_VERSION, E_CHECKOUT_DATE);
   /* Esnprintf(buf, sizeof(buf),
    * "Enlightenment Version : %s\n"
    * "Release Date          : Wednesday March 17, 1999\n",
    * ENLIGHTENMENT_VERSION);
    */

   if (buf)
      CommsSend(c, buf);

   return;

}

/* The IPC Handler */
/* this is the function that actually loops through the IPC array
 * and finds the command that you were trying to run, and then executes it.
 * you shouldn't have to touch this function
 * - Mandrake
 */

int
HandleIPC(char *params, Client * c)
{

   int                 i;
   int                 numIPC;
   char                w[FILEPATH_LEN_MAX];

   numIPC = sizeof(IPCArray) / sizeof(IPCStruct);

   word(params, 1, w);
   for (i = 0; i < numIPC; i++)
     {
	if (!strcmp(w, IPCArray[i].commandname))
	  {
	     word(params, 2, w);
	     if (w)
	       {
		  IPCArray[i].func(atword(params, 2), c);
	       }
	     else
	       {
		  IPCArray[i].func(NULL, c);
	       }
	     return 1;
	  }
     }

   return 0;
}

/* The External function designed for attaching to a dialog box
 * to return a message back to an external app telling you what
 * button was depressed
 */

void
ButtonIPC(int val, void *data)
{

   val = 0;
   data = NULL;

   return;
}
