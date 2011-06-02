PROJDIRS := src include
AUXFILES := Readme
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.cpp,%.d,$(SRCFILES))
TMPFILES := $(patsubst %.cpp,%.cpp~,$(SRCFILES)) $(patsubst %.hpp,%.hpp~,$(HDRFILES)) 


CODEFILES := $(SRCFILES) $(HDRFILES) $(AUXFILES)
ALLFILES := $(CODEFILES) Makefile


WARNINGS :=-Wall -Wextra -pedantic -Wdouble-promotion -Wuninitialized -Winit-self -Wignored-qualifiers -Wmissing-include-dirs -Wswitch-default \
	   -Wswitch-enum -Wunused-parameter -Wunused -Wunknown-pragmas -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations \
	   -Wredundant-decls -Wno-long-long -Wconversion  #-Winline 

CXX	 := g++
CXXFLAGS := -std=gnu++0x -m64 -O3 $(WARNINGS) 
IFLAGS   := -I/usr/include/igraph
LDFLAGS	 := -L/usr/local/lib -ligraph -lgsl -lgslcblas -lm 
DEBUG    := -g -pg

.PHONY: all clean dist todolist

all: test 

fresh: clean all

clean: clean-temps
	-@$(RM) $(OBJFILES) $(DEPFILES) test dist.tgz

clean-temps:
	-@$(RM) *~
	-@$(RM) $(TMPFILES)


dist:
	@tar czf dist.tgz $(ALLFILES)

todolist:
	-@for file in $(CODEFILES); do fgrep -H -e TODO -e FIXME $$file; done; true

test: $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -MMD -MP $^ -o $@

-include $(DEPFILES) 

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(IFLAGS) -MMD -MP -c $< -o $@ 

