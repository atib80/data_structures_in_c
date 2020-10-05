#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include <stdbool.h>

#define da_type_t(type) type##_da_t

#define generate_dynamic_array(type)                                          \
  typedef type item_type;                                                     \
  typedef struct {                                                            \
    item_type* ptr;                                                           \
    unsigned capacity;                                                        \
    unsigned size;                                                            \
  } da_type_t(type);                                                          \
  unsigned length(const da_type_t(type)*);                                    \
  void swap(item_type*, item_type*);                                          \
  void print(const da_type_t(type)*);                                         \
  bool increase_specified_dynamic_array_capacity(da_type_t(type)*);           \
  bool decrease_specified_dynamic_array_capacity(da_type_t(type)*);           \
  bool insert_element_at_the_beginning(da_type_t(type)*, const item_type);    \
  bool insert_element_at_the_end(da_type_t(type)*, const item_type);          \
  bool insert_element_at_specified_index(da_type_t(type) * da,                \
                                         const item_type, const unsigned);    \
  bool set_element_at_specified_index(da_type_t(type) * da, const item_type,  \
                                      const unsigned);                        \
  bool get_element_at_specified_index(const da_type_t(type)*, const unsigned, \
                                      item_type*);                            \
  bool delete_first_element(da_type_t(type)*);                                \
  bool delete_last_element(da_type_t(type)*);                                 \
  bool delete_element_at_specified_index(da_type_t(type)*, const unsigned);   \
  void destroy_dynamic_array(da_type_t(type)*);                               \
  bool reverse_dynamic_array_in_place(da_type_t(type)*);                      \
  da_type_t(type)                                                             \
      create_reversed_copy_of_specified_dynamic_array(const da_type_t(type)*);

generate_dynamic_array(int)

#define dynamic_array_t da_type_t(int)

#endif /* _DYNAMIC_ARRAY_H_ */