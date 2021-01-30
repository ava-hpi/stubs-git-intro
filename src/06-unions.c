/**
 * 06-unions.c - A data structure that can contain either 2- or 3-dimensional vector
 */

#include <stdio.h>
#include <math.h>

typedef enum vec_type {
   VEC2,
   VEC3,
} vec_type_t;

typedef struct vector {
   vec_type_t type;
   union {
      struct vec2 {
	 double x, y;
      } vec2;

      struct vec3 {
	 double x, y, z;
      } vec3;
   };
} vector_t;

/**
 * Print the contents of vec in a human-readable form
 */
void display_vec(vector_t vec)
{
   switch (vec.type)
   {
      case VEC2:
	 printf("Vec2(%.2f, %.2f)\n", vec.vec2.x, vec.vec2.y);
	 break;
      case VEC3:
	 printf("Vec3(%.2f, %.2f, %.2f)\n", vec.vec3.x, vec.vec3.y, vec.vec3.z);
	 break;
      default:
	 break;
   }
}

/**
 * Calculate the length of the vector. Hint: You may use the Pythagorean theorem here.
 * You may also use the math.h library, try `man pow` and `man sqrt`.
 */
double vec_length(vector_t vec)
{
   switch (vec.type)
   {
      case VEC2:
	 return sqrt(pow(vec.vec2.x, 2.0) + pow(vec.vec2.y, 2.0));
      case VEC3:
	 return sqrt(pow(vec.vec3.x, 2.0) + pow(vec.vec3.y, 2.0) + pow(vec.vec3.z, 2.0));
      default:
	 break;
   }
}

/**
 * Calculate the scalar product of the vectors, given as the sum of their
 * component-wise products. Your program should handle edge cases.
 */
double scalar_product(vector_t vec_a, vector_t vec_b)
{
   switch (vec_a.type)
   {
      case VEC2:
	 switch (vec_b.type) {
	    case VEC2:
	       return vec_a.vec2.x * vec_b.vec2.x + vec_a.vec2.y * vec_b.vec2.y;
	    case VEC3:
	       /* Treated as a vec3, the z component of vec_a is zero, so we ignore it. */
	       return vec_a.vec2.x * vec_b.vec3.x + vec_a.vec2.y * vec_b.vec3.y;
	 }
	 break;
      case VEC3:
	 switch (vec_b.type) {
	    case VEC2:
	       /* The same reasoning applies as above */
	       return vec_a.vec3.x * vec_b.vec2.x + vec_a.vec3.y * vec_b.vec2.y;
	    case VEC3:
	       return vec_a.vec3.x * vec_b.vec3.x + vec_a.vec3.y * vec_b.vec3.y + vec_a.vec3.z * vec_b.vec3.z;
	 }
	 break;
      default:
	 break;
   }
}

int main(void)
{
   vector_t v1 = {.type = VEC2, .vec2 = {.x = 1.0, .y = 3.0}};
   vector_t v2 = {.type = VEC3, .vec3 = {.x = 2.0, .y = 1.5, .z = 5.0}};
   vector_t v3 = {.type = VEC3, .vec3 = {.x = 4.0, .y = 2.0, .z = 3.0}};
   display_vec(v1);
   display_vec(v2);
   display_vec(v3);
   printf("Length: %.2f\n", vec_length(v1));
   printf("Scalar product of v1 and v2: %.2f\n", scalar_product(v1, v2));
   printf("Scalar product of v2 and v3: %.2f\n", scalar_product(v2, v3));
   return 0;
}
