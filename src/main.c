#include "s21_decimal.h"

int main() {
  // s21_decimal a = {0};
  // a.bits[0] = 0x3B9ACA00;
  // a.bits[3] = 9 << 16;
  // print_decimal_bits(a);

  // float aa = 0;
  // s21_from_decimal_to_float(a, &aa);
  // printf("aa = %f\n", aa);
  // s21_decimal b = {0};
  // b.bits[0] = 1;
  // print_decimal_bits(b);
  // float bb = 0;
  // s21_from_decimal_to_float(b, &bb);
  // printf("bb = %f\n", bb);

  // int res = s21_is_greater_or_equal(a, b);
  // printf("res = %d\n", res);

  s21_bigdecimal c = {0};
  c.bits[0] = 0b1111000011110000;
  // c.bits[1] = 0x000EB0B0;
  print_bigdecimal_bits(c);
  s21_decimal d = {0};
  bigdec_to_dec(c, &d);
  float dd = 0;
  s21_from_decimal_to_float(d, &dd);
  printf("dd = %f\n", dd);
  printf("\n");
  bigdec_mul_by_10(&c);
  print_bigdecimal_bits(c);
  bigdec_to_dec(c, &d);
  s21_from_decimal_to_float(d, &dd);
  printf("dd = %f\n", dd);

  return 0;
}
