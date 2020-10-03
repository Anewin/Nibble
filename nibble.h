#ifndef __NIBLE
#define __NIBLE

void sendMark(uint8_t n);
void sendNibble(uint8_t nib);
void sendByte(uint8_t label, uint8_t b);
void sendWord(uint8_t label, uint16_t w);
void sendLong(uint8_t label, uint32_t l);

#endif
