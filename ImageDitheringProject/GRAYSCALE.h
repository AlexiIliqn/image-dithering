#ifndef GRAYSCALE_H_INCLUDED
#define GRAYSCALE_H_INCLUDED

typedef unsigned char PIXEL;

void image_grayscale(PIXEL* data, int width, int height, int depth, PIXEL* output);

void image_grayscale(PIXEL* data, int width, int height, int depth, PIXEL* output)
{
    for(size_t y = 0; y<height; ++y)
    {
        for(size_t x = 0; x<width; ++x)
        {
            size_t offset = (y*width +x)*depth;
            PIXEL* in = data + (offset);
            PIXEL* out = output + (offset);

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

#endif // GRAYSCALE_H_INCLUDED
