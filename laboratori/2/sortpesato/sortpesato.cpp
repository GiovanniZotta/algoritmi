#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void stampa_vettore(vector<int>& vect){
    for(int i=0;i<vect.size();i++)
        std::cout << vect[i] << " ";
    std::cout << '\n';
}

bool is_ordered(vector<int>& vect, int start){
    for(int i=start; i<vect.size()-1; i++)
        if(vect[i] > vect[i+1])
            return false;
    return true;
}

int count_order(vector<int>& vect){
    int res=0;
    bool ret=false;
    for(int i=0; i<vect.size() && !ret; i++){
        if(vect[i] == i+2)
            res++;
        else
            ret=true;
    }
    return res;
}


int flip(vector<int>& vect){
    int costo=0;
    for(int i=0; i< vect.size(); i++){
        if(vect[i] != i+1){
            // std::cout << "flipping " << vect[i] << " and " << i+1<< '\n';
            // std::cout << "cost: " << vect[i] + i + 1<< '\n';
            if(vect[vect[i]-1] == i+1){
                costo += vect[i] + i + 1;
                vect[vect[i]-1] = vect[i];
                vect[i] = i+1;
            }
        }
    }
    return costo;
}

int scambi_minimi(vector<int> vect){
    int i = 0, contatore = 0;
    while(i < vect.size()){
        while(vect[i] != i + 1){
            int a = vect[i];
            vect[i] = vect[a-1];
            vect[a-1] = a;
            contatore++;
        }
        i++;
    }
    return contatore;
}

vector<int> create_support(vector<int>& vect){
    vector<int> support(vect.size(),0);
    for(int i=0; i<vect.size(); i++)
        support[vect[i]-1] = i;
    return support;
}

int altro_algoritmo(vector<int> vect){
    int costo = flip(vect);
    int min = count_order(vect);
    vector<int> support = create_support(vect);
    while(!is_ordered(vect, min)){
        // std::cout << '\n';
        // stampa_vettore(vect);
        // std::cout << "costo: " << costo << '\n';
        // std::cout << "min: " << min << "\n\n";
        if(vect[min] != 1){
            int pos = support[0];
            // std::cout << "flipping 1" << " and " << vect[support[pos]] << '\n';
            int pos2 = support[pos];
            vect[pos] = pos + 1;
            vect[pos2] = 1;

            support[0] = pos2;
            support[pos] = pos;

            costo += pos + 1 + 1;
        }else{
            // std::cout << "ordered: " << is_ordered(vect,min+1) << '\n';
            if(!is_ordered(vect,min+1)){
                int pos = support[min+1];
                vect[min] = min+2;
                vect[pos] = 1;
                support[0] = pos;
                support[min+1] = min;
                costo += min+3;
            }else{
                min++;
                break;
            }
            min++;
        }
        // 2 1 3 4 5 6 7 8 9 10
        // min=1
        //

    }
    for(int i=0; i<min; i++)
        costo += i+3;
    // std::cout << "fine: ";
    // stampa_vettore(vect);
    return costo;
}

pair<int,int> francesco(vector<int> & nums){
    pair<int, int> ret(0,0);
    int pos, sum, m, numsNo;
    for (int i = 1; i < nums.size(); i++) {
        if(nums[i] != -1){
            pos = sum = nums[i];
            numsNo = 1;
            m = nums[i];
            nums[i] = -1;
            while(pos != i){
                sum += nums[pos];
                m = min(m, nums[pos]);
                int tmp = nums[pos];
                nums[pos] = -1;
                pos = tmp;
                numsNo++;
            }
            ret.first += numsNo -1;
            ret.second += min((sum - m + (numsNo - 1) * m),
                          ((m + 1) * 2 + (sum - m) + numsNo -1 ));
        }
    }
    return ret;
}


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    int N;
    in >> N;

    vector<int> vect(N,0);
    for (int i = 0; i < N; i++)
        in >> vect[i];
    // std::cout << "input: ";
    // stampa_vettore(vect);
    vector<int> input = vect;
    std::cout << "inizio: " << '\n';
    stampa_vettore(vect);

    // out << scambi_minimi(vect) << " " << altro_algoritmo(vect);
    // std::cout << "algoritmo vecchio: " << '\n';
    // cout << scambi_minimi(vect) << " " << prezzo_minimo(vect)<<endl;
    std::cout << "result: ";
    int res = altro_algoritmo(vect);
    cout << scambi_minimi(vect) << " " << res <<endl;

    vector<int> nums(N+1);
    for (int i = 1; i < N+1; i++)
        nums[i] = vect[i-1];
    pair<int, int> ret = francesco(nums);
    std::cout << "francesco: " << ret.first << " " << ret.second << '\n';

    if(res < ret.second){
        ofstream special("special.txt");
        for(int i=0; i<input.size(); i++ )
            special << input[i] << " ";
    }
    std::cout << '\n';



    return 0;
}
