#include "GRAYSCALE.h"

void image_grayscale(unsigned char* data, int width, int height, int depth, unsigned char* output)
{
    for(size_t y = 0; y<height; ++y)
    {
        for(size_t x = 0; x<width; ++x)
        {
            size_t offset = (y*width +x)*depth;
            unsigned char* in = data + (offset);
            unsigned char* out = output + (offset);

            size_t avg;
            switch(depth)
            {
                case 3:
                    {
                        avg = (*in + *(in+1) + *(in+2))/3;
                        *out = *(out+1) = *(out+2) = avg;
                        break;
                    }
                case 4:
                    {
                        avg = (*in + *(in+1) + *(in+2))/3;
                        *out = *(out+1) = *(out+2) = avg;
                        *(out+3) = 255;
                        break;
                    }
            }
        }
    }
}
