ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

TEMPFILES += file.hole file.nohole

PROGS = \
		fileflags_f0311 \
		hole_f0302 \
		mycat_f0305 \
		seek_f0301 \
		nohole_uf0302 \
		tracefd_u0316 \
		mydup2_e0302 \
		append_e0306

all:	$(PROGS) setfl.o

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o *.out

include $(ROOT)/Make.libapue.inc
