#include <iostream>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <fstream>
#include <atomic>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


int sieve(int totalNums, std::ofstream &myfile){


    omp_set_num_threads(8);
    std::atomic<long long> sum (0);

    std::vector<int> isPrime(totalNums + 1, 1);
    int totalNumsSqrt = sqrt(totalNums);
    isPrime[0] = isPrime[1] = 0;

    #pragma omp parallel for schedule(dynamic, 8)
    for (int i = 2; i <= totalNumsSqrt; i++){
        if (isPrime[i]){
            for (int j = i*i; j <= totalNums; j += i)
                isPrime[j] = 0;
        }
    }


    int arr[100];
    int j = 0;
    for (int i = totalNums-1; i >= 2; i--) {
        if (isPrime[i] == 1){
            if(j <= 10){
                arr[j] = i;
            }
            j++;
            sum += i;
            if(j == 10){
                for (int k = 9; k >= 0; k--){
                    myfile << arr[k] << "\n";
                }
            }
        }
    }




    myfile << "Sum of primes: " << sum.load() << "\n";

    int totalPrimes = 0;
    #pragma omp parallel for reduction(+:totalPrimes)
    for (int i = 2; i <= totalNums; i++){
        totalPrimes += isPrime[i];
    }

    isPrime.clear();

    myfile << "total number of primes found: " << totalPrimes << "\n";

    return 0;

}


int main(void)
{
    std::ofstream myfile;
    myfile.open("outputs/primes.txt");

    long totalNums = pow(10,8);

    myfile << "Top 10 maximum primes, listed in order from lowest to highest: \n";

    auto start = high_resolution_clock::now();
    sieve(totalNums, myfile);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    auto seconds = duration.count() * pow(10,-6);

    myfile << "Execution time: " << seconds << "s\n";

    return 0;
}
