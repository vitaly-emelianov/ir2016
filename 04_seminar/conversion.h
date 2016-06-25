//
// Created by vitaly on 4/6/16.
//

#ifndef VARINT_CONVERSION_H
#define VARINT_CONVERSION_H

#include <iostream>


namespace Conversion {
    uint64_t decodeVarInt(const uint8_t* const data, size_t decoded_bytes);
    size_t encodeVarInt(uint8_t* const buffer, uint64_t value);
}

#endif //VARINT_CONVERSION_H

