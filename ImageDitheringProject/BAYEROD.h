#ifndef BAYEROD_H
#define BAYEROD_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define AT(x,y,size) ((y)*(size) + (x))

float* bayer_matrix_generate(int size);
void bayer_generate_recursive(float* m, int x, int y, int size, int mainsize);
void bayer_matrix_divide(float* m, int size);
void bayer_matrix_free(float* m);
void bayer_matrix_print(float* m, int size);

void image_bayerod(unsigned char* data, int width, int height, int depth, unsigned char* output, float* bayer_matrix, int bayer_size);
#endif // BAYEROD_H_INCLUDED
