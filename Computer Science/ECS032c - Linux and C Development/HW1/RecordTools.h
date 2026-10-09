#ifndef RECORDTOOLS_H
#define RECORDTOOLS_H

#ifdef __cplusplus
extern "C"{
#endif

/* Each record in the data files is four ints:  ID  DOB  height  weight
   DOB is ONE int in the form YYYYMMDD (October 1, 1969 is 19691001).
   Height is in centimeters. Weight is in grams.
   You may assume every record is valid: real dates, positive heights and
   weights, and every value fits in an int.                              */

/* BMI categories returned by BMICategory */
#define BMI_UNDERWEIGHT  'U'    /* BMI below 18.5               */
#define BMI_NORMAL       'N'    /* 18.5 or more, but below 25.0 */
#define BMI_OVERWEIGHT   'O'    /* 25.0 or more, but below 30.0 */
#define BMI_OBESE        'B'    /* 30.0 or more                 */

/* ---------- Conversions: int vs. double arithmetic ---------- */

/* CentimetersToMeters(179) returns 1.79 */
double CentimetersToMeters(int centimeters);

/* GramsToKilograms(75422) returns 75.422 */
double GramsToKilograms(int grams);

/* Body Mass Index = kilograms / (meters * meters).
   Must call CentimetersToMeters and GramsToKilograms.
   ComputeBMI(179, 75422) returns about 23.539 */
double ComputeBMI(int heightCm, int weightGrams);

/* ---------- Dates: output parameters and if ---------- */

/* Splits a YYYYMMDD date into its parts.
   After  SplitDate(19691001, &y, &m, &d);   y is 1969, m is 10, d is 1 */
void SplitDate(int date, int *year, int *month, int *day);

/* Age in whole years, on the date today, of a person born on dob.
   Both are YYYYMMDD, and today is never before dob.
   AgeOnDate(19691001, 20261001) returns 57  (birthday is today)
   AgeOnDate(19691002, 20261001) returns 56  (birthday is tomorrow)
   Someone born on February 29 has their birthday on March 1 in years
   that are not leap years:
   AgeOnDate(20000229, 20010228) returns 0,  AgeOnDate(20000229, 20010301) returns 1 */
int AgeOnDate(int dob, int today);

/* ---------- Categories: if/else and switch ---------- */

/* Returns BMI_UNDERWEIGHT, BMI_NORMAL, BMI_OVERWEIGHT or BMI_OBESE
   (see the table at the top of this file). Classify the unrounded BMI.
   BMICategory(23.5) returns BMI_NORMAL,  BMICategory(24.99) returns BMI_NORMAL */
char BMICategory(double bmi);

/* Turns one sort-order letter into an order value.
   Upper case means ascending (positive), lower case means descending (negative):
       'I' ->  1    'D' ->  2    'H' ->  3    'W' ->  4
       'i' -> -1    'd' -> -2    'h' -> -3    'w' -> -4
   Any other character returns 0. Must use a switch statement. */
int LetterToOrder(char letter);

/* ---------- Ordering: comparing and swapping through pointers ---------- */

/* Compares two values. order > 0 means ascending (smaller first),
   order < 0 means descending (larger first). order is never 0.
   left and right are always between 0 and 99999999.
   Returns a negative number if left should come first,
           0                 if they tie,
           a positive number if right should come first.
   Only the SIGN of the result matters.
   CompareByOrder(3, 7, 2) is negative,  CompareByOrder(3, 7, -4) is positive */
int CompareByOrder(int left, int right, int order);

/* Puts *first and *second in the order given by order, swapping them
   only when CompareByOrder says *second should come first.
   int a = 7, b = 3;   OrderPair(&a, &b, 1);    now a is 3, b is 7
   int a = 3, b = 7;   OrderPair(&a, &b, -1);   now a is 7, b is 3 */
void OrderPair(int *first, int *second, int order);

/* Puts *a, *b, *c in the order given by order.
   Must call OrderPair exactly three times, and nothing else.
   int x = 5, y = 9, z = 1;   SortThree(&x, &y, &z, 1);   now x is 1, y is 5, z is 9 */
void SortThree(int *a, int *b, int *c, int order);

#ifdef __cplusplus
}
#endif

#endif
