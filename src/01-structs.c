/**
 * 01-structs.c - A little employee management program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct {
   uint8_t day;
   uint8_t month;
   uint32_t year;
} date_t;

/* Für Aufgabe 03 - Dynamic Memory */
enum meal_option {
   PIZZA,
};

typedef struct employee {
   date_t last_seen;
   char *name;
   struct employee *manager;
   enum meal_option *meals;
} employee_t;

/* Für Aufgabe 03 - Dynamic Memory */
void determine_meals(employee_t *employee, int number_of_meals) {
   if (employee->meals) {
      free(employee->meals);
   }

   enum meal_option *chosen_meals = calloc(number_of_meals, sizeof(enum meal_option));

   for (int i = 0; i < number_of_meals; i++) {
      chosen_meals[i] = rand() % MAX_MEALS;
   }

   employee->meals = chosen_meals;
}

date_t today() {
   date_t date = { .day = 21, .month = 1, .year = 2021 };
   return date;
}

date_t yesterday() {
   date_t date = { .day = 20, .month = 1, .year = 2021 };
   return date;
}

employee_t *find_big_boss(employee_t **employees, size_t count) {
   for (size_t i = 0; i < count; i++) {
      if (employees[i]->manager == NULL)
	 return employees[i];
   }
   return NULL;
}

void print_inactive_employees(employee_t **employees, size_t count) {
   date_t current_date = today();
   for (size_t i = 0; i < count; i++) {
      if (employees[i]->last_seen.year < current_date.year ||
	    employees[i]->last_seen.month < current_date.month ||
	    employees[i]->last_seen.day < current_date.day) {
	 printf("Inactive: %s\n", employees[i]->name);
      }
   }
}

int main(void) {
   employee_t eve = { today(), "Eve", NULL };
   employee_t jane = { yesterday(), "Jane", &eve };
   employee_t bob = { today(), "Bob", &eve };
   employee_t alice = { yesterday(), "Alice", &jane };
   employee_t josh = { today(), "Josh", &eve };

   employee_t *employees[] = {
      &jane,
      &bob,
      &alice,
      &eve,
      &josh,
   };

   printf("%s\n", find_big_boss(employees, sizeof(employees) / sizeof(employee_t*))->name);
   print_inactive_employees(employees, sizeof(employees) / sizeof(employee_t*));

   /* Für Aufgabe 03 - Dynamic Memory */
   determine_meals(&eve, 5);
   free(eve.meals);
   determine_meals(&bob, 5);
   free(bob.meals);
}

