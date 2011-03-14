# 2010.2.22

#DIR = ./out/
#TAR_DIR = ./out/

src = $(wildcard *.c)
obj = $(patsubst %.c, $(DIR)%.o, $(src))
target = $(TAR_DIR)main

#CC = gcc
CC = arm-linux-gcc
CFLAGS = -Wall -g -c -I../jpeg-8/ -I../freetype-2.3.11/include -I../libmad-0.15.0b/
LDFLAGS = -lpthread -L../jpeg-8/.libs/ -ljpeg -L../freetype-2.3.11/objs/.libs -lfreetype -L../libmad-0.15.0b/.libs -lmad

all: $(target)

$(target): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)
$(DIR)%.o:%.c
	$(CC) -o $@ $(CFLAGS) $< 

clean:
	-rm -f $(target)
	-rm -f $(obj)
	-rm -f *~
	-rm -f .*.c.swp
	-rm -f .*.h.swp

.PHONY: clean
test:
	@echo $(src)
	@echo $(obj)
