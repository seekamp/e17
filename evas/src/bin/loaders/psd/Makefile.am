
MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
-I. \
-I$(top_srcdir)/src/lib \
-I$(top_srcdir)/src/lib/include \
-I$(top_srcdir)/src/lib/cserve2 \
-I$(top_srcdir)/src/bin \
@EVAS_GENERAL_CFLAGS@ \
@EVIL_CFLAGS@

if BUILD_LOADER_PSD
#if !EVAS_STATIC_BUILD_PSD

pkgdir = $(libdir)/evas/cserve2/loaders/psd/$(MODULE_ARCH)
pkg_LTLIBRARIES = module.la

module_la_SOURCES = evas_image_load_psd.c

module_la_LIBADD = @EVAS_GENERAL_LIBS@ @EVIL_LIBS@
module_la_LDFLAGS = -no-undefined @lt_enable_auto_import@ -module -avoid-version
module_la_LIBTOOLFLAGS = --tag=disable-static

#else

#noinst_LTLIBRARIES = libevas_loader_psd.la
#libevas_loader_psd_la_SOURCES = evas_image_load_psd.c
#libevas_loader_psd_la_LIBADD =

#endif
endif
