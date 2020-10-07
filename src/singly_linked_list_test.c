#include "../include/singly_linked_list.h"

#include <stdio.h>

define_singly_linked_list(int)

    int main() {
  sll_t(int) sll = {0};

  insert_node_at_the_beginning(&sll, 1);
  insert_node_at_the_end(&sll, 3);
  insert_node_at_the_end(&sll, 5);
  insert_node_at_the_end(&sll, 7);
  insert_node_at_the_end(&sll, 8);

  delete_node_at_specified_position(&sll, 3);

  print(&sll);

  if (!reverse_singly_linked_list_in_place(&sll)) {
    printf(
        "Error occurred during reversing specified singly linked list in "
        "place!\n");
  } else {
    print(&sll);
  }

  sll_t(int) sll2 = create_reversed_copy_of_specified_singly_linked_list(&sll);

  print(&sll2);

  destroy_singly_linked_list(&sll);
  destroy_singly_linked_list(&sll2);

  return 0;
}
