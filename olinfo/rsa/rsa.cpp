#include <map>

using namespace std;
int power(int base, int esp, int mod) {
    long result = base;
    for (int i = 1; i < esp; i++)
        result = (result * base) % mod;
    return result % mod;
}

void decifra(int N, int d, int L, int* messaggio, char* plaintext) {
    int i, result;
    map<int, int> DP;
    for (i = 0; i < L; i++) {
        if (DP.count(messaggio[i] % N)) {
            plaintext[i] = DP.at(messaggio[i]);
        } else {
            result = power(messaggio[i] % N, d, N);
            DP.insert(make_pair(messaggio[i] % N, result));
            plaintext[i] = result; 
        }
    }
    plaintext[i] = '\0';
}