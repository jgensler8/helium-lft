# 2 "src.ino"
#include <ArduinoUnit.h>
#include "heliumlft.h"

test(that_HELIUM_LFT_MAX_DATA_SIZE_is_83)
{
  assertEqual(HELIUM_LFT_MAX_DATA_SIZE, 83);
}

test(that_zero_index_points_to_first_letter)
{
  const char * data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  
  Packet p = get_packet_at_index(data, 3, 0);
  
  const char* first_letter = (char*)p.data;
  const char* expected_first_letter = "A";
  assertEqual(p.len, 3);
  assertEqual(first_letter[0], expected_first_letter[0]);
}

test(that_first_index_of_small_string_has_zero_length)
{
  const char * data = "Hello World";
  Packet p = get_packet_at_index(data, 3, 1);
  assertEqual(p.len, 0);
}

test(that_first_index_of_long_string_points_to_first_letter)
{
  char arr[HELIUM_LFT_MAX_DATA_SIZE + 1] = "123";
  arr[HELIUM_LFT_MAX_DATA_SIZE] = "Z";
  const char * data = arr;

  Packet p = get_packet_at_index(data, HELIUM_LFT_MAX_DATA_SIZE + 1, 1);
  
  int pointer_value = (int)p.data;
  int expected_pointer_value = (int)arr + HELIUM_LFT_MAX_DATA_SIZE;
  assertEqual(pointer_value, expected_pointer_value);
  
  assertEqual(p.len, 1);
  
  const char first_letter = *(char*)p.data;
  const char expected_first_letter = "Z";
  assertEqual(first_letter, expected_first_letter);
}

test(that_get_channelable_packet_correctly_appends_data)
{
  Packet p;
  p.len=2;
  p.data = "123";

  Packet channelable_packet = generate_channelable_packet(1,1,1,p);

  char * expected_string = "1,1,1,12\n";
  assertEqual((char*)channelable_packet.data, expected_string);

  assertEqual(channelable_packet.len, strlen(expected_string));
}

void setup()
{
  Serial.begin(9600);
  while(!Serial) {} // Portability for Leonardo/Micro
}

void loop()
{
  Test::run();
}
