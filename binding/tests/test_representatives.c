#include "e8vectors.h"
#include "rank16_vectors.h"
#include <stdio.h>
#include "memory.h"
#include <math.h>
#include "vector_utils.h"

void print_vec(int * vec, int a)
{
  for (int i = 0; i < a; i++)
    {
      printf("%d, ", vec[i]);
    }
  printf("\n");
}

int test_norm_vec(void)
{
  cache_vectors_rk16();
  Rk16VecInt vec1[16];
  Rk16VecInt vec2[16];
  Rk16VecInt vec3[16];
  Rk16VecInt vec4[16];
  for (int i = 0; i < num_of_vectors_rk16[2]; i++)
    {
      memcpy(vec1, cached_vectors_rk16[2][i], sizeof(int) * 16);
      _convert_to_euclid_vector_rk16(vec1);
      memcpy(vec2, vec1, sizeof(int) * 16);
      normalize_vec_rk16(vec1);
      memcpy(vec3, vec1, sizeof(int) * 16);
      memcpy(vec4, vec2, sizeof(int) * 16);

      int mul1 = 1;
      int mul2 = 1;
      for (int j = 0; j < 16; j++)
        {
          mul1 *= vec1[j];
        }
      for (int j = 0; j < 16; j++)
        {
          mul2 *= vec2[j];
        }

      for (int j = 0; j < 7; j++)
        {
          if (vec1[j] != vec2[j])
            {
              printf("False: unchagne.\n");
              print_vec(vec1, 16);
              print_vec(vec2, 16);
              return -1;
            }
        }

      for (int j = 0; j < 16; j++)
        {
          vec1[j] = abs(vec1[j]);
          vec2[j] = abs(vec2[j]);
        }

      sort_int_vec(vec1, 16);
      sort_int_vec(vec2, 16);

      for (int j = 0; j < 16; j++)
        {
          if (vec1[j] != vec2[j])
            {
              printf("False: sorting\n");
              print_vec(vec1, 16);
              print_vec(vec2, 16);
              return -1;
            }
        }
      if (mul1 != mul2)
        {
          print_vec(vec3, 16);
          print_vec(vec4, 16);
          printf("False: sign\n");
          return -1;
        }
    }
  return 0;
}

int main()
{
  int a = test_norm_vec();
  printf("%d\n", a);
  /* static int _reprs[MAX_NM_OF_VECTORS_RK16][17]; */
  /* int num = repr_modulo_autom_rk16(3, _reprs); */
  /* printf("%d\n", num); */
  /* int s = 0; */
  /* for (int i = 0; i < num; i++) */
  /*   { */
  /*     s += _reprs[i][16]; */
  /*     /\* for (int j = 0; j < 17; j++) *\/ */
  /*     /\*   { *\/ */
  /*     /\*     printf("%d, ", _reprs[i][j]); *\/ */
  /*     /\*   } *\/ */
  /*     /\* printf("\n"); *\/ */
  /*   } */
  /* printf("%d\n", s); */
  /* cache_vectors_rk16(); */
  /* Rk16VecInt vec[16]; */
  /* for (int i = 0; i < num_of_vectors_rk16[2]; i++) */
  /*   { */
  /*     for (int j = 0; j < 16; j++) */
  /*       { */
  /*         vec[j] = cached_vectors_rk16[2][i][j]; */
  /*       } */
  /*     _convert_to_euclid_vector_rk16(vec); */
  /*     print_vec(vec); */
  /*     normalize_vec_rk16(vec); */
  /*     print_vec(vec); */
  /*   } */
  return 0;
}


/* Local Variables: */
/* compile-command: "gcc rank16_vectors.c -L./lib -lm -lint_vector_sort -o test -std=c11" */
/* End: */
