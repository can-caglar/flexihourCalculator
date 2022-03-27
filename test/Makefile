CC := gcc
CFLAGS := -Wall -O0 -MD -MP
SRCDIR := . ./../src
INCDIR := . ./../include
SRCS := $(foreach SRC, $(SRCDIR), $(wildcard $(SRC)/*.c))
INCFLAG := $(foreach INC, $(INCDIR), -I$(INC))

OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean debug

all: debug flexitest

debug:
	@echo "SRCS = $(SRCS)"
	@echo "INCFLAG = $(INCFLAG)"
	@echo "OBJS = $(OBJS)"
	@echo "DEPS = $(DEPS)"

flexitest: $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAG) -c $< -o $@

clean:
	rm *.exe *.o $(OBJS) $(DEPS)

-include $(DEPS)