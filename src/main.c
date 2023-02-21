#include "s21_decimal.h"

int main() {
  s21_bigdecimal a = {0};
  a.bits[0] = 918919191;
  a.bits[1] = 1;
  a.bits[3] = 0xF << 28;
  a.bits[4] = 0xF << 28;
  a.bits[5] = 0xF << 28;
  a.bits[6] = 0xF << 28;
  a.bits[7] = 5 << 16;
  print_uint_bits(a.bits[6]);
  printf("a:\n");
  print_bigdecimal_bits(a);
  right_shift_big(&a, 45);
  printf("a >> 45:\n");
  print_bigdecimal_bits(a);

  // s21_bigdecimal b = {0};
  // b.bits[0] = 785;
  // printf("b:\n");
  // print_bigdecimal_bits(b);
  // bigdec_to_decimal(b, &aa);
  // s21_from_decimal_to_float(aa, &aaa);
  // printf("float b: %.8f\n", aaa);

  // s21_bigdecimal c = {0};
  // mul_bigdec_noscale(a, b, &c);
  // c.bits[7] = 5 << 16;
  // print_bigdecimal_bits(c);

  // bigdec_to_decimal(c, &aa);
  // s21_from_decimal_to_float(aa, &aaa);
  // printf("float c: %.8f\n", aaa);

  //***************************************************************//

  // s21_decimal z = {0};
  // s21_decimal x = {0};

  // z.bits[0] = 0x000EB0B1;
  // x.bits[0] = 0x000EB0B0;

  // // z.bits[2] = 0xEE019612;
  // // x.bits[2] = 0xEE019612;
  // z.bits[3] = 3 << 16;
  // x.bits[3] = 2 << 16;

  // float zz = 0;
  // float xx = 0;
  // s21_from_decimal_to_float(z, &zz);
  // s21_from_decimal_to_float(x, &xx);

  // printf("z: ");
  // print_decimal_bits(z);
  // printf("float z: %.8f\n", zz);
  // printf("x: ");
  // print_decimal_bits(x);
  // printf("float x: %.8f\n", xx);

  // int l = s21_is_less(z, x);

  // printf("z < x: %d\n", l);

  return 0;
}

// 721351540736.000000
// 721351564935