#include "main.h"

#define SOFT_X    0
#define FB        1
#define GL_X      2
#define XRENDER_X 3

Eina_Prefix *pfx = NULL;
Ecore_Evas  *ee = NULL;
Evas        *evas = NULL;
int          im_cache = 4096 * 1024;
int          fn_cache = 512 * 1024;
int          engine = SOFT_X;
int          scr_w, scr_h;
int          flags;
char        *method;
int          clean_vt_lose = 0;

static char *theme = NULL;

static Eina_Bool  _cb_exit(void *data, int ev_type, void *ev);
static void _cb_delete_request(Ecore_Evas *ee);
static void _cb_resize(Ecore_Evas *ee);
static Eina_Bool _cb_idle_enterer(void *data);
static int  _args(void);


int
main(int argc, char **argv)
{
   if (!eina_init()) return -1;
   if (!ecore_init()) return -1;
   ecore_app_args_set(argc, (const char **)argv);
   ecore_event_handler_add(ECORE_EVENT_SIGNAL_EXIT, _cb_exit, NULL);
   if (!ecore_evas_init()) return -1;
   if (!edje_init()) return -1;

   pfx = eina_prefix_new(argv[0], main, "EXQUISITE", "exquisite", 
                         "data/themes/default.edj",
                         PACKAGE_BIN_DIR, PACKAGE_LIB_DIR, 
                         PACKAGE_DATA_DIR, PACKAGE_DATA_DIR);
   if (!pfx) return -1;
   _args();

   theme_init(theme);

   ecore_idle_enterer_add(_cb_idle_enterer, NULL);
   ecore_main_loop_begin();

   ipc_shutdown();
   theme_shutdown();

   edje_shutdown();
   ecore_evas_shutdown();
   ecore_shutdown();
   eina_prefix_free(pfx);
   eina_shutdown();
   return 0;
}

static Eina_Bool
_cb_exit(void *data, int ev_type, void *ev)
{
   ecore_main_loop_quit();
   return EINA_TRUE;
}

static void
_cb_theme_exit_done(void *data)
{
   ecore_main_loop_quit();
}

static void
_cb_delete_request(Ecore_Evas *ee)
{
   if (clean_vt_lose)
     theme_exit(_cb_theme_exit_done, NULL);
   else
     ecore_main_loop_quit();
}

static void
_cb_resize(Ecore_Evas *ee)
{
   evas_output_viewport_get(evas, NULL, NULL, &scr_w, &scr_h);
   theme_resize();
}

static Eina_Bool
_cb_idle_enterer(void *data)
{
   ipc_init();
   return EINA_FALSE;
}

static void
_cb_fb_lose(void *data)
{
   if (clean_vt_lose)
     theme_exit(_cb_theme_exit_done, NULL);
   else
     ecore_main_loop_quit();
}
    
