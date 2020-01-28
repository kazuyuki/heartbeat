TARGET = hbsv hbcl

#CFLAGS = -Wall -g -static
CFLAGS = -Wall -g

all:	$(TARGET)

hbsv:	hbsv.c
	cc $(CFLAGS) -o $@ $<

hbcl:	hbcl.c
	cc $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) *~
