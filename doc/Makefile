### Makefile --- 
## 
## Filename: Makefile
## Description: makefile for generating documentation
## Author: bigclean
## Maintainer: bigclean
## Created: Thu Feb 18 14:37:24 2010 (-0500)
## Version: 
## Last-Updated: Thu Feb 18 14:38:27 2010 (-0500)
##           By: bigclean
##     Update #: 1
## URL: 
## Keywords: 
## Compatibility: 
## 
######################################################################
## 
### Commentary: 
## 
## 
## 
######################################################################
## 
### Change log:
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


# all rst format sources
RST_SRCS     := $(wildcard *.rst) 
RST_HTML_OUT := $(patsubst %.rst, %.html, $(RST_SRCS))
# all markdown format sources
MKD_SRCS     := $(wildcard *mkd)
MKD_HTML_OUT := $(patsubst %.mkd, %.html, $(MKD_SRCS))
HTML_OUT     := $(RST_HTML_OUT) $(MKD_HTML_OUT)
RM           := rm
# FIXME: can't process right on windows
# in windows, it's rst2html.py
RST2HTML     := rst2html
# in windows, maybe markdown.pl pr others
MARKDOWN     := markdown

.PHONY: all html clean 

html: $(HTML_OUT)
%.html: %.rst
	$(RST2HTML) --time --source-link --generator --toc-top-backlinks \
	    --cloak-email-address $< $@

%.html: %.mkd
	$(MARKDOWN) $< > $@

clean:
	@echo "start to clean"
	@echo $(RST_SRCS)
	@echo $(MKD_SRCS)
	@echo $(RST_HTML_OUT)
	@echo $(MKD_HTML_OUT)
	-$(RM) $(HTML_OUT)
	@echo "clean is finished"

######################################################################
### Makefile ends here
