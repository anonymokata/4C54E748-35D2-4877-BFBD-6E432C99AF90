#pragma once

#include <stdlib.h>

struct _vector_reftype
{
  size_t * data;
  int capacity;
  int size;
};

typedef struct _vector_reftype * vector_reftype;

vector_reftype vectorRefType_create();
void vectorRefType_pushBack(vector_reftype this_ref, size_t item);
void vectorRefType_popBack(vector_reftype this_ref);
int vectorRefType_size(vector_reftype this_ref);
size_t vectorRefType_element(vector_reftype this_ref, int position);
void vectorRefType_destroy(vector_reftype this_ref);
