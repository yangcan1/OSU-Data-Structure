/*
 * In this file, you should implement an application that compares the
 * performance of a dynamic array and a linked list, as described in the
 * README. Don't forget to include your name and @oregonstate.edu email
 * address below.
 *
 * Name:Can Yang
 * Email:yangca@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "dynarray.h"
#include "list.h"

#define TEST_DATA_SIZE 1000000

/*
 * This function generates and an array of random integers of size n.
 */
int* generate_random_array(int n) {
  int* arr = malloc(n * sizeof(int));
  int i;

  for (i = 0; i < n; i++) {
    arr[i] = rand();
  }

  return arr;
}

int main(int argc, char const *argv[]) {
  int* test_data = generate_random_array(TEST_DATA_SIZE);
  
  /*
   * You should write code here to insert the data in test_data into a
   * dynamic array using the dynamic array interface you implemented.  As
   * you're doing this, measure two things:
   *   1. The total amount of time it takes to insert all the data into the
   *      dynamic array.
   *   2. The maximum amount of time it takes to insert any single element into
   *      the dynamic array.
   * To help with this, you can use the C functions time() and difftime()
   * from time.h.  Don't forget to include time.h above!
   */
  clock_t start_t_total, end_t_total, start_t_single, end_t_single;
  double differtime_total, differtime_single, max_difference = 0;
  struct dynarray *arr = dynarray_create();
  int *testdata = generate_random_array(TEST_DATA_SIZE);
  start_t_total = clock();
  for (int i = 0; i < TEST_DATA_SIZE; i++) {
    
    start_t_single = clock();
    dynarray_insert(arr, &testdata[i]);
    
    end_t_single = clock();
    differtime_single = (double) (end_t_single - start_t_single) / CLOCKS_PER_SEC;
    if (differtime_single> max_difference){
      max_difference = differtime_single;
    }
  }
  end_t_total = clock();
  differtime_total = (double) (end_t_total - start_t_total)  / CLOCKS_PER_SEC;

  printf("(dynarray) the total time spend is: %f\n", differtime_total);
  printf("(dynarray) the single time spend is: %f\n", max_difference);

   /*
    * You should write code here to insert the data in test_data into a
    * linked list using the linked list interface you implemented.  As
    * you're doing this, measure two things:
    *   1. The total amount of time it takes to insert all the data into the
    *      linked list.
    *   2. The maximum amount of time it takes to insert any single element into
    *      the linked list.
    * Again, you can use the C functions time() and difftime() from time.h to
    * help with this.
    *
    * How do the times associated with the dynamic array compare to the times
    * associated with the linked list?  How does this change if you modify the
    * value of TEST_DATA_SIZE above?
    */

  struct list *list = list_create();
  start_t_total = clock();
  for (int i = 0; i < TEST_DATA_SIZE; i++) {
    
    start_t_single = clock();
    list_insert(list, &testdata[i]);
    end_t_single = clock();
    differtime_single = (double) (end_t_single - start_t_single) / CLOCKS_PER_SEC;
    if (differtime_single > max_difference) {
      max_difference = differtime_single;
    }
  }
  end_t_total = clock();
  differtime_total = (double) (end_t_total - start_t_total)  / CLOCKS_PER_SEC;

  printf("(linked list) the total time spend is: %f\n", differtime_total);
  printf("(linked list) the single time spend is: %f\n", max_difference);
}