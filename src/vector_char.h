#pragma once

struct _vector_char
{
  char * data;
  int capacity;
  int size;
};

typedef struct _vector_char * vector_char;

vector_char vectorChar_create();
void vectorChar_pushBack(vector_char this_ref, char item);
void vectorChar_popBack(vector_char this_ref);
int vectorChar_size(vector_char this_ref);
char vectorChar_element(vector_char this_ref, int position);
void vectorChar_destroy(vector_char this_ref);
