// packet_parser.c

#include "../include/packet_parser.h"
#include <stdio.h>

void parse_packet(const unsigned char *packet, int packet_length) {
    // パケットの解析処理を実装する
    // ここでは、単純にパケットの長さを表示するだけとします
    printf("Packet length: %d\n", packet_length);
}
