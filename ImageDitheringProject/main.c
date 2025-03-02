#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#include "GRAYSCALE.h"
#include "BAYEROD.h"

void make_grayscale(unsigned char* data, int width, int height, int depth);
void make_bayerod(unsigned char* data, int width, int height, int depth);

int main()
{
    printf("Hello world!\n");
    const char* source_file_name = "images/source.jpg";
    unsigned char* source_img;
    int width, height, n;
    assert(stbi_info(source_file_name, &width, &height, &n));
    assert((source_img = stbi_load(source_file_name, &width, &height, &n, STBI_rgb_alpha)));

    make_grayscale(source_img, width, height, STBI_rgb_alpha);

    stbi_image_free(source_img);

    printf("[FINISHED]\n");
    return 0;
}

void make_grayscale(unsigned char* data, int width, int height, int depth)
{
    unsigned char* output = malloc(sizeof(unsigned char)*width*height*depth);
    assert(output);

    image_grayscale(data, width, height, depth, output);

    make_bayerod(output, width, height, depth);
    // bayer, floyd, atkinson

    assert(stbi_write_jpg("images/grayscale.jpg", width, height, depth, output, 100));

    free(output);

    printf("[GRAYSCALE]\n");
}

void make_bayerod(unsigned char* data, int width, int height, int depth)
{
    int bayer_matrix_size = 16;
    float* bayer_matrix = bayer_matrix_generate(bayer_matrix_size);
    bayer_matrix_divide(bayer_matrix, bayer_matrix_size);
    //bayer_matrix_print(bayer_matrix, bayer_matrix_size);

    unsigned char* output = malloc(sizeof(unsigned char)*width*height*depth);
    assert(output);

    image_bayerod(data, width, height, depth, output, bayer_matrix, bayer_matrix_size);

    assert(stbi_write_jpg("images/bayerod.jpg", width, height, depth, output, 100));

    bayer_matrix_free(bayer_matrix);
    free(output);

    printf("[BAYER]\n");
}
