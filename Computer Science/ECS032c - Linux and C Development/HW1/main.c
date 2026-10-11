#include <stdio.h>
#include <stdlib.h>
#include "RecordTools.h"

/* Part 4: finish this program.

   It reads records from STANDARD INPUT until end of file, one record
   (ID DOB height weight) at a time, so you run it with input redirection:

       bin/warmup < data/data_sml.txt

   Your output must match the expected files EXACTLY, so use the printf
   format strings below without changing them. */

#define AS_OF_DATE  20261001

int main(void){
    /* TODO 0: declare the variables you need. */
   int id, dob, heightCm, weightGrams;
   int count = 0;
   double totalBMI = 0.0;
   int under = 0, normal = 0, over = 0, obese = 0;
   int oldestID = 0, oldestDOB = 0;
   int tallest1 = 0, tallest2 = 0, tallest3 = 0;
    printf("  ID         DOB  Age  Height(m)  Weight(kg)   BMI  Cat\n");

    /* TODO 1: loop until scanf does NOT read 4 numbers.
       For each record, print ONE line using:

       printf("%4d  %04d-%02d-%02d  %3d  %9.2f  %10.3f  %4.1f    %c\n",
              id, year, month, day, age, meters, kilograms, bmi, category);

       The ID comes straight from scanf. Use your RecordTools functions to
       compute every other value. The age is the age on AS_OF_DATE.
       Classify and add up the UNROUNDED bmi; %4.1f rounds it only when
       printing (24.99 prints as 25.0 but is still BMI_NORMAL). */
      while (scanf("%d %d %d %d", &id, &dob, &heightCm, &weightGrams) == 4) {
        int year, month, day;
        SplitDate(dob, &year, &month, &day);
        int age = AgeOnDate(dob, AS_OF_DATE);
        double meters = CentimetersToMeters(heightCm);
        double kilograms = GramsToKilograms(weightGrams);
        double bmi = ComputeBMI(heightCm, weightGrams);
        char category = BMICategory(bmi);

        printf("%4d  %04d-%02d-%02d  %3d  %9.2f  %10.3f  %4.1f    %c\n",
               id, year, month, day, age, meters, kilograms, bmi, category);

        /* TODO 2: inside the same loop, keep track of
         - how many records were read
         - the total of all the BMI values
         - how many records are in each BMI category (use a switch)
         - the ID and DOB of the oldest person (use CompareByOrder).
           If two people share the oldest DOB, keep the one read first.
         - the three tallest heights (use SortThree; see the handout).
           Equal heights count separately, and if there are fewer than
           three records the missing places print as 0. */
         totalBMI += bmi;
         count++;
         switch (category) {
             case BMI_UNDERWEIGHT:
                 under++;
                 break;
             case BMI_NORMAL:
                 normal++;
                 break;
             case BMI_OVERWEIGHT:
                 over++;
                 break;
             case BMI_OBESE:
                 obese++;
                 break;
         }
         if (count == 1 || CompareByOrder(dob, oldestDOB, 1) < 0) {
             oldestID = id;
             oldestDOB = dob;
         }
         if (heightCm > tallest3) {
             tallest3 = heightCm;
             SortThree(&tallest1, &tallest2, &tallest3, -1);
         }
      }
    /* TODO 2: inside the same loop, keep track of
         - how many records were read
         - the total of all the BMI values
         - how many records are in each BMI category (use a switch)
         - the ID and DOB of the oldest person (use CompareByOrder).
           If two people share the oldest DOB, keep the one read first.
         - the three tallest heights (use SortThree; see the handout).
           Equal heights count separately, and if there are fewer than
           three records the missing places print as 0. */

    /* TODO 3: after the loop, if no records were read, print
      
       printf("No records\n");

       Otherwise print these five lines:

       printf("Records: %d\n", count);
       printf("Average BMI: %.1f\n", averageBMI);
       printf("Underweight: %d  Normal: %d  Overweight: %d  Obese: %d\n",
              under, normal, over, obese);
       printf("Oldest: %d (born %04d-%02d-%02d)\n", id, year, month, day);
       printf("Tallest three (cm): %d %d %d\n", first, second, third);  */
      if (count == 0) {
          printf("No records\n");
      } else {
          double averageBMI = totalBMI / count;
          int oldestYear, oldestMonth, oldestDay;
          SplitDate(oldestDOB, &oldestYear, &oldestMonth, &oldestDay);
          printf("Records: %d\n", count);
          printf("Average BMI: %.1f\n", averageBMI);
          printf("Underweight: %d  Normal: %d  Overweight: %d  Obese: %d\n",
                 under, normal, over, obese);
          printf("Oldest: %d (born %04d-%02d-%02d)\n", oldestID, oldestYear, oldestMonth, oldestDay);
          printf("Tallest three (cm): %d %d %d\n", tallest1, tallest2, tallest3);
      }
    return EXIT_SUCCESS;
}
