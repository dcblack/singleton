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

################################################################################
#
#   Copyright 2017 Doulos Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
################################################################################
