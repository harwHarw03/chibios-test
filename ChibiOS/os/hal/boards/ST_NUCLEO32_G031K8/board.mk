# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO32_G031K8/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_NUCLEO32_G031K8

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
