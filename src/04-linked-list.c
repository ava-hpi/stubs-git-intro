/**
 * 04-linked-list.c - An implementation of a linked list
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct list {
   int data;
   struct list *next;
} list_t;

list_t *create_list(int data, list_t *next) {
   list_t *l = calloc(1, sizeof(list_t));
   l->data = data;
   l->next = next;
   return l;
}

list_t *list_insert(list_t *list, int index, int data) {
   list_t *current = list;
   if (!current || index == 0) {
      return create_list(data, list);
   }

   // we do index-2 since we need handle inserting at 0 at the top and we want to
   // skip one item before we have to insert our new item.
   for (int i = 0; i < (index - 2) && current->next; i++, current = current->next);

   current->next = create_list(data, current->next);
   return list;
}

list_t *list_prepend(list_t *list, int data) {
   return create_list(data, list);
}

list_t *list_append(list_t *list, int data) {
   list_t *new = create_list(data, NULL);

   if (!list) {
      return new;
   }

   list_t *current_end;
   for (current_end = list; current_end->next; current_end = current_end->next);
   current_end->next = new;

   return list;
}

void print_list(list_t *list) {
   for (; list; list = list->next) {
      printf("%i\n", list->data);
   }
}

int main(void) {
   list_t *my_list = list_prepend(NULL, 3);
   my_list = list_prepend(my_list, 2);
   my_list = list_prepend(my_list, 1);
   my_list = list_append(my_list, 5);
   my_list = list_append(my_list, 6);
   my_list = list_insert(my_list, 4, 4);

   print_list(my_list);

   // NOTE: we are not freeing the memory again here!
}

