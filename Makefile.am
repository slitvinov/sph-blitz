##incluse m4 macros
ACLOCAL_AMFLAGS = -I m4
SUBDIRS=src

EXTRA_DIST = scripts/start.in scripts/sphrmcm.in \
	cases/*.cfg poly.plg \
	polymer.cfg \
	Doxyfile

start.sh: scripts/start.in
	cp $< $@
	chmod +x $@

awk/sphrmcm.awk: scripts/sphrmcm.in
	-mkdir awk
	cp $< $@
	chmod +x $@

