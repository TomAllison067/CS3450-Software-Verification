SRCDIR := example-programs
BUILDDIR := build
SRCS := $(wildcard $(SRCDIR)/*.c)
PROGS := $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	gcc -o $@ $<
