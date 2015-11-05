# $Id: Makefile,v 1.2 2004/10/12 09:06:17 marquet Exp $
##############################################################################

ROOTDIR=.

CC	= gcc
CFLAGS	= -m32 -Wall -ansi -pedantic
CFLAGS  += -g
LIBDIR  = $(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    = -L$(LIBDIR) -lhardware -lpthread

###------------------------------
### Main targets
###------------------------------------------------------------
BINARIES= dmps frmt mkvol
OBJECTS	= $(addsuffix .o,\
	  dmps frmt mkvol)

all: $(BINARIES) $(OBJECTS)


###------------------------------
### Main rules
###------------------------------------------------------------
drive.o: $(LIBDIR)/drive.c
	$(CC) $(CFLAGS) -c $(LIBDIR)/drive.c $(INCDIR)

vol.o: $(LIBDIR)/vol.c
	$(CC) $(CFLAGS) -c $(LIBDIR)/vol.c $(INCDIR)

dmps.o: dmps.c
	$(CC) $(CFLAGS) -c dmps.c $(INCDIR)

dmps: dmps.o drive.o
	$(CC) $(CFLAGS) -o dmps $^ $(LIBS)

frmt.o: frmt.c
		$(CC) $(CFLAGS) -c frmt.c $(INCDIR)

frmt: frmt.o drive.o
		$(CC) $(CFLAGS) -o frmt $^ $(LIBS)

mkvol.o: mkvol.c
		$(CC) $(CFLAGS) -c mkvol.c $(INCDIR)

mkvol: mkvol.o drive.o vol.o
		$(CC) $(CFLAGS) -o mkvol $^ $(LIBS)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin
