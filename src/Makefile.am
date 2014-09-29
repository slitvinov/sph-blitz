bin_PROGRAMS = sphopt

# dist_DATA= $(CASEDIR)/test-2.cfg \
# 	$(CASEDIR)/test-couette.cfg \
# 	$(CASEDIR)/test-marco.cfg \
# 	$(CASEDIR)/test-old.cfg \
# 	$(CASEDIR)/test-p.cfg \
# 	$(CASEDIR)/test-poiseuille.cfg \
# 	$(CASEDIR)/test.cfg

sphopt_SOURCES = abspolymercreator.cpp abspolymercreator.h\
	betaspline.cpp betaspline.h\
	boundary.cpp boundary.h\
	boundarystruct.cpp boundarystruct.h\
	command.cpp command.h\
	compositedatacollector.cpp compositedatacollector.h\
	ConfigFile.cpp ConfigFile.h\
	datacollector.cpp datacollector.h\
	diagnose.cpp diagnose.h\
	force.cpp force.h\
	glbfunc.cpp glbfunc.h\
	hydrodynamics.cpp hydrodynamics.h\
	initiation.cpp initiation.h\
	input.cpp input.h\
	interaction.cpp interaction.h\
	interactionstate.cpp interactionstate.h\
	kernel.cpp kernel.h\
	massdatacollector.cpp massdatacollector.h\
	material.cpp material.h\
	mls.cpp mls.h\
	netcdfoutputstream.cpp netcdfoutputstream.h\
	newrgdatacollector.cpp newrgdatacollector.h\
	node.cpp node.h\
	observer.cpp observer.h\
	output.cpp output.h\
	outputstream.cpp outputstream.h\
	particle.cpp particle.h\
	particlemanager.cpp particlemanager.h\
	polymerdatacollector.cpp polymerdatacollector.h\
	polymerinteraction.cpp polymerinteraction.h\
	polymerparticle.cpp polymerparticle.h\
	quinticspline.cpp quinticspline.h\
	reflection.cpp reflection.h\
	rgdatacollector.cpp rgdatacollector.h\
	safeoutputstream.cpp safeoutputstream.h\
	simpledatacollector.cpp simpledatacollector.h\
	simpleparticlecommand.cpp simpleparticlecommand.h\
	simplepolymercreator.cpp simplepolymercreator.h\
	subject.cpp subject.h\
	textoutputstream.cpp textoutputstream.h\
	timer.cpp timer.h\
	timesolver.cpp timesolver.h\
	torrgdatacollector.cpp torrgdatacollector.h\
	vec2d.cpp vec2d.h\
	wiener.cpp wiener.h\
	dllist.h\
	main.h\
	simplecommand.h\
	particlecommand.h\
	sphopt.cpp

AM_CXXFLAGS=-Wall -DNOLOG -DQFIX  $(GSL_CFLAGS) \
	$(BOOST_CPPFLAGS) $(CPPFLAGS)

AM_LDFLAGS=$(GSL_LIBS) $(LDFLAGS)\
	$(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_LDFLAGS) -lnetcdf_c++


