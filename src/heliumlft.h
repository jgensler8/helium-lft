#ifndef HELIUMULFT_H
#define HELIUMULFT_H

#include <Helium.h>
#include <HeliumUtil.h>

const int HELIUM_LFT_MAX_DATA_SIZE = HELIUM_MAX_DATA_SIZE - 20;

class Packet {
  public:
    void const * data;
    size_t len;
};

Packet
get_packet_at_index(void const * data, size_t len, int index);

Packet
generate_channelable_packet(int transaction_id, int packet_index, int total_number_of_packets, Packet p);

void
channel_send_lft(Channel *    channel,
             const char * channel_name,
             void const * data,
             size_t       len);
             
#endif HELIUMULFT_H
