#include "vector_char.h"

#include <stdlib.h>
#include <string.h>

vector_char vectorChar_create()
{
  vector_char retval = (vector_char) malloc(sizeof(struct _vector_char));
  retval->capacity = 8;
  retval->size = 0;
  retval->data = (char *) malloc(sizeof(char) * retval->capacity);

  return retval;
}

void vectorChar_pushBack(vector_char this_ref, char item)
{
  if(this_ref->size >= this_ref->capacity)
  {
    int new_cap = this_ref->capacity * 2;
    char * new_array = (char *) malloc(sizeof(char) * new_cap);
    memcpy(new_array, this_ref->data, sizeof(char) * this_ref->capacity);
    free(this_ref->data);
    this_ref->data = new_array;
    this_ref->capacity = new_cap;
  }
  this_ref->data[this_ref->size] = item;
  this_ref->size++;
}

void vectorChar_popBack(vector_char this_ref)
{
  this_ref->size--;
}

char vectorChar_element(vector_char this_ref, int position)
{
  return this_ref->data[position]; 
}

int vectorChar_size(vector_char this_ref)
{
  return this_ref->size;
}

void vectorChar_destroy(vector_char this_ref)
{
  free(this_ref->data);
  free(this_ref);
}
