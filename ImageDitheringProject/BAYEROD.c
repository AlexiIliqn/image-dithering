#include "BAYEROD.h"

float* bayer_matrix_generate(int size)
{
    float* bayer_matrix = calloc(size*size, sizeof(float));
    assert(bayer_matrix);

    bayer_generate_recursive(bayer_matrix, 0, 0, size, size);

    return bayer_matrix;
}

void bayer_generate_recursive(float* m, int x, int y, int size, int mainsize)
{
    if(size == 1)
    {
        m[AT(x, y, mainsize)] = 0.0f;
        return;
    }

    int half = size/2;
    bayer_generate_recursive(m, x, y, half, mainsize);

    for(size_t dy = 0; dy<half; ++dy)
    {
        for(size_t dx = 0; dx<half; ++dx)
        {
            float up_left_value = 4.0f * m[AT(x+dx, y+dy, mainsize)];
            m[AT(x+dx, y+dy, mainsize)] = up_left_value;
            m[AT(x+half+dx, y+dy, mainsize)] = up_left_value + 2.0f;
            m[AT(x+dx, y+half+dy, mainsize)] = up_left_value + 3.0f;
            m[AT(x+half+dx, y+half+dy, mainsize)] = up_left_value + 1.0f;
        }
    }
}

void bayer_matrix_divide(float* m, int size)
{
    float divider = (float)size*size;
    for(size_t y=0; y<size; ++y)
    {
        for(size_t x=0; x<size; ++x)
        {
            m[AT(x, y, size)] /= divider;
        }
    }
}

void bayer_matrix_free(float* m)
{
    free(m);
}

void bayer_matrix_print(float* m, int size)
{
    for(size_t y = 0; y<size; ++y)
    {
        for(size_t x = 0; x<size; ++x)
        {
            printf("%3.3f ", m[AT(x, y ,size)]);
        }
        printf("\n");
    }
}

void image_bayerod(unsigned char* data, int width, int height, int depth, unsigned char* output, float* bayer_matrix, int bayer_size)
{
    for(size_t y = 0; y<height; ++y)
    {
        for(size_t x = 0; x<width; ++x)
        {
            size_t offset = (y*width +x)*depth;
            unsigned char* in = data + (offset);
            unsigned char* out = output + (offset);

            float color_normalized = (float)(in[0])/255.0f;
            size_t new_color;

            if(color_normalized > bayer_matrix[AT(x%bayer_size, y%bayer_size, bayer_size)])
            {
                new_color = 255;
            }else{
                new_color = 0;
            }

            switch(depth)
            {
                case 3:
                    {
                        *out = *(out+1) = *(out+2) = new_color;
                        break;
                    }
                case 4:
                    {
                        *out = *(out+1) = *(out+2) = new_color;
                        *(out+3) = 255;
                        break;
                    }
                default:
                    {
                        assert(0);
                        break;
                    }
            }
        }
    }
}

