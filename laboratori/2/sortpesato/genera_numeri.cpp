#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
int main(int argc, char const *argv[]) {
    int N = 20;
    if(argc == 2)
        N = atoi(argv[1]);
    vector<int> vect;
    unsigned seed = std::chrono::system_clock::now()
						   .time_since_epoch()
						   .count();
    for(int i=1; i<=N; i++)
        vect.push_back(i);
    shuffle(vect.begin(), vect.end(), default_random_engine(seed));
    std::cout << N << '\n';
    for(int i=0; i < N; i++){
        std::cout << vect[i] << " ";
    }
    return 0;
}
