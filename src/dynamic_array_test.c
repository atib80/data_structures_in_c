#include "../include/dynamic_array.h"

#include <stdio.h>

define_dynamic_array(int)

    int main() {
  dynamic_array_t(int) da1 = {0};

  insert_element_at_the_beginning(&da1, 1);
  insert_element_at_the_end(&da1, 3);
  insert_element_at_specified_index(&da1, 2, 1);
  insert_element_at_the_end(&da1, 5);
  insert_element_at_specified_index(&da1, 4, 3);
  insert_element_at_the_end(&da1, 7);
  insert_element_at_the_end(&da1, 8);
  insert_element_at_the_beginning(&da1, 0);

  print(&da1);

  delete_element_at_specified_index(&da1, 3);

  print(&da1);

  delete_first_element(&da1);

  print(&da1);

  if (!reverse_dynamic_array_in_place(&da1)) {
    printf(
        "Error occurred during reversing specified dynamic array in place!\n");
  } else {
    print(&da1);
  }

  dynamic_array_t(int) da2 =
      create_reversed_copy_of_specified_dynamic_array(&da1);

  print(&da2);

  destroy_dynamic_array(&da1);
  destroy_dynamic_array(&da2);

  return 0;
}
