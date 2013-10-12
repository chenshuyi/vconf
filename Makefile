#
# Makefile for vnic configure tool
#

CROSS_COMPILE = mipsel-linux-uclibc-
LINUXDIR = # Your Own Kernel Path

CC = $(CROSS_COMPILE)gcc

CFLAGS += -Wall -I$(LINUXDIR)/include

VCONF_OBJ = vconf.o

vconf: $(VCONF_OBJ)
	$(CC) $(CFLAGS) $(VCONF_OBJ) -o vconf

$(VCONF_OBJ): %.o: %.c
	@echo " "
	@echo "Making $<"
	$(CC) $(CFLAGS) -c $<

clean:
	-rm -f *.o *~ vconf

