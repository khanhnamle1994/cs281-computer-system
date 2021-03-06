// James Le
// CS281 - Fall 2015
// Dr. Thomas Bressoud
// 9/25/2015

#include <stdio.h>

int x = 5;
int y = 3;
unsigned z;
int result;

int main(int argc, char **argv)
{
  result = x + y; // Add
  result = x - y; // Subtract
  result = x * y; // Multiply
  result = x ^ y; // Exclusive-or
  result = x | y; // Or
  result = x & y; // And
  result = -x; // Negate
  result = ~x; // Complement
  result = x++; // Load effective address
  result = x >> 2; // Arithmetic right shift
  result = z >> 2; // Logical right shift

  printf("result = %d (0x%8.8x)\n", result, result);
  return 0;
}

