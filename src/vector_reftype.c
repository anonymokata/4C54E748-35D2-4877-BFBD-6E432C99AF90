#include "vector_reftype.h"

#include <stdlib.h>
#include <string.h>

vector_reftype vectorRefType_create()
{
  vector_reftype retval = (vector_reftype) malloc(sizeof(struct _vector_reftype));
  retval->capacity = 8;
  retval->size = 0;
  retval->data = (size_t *) malloc(sizeof(size_t) * retval->capacity);

  return retval;
}

void vectorRefType_pushBack(vector_reftype this_ref, size_t item)
{
  if(this_ref->size >= this_ref->capacity)
  {
    int new_cap = this_ref->capacity * 2;
    size_t * new_array = (size_t *) malloc(sizeof(size_t) * new_cap);
    memcpy(new_array, this_ref->data, sizeof(size_t) * this_ref->capacity);
    free(this_ref->data);
    this_ref->data = new_array;
    this_ref->capacity = new_cap;
  }
  this_ref->data[this_ref->size] = item;
  this_ref->size++;
}

void vectorRefType_popBack(vector_reftype this_ref)
{
  this_ref->size--;
}

size_t vectorRefType_element(vector_reftype this_ref, int position)
{
  return this_ref->data[position]; 
}

int vectorRefType_size(vector_reftype this_ref)
{
  return this_ref->size;
}

void vectorRefType_destroy(vector_reftype this_ref)
{
  free(this_ref->data);
  free(this_ref);
}
