#include "AFE-EEPROM.h"                                                                                                                                       

AFEEEPROM::AFEEEPROM (){
    EEPROM.begin(EEPROM_SIZE);
}


void AFEEEPROM::write(uint16_t address, uint16_t size, String in) {
    clear(address, size);
    for (uint16_t i = 0; i < in.length(); ++i) {
        EEPROM.write(address + i, in[i]);
    }
    EEPROM.commit();
}


void AFEEEPROM::write(uint16_t address, boolean in) {
    write(address,1,String(in?1:0));
}

void AFEEEPROM::write(uint16_t address, uint16_t size, long in) {
  write(address,size,String(in));
}

void AFEEEPROM::write(uint16_t address, uint16_t size, float in) {
  write(address,size,String(in));
}


String AFEEEPROM::read(uint16_t address, uint16_t size) {
    String _return;
    for (uint16_t i = address; i < address + size; ++i) {
        if (EEPROM.read(i) != 255) {
            _return += char(EEPROM.read(i));
        }
    }
    return _return;
}

boolean AFEEEPROM::read(uint16_t address) {
    return (read(address, 1).toInt() == 1 ? true : false);
}

void AFEEEPROM::writeUInt8(uint16_t address, uint8_t in) {
  write(address,1,String((char)in));
}

uint8_t AFEEEPROM::readUInt8(uint16_t address) {
    return EEPROM.read(address);
}

IPAddress AFEEEPROM::readIP(uint16_t address) {
   IPAddress ip(readUInt8(address),readUInt8(address+1),readUInt8(address+2),readUInt8(address+3));
   return ip;
}

void AFEEEPROM::clear(uint16_t address, uint16_t size) {
    for (uint16_t i = 0; i < size; ++i) {
        EEPROM.write(i + address, 255);
    }
    EEPROM.commit();
}

void AFEEEPROM::erase() {
    clear(0, EEPROM_SIZE);
}