static int
_args(void)
{
   int argc;
   char **argv;
   char buf[PATH_MAX];
   int i;
   
   int w = 640;
   int h = 480;
   double fps = 60.0;
   int fullscreen = 0;
   int rot = 0;
   flags = EXQUISITE_FLAG_QUIET;
   method = NULL;

   ecore_app_args_get(&argc, &argv);
   for (i = 1; i < argc; i++)
     {
	if      (!strcmp(argv[i], "-x11")) engine = SOFT_X;
	else if (!strcmp(argv[i], "-gl"))  engine = GL_X;
	else if (!strcmp(argv[i], "-fb"))  engine = FB;
	else if (!strcmp(argv[i], "-xr"))  engine = XRENDER_X;
        else if (!strcmp(argv[i], "-fs")) fullscreen = 1;
	else if ((!strcmp(argv[i], "-t")) && (i < (argc - 1)))
	  {
	     i++;
	     theme = argv[i];
	  }
	else if ((!strcmp(argv[i], "-x")) && (i < (argc - 1)))
	  {
	     i++;
	     w = atoi(argv[i]);
	  }
	else if ((!strcmp(argv[i], "-y")) && (i < (argc - 1)))
	  {
	     i++;
	     h = atoi(argv[i]);
	  }
	else if ((!strcmp(argv[i], "-rot")) && (i < (argc - 1)))
	  {
	     i++;
	     rot = atoi(argv[i]);
	  }
        else if ((!strcmp(argv[i], "-cleanvt")))
          {
             clean_vt_lose = 1;
          }
	else if ((!strcmp(argv[i], "-ic")) && (i < (argc - 1)))
	  {
	     i++;
	     im_cache = atoi(argv[i]);
	     if ((im_cache < 0) || (im_cache > 65536 * 1024))
	       {
		  printf("Invalid image cache value. use between 0 and 65536\n");
		  exit(-1);
	       }
	  }
	else if ((!strcmp(argv[i], "-fc")) && (i < (argc - 1)))
	  {
	     i++;
	     fn_cache = atoi(argv[i]);
	     if ((fn_cache < 0) || (fn_cache > 65536 * 1024))
	       {
		  printf("Invalid font cache value. use between 0 and 65536\n");
		  exit(-1);
	       }
	  }
	else if ((!strcmp(argv[i], "-fps")) && (i < (argc - 1)))
	  {
	     i++;
	     fps = atof(argv[i]);
	     if (fps <= 0.0)
	       {
		  printf("Invalid fps value. must be greater than 0.0\n");
		  exit(-1);
	       }
	  }
        else if ((!strcmp(argv[i], "-verbose")))
          {
             flags &= ~EXQUISITE_FLAG_QUIET;
          }
        else if ((!strcmp(argv[i], "-ipc")))
          {
             // Read next arg as ipc method
             if (i++ > argc) exit(0);
             method = strdup(argv[i]);
          }
	else if ((!strcmp(argv[i], "-h")))
	  {
	     printf("%s [OPTIONS]\n"
		    "Where OPTIONS is 0 or more of the following:\n"
		    "\n"
		    "-x11         Display using software X11\n"
		    "-gl          Display using OpenGL in X11\n"
		    "-fb          Display using Framebuffer\n"
		    "-xr          Display using XRender\n"
		    "-fs          Display fullscreen (use current screen res)\n" 
		    "-t theme     Use Theme file 'theme'\n"
		    "-x res       Use horizontal res 'res'\n"
		    "-y res       Use vertical res 'res'\n" 
		    "-rot deg     Use rotation 'deg' if supported by engine (0, 90, 180, 270)\n"
		    "-ic Kb       Set image cache in Kb\n"
		    "-fc Kb       Set font cache in Kb\n"
		    "-fps fps     Set attempted framerate in frames per second\n"
		    "-verbose     Run Exquisite in verbose mode\n"
                    "-ipc [mode]  Choose ipc mechanism (fifo [default], socket, abstract_socket)\n"
		    "-cleanvt     On VT change signal, show end anim before giving up the VT\n"
		    "-h           Display this help\n"
		    "\n"
		    "Notes:\n"
		    "\n"
		    "You can also set the EXQUISITE_IPC environment variable\n"
		    "to give a fill path to any file to be used as the base\n"
		    "filename of the IPC socket to be used between exquisite\n"
		    "and exquisitie-write for communication.\n"
		    , argv[0]);
	     exit(0);
	  }
     }

   if (engine == SOFT_X)
     ee = ecore_evas_software_x11_new(NULL, 0, 0, 0, w, h);
   else if (engine == GL_X)
     ee = ecore_evas_gl_x11_new(NULL, 0, 0, 0, w, h);
   else if (engine == FB)
     {
        ee = ecore_evas_fb_new(NULL, rot, w, h);
#ifdef HAVE_ECORE_FB
        /* exit on first vt switch away */
        ecore_fb_callback_lose_set(_cb_fb_lose, NULL);
#endif        
     }
   else if (engine == XRENDER_X)
     ee = ecore_evas_xrender_x11_new(NULL, 0, 0, 0, w, h);
   if (!ee)
     {
	printf("Error. Cannot create canvas. Abort.\n");
	exit(-1);
     }

   ecore_evas_rotation_set(ee, rot);
   ecore_evas_size_min_set(ee, w, h);
   ecore_evas_size_max_set(ee, w, h);
   ecore_evas_callback_resize_set(ee, _cb_resize);
   ecore_evas_callback_delete_request_set(ee, _cb_delete_request);
   ecore_evas_title_set(ee, "Exquisite Window");
   ecore_evas_name_class_set(ee, "exquisite", "Exquisite");
   if (fullscreen)
     {
	ecore_evas_fullscreen_set(ee, 1);
	ecore_evas_cursor_set(ee, "", 999, 0, 0);
     }
   ecore_evas_show(ee);
   evas = ecore_evas_get(ee);
   evas_output_viewport_get(evas, NULL, NULL, &scr_w, &scr_h);
   evas_image_cache_set(evas, im_cache);
   evas_font_cache_set(evas, fn_cache);
   snprintf(buf, sizeof(buf), "%s/data/fonts", eina_prefix_data_get(pfx));
   evas_font_path_append(evas, buf);
   edje_frametime_set(1.0 / fps);
   return 1;
}
