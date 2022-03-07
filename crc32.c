/*
http://home.thep.lu.se/~bjorn/crc/

*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

unsigned int
GET_32bit(unsigned long c)
{
	return c & 0xffffffff;
}

uint32_t crc32_for_byte(uint32_t r) {
  for(int j = 0; j < 8; ++j)
    r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
  return r ^ (uint32_t)0xFF000000L;
}

uint32_t crc32(const void *data, size_t n_bytes) 
{
  static uint32_t table[0x100];
  uint32_t crc = 0;

  if(!*table)
    for(size_t i = 0; i < 0x100; ++i)
      table[i] = crc32_for_byte(i);
  for(size_t i = 0; i < n_bytes; ++i)
    crc = table[(uint8_t)crc ^ ((uint8_t*)data)[i]] ^ crc >> 8;
  return crc;
}
