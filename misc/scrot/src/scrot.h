/* feh.h

Copyright (C) 1999,2000 Tom Gilbert.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies of the Software and its documentation and acknowledgment shall be
given in the documentation and software packages that this Software was
used.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef FEH_H
#define FEH_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xos.h>
#include <X11/keysym.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <dirent.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/wait.h>
#include <Imlib2.h>

#include "structs.h"
#include "utils.h"
#include "getopt.h"
#include "debug.h"

#ifndef __GNUC__
# define __attribute__(x)
#endif

typedef void (*sighandler_t) (int);

void show_usage(void);
void show_version(void);
void init_x_and_imlib(void);
void show_mini_usage(void);
char *chop_file_from_full_path(char *str);
void show_mini_usage(void);
Imlib_Image scrot_grab_shot(void);
void scrot_exec_app(void);

/* Imlib stuff */
extern Display *disp;
extern Visual *vis;
extern Colormap cm;
extern int depth;
extern Atom wmDeleteWindow;

/* Thumbnail sizes */
extern Window root;
extern Screen *scr;
extern int call_level;

#endif
