# Linear-algebra library
EIGEN = /usr/include/eigen3/


CXX          = g++
CLINKER     = g++

CXXFLAGS      = -I$(EIGEN) -O3
LIBS        = -lm
DEPEND= makedepend

SRC1        =main_DensityProfile.cpp transfermatrix.cpp
OBJS1       =main_DensityProfile.o transfermatrix.o
EXECS1      =main_DensityProfile.exe

SRC2        =main_EquationOfState.cpp transfermatrix.cpp
OBJS2       =main_EquationOfState.o transfermatrix.o
EXECS2      =main_EquationOfState.exe

default: main_DensityProfile main_EquationOfState

all: main_DensityProfile main_EquationOfState

main_DensityProfile:$(OBJS1)
	$(CLINKER) $(OPTFLAGS) -o $(EXECS1) $(OBJS1) $(LIBS) $(CXXFLAGS)

main_EquationOfState:$(OBJS2)
	$(CLINKER) $(OPTFLAGS) -o $(EXECS2) $(OBJS2) $(LIBS) $(CXXFLAGS)

clean:
	/bin/rm -f *.o *~ $(EXECS1) $(EXECS2)

.c.o:
	$(CXX) $(CXXFLAGS) -c $*.cpp