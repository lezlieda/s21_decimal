#include "s21_decimal.h"

int main() {
  s21_decimal a = {0};
  a.bits[0] = 0xFFFFFFFD;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  // a.bits[3] = 28 << 16;
  // print_decimal_bits(a);

  // float aa = 0;
  // s21_from_decimal_to_float(a, &aa);
  // printf("aa = %f\n", aa);

  s21_decimal b = {0};
  b.bits[0] = 0x5;
  b.bits[3] = 1 << 16;
  // print_decimal_bits(b);
  // float bb = 0;
  // s21_from_decimal_to_float(b, &bb);
  // printf("bb = %f\n", bb);

  s21_bigdecimal aaa = {0};
  s21_bigdecimal bbb = {0};
  decimal_to_bigdec(a, &aaa);
  printf("aaa:\n");
  print_bigdecimal_bits(aaa);
  decimal_to_bigdec(b, &bbb);
  printf("bbb:\n");
  print_bigdecimal_bits(bbb);
  s21_bigdecimal ccc = {0};
  scale_equilizer_bigdec(&aaa, &bbb);
  int scale = get_bigdec_scale(bbb);
  printf("scale = %d\n", scale);
  add_bigdec_noscale(aaa, bbb, &ccc);
  ccc.bits[7] |= scale << 16;
  print_bigdecimal_bits(ccc);
  s21_decimal ddd = {0};
  bigdec_to_decimal(ccc, &ddd);
  print_decimal_bits(ddd);

  // s21_bigdecimal c = {0};
  // c.bits[5] = 0xFFFFFFFF;
  // c.bits[7] = 25 << 16;
  // // c.bits[1] = 0x000EB0B0;
  // print_bigdecimal_bits(c);
  // s21_decimal d = {0};
  // bigdec_to_dec(c, &d);
  // float dd = 0;
  // s21_from_decimal_to_float(d, &dd);
  // printf("dd = %f\n", dd);
  // printf("\n");
  // bigdec_mul_by_10(&c);
  // print_bigdecimal_bits(c);
  // bigdec_to_dec(c, &d);
  // s21_from_decimal_to_float(d, &dd);
  // printf("dd = %f\n", dd);
  // right_shift_big(&c, 4);
  // print_bigdecimal_bits(c);

  return 0;
}
