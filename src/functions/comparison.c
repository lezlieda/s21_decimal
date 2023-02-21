#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_bigdecimal bigdec_1 = {0};
  s21_bigdecimal bigdec_2 = {0};
  decimal_to_bigdec(value_1, &bigdec_1);
  decimal_to_bigdec(value_2, &bigdec_2);
  return is_equal_bigdec(bigdec_1, bigdec_2);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_bigdecimal bigdec_1 = {0};
  s21_bigdecimal bigdec_2 = {0};
  decimal_to_bigdec(value_1, &bigdec_1);
  decimal_to_bigdec(value_2, &bigdec_2);
  return is_less_bigdec(bigdec_1, bigdec_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less_or_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}
