# $Header: /2000XS/CyGOS/Devices/Makefile,v 1.3 2013/05/22 23:01:29 Ellery Exp $
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

DEVCPP = CPLD.cpp TLV5604.cpp 24AA025E48.cpp I2CDevice.cpp PCF8563.cpp AD7890.cpp AT93C66.cpp LPC1758.cpp AD7689.cpp

DEVHDR = ADC.h DAC.h

# This is a relative path to RTOS files from the BSP folder.
DEVDIR = ../../../../Devices

DEVOBJ = $(addprefix $(OBJ_DIR)/Dev_, $(DEVCPP:.cpp=_cpp.o))

INC += $(DEVDIR)

OBJ += $(DEVOBJ)

$(OBJ_DIR)/Dev_%_cpp.o : $(DEVDIR)/%.cpp $(wildcard $(addsuffix /*.h,$(INC)))
	$(CC) $(CCOPT) -o $@ $<

COPYHDR += $(addprefix $(DEVDIR)/,$(DEVHDR) $(DEVCPP:.cpp=.h))
