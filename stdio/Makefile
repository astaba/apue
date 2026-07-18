ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

ifeq "$(PLATFORM)" "linux"
  MEMSTR = memstr
else
  MEMSTR =
endif

# exr0504 is fromer: getcharbug
PROGS =	\
	fgetsfputs \
	getcputc \
	buf \
	ybuf \
	mkstemp \
	tempfiles \
	exr0504 \
	exr0501 \
	exr0502 \
	exr0503 \
	exr0505

TEMPFILES += std.out std.err std.log critical_data.log

all:	$(PROGS) $(MEMSTR)

# %:	%.c $(LIBAPUE)
# 	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

$(PROGS):	$(LIBAPUE)

clean:
	rm -f $(PROGS) $(TEMPFILES) *.o $(MEMSTR)

include $(ROOT)/Make.libapue.inc
