ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

.PHONY += clean utility

ACCT=
ACCTFLAGS=
ifeq "$(PLATFORM)" "linux"
  ACCT=pracct
  ACCTFLAGS = -DHAS_AXSIG -DHAS_ACORE
endif
ifeq "$(PLATFORM)" "macos"
  ACCT=pracct
  ACCTFLAGS = -DHAS_AXSIG -DHAS_ACORE
endif
ifeq "$(PLATFORM)" "solaris"
  ACCT=pracct
  ACCTFLAGS = -DHAS_AC_STAT
endif

PROGS =	\
	echoall \
	exec1 \
	exec2 \
	fork1 \
	fork2 \
	nice \
	pruids \
	tellwait1 \
	tellwait2 \
	test1 \
	times1 \
	vfork1 \
	wait1

MOREPROGS = systest1 systest3

TEMPFILES += temp.out
UTILITY_BINAREIS = ~/bin/echoall ~/bin/echoarg ~/bin/testinterp

all:	$(PROGS) $(MOREPROGS) system.o $(ACCT)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) $@.c -o $@ $(LDFLAGS) $(LDLIBS)

systest1:	system.o systest1.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o systest1 systest1.o system.o $(LDFLAGS) $(LDLIBS)

systest3:	system.o systest3.o $(LIBAPUE)
		$(CC) $(CFLAGS) -o systest3 systest3.o system.o $(LDFLAGS) $(LDLIBS)

pracct:		pracct.c $(LIBAPUE)
		$(CC) $(CFLAGS) $(ACCTFLAGS) -o pracct pracct.c $(LDFLAGS) $(LDLIBS)

utility: echoall
	if ! [ -x ~/bin/echoall ]; then \
		cp $< ~/bin; \
	fi
	if ! [ -x ../environ/echoarg ]; then \
		$(MAKE) echoarg -C ../environ && \
		mv ../environ/echoarg ~/bin; \
	else \
		cp ../environ/echoarg ~/bin; \
	fi
	if ! [ -x ~/bin/testinterp ]; then \
		( cd ~/bin; \
		  echo '#!/home/owner/bin/echoarg foo' > testinterp && \
		  chmod +x testinterp; \
		); \
	fi

clean:
	@rm -vf $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o $(ACCT)
	@for f in $(UTILITY_BINAREIS); do \
		if [ -e $$f ]; then \
			rm -vfi $$f; \
		fi; \
	done

include $(ROOT)/Make.libapue.inc
