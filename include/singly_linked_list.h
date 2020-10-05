#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

#include <stdbool.h>

#define sll_node(type) type##_node
#define sll_node_t(type) type##_node_t
#define sll_type_t(type) type##_sll_t

#define singly_linked_list(type)                                          \
  typedef struct sll_node(type) {                                         \
    type value;                                                           \
    struct sll_node(type) * next;                                         \
  }                                                                       \
  sll_node_t(type);                                                       \
  typedef struct {                                                        \
    sll_node_t(type) * head;                                              \
    sll_node_t(type) * tail;                                              \
    unsigned size;                                                        \
  } sll_type_t(type);                                                     \
  void print(const sll_type_t(type) * sll);                               \
  bool insert_node_at_the_beginning(sll_type_t(type) * sll,               \
                                    const int element);                   \
  bool insert_node_at_the_end(sll_type_t(type) * sll, const int element); \
  bool insert_node_at_specified_position(                                 \
      sll_type_t(type) * sll, const int element, const unsigned pos);     \
  bool delete_first_node(sll_type_t(type) * sll);                         \
  bool delete_last_node(sll_type_t(type) * sll);                          \
  bool delete_node_at_specified_position(sll_type_t(type) * sll,          \
                                         const unsigned pos);             \
  void destroy_singly_linked_list(sll_type_t(type) * sll);                \
  bool reverse_singly_linked_list_in_place(sll_type_t(type) * sll);       \
  sll_type_t(type) create_reversed_copy_of_specified_singly_linked_list(  \
      const sll_type_t(type) * sll);

singly_linked_list(int)

#define sll_t sll_type_t(int)
#define node_t sll_node_t(int)

#endif /* _SINGLY_LINKED_LIST_H_ */