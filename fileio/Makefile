ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

TEMPFILES += file.hole file.nohole

PROGS = \
	copy_inout \
	lseek_hole \
	lseek_stdin \
	nohole \
	print_flags \
	ytracefd \
	exr0302 \
	exr0306

all:	$(PROGS) set_flags.o

# NOTICE: Go to TLPI check if LDLIBS variable is a default in `make`
# database. To do that better reload the `make -pq` command from a
# directory with no Makefile. Afterward you could refactor this
# compilation pipeline to take advantage of the defaults.

# %:	%.c $(LIBAPUE)
# $(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

$(PROGS): $(LIBAPUE)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o *.out

include $(ROOT)/Make.libapue.inc
