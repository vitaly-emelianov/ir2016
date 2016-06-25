def simhash(tokens, hashbits=64):
    """Calculate simhash given tokens and hash size."""
    v = [0]*hashbits
    for t in [x.__hash__() for x in tokens]:
        bitmask = 0
        for i in xrange(hashbits):
            bitmask = 1 << i
            if t & bitmask:
                v[i] += 1
            else:
                v[i] -= 1
    fingerprint = 0
    for i in xrange(hashbits):
        if v[i] >= 0:
            fingerprint += 1 << i
    return fingerprint


def distance(a, b, hashbits=64):
    """Calculate Hamming distance between a and b."""
    x = (a ^ b) & ((1 << hashbits) - 1)
    total = 0
    while x:
        total += 1
        x &= x-1
    return total
