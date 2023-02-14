#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_bigdecimal bigdec_1 = {0};
  s21_bigdecimal bigdec_2 = {0};
  dec_to_bigdec(value_1, &bigdec_1);
  dec_to_bigdec(value_2, &bigdec_2);
  bigdec_scale_equilizer(&bigdec_1, &bigdec_2);
  if (is_bigdec_zero(bigdec_1) && is_bigdec_zero(bigdec_2)) {
    result = 1;
  } else if (get_bigdec_sign(bigdec_1) == get_bigdec_sign(bigdec_2)) {
    for (int i = 0; i < 7; i++) {
      if (bigdec_1.bits[i] != bigdec_2.bits[i]) {
        result = 0;
        break;
      } else {
        result = 1;
      }
    }
  } else {
    for (int i = 0; i < 7; i++) {
      if (bigdec_1.bits[i] != 0 && bigdec_2.bits[i] != 0) {
        result = 0;
        break;
      } else {
        result = 1;
      }
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_bigdecimal bigdec_1 = {0};
  s21_bigdecimal bigdec_2 = {0};
  dec_to_bigdec(value_1, &bigdec_1);
  dec_to_bigdec(value_2, &bigdec_2);
  bigdec_scale_equilizer(&bigdec_1, &bigdec_2);
  int sign_1 = get_bigdec_sign(bigdec_1);
  int sign_2 = get_bigdec_sign(bigdec_2);
  if (sign_1 == 0 && sign_2 == 1) {
    result = 0;
  } else if (sign_1 == 1 && sign_2 == 0) {
    result = 1;
  } else if (sign_1 == 0 && sign_2 == 0) {
    for (int i = 223; i >= 0; i--) {
      if (get_bigdec_bit(bigdec_1, i) < get_bigdec_bit(bigdec_2, i)) {
        result = 1;
        break;
      } else if (get_bigdec_bit(bigdec_1, i) > get_bigdec_bit(bigdec_2, i)) {
        result = 0;
        break;
      } else {
        result = 0;
      }
    }
  } else if (sign_1 == 1 && sign_2 == 1) {
    for (int i = 223; i >= 0; i--) {
      if (get_bigdec_bit(bigdec_1, i) < get_bigdec_bit(bigdec_2, i)) {
        result = 0;
        break;
      } else if (get_bigdec_bit(bigdec_1, i) > get_bigdec_bit(bigdec_2, i)) {
        result = 1;
        break;
      } else {
        result = 0;
      }
    }
  }
  return result;
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
