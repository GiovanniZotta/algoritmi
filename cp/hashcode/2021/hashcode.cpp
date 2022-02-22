#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<string, int> si;

ifstream in;
ofstream out;

// duration, number of intersections, streets, cars, bonus points for each car before time D 
int D, I, S, V, F;

struct Car {
    vector<string> streets;
    int travel_length;
    bool in_queue;
    Car () {}

    string toString(){
        string result;
        result = "in queue: " + to_string(in_queue) + ", travel_length: " + to_string(travel_length) + ", streets: ";
        for(string street_name : streets){
            result = result + street_name + " ";
        }
        return result;
    }
};

struct Street {
    string name;
    int from;
    int to;
    int length;
    int initial_cars;
    int frequency;
    queue<Car*> cars_queue;

    Street() {}

    Street(string NAME, int FROM, int TO, int LENGTH, int INITIAL_CARS): 
        name(NAME), from(FROM), to(TO), length(LENGTH), initial_cars(INITIAL_CARS) {}

    string toString() {
        return "name: " + name + ", from: " + to_string(from) +  ", to: " 
                + to_string(to) + ", length: " + to_string(length) + ", cars: " + to_string(initial_cars) + ", queue size: " + to_string(cars_queue.size()) + "\n";
    }
    
    void print_queue(){
        cout << "street " << name << " queue: " << endl;
        while(!cars_queue.empty()){
            Car* el = cars_queue.front(); cars_queue.pop();
            cout << el->toString();
        }
    }
};

struct Intersection {
    int id;
    double C = -1;
    vector<Street*> incoming;
    vector<Street*> outgoing;
    unordered_map<int, Street*> open_street;
    int cycle_length;
    vector<si> schedule;

    Intersection() {}
    
    Intersection(int ID): id(ID) {}

    // void compute_C(int street_frequency_sum) {
    //     for (Street &s : incoming) {
    //         if (s.frequency != 0) {
    //             double local_C = street_frequency_sum * s.initial_cars / s.frequency;
    //             C = max(local_C, C);
    //         }
    //     }
    // }

    int get_street_frequency_sum(){
        int street_frequency_sum = 0;
        for (Street *s : incoming) {
            street_frequency_sum += s->frequency;
        }
        return street_frequency_sum;
    }

    void setup_open_street(int last_cycle, int green_time, Street* s){
        for(int i = last_cycle; i < last_cycle + green_time; i++){
            open_street[i] = s;
        }
    }

    void create_schedule() {
        int last_cycle = 0;
        int street_frequency_sum = get_street_frequency_sum();
        int K = 3;

        if (street_frequency_sum != 0) {
            // compute_C(street_frequency_sum);
            for (Street *s : incoming) {
                if (s->frequency != 0) {
                    int result = ceil(double(s->frequency) / double(street_frequency_sum) * K);
                    result = max(result, 1);
                    result = min(result, D);
                    cycle_length += result;
                    setup_open_street(last_cycle, result, s);
                    last_cycle = last_cycle + result;
                    schedule.push_back(make_pair(s->name, result));
                }
            }
        }
        // cout << id << " cycle length: " << cycle_length << endl;
    }

    void print_schedule() {
        out << id << endl;
        out << schedule.size() << endl;
        for (si &street : schedule) {
            out << street.first << " " << street.second << endl;
        }
    }

    void print_open_street(){
        for(pair<const int, Street*> &el : open_street){
            cout << "at time " << el.first << " street " << el.second->name << " is open" << endl;
        }
    }

    string toString(){
        string result = "Intersection " + to_string(id) + "\n";
        result += "Streets: \n";
        for(Street *s: incoming){
            result += s->toString();
        }
        result += "Schedule: \n";
        for(si s : schedule){
            result += s.first + " stays green for " + to_string(s.second) + " seconds every cycle" + "\n";
        }
        return result;
    }
};

struct City {
    vector<Intersection*> intersections;
    unordered_map<string, Street*> streets_map;

    City() {}

    void compute_streets_map(){
        for (Intersection *intersection : intersections) {
            for (Street *street : intersection->incoming) {
                streets_map[street->name] = street;
            }
        }
    }

    Street* get_street_by_name(string street_name){
        return streets_map[street_name];
    }

    string toString(){
        string result = "City: \n";
        for(Intersection *i : intersections){
            result += i->toString();
        }
        return result;
    }

};

void print_cars(vector<Car*> &cars) {
    for (int i = 0; i < cars.size(); i++) {
        cout << "Car " << i << ": ";
        cout << cars[i]->toString();
        cout << endl;
    }
}

