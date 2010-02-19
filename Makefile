### Makefile --- 
## 
## Filename: Makefile
## Description: project of wzupwm master makefile
## Author: bigclean
## Maintainer: 
## Created: Thu Feb 18 20:28:14 2010 (-0500)
## Version: 
## Last-Updated: Thu Feb 18 20:31:30 2010 (-0500)
##           By: bigclean
##     Update #: 2
## URL: 
## Keywords: 
## Compatibility: 
## 
######################################################################
## 
### Commentary:
##  These are the targets for this Makefile:
#      all:   default target
#      build: build hex files
#      doc:   generate documentation
#      clean: clean project
#      dist:  release project
## 
## 
## 
######################################################################
## 
### Change log:
## 18-Feb-2010    bigclean  
##    Last-Updated: Thu Feb 18 20:31:03 2010 (-0500) #1 (bigclean)
##    first initial, needs to be consummated.
## 
## 
######################################################################
## 
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License as
## published by the Free Software Foundation; either version 3, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program; see the file COPYING.  If not, write to
## the Free Software Foundation, Inc., 51 Franklin Street, Fifth
## Floor, Boston, MA 02110-1301, USA.
## 
######################################################################
## 
### Code:


# global Makefile for project
# TODO: control two individual Makefiles and can pass inndividual
#       arguments to targets. 

PROJECT   := wzupwm
VERSION   := 0.1
DIRECTORY := $(PROJECT)-$(VERSION)
MAKE      := make
MAKECLEAN := make clean
MAKEDOC   := make doc
MAKEDIST  := make dist
MAKEBUILD := make build
CP        := cp -ir
MKDIR     := mkdir -v
RM        := rm -rf
MV        := mv -if
TAR       := tar -cjf

.PHONY: all doc test build test clean 

all: build

doc:
	$(MAKE) -C doc
	$(MAKEDOC) -C sdcc
build:
	$(MAKEBUILD) -C sdcc

dist: all doc
	$(MKDIR) ../$(DIRECTORY)
	$(CP) * ../$(DIRECTORY)
	$(TAR) $(DIRECTORY).tar.bz2 ../$(DIRECTORY)
	$(RM) ../$(DIRECTORY)
	$(MV) $(DIRECTORY).tar.bz2 ../

clean:
	$(MAKECLEAN) -C doc
	$(MAKECLEAN) -C sdcc
test:
	@echo $(PATH)

######################################################################
### Makefile ends here
