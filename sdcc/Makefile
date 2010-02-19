### Makefile --- 
## 
## Filename: Makefile
## Description: a commonly used makefile for SDCC
## Author: bigclean
## Maintainer: 
## Created: Sat Nov 21 02:12:25 2009 (-0500)
## Version: 
## Last-Updated: Fri Feb 19 12:45:23 2010 (-0500)
##           By: bigclean
##     Update #: 12
## URL: 
## Keywords: 
## Compatibility: 
## 
######################################################################
## 
### Commentary: 
##  These are the targets for this makefile:
#    all:         generate hex and documentation
#    build:       target refer to hex
#    hex:         generate hex file only
#    clean:       clean project
#    rebuild:     clean and then build project
#    doc:         generate documentations using doxygen and graphviz
#    TAGS:        generate tags for source files

## 
## 
######################################################################
## 
### Change log:
## 19-Feb-2010    bigclean  
##    Last-Updated: Thu Feb 18 23:51:20 2010 (-0500) #10 (bigclean)
##    some tricks to process doxygen and graphviz windows path
## 18-Feb-2010    bigclean  
##    Last-Updated: Thu Feb 18 20:25:22 2010 (-0500) #9 (bigclean)
##    different actions to doxygen and grapviz not found.
## 18-Feb-2010    bigclean  
##    Last-Updated: Sat Dec 19 16:01:30 2009 (+0800) #8 (bigclean)
##    add autodetection for doxygen and graphviz
## 19-Dec-2009    bigclean  
##    Last-Updated: Sat Dec 19 15:59:38 2009 (+0800) #7 (bigclean)
##    do some minor changes to Makefile,now compatible with gentoo.
## 21-Nov-2009    bigclean  
##    Last-Updated: Sat Nov 21 02:14:37 2009 (-0500) #2 (bigclean)
##    optimize echo output messages,but to be tested under windows.
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
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

# TODO: enhanced echo is not for windows.
SHELL    := /bin/sh
PROJECT  := pwm-commmunicate
# source files which main() function where is
MAINC    := exam.c 
CC       := sdcc
CPPFLAGS := 
CFLAGS   := -mmcs51
LDFLAGS  := 

# SRCS is the source files list(*.c),and SDCC requires the source file 
# which stores main() function must be located first.
SRCS     := $(MAINC)
SRCS     += $(filter-out $(MAINC),$(wildcard *.c))

# temporary files when compiled by SDCC
# object files
OBJS     := $(patsubst %.c,%.rel,$(SRCS))
# hex files and intel hex files format generated finally
IHEX     := $(addsuffix .ihx,$(PROJECT))
HEX      := $(addsuffix .hex,$(PROJECT))
CLEAN    := $(OBJS) $(IHEX) $(HEX)

# tools correalted to documentation generation
# doxygen and graphviz messages
DOXYGEN_MESSAGE  := generate document fails,you must install doxygen
GRAPHVIZ_MESSAGE := graphviz not found,suggested to install
DOXYGEN  := doxygen
DOXYFILE := pwm-doxyfile 
RM       := rm -rf
TAGS     := ctags -R --fields=+ialS --extra=+q

# echo colorize output
HIGH     :=\033[7m
LIGHT    :=\033[0m
.PHONY: all hex clean rebuild doc TAGS dist

all: build

build:hex

hex: $(HEX)
	@echo "---------------------------------------------------------------------"
	@echo -e "\t$(HIGH) HEX files is generated,now you can burn it!$(LIGHT)"
	@echo "---------------------------------------------------------------------"

$(HEX):$(IHEX)
	packihx $(IHEX) > $(HEX)

$(IHEX): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(IHEX)

%.rel:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "---------------------------------------------------------------------"
	@echo -e "\t$(HIGH) cleaning started. $(LIGHT)"
	-$(RM)  $(CLEAN)
	-$(RM)  *.asm
	-$(RM)  *.lst
	-$(RM)  *.sym
	-$(RM)  *.map
	-$(RM)  *.lnk
	-$(RM)  *.mem
	-$(RM)  *.rst
	-$(RM)  doc
	-$(RM)  tags
	@echo -e "\t$(HIGH) cleaning finished $(LIGHT)"
	@echo "---------------------------------------------------------------------"

rebuild:clean all
	@echo "---------------------------------------------------------------------"
	@echo -e "\n"
	@echo -e "\t$(HIGH) rebuild finished $(LIGHT)"
	@echo "---------------------------------------------------------------------"

doc:
	@echo "---------------------------------------------------------------------"
	@echo -e "\t$(HIGH) generate document started. $(LIGHT)"
# autodetection about doxygen and graphviz and display different info
# report error when doxygen not found and warning when graphviz not found
# FIXME: maybe command "ifeq ($(shell basename $(shell which doxygen | sed
#        's:\\:/:g')), )" still needs to be tested,so devil path process.
#        it seems that doxygen and graphviz can not be install in default
#        'Program Files' directory
# XXX:  use some tricks to process windows devil path, even if path
#       can not processed, at least it wasn't blank.
# or you can use $(shell basename `which doxygen`) to get doxygen
# exit make when doxygen not found
ifeq ($(shell basename $(shell which doxygen)), )
	$(error $(DOXYGEN_MESSAGE))
endif

# report warnings when graphviz not found
ifeq ($(shell basename $(shell which dot)), )
	$(warning $(GRAPHVIZ_MESSAGE))
endif
	-$(DOXYGEN) $(DOXYFILE)
	@echo -e "\t$(HIGH) html documentation generating finished $(LIGHT)"
	@echo "---------------------------------------------------------------------"

TAGS:
	@echo "---------------------------------------------------------------------"
	@echo -e "\t$(HIGH) generate tags files $(LIGHT)"
	$(TAGS) ./
	@echo "---------------------------------------------------------------------"

dist: all doc
######################################################################
### Makefile ends here
