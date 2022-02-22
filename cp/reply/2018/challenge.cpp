#include <bits/stdc++.h>
using namespace std;

int V, S, C, P;

struct Project {
    int penalty;
    string country;
    vector<int> units_needed;

    Project() {}

    Project(int PENALTY, string COUNTRY):
        penalty(PENALTY), country(COUNTRY) {}

    string toString(){
        string result = "";
        result += "Project, penalty: " + to_string(penalty) + ", country: " + country + "\n";
        return result;
    }
};

struct Region {
    string name;
    int id;
    int total_units;
    double cost;
    vector<int> latency;
    vector<int> n_units;
    Region() {}

    Region(string NAME, int ID, int TOTAL_UNITS, double COST, vector<int> LATENCY, vector<int> N_UNITS):
        name(NAME), id(ID), total_units(TOTAL_UNITS), cost(COST), latency(LATENCY), n_units(N_UNITS) {}

    string toString(){
        string result = "";
        result += "Region: " + name + ", id: " + to_string(id) + ", units: " + to_string(total_units) + "\n";
        return result;
    }
};

struct Provider {
    string name;
    int id;
    vector<Region> regions;

    Provider() {}

    Provider(string NAME, int ID):
        name(NAME), id(ID) {}

    string toString(){
        string result = "";
        result += "Provider: " + name + ", id: " + to_string(id) + "\n";
        for(Region &r : regions){
            result += "\t" + r.toString();
        }
        return result;
    }
};

unordered_map<string, int> service_mapping;
unordered_map<string, int> country_mapping;
vector<string> services;
vector<string> countries;
vector<Provider> providers;
vector<Project> projects;

void print_providers(){
    for(Provider &p : providers){
        cerr << p.toString() << endl;
    }
}

void print_projects(){
    for(Project &p: projects){
        cerr << p.toString();
    }
}

void read_services(){
    string tmp;
    for(int i=0; i<S; i++){
        cin >> tmp;
        services.push_back(tmp);
        service_mapping[tmp] = i;
    }
}

void read_countries(){
    string tmp;
    for(int i=0; i<C; i++){
        cin >> tmp;
        countries.push_back(tmp);
        country_mapping[tmp] = i;
    }
}

void read_providers(){
    string provider_name, region_name;
    int nregions, nservices, tmp_unit, country_lat;
    double cost;
    for(int i=0; i<V; i++){
        cin >> provider_name >> nregions;
        Provider p(provider_name, -1);
        for(int j=0; j<nregions; j++){
            cin >> region_name >> nservices >> cost;
            vector<int> n_units(S);
            vector<int> latency(C);
            for(int k=0; k<S; k++){
                cin >> tmp_unit;
                n_units[k] = tmp_unit;
            }
            for(int k=0; k<C; k++){
                cin >> country_lat;
                latency[k] = country_lat;
            }
            Region r(region_name, -1, nservices, cost, latency, n_units);   
            p.regions.push_back(r);
        }
        providers.push_back(p);
    }
}
                
void read_projects(){
    int penalty;
    string country;
    vector<int> units_needed;
    int tmp;
    for(int i=0; i<P; i++){
        cin >> penalty >> country;
        Project p(penalty, country);
        p.units_needed.resize(S);
        for(int j=0; j<S; j++){
            cin >> tmp;
            p.units_needed[j] = tmp;
        }
        projects.push_back(p);
    }
}



int main(int argc, char* argv[]){
    srand(atoi(argv[1]));
    cin >> V >> S >> C >> P;
    read_services();
    read_countries();
    read_providers();
    read_projects();
    print_providers();
    print_projects();
    return 0;
}
