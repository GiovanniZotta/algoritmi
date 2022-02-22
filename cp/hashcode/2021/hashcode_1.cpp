#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
#define NOT_ARRIVED -1

ifstream in;
ofstream out;

// duration, number of intersections, streets, cars, bonus points for each car before time D 
int D, I, S, V, F;
vector<vector<int>> first_car_times;
bool adjusted_order = false;

struct Car {
    vector<string> streets;
    int id;
    int current_street;
    int travel_length;
    bool in_queue;
    bool just_popped;
    int finish_time;
    Car () {}

    string toString(){
        string result = "car " + to_string(id) + " ";
        if(finish_time == NOT_ARRIVED){
            result += "in queue: " + to_string(in_queue) + ", just popped: " + to_string(just_popped) + ", travel_length: " 
                + to_string(travel_length) + ", current_street: " + streets[current_street]  + ", not arrived" + ", streets: ";
            for(string street_name : streets){
                result = result + street_name + " ";
            }
        }else{
            result += "arrived";
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
    int first_car_time;
    bool already_used;
    queue<Car*> cars_queue;

    Street() {}

    Street(string NAME, int FROM, int TO, int LENGTH, int INITIAL_CARS, bool ALREADY_USED): 
        name(NAME), from(FROM), to(TO), length(LENGTH), initial_cars(INITIAL_CARS), already_used(ALREADY_USED) {}

    string toString() {
        return "name: " + name + ", from: " + to_string(from) +  ", to: " 
                + to_string(to) + ", length: " + to_string(length) + ", cars: " + to_string(initial_cars) + ", queue size: " + to_string(cars_queue.size()) + 
                ", first_car_time: " + to_string(first_car_time) + "\n";
    }
    
    void print_queue(){
        cout << "street " << name << " queue: " << endl;
        while(!cars_queue.empty()){
            Car* el = cars_queue.front(); cars_queue.pop();
            cout << el->toString();
        }
    }
};

typedef pair<Street*, int> Schedule;

struct Intersection {
    int id;
    double C = -1;
    vector<Street*> incoming;
    vector<Street*> outgoing;
    unordered_map<int, Street*> open_street;
    int cycle_length;
    vector<Schedule> schedule;

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

    void setup_open_streets(){
        int range = 0, last_cycle = 0;
        cycle_length = 0;
        for(Schedule &s : schedule){
            int open_time = s.second;
            cycle_length += open_time;
            for(int i = last_cycle; i < last_cycle + open_time; i++){
                open_street[i] = s.first;
            }
            last_cycle = last_cycle + open_time;
        }
    }

    Street* get_open_street(int time){
        if(cycle_length != 0){
            return open_street[time%cycle_length];
        }else{
            return nullptr;
        }
    }

    void create_schedule() {
        int street_frequency_sum = get_street_frequency_sum();
        // int K = 1 + int( rand() % 3);

        if (street_frequency_sum != 0) {
            // compute_C(street_frequency_sum);
            for (Street *s : incoming) {
                if (s->frequency != 0) {
                    int result = 1;
                    result = max(result, 1);
                    result = min(result, D);
                    schedule.push_back(make_pair(s, result));
                }
            }
        }
        // if(schedule.size() > 100)
        //     cerr << "interesting roads for intersection " << id << ": " << schedule.size() << endl;
        // cerr << id << " cycle length: " << cycle_length << endl;
        if(adjusted_order){
            for(int i=0; i<first_car_times[id].size(); i++){
                int time_to_be_open = first_car_times[id][i];
                // cerr << time_to_be_open << endl;
                int j = rand() % 10000;
                if(j == 0){
                    cout << "before swap: \na: " << schedule[i].first->toString() << "b: " << schedule[time_to_be_open].first->toString();
                    cout << "schedule a index: " << i << ", schedule b index: " << time_to_be_open << endl;
                }
                swap(schedule[i], schedule[time_to_be_open]);
                if(j == 0){
                    cout << "after swap: \na: " << schedule[i].first->toString() << "b: " << schedule[time_to_be_open].first->toString();
                    cout << "schedule a index: " << time_to_be_open << ", schedule b index: " << i << endl;
                }

            }
        }else{
            random_shuffle(schedule.begin(), schedule.end());
        }
    }

    void adjust_schedule_order(){
        if(id == 0){
            cerr << "intersection 0 cycle length: " << cycle_length << endl;
        }
        for(int i=0; i<schedule.size(); i++){
            int time_to_be_open = ((schedule[i].first)->first_car_time) % cycle_length;
            // cerr << ((schedule[i].first)->first_car_time) << endl;
            first_car_times[id][i] = time_to_be_open;
            if(id == 0){
                cerr << schedule[i].first->name << " has to be open at time " << time_to_be_open << endl;
            }
            // cerr << "time to be open " << time_to_be_open << endl;
            // cerr << "swapping " << schedule[i].first->name << " with " << schedule[time_to_be_open].first->name << endl;
            // swap(schedule[i], schedule[time_to_be_open]);
        }        
    }

    string print_schedule() {
        string result = "";
        result += to_string(id) + "\n";
        result += to_string(schedule.size()) + "\n";
        // out << id << endl;
        // out << schedule.size() << endl;
        // cerr << "schedule size " << schedule.size() << endl;
        for (Schedule &street : schedule) {
            // cerr << street.first->name << endl;
            result += street.first->name + " " + to_string(street.second) + "\n";
            // out << street.first->name << " " << street.second << endl;
        }
        return result;
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
        for(Schedule &s : schedule){
            result += s.first->name + " stays green for " + to_string(s.second) + " seconds every cycle" + "\n";
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

    void setup_open_streets(){
        for(Intersection *i : intersections){
            i->setup_open_streets();
        }
    }

    void adjust_schedule_orders(){
        first_car_times.resize(I);
        for(Intersection *i : intersections){
            first_car_times[i->id].resize(i->schedule.size());
            i->adjust_schedule_order();
        }
        adjusted_order = true;
        cout << "adjusted order. " << endl;
        // for(Intersection *i : intersections){
        //     cout << "intersection " << i->id << endl;
        //     for(int j=0; j<first_car_times[i->id].size(); j++){
        //         cout << j << " first car time: " << first_car_times[i->id][j] << endl;
        //     }
        // }
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
        Street* s = new Street(name, from, dest, length, 0, false);
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
        c->id = i;
        c->in_queue = true;
        c->just_popped = false;
        c->travel_length = 0;
        c->current_street = 0;
        c->finish_time = NOT_ARRIVED;
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

string print_solution(vector<Intersection*> &intersections) {
    int interesting_intersections = 0;

    for (Intersection *intersection : intersections) {
        if (intersection->schedule.size() > 0){
            interesting_intersections++;
        }
    }

    string result = to_string(interesting_intersections) + "\n";
    for (Intersection *intersection : intersections){
        if (intersection->schedule.size() > 0) {
            result += intersection->print_schedule();
            // intersection->print_schedule();
        }
    }
    return result;
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

void pop_cars_from_queue(City &city, vector<Car*> &cars, int time){
    for(Intersection *i : city.intersections){
        // cout << "1" << endl;
        Street* s = i->get_open_street(time);
        if(s != nullptr){
            // cout << i->toString() << endl;
            // if(s->cars_queue.size() > 0)
            //     cout << "for intersection " << i->id << ", the open street is: " << s->name << " which has " << s->cars_queue.size() << " cars in queue" <<endl;
            // cout << s->cars_queue.empty() << endl;
            if(!s->cars_queue.empty()){
                // cout << "2" << endl;
                Car* car_popped = s->cars_queue.front(); s->cars_queue.pop();
                // cout << "3" << endl;
                car_popped->in_queue = false;
                car_popped->current_street++;
                int next_street_index = car_popped->current_street;
                // cout << "4" << endl;
                if(next_street_index < car_popped->streets.size()){
                    Street* next_street = city.get_street_by_name(car_popped->streets[next_street_index]);
                    // cout << "5" << endl;
                    car_popped->travel_length = next_street->length;
                    car_popped->just_popped = true;
                } else {
                    car_popped->finish_time = time;
                }
                // cout << car_popped->toString() << endl;
            }
        }
    }
}

void push_cars_in_queue(City &city, vector<Car*> &cars, int time){
    for(Car* c : cars){
        if(!c->in_queue && c->finish_time == NOT_ARRIVED){ // the car is in travel
            c->travel_length--;
            if(c->travel_length == 0){ // put the car in queue
                Street* current_street = city.get_street_by_name(c->streets[c->current_street]);
                if(c->current_street < c->streets.size()){
                    current_street->cars_queue.push(c);
                    c->in_queue = true;
                    if(!current_street->already_used){
                        current_street->already_used = true;
                        current_street->first_car_time = time+1; //forse time + 1
                        if(current_street->to == 0){
                            cerr << "first car coming at intersection 0 on street " << current_street->name << " is " << c->id << " at time " << time << endl;
                        }
                    }
                    // cout << "putting car in queue in street " << current_street->name << endl;
                }else{
                    c->finish_time = time;
                }
            }
        }
        if(c->just_popped){
            c->just_popped = false;
        }
    }
}

void delete_stuff(City &city, vector<Car*> &cars){
    for(Intersection *i : city.intersections){
        for(Street *s : i->incoming){
            delete s;
        }
        delete i;
    }
    for(Car *c : cars){
        delete c;
    }
}

void start_simulation(City &city, vector<Car*> &cars){
    int time = 0;
    // D = 7;
    while(time <= D){
        // if(rand() % 100 == 0) cerr << (double) time / D * 100 << "%   ";
        // cout << time << endl;
        // cout << "TIME: " << time << endl;
        // cout << "CARS: " << endl;
        // for(Car* c : cars){
        //     cout << c->toString() << endl;   
        // }
        // cout << "INTERSECTIONS: " << endl;
        pop_cars_from_queue(city, cars, time); // pop cars that are in queues in open streets
        push_cars_in_queue(city, cars, time); // put cars that have travel_time == 0 in queue

        // for(Intersection *i : city.intersections){
        //     cout << "at time " << t << ", in intersection " << i->id << " the open street is " << i->get_open_street(t)->name << endl;
        // }
        // cout << endl;
        time++;
    }
}

void print_open_streets(City &city){
    for(Intersection *i : city.intersections){
        cout << "Intersection " << i->id << " has " << i->incoming.size() << " streets with cycle length " << i->cycle_length << endl;
        i->print_open_street();
    }
}

void print_cars_finish_times(vector<Car*> &cars){
    for(Car* c : cars){
        cout << c->finish_time << endl;
    }
}

int calculate_score(vector<Car*> &cars){
    int arrived_cars = 0;
    int bonus_score = 0;
    for(Car* c : cars){
        if(c->finish_time != NOT_ARRIVED){
            arrived_cars++;
            bonus_score += D - c->finish_time;
        }
    }
    // cout << "arrived cars score: " << arrived_cars * F << endl;
    // cout << "bonus score awarded for early arrivals: " << bonus_score << endl;
    int total_score = (arrived_cars * F) + bonus_score;
    // cout << "total score: " << total_score << endl;
    return total_score;
}

int main(){
    vector<string> real_inputs = {"a.txt", "b.txt", "c.txt", "d.txt", "e.txt", "f.txt"};
    vector<string> test_inputs = {"d.txt"};
    int N_SIMUL = 2;
    int total_score = 0;
    
    for (string input: test_inputs) {
        cout << "testcase: " << input << endl;    
        int best_score = 0, i=0;
        string best_solution = "";
        while(i++ < N_SIMUL){
            cerr << "\nsimulation " << i << endl;
            in.open("input/" + input);

            in >> D >> I >> S >> V >> F;

            vector<Intersection*> intersections = generate_intersections(I, S);

            City city = City();
            city.intersections = intersections;
            city.compute_streets_map();
            vector<Car*> cars = generate_cars(V, city);
            // vector<Car*> interesting_cars = get_interesting_cars(intersections, cars); // those who can actually make it to the end

            set_street_frequency(intersections, cars);
            set_initial_cars(intersections, cars);

            // print_intersections(intersections);
            // print_cars(cars);
            
            generate_schedule(intersections, cars);
            // cout << city.toString() << endl;
            city.setup_open_streets();
            // print_open_streets(city);
            start_simulation(city, cars);
            if(!adjusted_order)
                city.adjust_schedule_orders();
            // print_cars_finish_times(cars);
            int testcase_score = calculate_score(cars);
            string solution = print_solution(intersections);
            if(testcase_score > best_score){
                best_solution = solution;
                best_score = testcase_score;
                cerr << "NEW BEST!!! " << best_score << endl;
            }
            // delete_stuff(city, cars);
            in.close();
        }
        out.open("output/" + input);
        cerr << "BEST EVER!!!!!" << endl;
        out << best_solution << endl;
        out.close();

        total_score += best_score;
    }

    cerr << "TOTAL SCORE: " << total_score << endl;

    return 0;
}
