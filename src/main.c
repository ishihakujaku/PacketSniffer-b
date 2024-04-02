// main.c

#include "../include/packet_parser.h"
#include <pcap.h>
#include <stdio.h>


void packet_handler(unsigned char *user, const struct pcap_pkthdr *pkthdr,
                    const unsigned char *packet) {
    parse_packet(packet, pkthdr->len);
}

int main() {
    pcap_t *handle;  // パケットキャプチャ用のハンドル
    char errbuf[PCAP_ERRBUF_SIZE];  // ライブラリ定義済みサイズ
    struct bpf_program fp;  // フィルタのプログラム構造体
    char filter_exp[] = "ip";  // キャプチャするパケットのフィルタ式

    // Error checking
    char *dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return 1;  // エラー終了
    }

    // ネットワークインターフェースを開く
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return 1;  // エラー終了
    }

    // フィルタを設定
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp,
                pcap_geterr(handle));
        return 1;  // エラー終了
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp,
                pcap_geterr(handle));
        return 1;  // エラー終了
    }

    // パケットをキャプチャしてパケットハンドラーを呼び出す
    pcap_loop(handle, -1, packet_handler, NULL);

    // クリーンアップ
    pcap_freecode(&fp);  // フィルタの解放
    pcap_close(handle);  // ハンドルをクローズ

    return 0;  // 正常終了
}
