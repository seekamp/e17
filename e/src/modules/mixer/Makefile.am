MAINTAINERCLEANFILES = Makefile.in
MODULE = mixer

# data files for the module
filesdir = $(libdir)/enlightenment/modules/$(MODULE)
files_DATA = e-module-$(MODULE).edj module.desktop

EXTRA_DIST = $(files_DATA)

# the module .so file
INCLUDES          = -I. \
                    -I$(top_srcdir) \
                    -I$(top_srcdir)/src/modules/$(MODULE) \
                    -I$(top_srcdir)/src/bin \
                    -I$(top_builddir)/src/bin \
                    -I$(top_srcdir)/src/modules \
                    @e_cflags@ @SOUND_CFLAGS@
if HAVE_ENOTIFY
INCLUDES          += @ENOTIFY_CFLAGS@
endif

pkgdir            = $(libdir)/enlightenment/modules/$(MODULE)/$(MODULE_ARCH)
pkg_LTLIBRARIES   = module.la

module_la_SOURCES = e_mod_main.h \
		    Pulse.h \
		    pa.h \
		    e_mod_main.c \
                    e_mod_system.h \
                    conf_gadget.c \
                    conf_module.c \
                    sys_pulse.c \
                    app_mixer.c \
                    msg.c \
                    pa.c \
                    serial.c \
                    sink.c \
                    tag.c

if HAVE_ALSA
module_la_SOURCES += sys_alsa.c
else
module_la_SOURCES += sys_dummy.c
endif

module_la_LIBADD       = @SOUND_LIBS@ @e_libs@ @dlopen_libs@
if HAVE_ENOTIFY
module_la_LIBADD       += @ENOTIFY_LIBS@
endif

module_la_LDFLAGS      = -module -avoid-version
module_la_DEPENDENCIES = $(top_builddir)/config.h

uninstall:
	rm -rf $(DESTDIR)$(libdir)/enlightenment/modules/$(MODULE)
