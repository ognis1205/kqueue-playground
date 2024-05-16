SRC_DIR := src

INC_DIR := include

SRCS=$(wildcard $(SRC_DIR)/*.c)

OBJS=$(SRCS:.c=.o)

CFLAGS=-std=c11 -g -fno-common -Wall -Wno-switch

playground: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf playground tmp*
	find * -type f '(' -name '*~' -o -name '*.o' ')' -exec rm {} ';'

.PHONY: clean
