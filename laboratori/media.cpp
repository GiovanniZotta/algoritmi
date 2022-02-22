#include <vector>
#include <iostream>

using namespace std;

void print_final_vote(float avg){
    float base = avg * 11 / 3;
    float bonus_points = (avg - 18.0) / 4.0;
    cout << "media ponderata: " << avg << endl;
    cout << "base di laurea: " << base << endl;
    cout << "punti bonus in base alla media (0 - 3): " << bonus_points << endl;
    base += bonus_points; // 0-3 in base alla media
    base += 1.0; //dicembre

    cout << "voto senza prova finale finendo entro dicembre: " << base << endl;
    for(int i = 27; i <= 30; i++){
        float tmp = base + ((i - 18.0) / 12.0) * 5; // 0-5 in base al voto della prova finale
        cout << "voto con tesi da " << i << ": " << tmp << endl;
    }
}

int main(int argc, char const *argv[]){
    int n, cfu = 0, a, b;
    string trash;
    float sum = 0.0;
    while(cin >> a >> b >> trash){
        if(a == 0)
            continue;
        cfu += b;
        sum += (a * b);

    }
    print_final_vote(sum / cfu);
    return 0;
}
