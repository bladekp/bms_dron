#include "utils.h"

uint8_t nibble32bit(uint32_t val, uint8_t k) {
    return (val >> (8*k)) & 0xFF;
}

uint8_t nibble16bit(uint16_t val, uint8_t k) {
    return (val >> (8*k)) & 0xFF;
}

