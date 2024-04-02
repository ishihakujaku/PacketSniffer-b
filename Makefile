CC=gcc
CFLAGS=-Wall -Wextra -O2
LDFLAGS=-lpcap

PacketSniffer-b: main.o packet_parser.o
	$(CC) $(CFLAGS) -o PacketSniffer-b main.o packet_parser.o $(LDFLAGS)

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

packet_parser.o: src/packet_parser.c
	$(CC) $(CFLAGS) -c src/packet_parser.c

clean:
	rm -f *.o PacketSniffer-b