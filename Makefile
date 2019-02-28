src = $(wildcard *.c)
obj = $(src:.c=.o)
CC = gcc
LDFLAGS = -Lraylib/mingw/i686-w64-mingw32/lib -lraylib -lopengl32 -lgdi32 -lm
CFLAGS = -std=c99 -Iraylib/src
boids: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	del $(obj) boids