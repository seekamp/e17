AUTOMAKE_OPTIONS = 1.4 foreign

MAINTAINERCLEANFILES = Makefile.in

if BUILD_MODULE_ECORE_FILE
if !EINA_STATIC_BUILD_ECORE_FILE

INCLUDES = -I. -I$(top_srcdir)/src/include @ECORE_FILE_CFLAGS@

pkgdir = $(libdir)/elixir/bindings/ecore-file/$(MODULE_ARCH)

pkg_LTLIBRARIES = module.la

module_la_SOURCES = 

module_la_LIBADD = $(top_builddir)/src/lib/libelixir.la @ECORE_FILE_LIBS@
module_la_LDFLAGS = -module -avoid-version -L$(tob_buildir)/src/lib -L$(top_buildir)/src/lib/.libs
module_la_DEPENDENCIES = $(top_builddir)/config.h

endif
endif

EXTRA_DIST = 
