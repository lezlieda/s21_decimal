#include "s21_decimal.h"

int main() {
  s21_decimal a = {0};
  s21_decimal b = {0};

  a.bits[0] = 0x93BC;
  a.bits[1] = 0x6124FEE9;
  // a.bits[2] = 0xF0005051;
  a.bits[3] = 14 << 16;

  b.bits[0] = 0xC0C0;
  b.bits[1] = 0x15050783;
  b.bits[3] = 16 << 16;

  s21_negate(a, &a);
  s21_negate(b, &b);

  float aa = 0;
  s21_from_decimal_to_float(a, &aa);
  printf("aa = %.28f, a.bits:\n", aa);
  print_decimal_bits(a);

  float bb = 0;
  s21_from_decimal_to_float(b, &bb);
  printf("bb = %.28f, b.bits:\n", bb);
  print_decimal_bits(b);

  s21_decimal c = {0};
  printf("mul = %d\n", s21_mul(a, b, &c));
  float cc = 0;
  s21_from_decimal_to_float(c, &cc);
  printf("cc = %.28f, b.bits:\n", cc);
  print_decimal_bits(c);

  // s21_bigdecimal u = {0};
  // s21_bigdecimal v = {0};
  // s21_bigdecimal w = {0};

  // decimal_to_bigdec(a, &u);
  // decimal_to_bigdec(b, &v);
  // bigdec_mul_noscale(u, v, &w);
  // printf("w.bits:\n");
  // print_bigdecimal_bits(w);

  return 0;
}
