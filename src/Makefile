TARGET = hbsv hbcl

#CFLAGS = -Wall -g -static
CFLAGS = -Wall -g

all:	$(TARGET)

hbsv:	hbsv.o raft_server.o raft_node.o raft_log.o raft_server_properties.o
	cc $(CFLAGS) -o $@ $^

hvsv.o:	hvsv.c
	cc $(CFLAGS) -c $<

raft_server.o: raft_server.c
	cc $(CFLAGS) -c $<

raft_server_properties.o: raft_server_properties.c
	cc $(CFLAGS) -c $<

raft_node.o: raft_node.c
	cc $(CFLAGS) -c $<

raft_log.o: raft_log.c
	cc $(CFLAGS) -c $<

hbcl:	hbcl.c
	cc $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) *~ *.o
