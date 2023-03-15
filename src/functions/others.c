#include "../s21_decimal.h"

/*
 * Возвращаемое значение - код ошибки:
 *    0 - OK
 *    1 - ошибка вычисления
 */

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  *result = (s21_decimal){0};
  int sign = get_dec_sign(value);
  int scale = get_dec_scale(value);
  printf("sign = %d, scale = %d\n", sign, scale);
  s21_bigdecimal val = {0};
  decimal_to_bigdec(value, &val);
  while (scale > 0) {
    bigdec_div_by_10(&val);
    scale--;
  }
  set_bigdec_sign(&val, sign);
  error = bigdec_to_decimal(val, result);
  return error;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  *result = (s21_decimal){0};
  *result = value;
  result->bits[3] ^= 0x80000000;
  return error;
}
