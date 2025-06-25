#define NN_IMPLEMENTATION

#include <time.h>
#include "nn.h"

#define MAT_PRINT(m) mat_print(m, #m, 0)
#define NN_PRINT(nn) nn_print(nn, #nn)
#define ARRAY_LEN(xs) sizeof((xs))/sizeof((xs)[0])

// training data.
float td[] = {
    0, 0, 0,
    0, 1, 1, 
    1, 0, 1, 
    1, 1, 0
};

int main() {
    srand(time(0));
    
    size_t stride = 3;
    size_t n = sizeof(td)/sizeof(td[0])/stride;
    
    
    Mat ti = {
        .rows = n, 
        .cols = 2, 
        .stride = stride,
        .es = td
    };
    
    Mat to = {
        .rows = n, 
        .cols = 1, 
        .stride = stride, 
        .es = td + 2
    };
    
    size_t arch[] = {2, 2, 1};
    NN nn = nn_alloc(arch, ARRAY_LEN(arch));
    NN g = nn_alloc(arch, ARRAY_LEN(arch));
    
    printf("-------------------------\n");

    mat_copy(NN_INPUT(nn), mat_row(ti, 1));
    nn_rand(nn, 0, 1);
    nn_forward(nn);

    float eps = 1e-3;
    float rate = 1;

    printf("-------------------------\n");

    printf("cost: %f\n", nn_cost(nn, ti, to));
    for(size_t i=0; i<2*1000; i++){
        nn_finite_diff(nn, g, ti, to, eps);
        nn_learn(nn, g, rate);
    }
    printf("cost: %f\n", nn_cost(nn, ti, to));

    printf("-------------------------\n");
    printf("-------------------------\n");

    NN_PRINT(nn);

    printf("-------------------------\n");
    printf("-------------------------\n");

    for(size_t i=0; i<2; i++){
        for(size_t j=0; j<2; j++){
            MAT_AT(NN_INPUT(nn), 0, 0) = i;
            MAT_AT(NN_INPUT(nn), 0, 1) = j;
            nn_forward(nn);
            float y = MAT_AT(NN_OUTPUT(nn), 0, 0);
            printf("%zu ^ %zu = %f\n", i, j, y);
        }
    }

    printf("-------------------------\n");
    printf("-------------------------\n");
    return 0;
}