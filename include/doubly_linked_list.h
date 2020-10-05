#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

#include <stdbool.h>

#define dll_node(type) type##_node
#define dll_node_t(type) type##_node_t
#define dll_type_t(type) type##_dll_t

#define doubly_linked_list(type)                                              \
  typedef struct dll_node(type) {                                             \
    type value;                                                               \
    struct dll_node(type) * prev;                                             \
    struct dll_node(type) * next;                                             \
  }                                                                           \
  dll_node_t(type);                                                           \
  typedef struct {                                                            \
    dll_node_t(type) * head;                                                  \
    dll_node_t(type) * tail;                                                  \
    unsigned size;                                                            \
  } dll_type_t(type);                                                         \
                                                                              \
  void swap(dll_node_t(type) * *first, dll_node_t(type) * *second);           \
  void print(const dll_type_t(type) * dll);                                   \
  bool insert_node_at_the_beginning(dll_type_t(type) * dll, const int value); \
  bool insert_node_at_the_end(dll_type_t(type) * dll, const int value);       \
  bool insert_node_before_specified_position(                                 \
      dll_type_t(type) * dll, const int value, const unsigned pos);           \
  bool insert_node_after_specified_position(                                  \
      dll_type_t(type) * dll, const int value, const unsigned pos);           \
  bool delete_first_node(dll_type_t(type) * dll);                             \
  bool delete_last_node(dll_type_t(type) * dll);                              \
  bool delete_node_at_specified_position(dll_type_t(type) * dll,              \
                                         const unsigned pos);                 \
  void destroy_doubly_linked_list(dll_type_t(type) * dll);                    \
  bool reverse_doubly_linked_list_in_place(dll_type_t(type) * dll);           \
  dll_type_t(type) create_reversed_copy_of_specified_doubly_linked_list(      \
      const dll_type_t(type) * dll);

doubly_linked_list(int)

#define dll_t dll_type_t(int)
#define node_t dll_node_t(int)

#endif /* _DOUBLY_LINKED_LIST_H_ */