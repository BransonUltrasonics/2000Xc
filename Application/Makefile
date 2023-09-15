#*
#$Header:$
#*/
#/*****************************************************************************
#$Log:$

#******************************************************************************/
# Copyright (c) Cyber Group, Inc 2007
# This program is the property of Cyber Group Inc
# Copying of this software is expressly forbidden, without the prior written
# consent of Cyber Group Inc
#
# This is the make file to build DCP1B application.

# First, the global configuration for the project
PRJ = SUNRISE

# Target project boards (all in upper case because of Windows).
BOARDS =
BOARDS += SUNRISE

CPPDIR = App
# C++ module list
CPP =  $(wildcard $(CPPDIR)/*.cpp) $(wildcard *.cpp)

# ASM module list WebSite.cpp SysConfig.cpp
ASM = 

# This conditional will activate if makefile is invoked second time inside this
# make build, with BOARD having one value out of BOARDS list. In main level
# makefile, BOARD is not defined, so board-specific makefile components cannot
# be included in here.
ifneq ($(BOARD),)
BINARY = $(BOARD).bin
# RTOS folder location. This folder includes the RTOS library and all related
# include files for the C++ compiler.

CyGOS = $(value PRODUCTIONCYGOS-$(BOARD))

# Include directories, relative to this directory.
INC = Inc $(CyGOS)

# This is an optional variable. If defined, the binary file built by this
# project will be copied into specified file.

BINARY = App_$(PRJ).bin

include $(CyGOS)/Makefile.app
include $(CyGOS)/Makefile.arch
include $(CyGOS)/Makefile.cpu

# Done including things that are defined only for specific board build.
endif

board-Flash:
	@echo Making the Complete Bin File
	@CompleteFlash.exe $(BOARD)
	@echo Complete Bin for $(BOARD) done.
	@ADDCHECKSUM.exe -b $(BOARD)
	@echo Add Checksum for $(BOARD) done.

CompleteFlash:
	@echo Making Complete Bin File
	@cmd /c "for %i in ($(BOARDS)) do @cs-make --no-print-directory BOARD=%i board-Flash"
	
all:
	touch Main.cpp
	@cmd /c "for %i in ($(BOARDS)) do @cs-make --no-print-directory BOARD=%i board-all"
	@cs-make CompleteFlash
	
allcopy:
	touch Main.cpp
	@cmd /c "for %i in ($(BOARDS)) do @cs-make --no-print-directory BOARD=%i board-allcopy"
	@cs-make CompleteFlash
	
clean:
	@cmd /c "for %i in ($(BOARDS)) do @cs-make --no-print-directory BOARD=%i board-clean"
