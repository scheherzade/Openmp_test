#include<iostream>
#include<vector>
#include<omp.h>
#include<exception>
#include<ctime>
#include<chrono>

int main(int argc, char* argv[]){
    int64_t vector_size = 0;
    if(argc > 1)
        vector_size = atoi(argv[1]);
    std::vector<float> a(vector_size,2.0f);
    std::vector<float> b(vector_size,3.0f);
    std::vector<float> c(vector_size,0);

    auto start = std::chrono::system_clock::now();
#pragma omp parallel for
    for (int64_t i = 0; i < vector_size; i++){
        c[i] = a[i]+b[i];
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    double elapsed_secs = elapsed_seconds.count();

    std::cout<<"time(seconds): "<<elapsed_secs<<std::endl;

    float operations = vector_size*1/elapsed_secs/1000000;

    for (int64_t i = 0; i < vector_size; i++){
        if(c[i] != 5){
            std::cout<<",WRONG ANSWER,"<<std::endl;
            throw std::invalid_argument("wrong result");
        }
    }

    std::cout<<"MFLOPS: "<<operations<<std::endl;

    return 0;
}
