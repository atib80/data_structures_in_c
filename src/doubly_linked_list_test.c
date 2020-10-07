#include "../include/doubly_linked_list.h"

#include <stdio.h>

define_doubly_linked_list(int)

    int main() {
  dll_t(int) dll = {0};

  insert_node_at_the_beginning(&dll, 1);
  insert_node_at_the_end(&dll, 3);
  insert_node_before_specified_position(&dll, 2, 2);
  insert_node_at_the_end(&dll, 5);
  insert_node_after_specified_position(&dll, 3, 4);
  insert_node_at_the_end(&dll, 7);
  insert_node_at_the_end(&dll, 8);
  insert_node_at_the_beginning(&dll, 0);

  print(&dll, " <=> ", "\n[", "]\n");

  delete_node_at_specified_position(&dll, 3);

  print(&dll, " <=> ", "\n[", "]\n");

  if (!reverse_doubly_linked_list_in_place(&dll)) {
    printf(
        "Error occurred during reversing specified doubly linked list in "
        "place!\n");
  } else {
    print(&dll, " <=> ", "\n[", "]\n");
  }

  dll_t(int) dll2 = create_reversed_copy_of_specified_doubly_linked_list(&dll);

  print(&dll2, " <=> ", "\n[", "]\n");

  destroy_doubly_linked_list(&dll);
  destroy_doubly_linked_list(&dll2);

  return 0;
}
