#include <bits/stdc++.h>

using namespace std;

int M, T2, T3, T4;
int total_score = 0;

ifstream in;
ofstream out;

vector<pair<int, set<string>>> get_pizzas(){
    // numero pizze, numero team da 2-3-4 persone
    in >> M >> T2 >> T3 >> T4;

    vector<pair<int, set<string>>> pizze(M);

    int n_ingredients; //numero ingredienti pizza i
    string ingredient;

    for (int i = 0 ; i < M ; i++) {
        in >> n_ingredients;
        for (int j = 0 ; j < n_ingredients ; j++) {
            in >> ingredient;
            pizze[i].first = i;
            pizze[i].second.insert(ingredient);
        }
    }

    sort(pizze.begin(), pizze.end(), []
        (pair<int, set<string>> set1, pair<int, set<string>> set2){
            return set1.second.size() < set2.second.size();
        }
    );

    return pizze;
}

int get_delivery_score(vector<pair<int, set<string>>> &pizzas, vector<int> &delivery){
    set<string> result_set;

    for (auto &pizza : pizzas) {
        for (int pizza_id : delivery) {
            if (pizza_id == pizza.first) {
                result_set.insert(pizza.second.begin(), pizza.second.end());
                break;
            }
        }
    }
    
    return pow(result_set.size(), 2);
}

pair<int, vector<vector<int>>> provide_pizzas(int n_teams, int participants, vector<pair<int, set<string>>> &pizzas, int &D) {
    vector<vector<int>> provided;
    int local_score = 0;
    bool done = false;
    
    while (n_teams > 0 && !done) { //finché ci sono team
        if (M >= participants) { //finché ci sono abbastanza pizze per un team
            vector<int> delivery;

            for (int i = pizzas.size() - participants; i <= pizzas.size() - 1; i++)
                delivery.push_back(pizzas[i].first);
                
            D += participants; // Add total delivered
            M -= participants; // Remove from total number of pizzas
            
            local_score += get_delivery_score(pizzas, delivery);
            
            provided.push_back(delivery);
            pizzas.erase(pizzas.end() - participants, pizzas.end()); //togli le ultime ${participants} pizze
        } else {
            done = true;
        }
        n_teams--;
    }

    return make_pair(local_score, provided);
}

void print_pizzas(int participants, vector<pair<int, set<string>>> &pizzas, vector<vector<int>> &delivered) {
    if (!delivered.empty()) {
        for (vector<int> pizzas : delivered) {
            out << participants << " ";
            for (int pizza : pizzas)
                out << pizza << " ";
            out << endl;
        }
    }
}

void find_sol(vector<pair<int, set<string>>> &pizze){
    int D = 0; // numero pizze totale

    cout << "M: " << M << ", T2: " << T2 << ", T3: " << T3 << ", T4: " << T4 << endl;
    
    pair<int, vector<vector<int>>> pizzas_4 = provide_pizzas(T4, 4, pizze, D);
    pair<int, vector<vector<int>>> pizzas_3 = provide_pizzas(T3, 3, pizze, D);
    pair<int, vector<vector<int>>> pizzas_2 = provide_pizzas(T2, 2, pizze, D);

    int local_score = pizzas_2.first + pizzas_3.first + pizzas_4.first;

    cout << "Score: " << local_score << endl;
    total_score += local_score;

    out << D << endl;
    print_pizzas(4, pizze, pizzas_4.second);
    print_pizzas(3, pizze, pizzas_3.second);
    print_pizzas(2, pizze, pizzas_2.second);
    
}

int main(){
    vector<string> real_inputs = {"a_example", "b_little_bit_of_everything.in", "c_many_ingredients.in", "d_many_pizzas.in", "e_many_teams.in"};
    vector<string> test_inputs = {"b_little_bit_of_everything.in"};
    for(string input: real_inputs){
        in.open("input/" + input);
        out.open("output/" + input);

        cout << "testcase: " << input << endl;
        vector<pair<int, set<string>>> pizze = get_pizzas();
        find_sol(pizze);

        in.close();
        out.close();
    }

    cout << "TOTAL SCORE: " << total_score << endl;
    return 0;
}
