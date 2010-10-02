bin_PROGRAMS= plugins_test
plugins_test_SOURCES= plugins_test.cpp
plugins_test_LDADD=-ldl
plugins_test_LDFLAGS=-Wl,-R $(abs_top_srcdir)/plugins/

lib_LTLIBRARIES=libbforce.la
libbforce_la_SOURCES=bodyforce.cpp bodyforce.h
libbforce_la_LDFLAGS=-avoid-version -module -shared

bin_SCRIPTS= compile.tcl

compile.tcl: compile.tmp.tcl
	sed \
	-e 's,{CXX},$(CXX),g' \
	-e 's,{CPPFLAGS},$(CXXFLAGS),g' \
	-e 's,{CXXFLAGS},$(CXXFLAGS),g' \
	-e 's,{LDFLAGS},$(LDFLAGS),g' \
	-e 's,{LIBS},$(LDFLAGS),g' \
	$< > $@