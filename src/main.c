#include "s21_decimal.h"

int main() {
  s21_decimal a = {0};
  s21_decimal b = {0};

  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  // a.bits[3] = 1 << 31;

  b.bits[0] = 0x6;
  b.bits[3] = 1 << 16;

  float aa = 0;
  s21_from_decimal_to_float(a, &aa);
  printf("aa = %.8f, a.bits:\n", aa);
  print_decimal_bits(a);

  float bb = 0;
  s21_from_decimal_to_float(b, &bb);
  printf("bb = %.8f, b.bits:\n", bb);
  print_decimal_bits(b);

  s21_decimal c = {0};
  printf("result of sub = %d\n", s21_sub(a, b, &c));
  float cc = 0;
  s21_from_decimal_to_float(c, &cc);
  printf("cc = %.8f, c.bits:\n", cc);
  print_decimal_bits(c);

  return 0;
}
