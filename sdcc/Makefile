### Makefile --- 
## 
## Filename: Makefile
## Description: a commonly used makefile for SDCC
## Author: bigclean
## Maintainer: 
## Created: Sat Nov 21 02:12:25 2009 (-0500)
## Version: 
## Last-Updated: Sat Nov 21 02:15:46 2009 (-0500)
##           By: bigclean
##     Update #: 3
## URL: 
## Keywords: 
## Compatibility: 
## 
######################################################################
## 
### Commentary: 
##  These are the targets for this makefile:
#    all:         generate hex and documentation
#    hex:         generate hex file only
#    clean:       clean project
#    rebuild:     clean and then build project
#    doc:         generate documentations using doxygen and graphviz

## 
## 
######################################################################
## 
### Change log:
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

# tools correalted to documentation generation
DOXYGEN  := doxygen
DOXYFILE := pwm-doxyfile 
RM       := rm -rf

.PHONY: all hex clean rebuild doc

all: hex doc

hex: $(HEX)
	@echo "---------------------------------------------------------------------"
	@echo "\t\033[7m HEX files is generated,now you can burn it!\033[0m"
	@echo "---------------------------------------------------------------------"
	@echo "\n"

$(HEX):$(IHEX)
	packihx $(IHEX) > $(HEX)

$(IHEX): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(IHEX)

%.rel:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "---------------------------------------------------------------------"
	@echo "\t\033[7m cleaning started\033[0m"
	-$(RM)  *.rel
	-$(RM)  *.asm
	-$(RM)  *.lst
	-$(RM)  *.sym
	-$(RM)  *.map
	-$(RM)  *.lnk
	-$(RM)  *.mem
	-$(RM)  *.ihx
	-$(RM)  *.hex
	-$(RM)  *.rst
	-$(RM)  doc
	@echo "\t\033[7m cleaning finished \033[0m"
	@echo "---------------------------------------------------------------------"
	@echo "\n"

rebuild:clean all
	@echo "---------------------------------------------------------------------"
	@echo "\n"
	@echo "\t\033[7m rebuild finished \033[0m"
	@echo "---------------------------------------------------------------------"
	@echo "\n"

doc:
	@echo "---------------------------------------------------------------------"
	@echo "\t\033[7m generate documentation using doxygen and graphviz \033[0m"
	@echo "\t\033[7m you must install doxygen and graphivz \033[0m"
	-$(DOXYGEN) $(DOXYFILE)
	@echo "\t\033[7m html documentation generating finished \033[0m"
	@echo "---------------------------------------------------------------------"

######################################################################
### Makefile ends here
