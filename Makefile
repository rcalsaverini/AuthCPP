PROJDIRS := src include
SCRIPTDIR := scripts
AUXFILES := Readme
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")
SCRIPTFS := $(shell find $(SCRIPTDIR) -type f -name "*")

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.cpp,%.d,$(SRCFILES))
TMPFILES := $(patsubst %.cpp,%.cpp~,$(SRCFILES)) $(patsubst %.hpp,%.hpp~,$(HDRFILES)) 


CODEFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)
ALLFILES := $(CODEFILES) Makefile
DISTFILES := $(ALLFILES) $(SCRIPTFS)

WARNINGS :=-Wall -Wextra -pedantic -Wdouble-promotion -Wuninitialized -Winit-self -Wignored-qualifiers -Wmissing-include-dirs -Wswitch-default \
	   -Wswitch-enum -Wunused-parameter -Wunused -Wunknown-pragmas -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations \
	   -Wredundant-decls -Wno-long-long -Wconversion  #-Winline 
DEBUG    := -g -pg

CXX	 := g++
CXXFLAGS := -std=gnu++0x -m64 -O3 $(WARNINGS) 
IFLAGS   := -I/usr/include/igraph
LDFLAGS	 := -L/usr/local/lib -ligraph -lgsl -lgslcblas -lm 


.PHONY: all clean clean-temps dist todolist

all: main info

main: authcpp
	-@echo "Congratulations, you've built the authcpp program."

clean: clean-temps
	-@$(RM) $(OBJFILES) $(DEPFILES) main dist.tgz authcpp 

clean-temps:
	-@$(RM) *~
	-@$(RM) $(TMPFILES)

dist:
	@tar czf dist.tgz $(DISTFILES)

todolist:
	-@for file in $(CODEFILES); do fgrep -H -e TODO -e FIXME $$file; done; true

authcpp: $(OBJFILES)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -MMD -MP $^ -o $@


-include $(DEPFILES) 

%.o: %.cpp Makefile
	@$(CXX) $(CXXFLAGS) $(IFLAGS) -MMD -MP -c $< -o $@ 

fresh: clean all

info: authcpp
	-@echo ------------------------------	
	-@echo AUTHCPP, CC-BY-NC - some rights reserved. Rafael S. Calsaverini.
	-@echo VERSIONING INFO:
	-@git describe --tags
	-@git log --pretty=format:'%H%n%aD %d' --abbrev-commit --date=short -1


