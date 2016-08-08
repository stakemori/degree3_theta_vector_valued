#ifndef _RANK16_VECTORS_H_
#define _RANK16_VECTORS_H_

#define MAX_NORM_RK16 3
/* MAX_NORM_RK16 th Fourier coefficient of the Eisenstein series of weight 8 */
#define MAX_NM_OF_VECTORS_RK16 1050240

typedef int Rk16VecInt;

extern int num_of_vectors_rk16[8];
Rk16VecInt cached_vectors_rk16[MAX_NORM_RK16 + 1][MAX_NM_OF_VECTORS_RK16][16];

void cache_vectors_rk16(void);

/* Extern followings only for tests */
void _convert_to_euclid_vector_rk16(Rk16VecInt vec[16]);
void _convert_from_euclid_vector_rk16(Rk16VecInt vec[16]);
void normalize_vec_rk16(Rk16VecInt vec[16]);
int repr_modulo_autom_rk16(int n, int repr[MAX_NM_OF_VECTORS_RK16][17]);

#endif /* _RANK16_VECTORS_H_ */
