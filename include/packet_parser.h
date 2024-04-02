#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include <netinet/ip.h>
#include <netinet/tcp.h>

void parse_packet(const unsigned char *packet, int packet_length);

#endif /* PACKET_PARSER_H */