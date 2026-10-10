#include "RecordTools.h"

/* Part 3: write the body (definition) of every function below.
   The prototypes (declarations) and what each function must do are in
   include/RecordTools.h. Each function is a stub right now: it compiles,
   but returns a placeholder value so the tests fail. */

double CentimetersToMeters(int centimeters){
    double meters = (double)centimeters / 100.0;
    return meters;
}

double GramsToKilograms(int grams){
    double kilograms = (double)grams / 1000.0;
    return kilograms;
}


double ComputeBMI(int heightCm, int weightGrams){
    double meters = CentimetersToMeters(heightCm);
    double kilograms = GramsToKilograms(weightGrams);
    double bmi = kilograms / (meters * meters);
    return bmi;
}

void SplitDate(int date, int *year, int *month, int *day){
    *year = date / 10000;
    *month = (date / 100) % 100;
    *day = date % 100;
}

int AgeOnDate(int dob, int today){
    int dobYear, dobMonth, dobDay;
    int todayYear, todayMonth, todayDay;
    SplitDate(dob, &dobYear, &dobMonth, &dobDay);
    SplitDate(today, &todayYear, &todayMonth, &todayDay);
    int age = todayYear - dobYear;
    if (todayMonth < dobMonth || (todayMonth == dobMonth && todayDay < dobDay)) {
        age--;
    }
    return age;
}

char BMICategory(double bmi){
    if (bmi < 18.5) {
        return BMI_UNDERWEIGHT;
    } else if (bmi < 25.0 && bmi >= 18.5) {
        return BMI_NORMAL;
    } else if (bmi < 30.0 && bmi >= 25.0) {
        return BMI_OVERWEIGHT;
    } else {
        return BMI_OBESE;
    }
    return ' ';
}

int LetterToOrder(char letter){
    switch (letter) {
        case 'I': return 1;
        case 'D': return 2;
        case 'H': return 3;
        case 'W': return 4;
        case 'i': return -1;
        case 'd': return -2;
        case 'h': return -3;
        case 'w': return -4;
        default: return 0;
    }
    return 0;
}

int CompareByOrder(int left, int right, int order){
    if (order > 0) {
        return left - right;
    } else {
        return right - left;
    }
    return 0;
}

void OrderPair(int *first, int *second, int order){
    int compare = CompareByOrder(*first, *second, order);
    if (compare > 0) {
        int temp = *first;
        *first = *second;
        *second = temp;
    }
}

void SortThree(int *a, int *b, int *c, int order){
    OrderPair(a, b, order);
    OrderPair(b, c, order);
    OrderPair(a, b, order);
}
