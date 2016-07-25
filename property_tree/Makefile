# Makefile for Boost test
# created by chengxiang
# email: chengxiang@deepglint.com
# time: Dec 22, 2015

# target
TARGET = test

# directory
SRCDIR=.
OUTDIR=build

# source file
SRCCPP=$(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.cpp))

OBJS=$(foreach file, $(SRCCPP:.cpp=.cpp.o), $(OUTDIR)/$(file))
DEPENDFILES=$(foreach file, $(SRCCPP:.cpp=.cpp.d), $(OUTDIR)/$(file))

# compile parameter
CXX=g++
CXXFLAGS=$(INCDIR) -fpermissive -fPIC -O3 

LDFLAGS=

# shell command
RM = rm -fr

# defination
.SUFFIXES: .cpp .h .d
.PHONY: mk_dir clean all echo

# rules
all:$(TARGET)

mk_dir:
	@[ -d $(OUTDIR) ] || mkdir -p $(OUTDIR);

$(OUTDIR)/%.cpp.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET):$(OBJS)
	@echo 'Makeing $@...'
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	-@ $(RM) $(OBJS) $(TARGET) *~

# source and header file dependent
-include $(DEPENDFILES)
$(OUTDIR)/%.cpp.d:%.cpp | mk_dir
	@set -e; rm -f $@;\
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	$(RM) $@.$$$$
