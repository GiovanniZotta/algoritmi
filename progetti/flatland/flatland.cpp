#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

vector<int> flatland(string set);
bool can_be_eliminated_left(string set, int index);
bool can_be_eliminated_right(string set, int index);

bool can_be_eliminated_left(string set, int index){
    if(set[index] == 's' || index < 0)
        return true;
    while(index > 0)
        if(set[index] == 's' && set[index+1] == 'd')
            return true;
        else
            index-=2;
    return false;
}

bool can_be_eliminated_right(string set, int index){
    if(set[index] == 'd' || index >= set.length())
        return true;
    while(index < set.length())
        if(set[index] == 'd' && set[index-1] == 's')
            return true;
        else
            index+=2;
    return false;
}


vector<int> flatland(string set){
    vector<int> solution;
    for(int i=0; i<set.length(); i+=2)
        if(can_be_eliminated_left(set, i-1) && can_be_eliminated_right(set, i+1))
            solution.push_back(i);
    return solution;
}

int main(int argc, char const *argv[]) {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N;
    in >> N;
    string set;
    in >> set;
    vector<int> solution = flatland(set);
    out << solution.size() << endl;
    for(int s : solution)
        out << s << " ";
    return 0;
}
