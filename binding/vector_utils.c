#include "vector_utils.h"
#include <stdio.h>

static int cmpfunc(const void * a, const void * b)
{
  int a0 = ((int *)a)[0];
  int b0 = ((int *)b)[0];
  if (a0 < b0)
        {
          return -1;
        }
  else if (a0 > b0)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

void sort_int_vec(int * base, size_t len)
{
  qsort(base, len, sizeof(int), cmpfunc);
}
