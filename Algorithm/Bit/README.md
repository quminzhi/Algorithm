# Bit Operations

## Query

> Check if ith bit is set.

Say we have `0b1110 0010`, we want check if kth (0-indexed) bit is set.

- shift right k bit: move kth bit to lowest significant bit (LSB).
- AND (&) `0b1`.

```text
ex> x = 0b1110 0010  check if 1th bit is set:

x >> 1: 0b0111 0001
x & 1 == 1 if 1th bit is set, and x & 1 == 0 if 1th bit is 0
```

## Set

- set kth bit (to 1)

OR x with kth mask (only 1 bit is set, ex> 0000 1000).

```text
ex> x = 0b1110 0010 set 1th bit:

make mask: shift left 1 bit, 1 << 1
OR: x |= (1 << 1)
```

- clear kth bit (to 0)

There are two ways: 1. query and XOR or 2. AND (~mask)

```text
ex> x = 0b1110 0110 clear/set 2th bit to 0

method 1. if ((x >> 2) & 1) then XOR mask (1 << 2)
          if ((x >> 2) & 1) {
              x ^= (1 << 2)
          }
method 2. ~mask (~(1 << 2)) AND (&) x, x &= ~(1 << 2)
```

## Bit Set

> calculate 1's bit in a binary number.

Bottom to up algorithm (conquer and divide): (8-bit example)

```text
ex > x = 0b1101 0111

0th (statistic on 1-bit level)

1st (statistic on 2-bit level): x & 0b0101 0101 + (x >> 1) & 0b0101 0101
=> 0b0101 0101 + 0b0110 1011 & 0b0101 0101 = 0b0101 0101 + 0b0100 0001 = 0b1001 0110 (on 2-bit level, we have [2, 1, 1, 2] 1's bit)

2nd (statistic on 4-bit level): x & 0b0011 0011 + (x >> 2) & 0b0011 0011
=> 0b1001 0110 & 0b0011 0011 + 0b0010 0101 & 0b0011 0011 = 0b0001 0010 + 0b0010 0001 = 0b0011 0011 (3 1's bit on the left 4 bits and 3 1's bit on the right 4 bits)

3rd (statistic on 8-bit level): x & 0b0000 1111 + (x >> 4) & 0b0000 1111
=> 0b0011 0011 & 0b0000 1111 + 0b00000011 & 0b0000 1111 = 0b0000 0011 + 0b0000 0011 = 0b0000 0110 (so we got 0b110 (6) 1's bit)
```

```c++

```