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

void decimal_to_bigdec(s21_decimal src, s21_bigdecimal *dst) {
  *dst = (s21_bigdecimal){0};
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[7] = src.bits[3];
}

int bigdec_to_decimal(s21_bigdecimal src, s21_decimal *dst) {
  int error = 0;
  *dst = (s21_decimal){0};
  dst->bits[0] = src.bits[0];
  dst->bits[1] = src.bits[1];
  dst->bits[2] = src.bits[2];
  dst->bits[3] = src.bits[7];
  for (int i = 3; i < 7; i++) {
    if (src.bits[i] & 0xFFFFFFF) error = 1;
  }
  return error;
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

void right_shift_big(s21_bigdecimal *src, int shift) {
  for (int i = 0; i < shift; i++) {
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
    if (get_bigdec_bit(*src, 32)) s1 = 1;
    if (get_bigdec_bit(*src, 64)) s2 = 1;
    if (get_bigdec_bit(*src, 96)) s3 = 1;
    if (get_bigdec_bit(*src, 128)) s4 = 1;
    if (get_bigdec_bit(*src, 160)) s5 = 1;
    if (get_bigdec_bit(*src, 192)) s6 = 1;
    src->bits[0] >>= 1;
    src->bits[0] &= 0x7FFFFFFF;
    if (s1) set_bigdec_bit(src, 31);
    src->bits[1] >>= 1;
    src->bits[1] &= 0x7FFFFFFF;
    if (s2) set_bigdec_bit(src, 63);
    src->bits[2] >>= 1;
    src->bits[2] &= 0x7FFFFFFF;
    if (s3) set_bigdec_bit(src, 95);
    src->bits[3] >>= 1;
    src->bits[3] &= 0x7FFFFFFF;
    if (s4) set_bigdec_bit(src, 127);
    src->bits[4] >>= 1;
    src->bits[4] &= 0x7FFFFFFF;
    if (s5) set_bigdec_bit(src, 159);
    src->bits[5] >>= 1;
    src->bits[5] &= 0x7FFFFFFF;
    if (s6) set_bigdec_bit(src, 191);
    src->bits[6] >>= 1;
    src->bits[6] &= 0x7FFFFFFF;
  }
}

void print_uint_bits(int64_t num) {
  for (int i = 63; i >= 0; i--) {
#ifdef __APPLE__
    printf("%lld", (num >> i) & 1);
#elif __linux__
    printf("%ld", (num >> i) & 1);
#endif
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
  int64_t carry = 0;
  int64_t tmp_a = a & 0xFFFFFFFF;
  int64_t tmp_b = b & 0xFFFFFFFF;
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
  int64_t carry = 0;
  int64_t tmp_a = a & 0xFFFFFFFF;
  int64_t tmp_b = b & 0xFFFFFFFF;
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

int add_bigdec_noscale(s21_bigdecimal a, s21_bigdecimal b,
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
  if (flag) add_bigdec_noscale(*res, tmp, res);
  if (carry) error = 1;
  return error;
}

int sub_bigdec_noscale(s21_bigdecimal a, s21_bigdecimal b,
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
  if (flag) sub_bigdec_noscale(*res, tmp, res);
  if (carry) error = 1;
  return error;
}

void bigdec_mul_by_10(s21_bigdecimal *src) {
  s21_bigdecimal tmp = *src;
  int sign = get_bigdec_sign(*src);
  int scale = get_bigdec_scale(*src);
  left_shift_big(src, 3);
  left_shift_big(&tmp, 1);
  add_bigdec_noscale(*src, tmp, src);
  set_bigdec_scale(src, scale + 1);
  set_bigdec_sign(src, sign);
}

int mul_bigdec_noscale(s21_bigdecimal a, s21_bigdecimal b,
                       s21_bigdecimal *res) {
  *res = (s21_bigdecimal){0};
  int error = 0;
  s21_bigdecimal zero = (s21_bigdecimal){0};
  while (!is_equal_bigdec(b, zero) && !error) {
    if (b.bits[0] & 1) {
      error = add_bigdec_noscale(*res, a, res);
    }
    left_shift_big(&a, 1);
    right_shift_big(&b, 1);
  }
  return error;
}

void scale_equilizer_bigdec(s21_bigdecimal *a, s21_bigdecimal *b) {
  int scale_a = get_bigdec_scale(*a);
  int scale_b = get_bigdec_scale(*b);
  if (scale_a > scale_b) {
    for (int i = 0; i < scale_a - scale_b; i++) {
      bigdec_mul_by_10(b);
    }
    set_bigdec_scale(b, scale_a);

  } else if (scale_a < scale_b) {
    for (int i = 0; i < scale_b - scale_a; i++) {
      bigdec_mul_by_10(a);
    }
    set_bigdec_scale(a, scale_b);
  }
}

int is_bigdec_zero(s21_bigdecimal src) {
  int i = 223;
  while (i >= 0 && !get_bigdec_bit(src, i)) i--;
  return i == -1;
}

int is_equal_bigdec(s21_bigdecimal bigdec_1, s21_bigdecimal bigdec_2) {
  int result = 0;
  scale_equilizer_bigdec(&bigdec_1, &bigdec_2);
  if (is_bigdec_zero(bigdec_1) && is_bigdec_zero(bigdec_2)) {
    result = 1;
  } else if (get_bigdec_sign(bigdec_1) == get_bigdec_sign(bigdec_2)) {
    result = 1;
    int i = 223;
    while (i > 0) {
      if (get_bigdec_bit(bigdec_1, i) != get_bigdec_bit(bigdec_2, i)) {
        result = 0;
        i = 0;
      }
      i--;
    }
  } else {
    result = 0;
  }
  return result;
}

int is_less_bigdec(s21_bigdecimal bigdec_1, s21_bigdecimal bigdec_2) {
  int result = 0;
  scale_equilizer_bigdec(&bigdec_1, &bigdec_2);
  int sign_1 = get_bigdec_sign(bigdec_1);
  int sign_2 = get_bigdec_sign(bigdec_2);
  if (is_bigdec_zero(bigdec_1) && is_bigdec_zero(bigdec_2)) {
    result = 0;
  } else if (sign_1 ^ sign_2) {
    result = sign_1;
  } else {
    int i = 223;
    while (i >= 0) {
      if (get_bigdec_bit(bigdec_1, i) < get_bigdec_bit(bigdec_2, i)) {
        result = sign_1 == 0 ? 1 : 0;
        i = -1;
      } else if (get_bigdec_bit(bigdec_1, i) > get_bigdec_bit(bigdec_2, i)) {
        result = sign_1 == 0 ? 0 : 1;
        i = -1;
      } else {
        // result = 0;
        i--;
      }
      // i--;
    }
  }
  return result;
}

// int is_less_bigdec(s21_bigdecimal bigdec_1, s21_bigdecimal bigdec_2) {
//   int result = 0;
//   scale_equilizer_bigdec(&bigdec_1, &bigdec_2);
//   int sign_1 = get_bigdec_sign(bigdec_1);
//   int sign_2 = get_bigdec_sign(bigdec_2);
//   if (sign_1 == 0 && sign_2 == 1) {
//     result = 0;
//   } else if (sign_1 == 1 && sign_2 == 0) {
//     result = 1;
//   } else {
//     int i = 223;
//     while (i >= 0) {
//       if (get_bigdec_bit(bigdec_1, i) < get_bigdec_bit(bigdec_2, i)) {
//         result = sign_1 == 0 ? 1 : 0;
//         i = 0;
//       } else if (get_bigdec_bit(bigdec_1, i) > get_bigdec_bit(bigdec_2, i)) {
//         result = sign_1 == 0 ? 0 : 1;
//         i = 0;
//       } else {
//         result = 0;
//       }
//       i--;
//     }
//   }
//   return result;
// }

int is_not_equal_bigdec(s21_bigdecimal value_1, s21_bigdecimal value_2) {
  return !is_equal_bigdec(value_1, value_2);
}

int is_less_or_equal_bigdec(s21_bigdecimal value_1, s21_bigdecimal value_2) {
  return is_less_bigdec(value_1, value_2) || is_equal_bigdec(value_1, value_2);
}

int is_greater_bigdec(s21_bigdecimal value_1, s21_bigdecimal value_2) {
  return !is_less_or_equal_bigdec(value_1, value_2);
}

int is_greater_or_equal_bigdec(s21_bigdecimal value_1, s21_bigdecimal value_2) {
  return !is_less_bigdec(value_1, value_2) || is_equal_bigdec(value_1, value_2);
}

int div_int_bigdec(s21_bigdecimal value_a, s21_bigdecimal value_b,
                   s21_bigdecimal *result) {
  int error = 0;
  s21_bigdecimal tmp_r = (s21_bigdecimal){0};
  s21_bigdecimal tmp_a = (s21_bigdecimal)value_a;
  for (int i = 223; i >= 0; i--) {
    s21_bigdecimal tmp_b = value_b;
    left_shift_big(&tmp_b, i);
    if (is_greater_or_equal_bigdec(tmp_a, tmp_b)) {
      error = sub_bigdec_noscale(tmp_a, tmp_b, &tmp_a);
      if (i < 223) set_bigdec_bit(&tmp_r, i);
    }
  }
  *result = (s21_bigdecimal)tmp_r;
  return error;
}

void div_by_10(s21_bigdecimal *value) {
  s21_bigdecimal tmp = *value;
  int scale = get_bigdec_scale(*value);
  s21_bigdecimal ten = (s21_bigdecimal){0};
  ten.bits[0] = 0xA;
  div_int_bigdec(tmp, ten, &tmp);
  set_bigdec_scale(&tmp, scale - 1);
  *value = tmp;
}

void bigdec_zero_remover(s21_bigdecimal *src) {
  s21_bigdecimal tmp = *src;
  int scale = get_bigdec_scale(*src);
  int count = 0;
  while (is_equal_bigdec(tmp, *src)) {
    div_by_10(&tmp);
    set_bigdec_scale(&tmp, --scale);
    count++;
  }
  for (int i = count - 1; i > 0; i--) {
    div_by_10(src);
  }
}

int is_mantissa_big(s21_bigdecimal value) {
  int result = 0;
  for (int i = 3; i < 7; i++) {
    if (value.bits[i] != 0) {
      result = 1;
      i = 7;
    }
  }
  return result;
}

void bigdec_mantissa_round(s21_bigdecimal *src) {
  s21_bigdecimal max_decimal = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0, 0}};
  s21_bigdecimal tmp = *src;
  int sign = get_bigdec_sign(tmp);
  set_bigdec_sign(&tmp, 0);
  if (is_mantissa_big(tmp) && is_less_or_equal_bigdec(tmp, max_decimal)) {
    while (is_mantissa_big(tmp)) {
      div_by_10(&tmp);
    }
  }
  set_bigdec_sign(&tmp, sign);
  *src = tmp;
}

int div_words(int a, int b, int *res) {
  unsigned int tmp_a = 0xFFFFFFFF & a;
  unsigned int tmp_b = 0xFFFFFFFF & b;
  unsigned int tmp_res = 0;
  for (int i = 31; i >= 0; i--) {
    if (tmp_a >= tmp_b << i) {
      tmp_a -= tmp_b << i;
      tmp_res += (1 << i);
    }
  }
  *res = tmp_res;

  return tmp_a;
}
