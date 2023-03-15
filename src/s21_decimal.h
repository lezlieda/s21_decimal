#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int bits[8];
} s21_bigdecimal;

typedef union float_bits {
  float f;
  uint32_t bits;
} float_bits;

// bits[0] - младшие биты 96-разрядного числа
// bits[1] - средние биты 96-разрядного числа
// bits[2] - старшие биты 96-разрядного числа
// bits[3] - биты 0-15 не используются и всегда равны 0
//         - биты 16-23 содержат показатель степени от 0 до 28, который
//           указывает степень 10 для разделения целого числа
//         - биты 24-30 не используются и всегда равны 0
//         - бит 31 содержит знак числа (0 - положительный, 1 - отрицательный)

// Конвертация
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// Сравнение
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

// Другие функции
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Вспомогательные функции
int get_dec_bit(s21_decimal src, int pos);
void set_dec_bit(s21_decimal *dst, int pos);
int get_dec_sign(s21_decimal src);
int get_dec_scale(s21_decimal src);
int get_bigdec_scale(s21_bigdecimal src);
int get_float_scale(float src);
void float_rounder(double *src);
void print_float_bits(float num);
void print_decimal_bits(s21_decimal num);
void decimal_to_bigdec(s21_decimal src, s21_bigdecimal *dst);
int bigdec_to_decimal(s21_bigdecimal src, s21_decimal *dst);
void print_bigdecimal_bits(s21_bigdecimal num);
int get_bigdec_sign(s21_bigdecimal src);
void left_shift_big(s21_bigdecimal *src, int shift);
void right_shift_big(s21_bigdecimal *src, int shift);
// s21_bigdecimal right_shift_big(s21_bigdecimal src, int shift);
int get_bigdec_bit(s21_bigdecimal src, int pos);
void set_bigdec_bit(s21_bigdecimal *dst, int pos);
int is_bigdec_zero(s21_bigdecimal src);
void set_bigdec_sign(s21_bigdecimal *dst, int sign);

int words_sum(int a, int b, int *sum);
int add_bigdec_noscale(s21_bigdecimal a, s21_bigdecimal b, s21_bigdecimal *res);
int words_sub(int a, int b, int *sub);
int sub_bigdec_noscale(s21_bigdecimal a, s21_bigdecimal b, s21_bigdecimal *res);

void scale_equilizer_bigdec(s21_bigdecimal *a, s21_bigdecimal *b);
void bigdec_zero_remover(s21_bigdecimal *src);
void div_by_10(s21_bigdecimal *value);

int is_mantissa_big(s21_bigdecimal value);
void bigdec_mantissa_round(s21_bigdecimal *src);

void print_uint_bits(int64_t num);
void print_int_bits(int num);

int is_equal_bigdec(s21_bigdecimal bigdec_1, s21_bigdecimal bigdec_2);
int is_less_bigdec(s21_bigdecimal bigdec_1, s21_bigdecimal bigdec_2);
int is_greater_or_equal_bigdec(s21_bigdecimal value_1, s21_bigdecimal value_2);

int bigdec_mul_noscale(s21_bigdecimal a, s21_bigdecimal b, s21_bigdecimal *res);

int div_words(int a, int b, int *res);
int bigdec_div_int(s21_bigdecimal value_a, s21_bigdecimal value_b,
                   s21_bigdecimal *result);

void bigdec_mul_by_10(s21_bigdecimal *src);
void bigdec_div_by_10(s21_bigdecimal *src);
void bigdec_equilizer(s21_bigdecimal *a, s21_bigdecimal *b);
void set_bigdec_scale(s21_bigdecimal *dst, int scale);

#endif
