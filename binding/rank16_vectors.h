#ifndef _RANK16_VECTORS_H_
#define _RANK16_VECTORS_H_

#define MAX_NORM_RK16 3
/* MAX_NORM_RK16 th Fourier coefficient of the Eisenstein series of weight 8 */
#define MAX_NM_OF_VECTORS_RK16 1050240

#define MAX_NM_REPRS_RK16 10000
typedef int Rk16VecInt;

extern int num_of_vectors_rk16[8];
Rk16VecInt cached_vectors_rk16[MAX_NORM_RK16 + 1][MAX_NM_OF_VECTORS_RK16][16];

void cache_vectors_rk16(void);
int repr_modulo_autom_rk16(int n, int reprs[MAX_NM_REPRS_RK16][16], unsigned int num_of_classes[MAX_NM_REPRS_RK16]);
int repr_modulo_autom_rk16_w_indices(Rk16VecInt vecs[MAX_NM_OF_VECTORS_RK16][16],
                                     int num_of_vecs,
                                     int reprs[MAX_NM_REPRS_RK16][16],
                                     unsigned int num_of_classes[MAX_NM_REPRS_RK16],
                                     int w_sign_indices[16],
                                     int wo_sign_indices_array[8][16]);
void set_w_sign_indices_rk16(int indices[16], const Rk16VecInt vec[16]);
void set_wo_sign_indices_array(int indices_array[8][16], const Rk16VecInt vec[16]);
void set_w_sign_indices_rk16_2(int indices[16], const Rk16VecInt vec1[16],
                               const Rk16VecInt vec2[16]);
void set_wo_sign_indices_array2(int indices_array[8][16], const Rk16VecInt vec1[16],
                                const Rk16VecInt vec2[16]);

/* Extern followings only for tests */
void normalize_vec_rk16_last9(Rk16VecInt vec[16]);
void normalize_vec_rk16_w_indices(Rk16VecInt vec[16], int w_sign_indices[16], int wo_sign_indices_array[8][16]);
#endif /* _RANK16_VECTORS_H_ */
