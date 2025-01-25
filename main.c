#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define train_count (sizeof(train)/sizeof(train[0]))

float train[][2] = {
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
    {5,10}
};

float rand_float() {
    return (float) rand() / (float) RAND_MAX;
}

// gives us the error value, and we then make it to near zero
float cost(float w, float b) {
    float result = 0.0f;
    for (size_t i = 0; i < train_count; ++i){
        float x = train[i][0];
        float y = x*w + b;
        float d = y - train[i][1]; 
        result += d*d;
    }
    return result;
}

int main() {
    srand(time(0));
    float w = rand_float()*10.0f;   // gives a random weight
    float b = rand_float()*5.0f;    // gives a random bias

    float eps = 1e-3;
    float rate = 1e-3;

    for (size_t i = 0; i < 5000; i++) {
        float dw = (cost(w + eps, b) - cost(w, b))/eps;     // w = weight
        float db = (cost(w, b + eps) - cost(w, b))/eps;     // b = bias

        w -= rate*dw;
        b -= rate*db;

        //printf("cost: %f    w: %f   b: %f\n", w+b /*cost(w,b)*/, w, b);   
    }

    for (size_t i = 0; i < train_count; i++) {
        printf("%f      %f\n", train[i][0], (w+b)*train[i][0]);
    }

    return 0;
}