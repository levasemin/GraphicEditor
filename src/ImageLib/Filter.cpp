#include "ImageLib.hpp"
#include <immintrin.h>
#include <iostream>
#include <deque>
#include <cstring>

#define func(value, min, max) (value < min ? min : value > max ? max: value)

void make_filter_intrinsic(float *array, int *kernel, int picture_h, int picture_w, int kernel_h, int kernel_w)
{
    int max_x = picture_w - 1;
    int max_y = picture_h - 1;
    std::deque<float *> saved_rows;
    
    for (int i = 0; i < kernel_h / 2 + 1; i++)
    {
        float *row_copy = new float[picture_w];
        std::copy(array, array + picture_w, row_copy);
        saved_rows.push_back(row_copy);
    }
    
    
    for (int y = 0; y < picture_h; y++)
    {
        float *current_save = saved_rows.back();
        saved_rows.pop_back();
        std::copy(array + y * picture_w, array + (y + 1) * picture_w, current_save);

        for (int x = 0; x < picture_w; x++)
        {   
            float curr_pix = 0;
            __m256 result = _mm256_setr_ps(0, 0, 0, 0, 0, 0, 0 , 0);

            for (int i = 0; i < kernel_h / 2 + 1; i++)
            {
                __m256 picture_part = _mm256_setr_ps(saved_rows[i][func(x - 3, 0, max_x)], saved_rows[i][func(x - 2, 0, max_x)],
                                                     saved_rows[i][func(x - 1, 0, max_x)], saved_rows[i][func(x,     0, max_x)],
                                                     saved_rows[i][func(x + 1, 0, max_x)], saved_rows[i][func(x + 2, 0, max_x)],
                                                     saved_rows[i][func(x + 3, 0, max_x)], 0);
                
                __m256 kernel_part =  _mm256_setr_ps(kernel[i * kernel_w],      kernel[i * kernel_w + 1],
                                                     kernel[i * kernel_w + 2],  kernel[i * kernel_w + 3],
                                                     kernel[i * kernel_w + 4],  kernel[i * kernel_w + 5],
                                                     kernel[i * kernel_w + 6],  0);
                
                result = _mm256_add_ps(result, _mm256_mul_ps(picture_part, kernel_part));
            }
            
            for (int i = 1; i < kernel_h / 2 + 1; i++)
            {
                int y_ = func(y + i, 0, max_y);
                
                if (y != picture_h - 1)
                {
                    y_ = y_ * picture_w;

                    __m256 picture_part = _mm256_setr_ps(array[y_ + func(x - 3, 0, max_x)], array[y_ + func(x - 2, 0, max_x)],
                                                        array[y_ + func(x - 1, 0, max_x)], array[y_ + func(x,     0, max_x)],
                                                        array[y_ + func(x + 1, 0, max_x)], array[y_ + func(x + 2, 0, max_x)],
                                                        array[y_ + func(x + 3, 0, max_x)], 0);
                    
                    int i_ = i + kernel_h / 2;

                    __m256 kernel_part =  _mm256_setr_ps(kernel[i_ * kernel_w],      kernel[i_ * kernel_w + 1],
                                                        kernel[i_ * kernel_w + 2],  kernel[i_ * kernel_w + 3],
                                                        kernel[i_ * kernel_w + 4],  kernel[i_ * kernel_w + 5],
                                                        kernel[i_ * kernel_w + 6],  0);
                    
                    result = _mm256_add_ps(result, _mm256_mul_ps(picture_part, kernel_part));
                }
                
                else
                {
                    y_ = y_ * picture_w;

                    __m256 picture_part = _mm256_setr_ps(current_save[func(x - 3, 0, max_x)], current_save[func(x - 2, 0, max_x)],
                                                         current_save[func(x - 1, 0, max_x)], current_save[func(x,     0, max_x)],
                                                         current_save[func(x + 1, 0, max_x)], current_save[func(x + 2, 0, max_x)],
                                                         current_save[func(x + 3, 0, max_x)], 0);
                    
                    int i_ = i + kernel_h / 2;

                    __m256 kernel_part =  _mm256_setr_ps(kernel[i_ * kernel_w],      kernel[i_ * kernel_w + 1],
                                                        kernel[i_ * kernel_w + 2],  kernel[i_ * kernel_w + 3],
                                                        kernel[i_ * kernel_w + 4],  kernel[i_ * kernel_w + 5],
                                                        kernel[i_ * kernel_w + 6],  0);
                    
                    result = _mm256_add_ps(result, _mm256_mul_ps(picture_part, kernel_part));
                }
                
            }
            
            float *pointer = (float *)&result;
            for (int    i = 0; i < kernel_w; i++)
            {
                curr_pix += *pointer;
            }

            array[y * picture_w + x] = curr_pix;
        }

        saved_rows.push_front(current_save);
    }
}

void make_filter(float *array, int *kernel, int picture_h, int picture_w, int kernel_h, int kernel_w)
{
    
    int max_x = picture_w - 1;
    int max_y = picture_h - 1;

    for (int y = 0; y < picture_h; y++)
    {
        for (int x = 0; x < picture_w; x++)
        {   
            float result = 0;
            for (int i = -kernel_h / 2; i < kernel_h / 2; i++)
            {
                int y_ = func(y_ - i, 0, max_y);
                y_ *= picture_w;

                for (int j = -kernel_w / 2; j < kernel_w / 2; j++)
                {
                    int x_ = func(x + j, 0, max_x);
                    result += array[y_ + x_] * kernel[(i + kernel_h) * kernel_w + j + kernel_w];
                }
            }

            array[y * picture_w + x] = result;
        }
    }
}