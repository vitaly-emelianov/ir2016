//
// Created by vitaly on 4/6/16.
//
#include "conversion.h"


size_t Conversion::encodeVarInt(uint8_t* const buffer, uint64_t value) {
    int encoded = 0;
    do {
        uint8_t next_byte = value & 127;
        value >>= 7;
        if (value) {
            next_byte |= 128;
        }
        buffer[encoded++] = next_byte;
    } while (value);
    return encoded;
}

uint64_t Conversion::decodeVarInt(const uint8_t* const data, size_t decoded_bytes) {
    int i = 0;
    uint64_t decoded_value = 0;
    int shift_amount = 0;
    do {
        decoded_value |= (uint64_t)(data[i] & 127) << shift_amount;
        shift_amount += 7;
    } while ( (data[i++] & 128) != 0 );
    decoded_bytes = i;
    return decoded_value;
}