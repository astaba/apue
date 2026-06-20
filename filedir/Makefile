.PHONY: all test clean

ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

TEMPFILES += foo bar

ifeq "$(PLATFORM)" "linux"
	ZAP = reset_times
else
	ZAP =
endif

# NOTICE: The original file names have been discarded because when
# compiled their names create confusions with default libc routines or
# bash commands.
PROGS = $(ZAP) \
	access_file \
	change_dir \
	change_mode \
	device_num \
	file_types \
	get_cwd \
	mode_mask \
	unlink_file

MOREPROGS = \
	ftree_walk \
	yftree_walk

all: $(PROGS) $(MOREPROGS)

# $(PROGS): %: %.c $(LIBAPUE)
#	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

# $(MOREPROGS): %: %.c $(LIBAPUE)
#	$(CC) $(CFLAGS) $(NAMEMAX) $< -o $@ $(LDFLAGS) $(LDLIBS)

$(PROGS) $(MOREPROGS): $(LIBAPUE)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o *.out $(ZAP)

include $(ROOT)/Make.libapue.inc
