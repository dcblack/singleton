#!make -f

ifndef CXX
CXX := clang++
endif

SRCS:=singleton.cpp main.cpp
OBJS:=$(patsubst %.cpp,%.o,${SRCS})
ROOT:=singleton
LOGF:=${ROOT}.log
define Announce
  perl -le 'print q(x)x100'
  echo "Info: $1";
  perl -le 'print q(=)x30'
endef

.PHONY: build clean version compile link run

build:
	@$(MAKE) clean version compile link run 2>&1 | tee ${LOGF}
	@$(call Announce,Done)

version:
	@$(call Announce,Compiler version)
	${CXX} --version

compile: $(OBJS)

%.o: %.cpp
	@$(call Announce,Compiling '$*')
	${CXX} -std=c++14 -o $*.o -c $*.cpp

link:
	@$(call Announce,Linking)
	${CXX} -o singleton.x singleton.o main.o

run:
	@$(call Announce,Running)
	./singleton.x

clean:
	@$(call Announce,Cleaning)
	-rm -f singleton.{[xo],log} main.o
