#include "s21_decimal.h"

int main() {
  // s21_bigdecimal a = {0};
  // s21_bigdecimal b = {0};

  // a.bits[1] = 0xF00EB0B0;
  // b.bits[0] = 0xC0C1D1C;

  // s21_bigdecimal c = {0};

  // printf("a: \n");
  // print_bigdecimal_bits(a);

  // printf("b: \n");
  // print_bigdecimal_bits(b);

  // div_bigdec(a, b, &c);

  // printf("c: \n");
  // print_bigdecimal_bits(c);

  int a = 0b1010100001;
  int b = 0b111;
  int c = 0;

  printf("a: %d\n", a);
  print_int_bits(a);
  printf("b: %d\n", b);
  print_int_bits(b);

  int z = div_words(a, b, &c);

  printf("z: %d\n", z);

  printf("c: %d\n", c);
  print_int_bits(c);

  //***************************************************************//

  // s21_decimal z = {0};
  // s21_decimal x = {0};

  // // z.bits[2] = 0xEE019612;
  // x.bits[0] = 0xEE019612;
  // z.bits[3] = 1 << 31;

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

  // s21_bigdecimal xxx = {0};
  // s21_bigdecimal zzz = {0};
  // decimal_to_bigdec(x, &xxx);
  // decimal_to_bigdec(z, &zzz);

  // printf("is_zero(x): %d\n", is_bigdec_zero(xxx));
  // printf("is_zero(z): %d\n", is_bigdec_zero(zzz));

  return 0;
}

// 721351540736.000000
// 721351564935