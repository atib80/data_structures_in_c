#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define dll_node(type) type##_node
#define dll_node_t(type) type##_node_t
#define dll_t(type) type##_dll_t
#define doubly_linked_list_t(type) type##_dll_t

#define define_doubly_linked_list(type)                                     \
  typedef type item_type;                                                   \
  typedef struct dll_node(type) {                                           \
    item_type value;                                                        \
    struct dll_node(type) * prev;                                           \
    struct dll_node(type) * next;                                           \
  }                                                                         \
  dll_node_t(type);                                                         \
  typedef struct {                                                          \
    dll_node_t(type) * head;                                                \
    dll_node_t(type) * tail;                                                \
    unsigned size;                                                          \
  } dll_t(type);                                                            \
                                                                            \
  void swap(dll_node_t(type) * *first, dll_node_t(type) * *second) {        \
    dll_node_t(type)* temp = *first;                                        \
    *first = *second;                                                       \
    *second = temp;                                                         \
  }                                                                         \
                                                                            \
  void print(const dll_t(type) * dll, const char* sep, const char* prefix,  \
             const char* suffix) {                                          \
    const dll_node_t(type)* current = dll->head;                            \
    printf(prefix);                                                         \
    while (NULL != current) {                                               \
      printf("%d%s", current->value, NULL != current->next ? sep : suffix); \
      current = current->next;                                              \
    }                                                                       \
  }                                                                         \
                                                                            \
  bool insert_node_at_the_beginning(dll_t(type) * dll, const int value) {   \
    dll_node_t(type)* new_node =                                            \
        (dll_node_t(type)*)malloc(sizeof(dll_node_t(type)));                \
    if (NULL == new_node)                                                   \
      return false;                                                         \
    new_node->value = value;                                                \
    new_node->prev = NULL;                                                  \
    if (NULL == dll->head) {                                                \
      new_node->next = NULL;                                                \
      dll->head = new_node;                                                 \
      dll->tail = new_node;                                                 \
      dll->size = 1U;                                                       \
    } else {                                                                \
      new_node->next = dll->head;                                           \
      dll->head->prev = new_node;                                           \
      dll->head = new_node;                                                 \
      ++dll->size;                                                          \
    }                                                                       \
    return true;                                                            \
  }                                                                         \
  bool insert_node_at_the_end(dll_t(type) * dll, const int value) {         \
    dll_node_t(type)* new_node =                                            \
        (dll_node_t(type)*)malloc(sizeof(dll_node_t(type)));                \
    if (NULL == new_node)                                                   \
      return false;                                                         \
    new_node->value = value;                                                \
    new_node->next = NULL;                                                  \
    if (NULL == dll->head) {                                                \
      new_node->prev = NULL;                                                \
      dll->head = new_node;                                                 \
      dll->tail = new_node;                                                 \
      dll->size = 1U;                                                       \
    } else {                                                                \
      new_node->prev = dll->tail;                                           \
      dll->tail->next = new_node;                                           \
      dll->tail = new_node;                                                 \
      ++dll->size;                                                          \
    }                                                                       \
    return true;                                                            \
  }                                                                         \
                                                                            \
  bool insert_node_before_specified_position(                               \
      dll_t(type) * dll, const int value, const unsigned pos) {             \
    if (NULL == dll->head) {                                                \
      dll_node_t(type)* new_node =                                          \
          (dll_node_t(type)*)malloc(sizeof(dll_node_t(type)));              \
      if (NULL == new_node)                                                 \
        return false;                                                       \
      new_node->value = value;                                              \
      new_node->prev = NULL;                                                \
      new_node->next = NULL;                                                \
      dll->head = dll->tail = new_node;                                     \
      dll->size = 1U;                                                       \
      return true;                                                          \
    }                                                                       \
                                                                            \
    if (0U == pos || pos > dll->size)                                       \
      return false;                                                         \
    if (1U == pos)                                                          \
      return insert_node_at_the_beginning(dll, value);                      \
    if (pos == dll->size)                                                   \
      return insert_node_at_the_end(dll, value);                            \
    unsigned current_pos = 1U;                                              \
    dll_node_t(type)* next_node = dll->head;                                \
    while (current_pos < pos) {                                             \
      next_node = next_node->next;                                          \
      ++current_pos;                                                        \
    }                                                                       \
    dll_node_t(type)* new_node =                                            \
        (dll_node_t(type)*)malloc(sizeof(dll_node_t(type)));                \
    if (NULL == new_node)                                                   \
      return false;                                                         \
    new_node->value = value;                                                \
    new_node->next = next_node;                                             \
    new_node->prev = next_node->prev;                                       \
    next_node->prev->next = new_node;                                       \
    next_node->prev = new_node;                                             \
    ++dll->size;                                                            \
    return true;                                                            \
  }                                                                         \
                                                                            \
  bool insert_node_after_specified_position(                                \
      dll_t(type) * dll, const int value, const unsigned pos) {             \
    if (NULL == dll->head) {                                                \
      dll_node_t(type)* new_node =                                          \
          (dll_node_t(type)*)malloc(sizeof(dll_node_t(type)));              \
      if (NULL == new_node)                                                 \
        return false;                                                       \
      new_node->value = value;                                              \
      new_node->prev = NULL;                                                \
      new_node->next = NULL;                                                \
      dll->head = dll->tail = new_node;                                     \
      dll->size = 1U;                                                       \
      return true;                                                          \
    }                                                                       \
    if (0U == pos || pos > dll->size)                                       \
      return false;                                                         \
    if (pos == dll->size)                                                   \
      return insert_node_at_the_end(dll, value);                            \
    unsigned current_pos = 1U;                                              \
    dll_node_t(type)* prev_node = dll->head;                                \
    while (current_pos < pos) {                                             \
      prev_node = prev_node->next;                                          \
      ++current_pos;                                                        \
    }                                                                       \
    dll_node_t(type)* new_node =                                            \
        (dll_node_t(type)*)malloc(sizeof(dll_node_t(type)));                \
    if (NULL == new_node)                                                   \
      return false;                                                         \
    new_node->value = value;                                                \
    new_node->next = prev_node->next;                                       \
    new_node->prev = prev_node;                                             \
    prev_node->next->prev = new_node;                                       \
    prev_node->next = new_node;                                             \
    ++dll->size;                                                            \
    return true;                                                            \
  }                                                                         \
                                                                            \
  bool delete_first_node(dll_t(type) * dll) {                               \
    if (NULL == dll->head)                                                  \
      return false;                                                         \
    dll_node_t(type)* current = dll->head;                                  \
    dll->head = dll->head->next;                                            \
    dll->head->prev = current->next = NULL;                                 \
    free(current);                                                          \
    if (NULL == dll->head) {                                                \
      dll->tail = NULL;                                                     \
      dll->size = 0U;                                                       \
    }                                                                       \
    return true;                                                            \
  }                                                                         \
                                                                            \
  bool delete_last_node(dll_t(type) * dll) {                                \
    if (NULL == dll->tail)                                                  \
      return false;                                                         \
    dll_node_t(type)* current = dll->tail;                                  \
    dll->tail = dll->tail->prev;                                            \
    dll->tail->next = current->prev = NULL;                                 \
    free(current);                                                          \
    if (NULL == dll->tail) {                                                \
      dll->head = NULL;                                                     \
      dll->size = 0U;                                                       \
    }                                                                       \
    return true;                                                            \
  }                                                                         \
                                                                            \
  bool delete_node_at_specified_position(dll_t(type) * dll,                 \
                                         const unsigned pos) {              \
    if (NULL == dll->head || 0U == pos || pos > dll->size)                  \
      return false;                                                         \
    if (1U == pos)                                                          \
      return delete_first_node(dll);                                        \
    if (pos == dll->size)                                                   \
      return delete_last_node(dll);                                         \
    dll_node_t(type)* current = dll->head, *prev;                           \
    unsigned i = 1U;                                                        \
    while (i < pos) {                                                       \
      prev = current;                                                       \
      current = current->next;                                              \
      ++i;                                                                  \
    }                                                                       \
    if (dll->tail == current)                                               \
      return delete_last_node(dll);                                         \
    prev->next = current->next;                                             \
    current->next->prev = prev;                                             \
    current->prev = current->next = NULL;                                   \
    free(current);                                                          \
    return true;                                                            \
  }                                                                         \
                                                                            \
  void destroy_doubly_linked_list(dll_t(type) * dll) {                      \
    dll_node_t(type)* current_node = dll->head;                             \
    while (current_node != NULL) {                                          \
      dll_node_t(type)* next_node = current_node->next;                     \
      current_node->prev = current_node->next = NULL;                       \
      free(current_node);                                                   \
      current_node = next_node;                                             \
    }                                                                       \
    dll->head = NULL;                                                       \
    dll->tail = NULL;                                                       \
    dll->size = 0U;                                                         \
  }                                                                         \
                                                                            \
  bool reverse_doubly_linked_list_in_place(dll_t(type) * dll) {             \
    swap(&dll->head, &dll->tail);                                           \
    dll_node_t(type)* current = dll->head;                                  \
    while (NULL != current) {                                               \
      swap(&current->prev, &current->next);                                 \
      current = current->next;                                              \
    }                                                                       \
    return true;                                                            \
  }                                                                         \
                                                                            \
  dll_t(type) create_reversed_copy_of_specified_doubly_linked_list(         \
      const dll_t(type) * dll) {                                            \
    dll_t(type) reversed_dll = {0};                                         \
    const dll_node_t(type)* current = dll->head;                            \
    while (NULL != current) {                                               \
      if (!insert_node_at_the_beginning(&reversed_dll, current->value)) {   \
        destroy_doubly_linked_list(&reversed_dll);                          \
        return reversed_dll;                                                \
      }                                                                     \
      current = current->next;                                              \
    }                                                                       \
    return reversed_dll;                                                    \
  }

#endif /* _DOUBLY_LINKED_LIST_H_ */