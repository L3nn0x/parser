PREFIX=.

SRCDIR= $(PREFIX)/src
INCDIR= $(PREFIX)/include
BINDIR= $(PREFIX)/bin
OBJDIR= $(PREFIX)/obj

CC=gcc
CPPFLAGS= -I $(INCDIR)
CFLAGS= -Wall -c
DEBUG=yes
ifeq ($(DEBUG), yes)
	CFLAGS+= -g3
else
	CFLAGS+= -O3
endif
LDFLAGS= -lm -lfl

LEX=flex

YACC=bison
YFLAGS= -d -v -t

SRCFILES= $(wildcard $(SRCDIR)/*.c) $(SRCDIR)/lexer.c #$(SRCDIR)/parser.c 
OBJS= $(SRCFILES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

OUTFILE=$(BINDIR)/a.out

.PHONY: all clean mrproper etags ctags

all: $(OUTFILE)

$(OUTFILE): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.c: %.l
	$(LEX) -o $@ $<

%.c: %.y
	$(YACC) $(YFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

etags:
	etags `find -name *.c && find -name *.h`

ctags:
	ctags `find -name *.c && find -name *.h`

clean:
	$(RM) $(OBJS)
	find -name "*~" -delete
	find -name core -delete

mrproper: clean
	$(RM) $(OUTFILE) $(SRCDIR)/lexer.c $(SRCDIR)/parser.c $(SRCDIR)/parser.h
	find -name "*.d" -delete
	find -name "*.output" -delete
	$(RM) TAGS

include $(SRCFILES:.c=.d)

%.d: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MM -MT $(<:.c=.o) $^> $@
