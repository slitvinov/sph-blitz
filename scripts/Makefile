# compilation flags
CXXFLAGS=-O2 -g -Wall -Wextra

all: create_IC1D_mConst create_IC1D_SpaceConst create_ICq1D create_ICq1D_mConst create_ICq1D_SpaceConst

create_IC1D_mConst: create_IC1D_mConst.cpp

create_IC1D_SpaceConst: create_IC1D_SpaceConst.cpp

create_ICq1D: create_ICq1D.cpp

create_ICq1D_mConst: create_ICq1D_mConst.cpp

create_ICq1D_SpaceConst: create_ICq1D_SpaceConst.cpp

.PHONY: clean

clean:
	-rm create_IC1D_SpaceConst
	-rm create_IC1D_mConst
	-rm create_ICq1D
	-rm create_ICq1D_mConst
	-rm create_ICq1D_SpaceConst

