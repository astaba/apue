ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PROGS =	fileflags hole mycat seek nohole tracefd mydup2 append

all:	$(PROGS) setfl.o

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o *.out file.hole file.nohole

include $(ROOT)/Make.libapue.inc
