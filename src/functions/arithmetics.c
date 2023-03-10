#include "../s21_decimal.h"
/*
 *  Функции возвращают код ошибки:
 *  0 - OK
 *  1 - число слишком велико или равно бесконечности
 *  2 - число слишком мало или равно отрицательной бесконечности
 *  3 - деление на 0
 */

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_bigdecimal val_1 = (s21_bigdecimal){0};
  s21_bigdecimal val_2 = (s21_bigdecimal){0};
  s21_bigdecimal val_r = (s21_bigdecimal){0};
  decimal_to_bigdec(value_1, &val_1);
  decimal_to_bigdec(value_2, &val_2);
  scale_equilizer_bigdec(&val_1, &val_2);
  int scale = get_bigdec_scale(val_1);
  int sign_1 = get_bigdec_sign(val_1);
  int sign_2 = get_bigdec_sign(val_2);
  set_bigdec_sign(&val_1, 0);
  set_bigdec_sign(&val_2, 0);
  int bigger = is_greater_or_equal_bigdec(val_1, val_2);
  if (sign_1 ^ sign_2) {
    if (bigger) {
      sub_bigdec_noscale(val_1, val_2, &val_r);
      set_bigdec_sign(&val_r, sign_1);
    } else {
      sub_bigdec_noscale(val_2, val_1, &val_r);
      set_bigdec_sign(&val_r, sign_2);
    }
  } else {
    add_bigdec_noscale(val_1, val_2, &val_r);
    set_bigdec_sign(&val_r, sign_1);
  }
  set_bigdec_scale(&val_r, scale);
  error = bigdec_to_decimal(val_r, result);
  if (error && get_bigdec_sign(val_r)) error = 2;
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal tmp_2 = value_2;
  tmp_2.bits[3] ^= 0x80000000;
  error = s21_add(value_1, tmp_2, result);
  return error;
}
