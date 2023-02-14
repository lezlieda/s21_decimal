#include "../s21_decimal.h"

int get_dec_bit(s21_decimal src, int pos) {
  int word = pos / 32;
  int bit_in_word = pos % 32;
  return (src.bits[word] >> bit_in_word) & 1;
}

int get_bigdec_bit(s21_bigdecimal src, int pos) {
  int word = pos / 32;
  int bit_in_word = pos % 32;
  return (src.bits[word] >> bit_in_word) & 1;
}

void set_dec_bit(s21_decimal *dst, int pos) {
  int word = pos / 32;
  int bit_in_word = pos % 32;
  dst->bits[word] |= 1 << bit_in_word;
}

void set_bigdec_bit(s21_bigdecimal *dst, int pos) {
  int word = pos / 32;
  int bit_in_word = pos % 32;
  dst->bits[word] |= 1 << bit_in_word;
}

int get_dec_sign(s21_decimal src) { return (src.bits[3] >> 31) & 1; }

int get_dec_scale(s21_decimal src) {
  int scale = 0;
  s21_decimal tmp = src;
  tmp.bits[3] >>= 16;
  tmp.bits[3] &= 0xFF;
  scale = tmp.bits[3];
  return scale;
}

int get_bigdec_scale(s21_bigdecimal src) {
  int scale = 0;
  s21_bigdecimal tmp = src;
  tmp.bits[7] >>= 16;
  tmp.bits[7] &= 0xFF;
  scale = tmp.bits[7];
  return scale;
}

void set_bigdec_scale(s21_bigdecimal *dst, int scale) {
  s21_bigdecimal tmp = *dst;
  tmp.bits[7] &= 0xFF00FFFF;
  tmp.bits[7] |= scale << 16;
  *dst = tmp;
}

int get_float_scale(float src) {
  int scale = 0;
  if (src < 1.0) {
    while (src < 1.0) {
      src *= 10.0;
      scale--;
    }
  } else {
    while (src >= 10.0) {
      src /= 10.0;
      scale++;
    }
  }
  return scale;
}

void float_rounder(double *src) {
  double int_part = 0;
  double fract_part = modf((double)*src, &int_part);
  fract_part = roundf(fract_part * 10000000);
  fract_part /= 10000000;
  *src = int_part + fract_part;
}

void print_float_bits(float num) {
  union float_bits fb;
  fb.f = num;
  for (int i = 31; i >= 0; i--) {
    printf("%d", (fb.bits >> i) & 1);
  }
  printf("\n");
}

void print_decimal_bits(s21_decimal num) {
  for (int i = 3; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      printf("%d", (num.bits[i] >> j) & 1);
      if (!(j % 4)) printf(" ");
    }
    printf("\n");
  }
}

void dec_to_bigdec(s21_decimal src, s21_bigdecimal *dst) {
  *dst = (s21_bigdecimal){0};
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[7] = src.bits[3];
}

void bigdec_to_dec(s21_bigdecimal src, s21_decimal *dst) {
  *dst = (s21_decimal){0};
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[7];
}

void print_bigdecimal_bits(s21_bigdecimal num) {
  for (int i = 7; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      printf("%d", (num.bits[i] >> j) & 1);
      if (!(j % 4)) printf(" ");
    }
    printf("\n");
  }
}

int get_bigdec_sign(s21_bigdecimal src) { return (src.bits[7] >> 31) & 1; }

void set_bigdec_sign(s21_bigdecimal *dst, int sign) {
  s21_bigdecimal tmp = *dst;
  tmp.bits[7] &= 0x7FFFFFFF;
  tmp.bits[7] |= sign << 31;
  *dst = tmp;
}

void left_shift_big(s21_bigdecimal *src, int shift) {
  for (int i = 0; i < shift; i++) {
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
    if (get_bigdec_bit(*src, 31)) s1 = 1;
    if (get_bigdec_bit(*src, 63)) s2 = 1;
    if (get_bigdec_bit(*src, 95)) s3 = 1;
    if (get_bigdec_bit(*src, 127)) s4 = 1;
    if (get_bigdec_bit(*src, 159)) s5 = 1;
    if (get_bigdec_bit(*src, 191)) s6 = 1;
    src->bits[0] <<= 1;
    src->bits[1] <<= 1;
    if (s1) set_bigdec_bit(src, 32);
    src->bits[2] <<= 1;
    if (s2) set_bigdec_bit(src, 64);
    src->bits[3] <<= 1;
    if (s3) set_bigdec_bit(src, 96);
    src->bits[4] <<= 1;
    if (s4) set_bigdec_bit(src, 128);
    src->bits[5] <<= 1;
    if (s5) set_bigdec_bit(src, 160);
    src->bits[6] <<= 1;
    if (s6) set_bigdec_bit(src, 192);
  }
}

