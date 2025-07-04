#ifndef NN_H_
#define NN_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#define MAT_AT(m, i, j) (m).es[(i) * (m).stride + (j)]

typedef struct{
    size_t rows; 
    size_t cols; 
    size_t stride;
    float *es;
} Mat; 


Mat mat_alloc(size_t rows, size_t cols);
void mat_fill(Mat m, float x);
float rand_float();
void mat_rand(Mat m, float low, float high);
Mat mat_row(Mat m, size_t row);
void mat_copy(Mat dst, Mat src);
float sigmoidf(float f);
void mat_sig(Mat m);
void mat_dot(Mat dst, Mat a, Mat b);
void mat_sum(Mat dst, Mat a);
void mat_print(Mat m, const char *s, int padding);



typedef struct{
    size_t count;
    Mat *ws; 
    Mat *bs; 
    Mat *as;
} NN;

#define NN_INPUT(nn) (nn).as[0]
#define NN_OUTPUT(nn) (nn).as[(nn).count]

NN nn_alloc(size_t *arch, size_t arch_count);
void nn_print(NN nn, char *name);
void nn_rand(NN nn, float low, float high);
void nn_forward(NN nn);
float nn_cost(NN nn, Mat ti, Mat to);
void nn_finite_diff(NN nn, NN g, Mat ti, Mat to, float eps);
void nn_learn(NN nn, NN g, float rate);

#endif // NN_H_

#ifdef NN_IMPLEMENTATION

// MATRICES stuff
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

void mat_sum(Mat dst, Mat a){
    for(size_t i=0; i<dst.rows; i++){
        for(size_t j=0; j<dst.cols; j++){
            MAT_AT(dst, i, j) += MAT_AT(a, i, j);
        }
    }
}

Mat mat_row(Mat m, size_t row){
    return (Mat){
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

void mat_print(Mat m, const char *s, int padding){
    printf("%*s%s = [\n", (int)padding, "", s);
    for(size_t i=0; i<m.rows; i++){
        printf("%*s", (int)padding, "");
        for (size_t j=0; j<m.cols; j++){
            printf("    %f", MAT_AT(m, i, j));
        }
        printf("\n");
    }
    printf("%*s]\n", (int)padding, "");
}


// NN stuff 

NN nn_alloc(size_t *arch, size_t arch_count){

    NN nn;
    nn.count = arch_count - 1;

    nn.ws = malloc(sizeof(*nn.ws)*nn.count);
    assert(nn.ws != NULL);
    nn.bs = malloc(sizeof(*nn.bs)*nn.count);
    assert(nn.bs != NULL);
    nn.as = malloc(sizeof(*nn.as)*(nn.count+1));
    assert(nn.as != NULL);

    assert(arch_count > 0);
    nn.as[0] = mat_alloc(1, arch[0]);

    for(size_t i=1; i<arch_count; i++){
        nn.ws[i-1] = mat_alloc(nn.as[0].cols, arch[i]);
        nn.bs[i-1] = mat_alloc(1, arch[i]);
        nn.as[i] = mat_alloc(1, arch[i]);
    }

    return nn;
}

void nn_print(NN nn, char *name){
    printf("%s = [\n", name);
    char buff[256];
    for(size_t i = 0; i < nn.count; i++){
        snprintf(buff, sizeof(buff), "ws%zu", i);
        mat_print(nn.ws[i], buff, 4);
        snprintf(buff, sizeof(buff), "bs%zu", i);
        mat_print(nn.bs[i], buff, 4);
    } 
    printf("]\n");
}

void nn_rand(NN nn, float low, float high){
    for(size_t i=0; i<nn.count; i++){
        mat_rand(nn.ws[i], low, high);
        mat_rand(nn.bs[i], low, high);
    }
}

void nn_forward(NN nn){ 
    for(size_t i=0; i<nn.count; i++){
        mat_dot(nn.as[i+1], nn.as[i], nn.ws[i]);
        mat_sum(nn.as[i+1], nn.bs[i]);
        mat_sig(nn.as[i+1]);
    }
}

float nn_cost(NN nn, Mat ti, Mat to){
    assert(ti.rows == to.rows);
    assert(to.cols == NN_OUTPUT(nn).cols);
    size_t n = ti.rows;
    size_t q = to.cols;

    float c = 0;
    for(size_t i=0; i<n; i++){
        Mat x = mat_row(ti, i);
        Mat y = mat_row(to, i);

        mat_copy(NN_INPUT(nn), x);
        nn_forward(nn);

        for(size_t j=0; j<q; j++){
            float d = MAT_AT(NN_OUTPUT(nn), 0, j) - MAT_AT(y, 0, j);
            c += d*d;
        }
    }
    
    return c/(n);
}

void nn_finite_diff(NN nn, NN g, Mat ti, Mat to, float eps){
    float saved;
    float c = nn_cost(nn, ti, to);

    for(size_t i=0; i<nn.count; i++){
        for(size_t j=0; j<nn.ws[i].rows; j++){
            for(size_t k=0; k<nn.ws[i].cols; k++){
                saved = MAT_AT(nn.ws[i], j, k);
                MAT_AT(nn.ws[i], j, k) += eps;
                MAT_AT(g.ws[i], j, k) = (nn_cost(nn, ti, to) - c)/eps;
                MAT_AT(nn.ws[i], j, k) = saved;
            }
        }

        for(size_t j = 0; j < nn.bs[i].rows; j++){
            for(size_t k = 0; k < nn.bs[i].cols; k++){
                saved = MAT_AT(nn.bs[i], j, k);
                MAT_AT(nn.bs[i], j, k) += eps;
                MAT_AT(g.bs[i], j, k) = (nn_cost(nn, ti, to) - c)/eps;
                MAT_AT(nn.bs[i], j, k) = saved;
            }
        }
    }
}


void nn_learn(NN nn, NN g, float rate){
    for (size_t i = 0; i < nn.count; ++i) {
        for (size_t j = 0; j < nn.ws[i].rows; ++j) {
            for (size_t k = 0; k < nn.ws[i].cols; ++k) {
                MAT_AT(nn.ws[i], j, k) -= rate * MAT_AT(g.ws[i], j, k);
            }
        }

        for (size_t j = 0; j < nn.bs[i].rows; ++j) {
            for (size_t k = 0; k < nn.bs[i].cols; ++k) {
                MAT_AT(nn.bs[i], j, k) -= rate * MAT_AT(g.bs[i], j, k);
            }
        }
    }
}


#endif  // NN_IMPLEMENTATION