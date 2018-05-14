#include "heliumlft.h"

int _GLOBAL_TRANSACTION_ID = 0;

Packet
get_packet_at_index(void const * data, size_t len, int index) {
  Packet p;

  // Calculate start of data
  int read_start = index * HELIUM_LFT_MAX_DATA_SIZE;
  if (read_start >= len) {
    p.data = 0;
    p.len = 0;
    return p;
  }
  p.data = data + read_start;

  // Calculate length of the data
  int len_remaining = HELIUM_LFT_MAX_DATA_SIZE;
  if ( read_start + HELIUM_LFT_MAX_DATA_SIZE > len) {
    len_remaining = len % HELIUM_LFT_MAX_DATA_SIZE;
  }
  p.len = len_remaining;
  
  return p;
}

Packet
generate_channelable_packet(int transaction_id, int packet_index, int total_number_of_packets, Packet p) {
  char packet_data_buffer[HELIUM_MAX_DATA_SIZE];
  int total_prefix_characters = sprintf(packet_data_buffer, "%d,%d,%d,", transaction_id, packet_index, total_number_of_packets);
  memcpy(packet_data_buffer + total_prefix_characters, p.data, p.len);
  sprintf(packet_data_buffer + total_prefix_characters + p.len, "\n");
  
  p.data = packet_data_buffer;
  p.len = total_prefix_characters + p.len + 1;
  return p;
}

void
channel_send_lft(Channel * channel, const char * channel_name, void const * data, size_t len) {
  float len_f = (float)len;
  int total_number_of_packets = ceil(len_f / HELIUM_LFT_MAX_DATA_SIZE);
  for (int packet_index = 0; packet_index < total_number_of_packets; packet_index++) {
    Packet p = get_packet_at_index(data, len, packet_index);
    Packet channelable_packet = generate_channelable_packet(_GLOBAL_TRANSACTION_ID, packet_index, total_number_of_packets, p);
    channel_send(channel, channel_name, channelable_packet.data, channelable_packet.len);
  }
  
  _GLOBAL_TRANSACTION_ID = (_GLOBAL_TRANSACTION_ID + 1 ) % 10;
}
