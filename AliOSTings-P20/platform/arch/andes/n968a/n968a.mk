NAME := n968a

$(NAME)_TYPE := kernel
GLOBAL_INCLUDES += .

$(NAME)_CFLAGS := -g3 -Os -c -Wall -mcmodel=medium  -mcpu=n968a

$(NAME)_SOURCES	 += gcc/port_c.c   gcc/port_s.S