vector<Intersection*> generate_intersections(int I, int S) {
    vector<Intersection*> intersections(I);

    for (int i = 0; i < I; i++) {
        intersections[i] = new Intersection(i);
    }

    for (int i = 0 ; i < S; i++) {
        int from, dest, length;
        string name;
        in >> from >> dest >> name >> length;
        Street* s = new Street(name, from, dest, length, 0);
        intersections[from]->outgoing.push_back(s);
        intersections[dest]->incoming.push_back(s);
    }
    
    return intersections;
}

vector<Car*> generate_cars(int V, City &city) {
    vector<Car*> cars;
    int length;
    string street_name;
    
    for (int i = 0 ; i < V; i++) {
        in >> length;
        Car* c = new Car();
        c->in_queue = true;
        c->travel_length = 0;
        for(int j = 0; j < length; j++){
            in >> street_name;
            c->streets.push_back(street_name);
        }
        cars.push_back(c);
        if(length > 0){
            city.get_street_by_name(c->streets[0]) -> cars_queue.push(c);
        }
    }
    return cars;
}

vector<Car*> get_interesting_cars(vector<Intersection*> &intersections, vector<Car*> &cars){
    unordered_map<string, int> street_length;
    for (Intersection *i : intersections) {
        for(Street *s : i->incoming){
            street_length[s->name] = s->length;
        }
    }

    vector<Car*> interesting_cars;

    for(Car *c : cars){
        int time_of_path = 0;
        for(string street : c->streets){
            time_of_path += street_length[street];
        }
        if(time_of_path < D){
            interesting_cars.push_back(c);
        }
    }
    
    return interesting_cars;
}

void generate_schedule(vector<Intersection*> &intersections, vector<Car*> &cars) {
    for (Intersection *intersection : intersections) {
        intersection->create_schedule();
    }
}

void print_solution(vector<Intersection*> &intersections) {
    int interesting_intersections = 0;

    for (Intersection *intersection : intersections) {
        if (intersection->schedule.size() > 0){
            interesting_intersections++;
        }
    }

    out << interesting_intersections << endl;
    for (Intersection *intersection : intersections){
        if (intersection->schedule.size() > 0) {
            intersection->print_schedule();
        }
    }
}

void set_initial_cars(vector<Intersection*> &intersections, vector<Car*> &cars){
    unordered_map<string, int> streets;

    for(Car *c : cars){
        if(c->streets.size() > 0){
            streets[c->streets[0]]++;
        }
    }

    for (Intersection *i : intersections){
        for(Street *s : i->incoming){
            s->initial_cars = streets[s->name];
        }   
    }
}

void set_street_frequency(vector<Intersection*> &intersections, vector<Car*> &cars){
    unordered_map<string, int> street_frequency;
    for(Car *c : cars){
        for (string street_name : c->streets) {
            street_frequency[street_name]++;
        }
    }

    for(Intersection *i : intersections){
        for(Street *s : i->incoming){
            s->frequency = street_frequency[s->name];
        }
        // for(Street &s : i.outgoing){
        //     s.frequency = street_frequency[s.name];
        // }
    }
}

void advance_cars_in_travel(vector<Car*> &cars){
    for(Car *c : cars){
        if(!c->in_queue){
            c->travel_length--;
        }
    }
}

void start_simulation(City &city, vector<Car*> &cars){
    int t = 0;
    while(t < D){
        advance_cars_in_travel(cars);

    }
}

void print_open_streets(City &city){
    for(Intersection *i : city.intersections){
        cout << "Intersection " << i->id << " has " << i->incoming.size() << " streets with cycle length " << i->cycle_length << endl;
        i->print_open_street();
    }
}

int main(){
    vector<string> real_inputs = {"a.txt", "b.txt", "c.txt", "d.txt", "e.txt", "f.txt"};
    vector<string> test_inputs = {"a.txt"};
    
    for (string input: real_inputs) {
        in.open("input/" + input);
        out.open("output/" + input);

        cout << "testcase: " << input << endl;    
        in >> D >> I >> S >> V >> F;

        vector<Intersection*> intersections = generate_intersections(I, S);

        City city = City();
        city.intersections = intersections;
        city.compute_streets_map();
        vector<Car*> cars = generate_cars(V, city);
        vector<Car*> interesting_cars = get_interesting_cars(intersections, cars); // those who can actually make it to the end

        set_street_frequency(intersections, cars);
        set_initial_cars(intersections, cars);

        // print_intersections(intersections);
        // print_cars(cars);

        generate_schedule(intersections, cars);
        // cout << city.toString() << endl;
        // print_open_streets(city);

        // start_simulation(city, cars);

        print_solution(intersections);

        in.close();
        out.close();
    }

    return 0;
}
