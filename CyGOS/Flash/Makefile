# $Header: /2000XS/CyGOS/Flash/Makefile,v 1.2 2013/05/24 14:55:46 Ellery Exp $
#
# Copyright (c) Cyber Group, Inc 2007
# This program is the property of Cyber Group Inc
# Copying of this software is expressly forbidden, without the prior written
# consent of Cyber Group Inc
#
# This file is part of CyGOS-3.
#
# This is the Flash directory make file.
#
# This makefile should be included from the board-specific Makefile.

FLASHCPP = Flash.cpp FlashAMD.cpp FlashM29W320E.cpp FlashM29W128G.cpp
	
FLASHHDR = Flash.h

# This is a relative path to RTOS files from the BSP folder.
FLASHDIR = ../../../../Flash

FLASHOBJ = $(addprefix $(OBJ_DIR)/Flash_, $(FLASHCPP:.cpp=_cpp.o))

INC += $(FLASHDIR)

OBJ += $(FLASHOBJ)

$(OBJ_DIR)/Flash_%_cpp.o : $(FLASHDIR)/%.cpp $(wildcard $(addsuffix /*.h,$(INC)))
	$(CC) $(CCOPT) -o $@ $<

COPYHDR += $(addprefix $(FLASHDIR)/,$(FLASHHDR))
