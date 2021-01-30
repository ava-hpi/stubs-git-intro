/**
 * 05-vector.c - A data structure for dynamically sized lists
 */
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A vector manages a dynamic array, that increases in size as necessary.
 * If more elements than the current array capacity are added, it will allocate
 * a new array (typically double in size) and move all old values to the new array.
 */
typedef struct {
   size_t length;
   size_t capacity;
   int* data;
} vector;

/**
 * Should create a new vector on the heap, with length 0.
 */
vector* vec_create() {
   vector* vec = calloc(1, sizeof(vector));

   vec->capacity = 8;
   vec->data = calloc(sizeof(int), vec->capacity);
   vec->length = 0;

   return vec;
}

/**
 * Should free the vector and any data held by it.
 */
void vec_free(vector* v) {
   free(v->data);
   free(v);
}

/**
 * Should insert the value at the end of the array.
 * It must increase the capacity if necessary.
 */
void vec_push(vector* v, int value) {
   if (v->length == v->capacity) {
      v->capacity *= 2;
      v->data = realloc(v->data, sizeof(int) * v->capacity);
   }
   v->data[v->length] = value;
   v->length++;
}

/**
 * Should return the i'th-Element in the vector.
 * Return 0 if index >= length.
 */
int vec_get(vector* v, size_t i) {
   if (i >= v->length) {
      return 0;
   } else {
      return v->data[i];
   }
}

/**
 * Should set the i'th-Element in the vector to "value".
 * Should return true if the value was inserted successfully.
 * Should return false if i >= length
 */
bool vec_set(vector* v, size_t i, int value) {
   if (i >= v->length) {
      return false;
   } else {
      v->data[i] = value;
      return true;
   }
}

int main(void) {
   vector* vec = vec_create();

   for (int i = 0; i < 100; i++) {
      vec_push(vec, i);
   }

   int x = vec_get(vec, 50);
   if(x != 50) {
      printf("Error: value at index 50 is incorrect, expected: %i, actual: %i", 50, x);
      return 1;
   }

   int new_value = 10;
   vec_set(vec, 50, new_value);
   int y = vec_get(vec, new_value);
   if(y != new_value) {
      printf("Error: value at index 50 is incorrect, expected: %i, actual: %i", new_value, y);
      return 1;
   }

   // this should print the numbers from 0 to 100, but 50 is replaced by 10
   for (int i = 0; i < vec->length; i++) {
      printf("%i\n", vec_get(vec, i));
   }

   vec_free(vec);
}
