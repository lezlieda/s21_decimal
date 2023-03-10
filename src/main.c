#include "s21_decimal.h"

int main() {
  // s21_decimal a = {0};
  // s21_decimal b = {0};
  // s21_decimal c = {0};

  // a.bits[0] = 0xF00EB0B0;
  // // a.bits[1] = 0xFFFFFFFF;
  // // a.bits[2] = 0xFFFFFFFF;

  // b.bits[0] = 0xD1C0C0C;
  // // b.bits[1] = 0xFFFFFFFF;
  // // b.bits[2] = 0xFFFF0FFF;

  // a.bits[3] = 4 << 16;
  // b.bits[3] = 7 << 16;
  // b.bits[3] |= 0x80000000;

  // float aa, bb, cc;
  // s21_from_decimal_to_float(a, &aa);
  // s21_from_decimal_to_float(b, &bb);

  // printf("a = %f; bits:\n", aa);
  // print_decimal_bits(a);
  // printf("b = %f; bits:\n", bb);
  // print_decimal_bits(b);

  // int res = s21_sub(a, b, &c);

  // s21_from_decimal_to_float(c, &cc);
  // printf("res = %d; c = %f; bits:\n", res, cc);
  // print_decimal_bits(c);

  s21_bigdecimal a = (s21_bigdecimal){0};

  a.bits[0] = 0x2FAF0800;
  a.bits[7] = 10 << 16;
  printf("a.bits:\n");
  print_bigdecimal_bits(a);

  s21_decimal aa = {0};
  bigdec_to_decimal(a, &aa);
  float aaa = 0;
  s21_from_decimal_to_float(aa, &aaa);

  printf("aa = %f; bits:\n", aaa);
  print_decimal_bits(aa);

  compress_bigdec(&a);
  printf("after compression a.bits:\n");
  print_bigdecimal_bits(a);
  bigdec_to_decimal(a, &aa);
  s21_from_decimal_to_float(aa, &aaa);
  printf("aa = %f; bits:\n", aaa);
  print_decimal_bits(aa);

  return 0;
}
