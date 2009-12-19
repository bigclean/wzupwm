### Makefile --- 
## 
## Filename: Makefile
## Description: a commonly used makefile for SDCC
## Author: bigclean
## Maintainer: 
## Created: Sat Nov 21 02:12:25 2009 (-0500)
## Version: 
## Last-Updated: Sat Dec 19 16:01:30 2009 (+0800)
##           By: bigclean
##     Update #: 8
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

# echo colorize output
HIGH     :=\033[7m
LIGHT    :=\033[0m
.PHONY: all hex clean rebuild doc

all: hex doc

hex: $(HEX)
	@echo "---------------------------------------------------------------------"
	@echo -e "\t$(HIGH) HEX files is generated,now you can burn it!$(LIGHT)"
	@echo "---------------------------------------------------------------------"
	@echo -e "\n"

$(HEX):$(IHEX)
	packihx $(IHEX) > $(HEX)

$(IHEX): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(IHEX)

%.rel:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "---------------------------------------------------------------------"
	@echo -e "\t$(HIGH) cleaning started. $(LIGHT)"
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
	@echo -e "\t$(HIGH) cleaning finished $(LIGHT)"
	@echo "---------------------------------------------------------------------"
	@echo -e "\n"

rebuild:clean all
	@echo "---------------------------------------------------------------------"
	@echo -e "\n"
	@echo -e "\t$(HIGH) rebuild finished $(LIGHT)"
	@echo "---------------------------------------------------------------------"
	@echo -e "\n"

doc:
	@echo "---------------------------------------------------------------------"
	@echo -e "\t$(HIGH) generate documentation using doxygen and graphviz $(LIGHT)"
	@echo -e "\t$(HIGH) you must install doxygen and graphivz $(LIGHT)"
	-$(DOXYGEN) $(DOXYFILE)
	@echo -e "\t$(HIGH) html documentation generating finished $(LIGHT)"
	@echo -e "---------------------------------------------------------------------"

######################################################################
### Makefile ends here