s21_bigdecimal right_shift_big(s21_bigdecimal src, int shift) {
  s21_bigdecimal tmp = {0};
  tmp.bits[7] = src.bits[7];
  for (int i = 0; i < 223 - shift; i++) {
    if (get_bigdec_bit(src, i + shift)) set_bigdec_bit(&tmp, i);
  }
  return tmp;
}

void print_uint_bits(uint64_t num) {
  for (int i = 63; i >= 0; i--) {
    printf("%lld", (num >> i) & 1);
  }
  printf("\n");
}

void print_int_bits(int num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
  printf("\n");
}

int words_sum(int a, int b, int *sum) {
  int shift = 0;
  uint64_t carry = 0;
  uint64_t tmp_a = a & 0xFFFFFFFF;
  uint64_t tmp_b = b & 0xFFFFFFFF;
  while (tmp_b != 0) {
    carry = tmp_a & tmp_b;
    tmp_a ^= tmp_b;
    tmp_b = carry << 1;
  }
  *sum = tmp_a & 0xFFFFFFFF;
  if (tmp_a >> 32) {
    shift = 1;
  }
  return shift;
}

int words_sub(int a, int b, int *sub) {
  int shift = 0;
  uint64_t carry = 0;
  uint64_t tmp_a = a & 0xFFFFFFFF;
  uint64_t tmp_b = b & 0xFFFFFFFF;
  while (tmp_b != 0) {
    carry = (~tmp_a) & tmp_b;
    tmp_a ^= tmp_b;
    tmp_b = carry << 1;
  }
  *sub = tmp_a & 0xFFFFFFFF;
  if (tmp_a >> 32) {
    shift = 1;
  }
  return shift;
}

int bigdec_add_noscale(s21_bigdecimal a, s21_bigdecimal b,
                       s21_bigdecimal *res) {
  *res = (s21_bigdecimal){0};
  int error = 0;
  int carry = 0;
  s21_bigdecimal tmp = (s21_bigdecimal){0};
  for (int i = 0; i < 7; i++) {
    if (carry) tmp.bits[i] = 1;
    carry = words_sum(a.bits[i], b.bits[i], &res->bits[i]);
  }
  int flag = 0;
  for (int i = 0; i < 7; i++) {
    if (tmp.bits[i] != 0) flag = 1;
  }
  if (flag) bigdec_add_noscale(*res, tmp, res);
  if (carry) error = 1;
  return error;
}

int bigdec_sub_noscale(s21_bigdecimal a, s21_bigdecimal b,
                       s21_bigdecimal *res) {
  *res = (s21_bigdecimal){0};
  int error = 0;
  int carry = 0;
  s21_bigdecimal tmp = (s21_bigdecimal){0};
  for (int i = 0; i < 7; i++) {
    if (carry) tmp.bits[i] = 1;
    carry = words_sub(a.bits[i], b.bits[i], &res->bits[i]);
  }
  int flag = 0;
  for (int i = 0; i < 7; i++) {
    if (tmp.bits[i] != 0) flag = 1;
  }
  if (flag) bigdec_sub_noscale(*res, tmp, res);
  if (carry) error = 1;
  return error;
}

void bigdec_mul_by_10(s21_bigdecimal *src) {
  s21_bigdecimal tmp = *src;
  left_shift_big(src, 3);
  left_shift_big(&tmp, 1);
  bigdec_add_noscale(*src, tmp, src);
}

void bigdec_scale_equilizer(s21_bigdecimal *a, s21_bigdecimal *b) {
  int scale_a = get_bigdec_scale(*a);
  int scale_b = get_bigdec_scale(*b);
  if (scale_a > scale_b) {
    for (int i = 0; i < scale_a - scale_b; i++) {
      bigdec_mul_by_10(b);
    }
  } else if (scale_a < scale_b) {
    for (int i = 0; i < scale_b - scale_a; i++) {
      bigdec_mul_by_10(a);
    }
  }
}

int is_bigdec_zero(s21_bigdecimal src) {
  int flag = 1;
  for (int i = 0; i < 223; i++) {
    if (get_bigdec_bit(src, i)) flag = 0;
  }
  return flag;
}
