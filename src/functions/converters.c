#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    *dst = (s21_decimal){0};  // обнуляем структуру
    dst->bits[0] = src;
    if (src < 0) {
      dst->bits[3] |= 1 << 31;  // устанавливаем бит знака
      dst->bits[0] = ~dst->bits[0] + 1;  // если число отрицательное, то
                                         // инвертируем его и прибавляем 1
    }
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    int scale = get_dec_scale(src);
    double data = 0;
    for (int i = 0; i < 96; i++) {
      data += get_dec_bit(src, i) * pow(2, i);
    }
    data /= pow(10, scale);
    if (get_dec_sign(src)) {
      data = -data;
      if (data == 0) data = -0.;
    }
    float_rounder(&data);
    *dst = (float)data;
  }

  return error;
}

// int s21_from_decimal_to_int(s21_decimal src, int *dst) {
//   int error = 0;
//   if (dst == NULL) {
//     error = 1;
//   } else {  // здесь следует использовать функцию s21_truncate, а потом
//             // записывать младшее слово
//     float frac = 0;
//     float tmp = 0;
//     s21_from_decimal_to_float(src, &tmp);
//     tmp = modff(tmp, &frac);
//     if (tmp > __INT_MAX__ || tmp < __WINT_MIN__) {
//       error = 1;
//     } else {
//       *dst = (int)tmp;
//     }
//   }
//   return error;
// }

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  }
  double cpy = src;
  if (fabs(cpy) > MAX_DECIMAL) {
    error = 1;
  } else if (fabs(cpy) < MIN_DECIMAL) {
    error = 1;
    *dst = (s21_decimal){0};
  } else {
    float_bits fb;
    fb.f = src;
    int sign = (fb.bits >> 31) & 1;
    int exp = (fb.bits >> 23) & 0xFF;
    exp -= 127;
    int mantissa = fb.bits & 0x7FFFFF;
    if (exp > 95 || exp < -95) {
      error = 1;
    } else {
      mantissa |= 1 << 23;
    }
    if (sign) dst->bits[3] |= 1 << 31;
  }
  return error;
}  // 8388607
