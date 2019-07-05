#ifndef Id_Maker_h
#define Id_Maker_h

#include <Arduino.h>
#include <inttypes.h>

class Id_MakerClass
{
  public:
  ICACHE_FLASH_ATTR Id_MakerClass();
  ICACHE_FLASH_ATTR int rand();
  ICACHE_FLASH_ATTR long random();
  ICACHE_FLASH_ATTR long random(long howBig);
  ICACHE_FLASH_ATTR long random(long howsmall, long how);
  ICACHE_FLASH_ATTR int randomBit(void);
  ICACHE_FLASH_ATTR char randomByte(void);
  ICACHE_FLASH_ATTR void memfill(char* location, int size);
  ICACHE_FLASH_ATTR void mac(uint8_t* macLocation);
  ICACHE_FLASH_ATTR void uuid(uint8_t* uuidLocation);
  ICACHE_FLASH_ATTR String uuidToString(uint8_t* uuidLocation);
    bool useRNG;
  private:
    unsigned long lastYield;
    ICACHE_FLASH_ATTR int randomBitRaw(void);
    ICACHE_FLASH_ATTR int randomBitRaw2(void);
};
extern Id_MakerClass Id_Maker;
#endif
