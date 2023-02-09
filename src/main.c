#include "s21_decimal.h"

int main() {
  s21_bigdecimal a = {0};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0xFFFFFFFF;
  a.bits[4] = 0xFFFFFFFF;
  a.bits[5] = 0xFFFFFFFF;
  a.bits[6] = 0xFFFFFFFF;

  print_bigdecimal_bits(a);
  printf("\n");
  s21_bigdecimal b = {0};

  b.bits[0] = 0x1;
  print_bigdecimal_bits(b);
  printf("\n");
  s21_bigdecimal c = {0};

  bigdec_add_noscale(a, b, &c);
  print_bigdecimal_bits(c);

  return 0;
}

// 0000 0000 0000 0001 0000 0000 0000 0000
