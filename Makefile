CC = gcc --std=gnu11
CFLAGS = -Wall -g
PROGNAME = shelleton

CFILELIST = shelleton.c command.c execute.c parsing/memory_pool.c parsing/parsing_interface.c parsing/parse.tab.c parsing/lex.yy.c task.c queue.c background_queue.c
HFILELIST = shelleton.h command.h execute.h parsing/memory_pool.h parsing/parsing_interface.h parsing/parse.tab.h deque.h task.h queue.h background_queue.h

INCLIST = ./src ./src/parsing

SRCDIR = ./src/
OBJDIR = ./obj/

EXECNAME = $(patsubst %,./%,$(PROGNAME))

CFILES = $(patsubst %,$(SRCDIR)%,$(CFILELIST))
HFILES = $(patsubst %,$(SRCDIR)%,$(HFILELIST))
OFILES = $(patsubst %.c,$(OBJDIR)%.o,$(CFILELIST))

RAWC = $(patsubst %.c,%,$(addprefix $(SRCDIR), $(CFILELIST)))
RAWH = $(patsubst %.h,%,$(addprefix $(SRCDIR), $(HFILELIST)))

INCDIRS = $(patsubst %,-I%,$(INCLIST))

OBJINNERDIRS = $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(shell find $(SRCDIR) -type d))

all: $(OBJINNERDIRS) $(PROGNAME)

$(OBJINNERDIRS):
	$(foreach dir, $(OBJINNERDIRS), mkdir -p $(dir);)

$(PROGNAME): $(OFILES)
	$(CC) $(CFLAGS) $^ -o $(PROGNAME) $(LIBLIST)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HFILES)
	$(CC) $(CFLAGS) -c $(INCDIRS) -o $@ $< $(LIBS)

%lex.yy.c: %parse.l
	lex -o $@ $<

%.tab.c %.tab.h: %.y
	bison -t --verbose --defines=$(dir $@)parse.tab.h -o $(dir $@)parse.tab.c $<
