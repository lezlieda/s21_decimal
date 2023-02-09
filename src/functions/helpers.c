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
  for (int i = 0; i < 4; i++) {
    for (int j = 31; j >= 0; j--) {
      printf("%d", (num.bits[i] >> j) & 1);
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
  for (int i = 0; i < 8; i++) {
    for (int j = 31; j >= 0; j--) {
      printf("%d", (num.bits[i] >> j) & 1);
    }
    printf("\n");
  }
}

int get_bigdec_sign(s21_bigdecimal src) { return (src.bits[7] >> 31) & 1; }

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

void print_uint_bits(uint64_t num) {
  for (int i = 63; i >= 0; i--) {
    printf("%ld", (num >> i) & 1);
  }
  printf("\n");
}

void print_int_bits(int num) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", (num >> i) & 1);
  }
  printf("\n");
}

// int int_words_sum(int a, int b, int *sum) {
//   int shift = 0;
//   uint64_t carry = 0;
//   uint64_t tmp_a = a;
//   // print_uint_bits(tmp_a);
//   uint64_t tmp_b = b;
//   // print_uint_bits(tmp_b);
//   while (tmp_b != 0) {
//     carry = tmp_a & tmp_b;
//     tmp_a ^= tmp_b;
//     tmp_b = carry << 1;
//   }
//   if (tmp_a > 0x7FFFFFFF) {
//     shift = 1;
//   }
//   // print_uint_bits(tmp_a);
//   *sum = tmp_a & 0xFFFFFFFF;
//   // print_int_bits(*sum);
//   return shift;
// }

int bigdec_add_noscale(s21_bigdecimal a, s21_bigdecimal b,
                       s21_bigdecimal *res) {
  *res = (s21_bigdecimal){0};
  int error = 0;
  int carry = 0;
  for (int i = 0; i < 7; i++) {
    uint64_t tmp_a = a.bits[i];
    uint64_t tmp_b = b.bits[i];
    uint64_t tmp_res = tmp_a + tmp_b + carry;
    if (tmp_res < tmp_a || tmp_res < tmp_b) {
      carry = 1;
    } else {
      carry = 0;
    }
    res->bits[i] = tmp_res & 0xFFFFFFFF;
  }
  if (carry) {
    error = 1;
  }
  printf("\terror: %d\n", error);
  return error;
}

// void normalize_bigdec(s21_bigdecimal *a, s21_bigdecimal *b) {
//   int res = 0;
//   int scale_a = get_bigdec_scale(*a);
//   int scale_b = get_bigdec_scale(*b);
// }
