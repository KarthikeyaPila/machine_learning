#ifndef NN_H_
#define NN_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#define MAT_AT(m, i, j) (m).es[(i) * (m).stride + (j)]

typedef struct {
    size_t rows; 
    size_t cols; 
    size_t stride;
    float *es;
} Mat; 


Mat mat_alloc(size_t rows, size_t cols);
float rand_float();
void mat_rand(Mat m, float low, float high);
Mat mat_row(Mat m, size_t row);
void mat_copy(Mat dst, Mat src);
float sigmoidf(float f);
void mat_sig(Mat m);
void mat_dot(Mat dst, Mat a, Mat b);
void mat_sum(Mat dst, Mat a);
void mat_print(Mat m, const char *s);



#endif // NN_H_

#ifdef NN_IMPLEMENTATION

Mat mat_alloc(size_t rows, size_t cols){
    Mat m; 
    m.cols = cols;
    m.rows = rows; 
    m.stride = cols;
    m.es = (float *)malloc(sizeof(*m.es)*rows*cols);
    assert(m.es != NULL);
    return m;
}

void mat_fill(Mat m, float x){
    for(size_t i=0; i<m.rows; i++){
        for (size_t j=0; j<m.cols; j++){
           MAT_AT(m, i, j) = x;
        }
    }
}

float rand_float(){
    return (float) rand() / (float) RAND_MAX;
}

float sigmoidf(float x){
    float out = (1.f / (1.f + expf(-x)));
    return out;
}

void mat_sig(Mat m){
    for(size_t i=0; i<m.rows; i++){
        for (size_t j=0; j<m.cols; j++){
           MAT_AT(m, i, j) = sigmoidf(MAT_AT(m, i, j));
        }
    }
}

void mat_rand(Mat m, float low, float high){
    for(size_t i=0; i<m.rows; i++){
        for (size_t j=0; j<m.cols; j++){
           MAT_AT(m, i, j) = rand_float()*(high-low) + low;
        }
    }
}

// => C is the destination mat, a and b are the one's to be multiplied.
void mat_dot(Mat dst, Mat a, Mat b){
    assert(a.cols == b.rows);
    size_t n = a.cols;
    assert(dst.rows == a.rows);
    assert(dst.cols == b.cols);

    for(size_t i=0; i<dst.rows; i++){
        for(size_t j=0; j<dst.cols; j++){
            MAT_AT(dst, i, j) = 0;
            for(size_t k=0; k<n; k++){
                MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
            }
        }
    }
}

void mat_sum(Mat dst, Mat a) {
    for(size_t i=0; i<dst.rows; i++){
        for(size_t j=0; j<dst.cols; j++){
            MAT_AT(dst, i, j) += MAT_AT(a, i, j);
        }
    }
}

Mat mat_row(Mat m, size_t row){
    return (Mat) {
        .rows = 1,
        .cols = m.cols,
        .stride = m.stride,
        .es = &MAT_AT(m, row, 0)
    };
}


void mat_copy(Mat dst, Mat src){
    assert(dst.rows == src.rows);
    assert(dst.cols == src.cols);

    for(size_t i=0; i<dst.rows; i++){
        for(size_t j=0; j<dst.cols; j++){
            MAT_AT(dst, i, j) = MAT_AT(src, i, j);
        }
    }

}


void mat_print(Mat m, const char *s){
    printf("%s = [\n", s);
    for(size_t i=0; i<m.rows; i++){
        for (size_t j=0; j<m.cols; j++){
            printf("    %f", MAT_AT(m, i, j));
        }
        printf("\n");
    }
    printf("]\n");
}   

#endif  // NN_IMPLEMENTATION