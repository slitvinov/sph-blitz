all: create_IC1D_mConst create_IC1D_SpaceConst create_ICq1D_mConst create_ICq1D_SpaceConst  create_IC1D_SpaceConstRAND create_IC1D_mConstRAND

create_IC1D_mConst: create_IC1D_mConst.cpp

create_IC1D_mConstRAND: create_IC1D_mConstRAND.cpp

create_IC1D_SpaceConst: create_IC1D_SpaceConst.cpp

create_IC1D_SpaceConstRAND: create_IC1D_SpaceConstRAND.cpp

# create_IC1D_SpaceConstRAND.o:  create_IC1D_SpaceConstRAND.cpp \
 RandNumGenerators/sfmt.h RandNumGenerators/sfmt.cpp

create_ICq1D_mConst: create_ICq1D_mConst.cpp

create_ICq1D_SpaceConst: create_ICq1D_SpaceConst.cpp

.PHONY: clean

clean:
	-rm create_IC1D_SpaceConst
	-rm create_IC1D_mConst
	-rm create_ICq1D_mConst
	-rm create_ICq1D_SpaceConst
	-rm create_IC1D_SpaceConstRAND
	-rm create_IC1D_mConstRAND

