MAINTAINERCLEANFILES = Makefile.in
MODULE = conf_display

# data files for the module
filesdir = $(libdir)/enlightenment/modules/$(MODULE)
files_DATA = \
module.desktop

EXTRA_DIST = $(files_DATA)

# the module .so file
INCLUDES               = -I. \
                         -I$(top_srcdir) \
                         -I$(top_srcdir)/src/modules/$(MODULE) \
                         -I$(top_srcdir)/src/bin \
                         -I$(top_builddir)/src/bin \
                         -I$(top_srcdir)/src/modules \
                         @e_cflags@
pkgdir                 = $(libdir)/enlightenment/modules/$(MODULE)/$(MODULE_ARCH)
pkg_LTLIBRARIES        = module.la
module_la_SOURCES      = e_mod_main.c \
                         e_mod_main.h \
                         e_int_config_display.c \
                         e_int_config_display.h \
                         e_int_config_screensaver.c \
                         e_int_config_screensaver.h \
                         e_int_config_dpms.c \
                         e_int_config_dpms.h \
                         e_int_config_desklock.c \
                         e_int_config_desklock.h \
                         e_int_config_desklock_fsel.c \
                         e_int_config_desklock_fsel.h \
                         e_int_config_desks.c \
                         e_int_config_desks.h \
                         e_int_config_desk.c \
                         e_int_config_desk.h
                                                  
module_la_LIBADD       = @e_libs@ @dlopen_libs@
module_la_LDFLAGS      = -module -avoid-version
module_la_DEPENDENCIES = $(top_builddir)/config.h

uninstall:
	rm -rf $(DESTDIR)$(libdir)/enlightenment/modules/$(MODULE)
