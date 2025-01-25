#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define train_count (sizeof(train)/sizeof(train[0]))

//And gate
float train[][3] = {
    {0, 0, 0}, 
    {0, 1, 1}, 
    {1, 0, 1},
    {1, 1, 0},
};

float sigmoidf (float x) {
    return (1.f / (1.f + expf(-x)));
}   

float rand_float() {
    return ((float) rand() / (float)RAND_MAX - 0.5f)*2;
}

//the model now has two weights, as it now has two inputs.
float cost(float w1, float w2, float b) {  
 
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i){
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1*w1 + x2*w2 + b);
        float d = y - train[i][2]; 
        result += d*d;
    }
    result /= train_count;
    return result;
}

int main() {
    srand(time(0));

    float w1 = rand_float();
    float w2 = rand_float();
    float b  = rand_float();

    float eps = 1e-4;
    float rate = 0.01;

    for (size_t i = 0; i<100000; i++) {

        float c = cost(w1, w2, b);
        printf("w1 = %f     w2 = %f     b = %f     c = %f\n", w1, w2, b, c);   

        float dw1 = (cost(w1 + eps, w2 , b) - c)/eps; 
        float dw2 = (cost(w1, w2 + eps, b) - c)/eps;
        float db  = (cost(w1, w2, b + eps) - c)/eps;

        w1 -= rate*dw1;
        w2 -= rate*dw2;
        b  -= rate*db;

    }


    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j){
            float y = sigmoidf(i*w1 + j*w2 + b);
            printf("%zu | %zu = %f (Thresholded: %d)\n", i, j, y, y >= 0.5 ? 1 : 0);
        }
    }

return 0;

}