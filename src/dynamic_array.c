#include "../include/dynamic_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef int item_type;

// typedef struct {
//   item_type* ptr;
//   unsigned capacity;
//   unsigned size;
// } dynamic_array_t;

unsigned length(const dynamic_array_t* da) {
  return da->size;
}

void swap(item_type* x, item_type* y) {
  item_type temp = *x;
  *x = *y;
  *y = temp;
}

void print(const dynamic_array_t* da) {
  printf("\n[");
  if (0U == da->size) {
    printf("]\n");
  } else {
    for (unsigned i = 0U; i != da->size; ++i)
      printf("%d%s", da->ptr[i], i + 1 != da->size ? "|" : "]\n");
  }
}

bool increase_specified_dynamic_array_capacity(dynamic_array_t* da) {
  const unsigned new_capacity = da->capacity != 0U ? da->capacity << 1 : 8U;
  item_type* new_ptr = (item_type*)malloc(new_capacity * sizeof(item_type));
  if (NULL == new_ptr)
    return false;
  memcpy(new_ptr, da->ptr, da->size * sizeof(item_type));
  free(da->ptr);
  da->ptr = new_ptr;
  da->capacity = new_capacity;
  return true;
}

bool decrease_specified_dynamic_array_capacity(dynamic_array_t* da) {
  if (da->capacity <= 8U)
    return false;

  const unsigned new_capacity = da->capacity >> 1;
  item_type* new_ptr = (item_type*)malloc(new_capacity * sizeof(item_type));
  if (NULL == new_ptr)
    return false;
  memcpy(new_ptr, da->ptr, da->size * sizeof(item_type));
  free(da->ptr);
  da->ptr = new_ptr;
  da->capacity = new_capacity;
  return true;
}

bool insert_element_at_the_beginning(dynamic_array_t* da,
                                     const item_type value) {
  if (da->size == da->capacity) {
    if (!increase_specified_dynamic_array_capacity(da))
      return false;
  }

  for (unsigned i = da->size; i > 0U; --i)
    da->ptr[i] = da->ptr[i - 1];

  da->ptr[0] = value;
  ++da->size;

  return true;
}

bool insert_element_at_the_end(dynamic_array_t* da, const item_type value) {
  if (da->size == da->capacity) {
    if (!increase_specified_dynamic_array_capacity(da))
      return false;
  }

  da->ptr[da->size] = value;
  ++da->size;

  return true;
}

bool insert_element_at_specified_index(dynamic_array_t* da,
                                       const item_type value,
                                       const unsigned index) {
  if (index >= da->size)
    return false;

  if (da->size == da->capacity) {
    if (!increase_specified_dynamic_array_capacity(da))
      return false;
  }

  for (unsigned i = da->size; i > index; --i)
    da->ptr[i] = da->ptr[i - 1];

  da->ptr[index] = value;

  return true;
}

bool set_element_at_specified_index(dynamic_array_t* da,
                                    const item_type value,
                                    const unsigned index) {
  if (index >= da->size)
    return false;

  da->ptr[index] = value;

  return true;
}

bool get_element_at_specified_index(const dynamic_array_t* da,
                                    const unsigned index,
                                    item_type* element) {
  if (index >= da->size)
    return false;

  *element = da->ptr[index];

  return true;
}

bool delete_first_element(dynamic_array_t* da) {
  if (NULL == da->ptr || 0U == da->size)
    return false;

  for (unsigned i = 0U; i < da->size - 1; ++i)
    da->ptr[i] = da->ptr[i + 1];

  --da->size;

  if (da->size <= da->capacity / 4)
    decrease_specified_dynamic_array_capacity(da);

  return true;
}

bool delete_last_element(dynamic_array_t* da) {
  if (NULL == da->ptr || 0U == da->size)
    return false;

  --da->size;

  if (da->size <= da->capacity / 4)
    decrease_specified_dynamic_array_capacity(da);

  return true;
}

bool delete_element_at_specified_index(dynamic_array_t* da,
                                       const unsigned index) {
  if (NULL == da->ptr || index >= da->size)
    return false;

  for (unsigned i = index; i < da->size - 1; ++i)
    da->ptr[i] = da->ptr[i + 1];

  --da->size;

  if (da->size <= da->capacity / 4)
    decrease_specified_dynamic_array_capacity(da);

  return true;
}

void destroy_dynamic_array(dynamic_array_t* da) {
  if (NULL != da->ptr)
    free(da->ptr);

  da->ptr = NULL;
  da->capacity = 0U;
  da->size = 0U;
}

bool reverse_dynamic_array_in_place(dynamic_array_t* da) {
  item_type* ptr = da->ptr;

  if (NULL == da->ptr || da->size < 2U)
    return false;

  for (unsigned i = 0U, j = da->size - 1; i < j; ++i, --j)
    swap(&ptr[i], &ptr[j]);

  return true;
}

dynamic_array_t create_reversed_copy_of_specified_dynamic_array(
    const dynamic_array_t* da) {
  dynamic_array_t reversed_da = {0};
  reversed_da.ptr = (item_type*)malloc(da->capacity * sizeof(item_type));
  reversed_da.size = da->size;
  reversed_da.capacity = da->capacity;
  for (unsigned i = 0U, j = da->size - 1; i < da->size; ++i, --j)
    reversed_da.ptr[i] = da->ptr[j];
  return reversed_da;
}
