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
/**
 * @brief the program calculates the number of 1's bit in a binary number
 *
 * bottom to top algorithm:
 * 1. calculate 1's bit in all 2-bit range with mask
 *   0b0101 0101 ... 0101 0101 = 0x5555 5555
 * 2. calculate 1's bit in all 4-bit range with mask
 *   0b0011 0011 ... 0011 0011 = 0x3333 3333
 * 3. ... in all 8-bit range with mask 0b0000 1111 ... 0000 1111 = 0x0F0F 0F0F
 * 4. ... in all 16-bit range with mask 0b 0000 0000 1111 1111 ... = 0x00FF 00FF
 * 5. ... in all 32-bit range with mask 0b 0000 ...1111 = 0x0000 FFFF
 *
 * x := x & mask + (x >> half range) & mask
 *
 * @param num
 * @return int
 */
int BitCounter(int num) {
    vector<int> mask = {0x55555555, 0x33333333, 0x0f0f0f0f, 0x00ff00ff, 0x0000ffff};
    int shift = 4;   // 2^4 = 16, it will be shifted at most 16 bit in the last round for
                     // the 32 bit number
    for (int i = 0; i <= shift; i++) {
        int highbits = num >> (1 << i);
        int low = num & mask[i];
        int high = highbits & mask[i];
        num = low + high;
    }

    return num;
}
```

## Eliminate Least Bit 1

> Say we have an binary number `0b1110 0100` and we want to eliminate the least bit 1 (which is on 3rd bit from LSB to HSB).

One useful operation to do that is `x & (x - 1)`.

The function of `x - 1` is to set the least bit 1 to 0 and all following 0s to 1 due to borrowing 1 bit from 1's bit, and keep other bits unchanged.

```text
ex>  0b1110 0100
  -1 0b1110 0011
             ^
       least bit 1
   &
  ---------------
     0b1110 0000
```

With the trick above, we can calculate 1's bit in a binary number by eliminating least bit 1 repeatedly.

```c++
int BitCounterII(int num) {
    int cnt = 0;
    while (num != 0) {
        num &= (num - 1);
        cnt++;
    }

    return cnt;
}
```

