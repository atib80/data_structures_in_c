#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_CAP 64

#define stack_t(type) type##_stack_t

#define create_stack_of(type)                                                  \
  typedef type item_type;                                                      \
  typedef struct stack {                                                       \
    item_type* ptr;                                                            \
    unsigned capacity;                                                         \
    unsigned size;                                                             \
                                                                               \
  } type##_stack_t;                                                            \
                                                                               \
  inline void stack_init(stack_t(type) * s) {                                  \
    s->ptr = NULL;                                                             \
    s->capacity = 0U;                                                          \
    s->size = 0U;                                                              \
  }                                                                            \
  void stack_destroy(stack_t(type) * s) {                                      \
    free(s->ptr);                                                              \
    s->ptr = NULL;                                                             \
    s->capacity = 0U;                                                          \
    s->size = 0U;                                                              \
  }                                                                            \
                                                                               \
  void stack_error(FILE* fp, const char* msg, const bool is_terminate) {       \
    fprintf(fp, "Error: %s!\n", msg);                                          \
    if (is_terminate)                                                          \
      exit(1);                                                                 \
  }                                                                            \
                                                                               \
  inline unsigned stack_size(const stack_t(type) * s) {                        \
    return NULL == s ? 0U : s->size;                                           \
  }                                                                            \
                                                                               \
  inline bool stack_empty(const stack_t(type) * s) {                           \
    return NULL == s || 0U == s->size;                                         \
  }                                                                            \
                                                                               \
  inline bool stack_full(const stack_t(type) * s) {                            \
    return s->size == s->capacity;                                             \
  }                                                                            \
                                                                               \
  bool stack_increase_capacity(stack_t(type) * s) {                            \
    const unsigned new_capacity =                                              \
        s->capacity != 0U ? s->capacity << 1 : STACK_INIT_CAP;                 \
    if (NULL == s->ptr) {                                                      \
      s->ptr = (item_type*)malloc(new_capacity * sizeof(item_type));           \
      if (NULL == s->ptr)                                                      \
        return false;                                                          \
    } else {                                                                   \
      item_type* new_ptr =                                                     \
          (item_type*)realloc(s->ptr, new_capacity * sizeof(item_type));       \
      if (NULL == new_ptr)                                                     \
        return false;                                                          \
      s->ptr = new_ptr;                                                        \
    }                                                                          \
    s->capacity = new_capacity;                                                \
    return true;                                                               \
  }                                                                            \
                                                                               \
  bool stack_decrease_capacity(stack_t(type) * s) {                            \
    if (s->capacity <= STACK_INIT_CAP)                                         \
      return false;                                                            \
    const unsigned new_capacity = s->capacity >> 1;                            \
    item_type* new_ptr = (item_type*)malloc(new_capacity * sizeof(item_type)); \
    if (NULL == new_ptr)                                                       \
      return false;                                                            \
    memcpy(new_ptr, s->ptr, s->size * sizeof(item_type));                      \
    free(s->ptr);                                                              \
    s->ptr = new_ptr;                                                          \
    s->capacity = new_capacity;                                                \
    return true;                                                               \
  }                                                                            \
                                                                               \
  bool stack_push(stack_t(type) * s, const item_type value) {                  \
    if (s->size == s->capacity) {                                              \
      if (!stack_increase_capacity(s)) {                                       \
        stack_destroy(s);                                                      \
        stack_error(stderr,                                                    \
                    "Couldn't increase dynamic memory capacity of stack!",     \
                    true);                                                     \
        return false;                                                          \
      }                                                                        \
    }                                                                          \
    s->ptr[s->size] = value;                                                   \
    ++s->size;                                                                 \
    return true;                                                               \
  }                                                                            \
                                                                               \
  bool stack_top(const stack_t(type) * s, item_type * top_element) {           \
    if (stack_empty(s))                                                        \
      return false;                                                            \
    *top_element = s->ptr[s->size - 1];                                        \
    return true;                                                               \
  }                                                                            \
                                                                               \
  bool stack_pop(stack_t(type) * s) {                                          \
    if (stack_empty(s))                                                        \
      return false;                                                            \
    --s->size;                                                                 \
    if (s->size <= s->capacity / 4)                                            \
      stack_decrease_capacity(s);                                              \
    return true;                                                               \
  }                                                                            \
                                                                               \
  void stack_print(const stack_t(type) * s, const char* sep,                   \
                   const char* prefix, const char* suffix) {                   \
    printf(prefix);                                                            \
    if (stack_empty(s)) {                                                      \
      printf(suffix);                                                          \
    } else {                                                                   \
      for (unsigned i = s->size; i > 1U; --i)                                  \
        printf("%d%s", s->ptr[i - 1], sep);                                    \
      printf("%d%s", s->ptr[0], suffix);                                       \
    }                                                                          \
  }

#endif /* _STACK_H_ */