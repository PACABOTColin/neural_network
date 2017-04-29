GCC = gcc
INCLUDES = 
CFLAGS = -Wall -O2 -std=gnu99
LDFLAGS = -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: neural_network

neural_network: $(OBJS)
	@echo Link $@
	$(GCC) $(INCLUDES) $(CFLAGS) $(OBJS) -o $@ $(LIBNAME) $(LDFLAGS)

-include $(OBJS:.o=.d)

%.o: %.c
	@echo Build $@
	$(GCC) -MMD $(INCLUDES) $(CFLAGS) -c $< -o $@

clean:
	rm -f *~ *.o *.d

deepclean: clean
	rm -f neural_network

