ACLOCAL_AMFLAGS = -I m4
AM_MAKEFLAGS = --no-print-directory
EXTRA_DIST = \
	AUTHORS \
	COPYING \
	README \
	autogen.sh \
	econnman-bin.in

dist_bin_SCRIPTS = econnman-bin

econnman-bin: $(top_srcdir)/econnman-bin.in $(top_builddir)/Makefile
	rm -f $(top_builddir)/econnman-bin
	sed -e 's:@PKGDATADIR@:$(pkgdatadir):g' \
		$(top_srcdir)/econnman-bin.in > $(top_builddir)/econnman-bin
	chmod +x $(top_builddir)/econnman-bin

desktopdir = $(datadir)/applications
desktop_DATA = \
	data/desktop/econnman-agent.desktop \
	data/desktop/econnman.desktop

EXTRA_DIST += $(desktop_DATA)

EDJE_CC = @edje_cc@
EDJE_FLAGS_VERBOSE_ =
EDJE_FLAGS_VERBOSE_0 =
EDJE_FLAGS_VERBOSE_1 = -v
EDJE_FLAGS = $(EDJE_FLAGS_VERBOSE_$(V)) -id $(top_srcdir)/data/theme -fd $(top_srcdir)/data/theme
AM_V_EDJ = $(am__v_EDJ_$(V))
am__v_EDJ_ = $(am__v_EDJ_$(AM_DEFAULT_VERBOSITY))
am__v_EDJ_0 = @echo "  EDJ   " $@;

THEME_IMAGES = \
data/theme/connman-connected.png \
data/theme/connman-ethernet.png \
data/theme/connman-favorite.png \
data/theme/connman-lock.png \
data/theme/connman-tech-connected.png \
data/theme/connman-tech-offline.png \
data/theme/connman-tech-powered.png \
data/theme/connman-wifi-bad.png \
data/theme/connman-wifi-good.png \
data/theme/connman-wifi-medium.png \
data/theme/connman-bluetooth.png \
data/theme/connman-cellular.png


themedir = $(pkgdatadir)/theme
theme_DATA = data/theme/default.edj

EXTRA_DIST += data/theme/default.edc $(THEME_IMAGES)

data/theme/default.edj: $(top_builddir)/Makefile $(top_srcdir)/data/theme/default.edc $(THEME_IMAGES)
	$(MKDIR_P) $(top_builddir)/data/theme
	$(AM_V_EDJ)$(EDJE_CC) $(EDJE_FLAGS) \
	$(top_srcdir)/data/theme/default.edc \
	$(top_builddir)/data/theme/default.edj

clean-local:
	rm -f $(top_builddir)/data/theme/default.edj
	rm -f $(top_builddir)/econnman-bin

MAINTAINERCLEANFILES = \
	aclocal.m4 \
	configure \
	depcomp \
	INSTALL \
	install-sh \
	Makefile.in \
	missing

