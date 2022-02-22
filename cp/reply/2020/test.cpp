#include <bits/stdc++.h>

using namespace std;
#define DEV 0
#define PM 1
#define WALL 2
#define NOT_ASSIGNED -1

typedef pair<int,int> ii;
ii NA_PAIR = {NOT_ASSIGNED, NOT_ASSIGNED};
static vector<int> ew = {0, 0,  1, -1};
static vector<int> ns = {1, -1, 0, 0};

string folder_name = "asd";
const int CYCLES = 1;
const long long int SWAPS = 20'000'000;

// total swaps = 2 * CYCLES * SWAPS

struct Dev{
    int company, bonus;
    ii pos;
    vector<int> skills;

    string toString(){
        string result = "dev. company: " + to_string(company) + ", bonus: " + to_string(bonus) + ", pos: (" + to_string(pos.first) + ", " + to_string(pos.second) + ")" + ", skills: ";
        for(int skill : skills)
            result += to_string(skill) + " ";
        return result;
    }
};


int W, H, NDEV, NPM;
unordered_map<string, int> company_mapping;
unordered_map<string, int> skills_mapping;
vector<vector<ii>> room;
vector<vector<ii>> components;
vector<Dev> devs;
vector<bool> used_devs;
vector<Dev> pms;
vector<bool> used_pms;

void print_room(){
    for(int i=0; i<room.size(); i++){
        for(int j=0; j<room[i].size(); j++){
            if(room[i][j].first == DEV)
                cerr << '_';
            if(room[i][j].first == PM)
                cerr << 'M';
            if(room[i][j].first == WALL)
                cerr << '#';
        }
        cerr << endl;
    }
}

void print_devs(){
    for(Dev &d : devs){
        cerr << d.toString() << endl;
    }
}

void print_pms(){
    for(Dev &pm : pms){
        cerr << pm.toString() << endl;
    }
}

void read_room(){
    cin >> W >> H;
    room.resize(H+2);
    for(int i=0; i<H+2; i++){
        room[i].resize(W+2);
        if(i == 0 || i == H+1){
            for(int j=0; j<W+2; j++)
                room[i][j] = {WALL, NOT_ASSIGNED};
        }else{
            string r;
            cin >> r;
            for(int j=0; j<W+2; j++){
                if(j == 0 || j == W+1){
                    room[i][j] = {WALL, NOT_ASSIGNED};
                }else{
                    if(r[j-1] == '_')
                        room[i][j] = {DEV, NOT_ASSIGNED};
                    if(r[j-1] == 'M')
                        room[i][j] = {PM, NOT_ASSIGNED};
                    if(r[j-1] == '#')
                        room[i][j] = {WALL, NOT_ASSIGNED};
                }
            }
        }
    }
}

void read_devs(){
    cin >> NDEV;
    devs.resize(NDEV);
    used_devs.resize(NDEV, false);
    string company, skill;
    int bonus, nskills;
    for(int i=0; i<NDEV; i++){
        cin >> company >> bonus >> nskills;
        if(company_mapping.find(company) == company_mapping.end()){
            company_mapping[company] = company_mapping.size();
        }
        devs[i].company = company_mapping[company];
        devs[i].bonus = bonus;
        devs[i].pos = NA_PAIR;
        for(int j=0; j<nskills; j++){
            cin >> skill;
            if(skills_mapping.find(skill) == skills_mapping.end()){
                skills_mapping[skill] = skills_mapping.size();
            }
            devs[i].skills.push_back(skills_mapping[skill]);
        }
    }
}

void read_pms(){
    cin >> NPM;
    pms.resize(NPM);
    used_pms.resize(NPM, false);
    string company;
    int bonus;
    for(int i=0; i<NPM; i++){
        cin >> company >> bonus;
        if(company_mapping.find(company) == company_mapping.end()){
            company_mapping[company] = company_mapping.size();
        }
        pms[i].company = company_mapping[company];
        pms[i].bonus = bonus;
        pms[i].pos = NA_PAIR;
    }
}

void print_sol(){
    for(int i=0; i<NDEV; i++){
        if(devs[i].pos == NA_PAIR){
            cout << "X" << endl;
        }else{
            cout << devs[i].pos.second-1 << " " << devs[i].pos.first-1 << endl;
        }
    }
    for(int i=0; i<NPM; i++){
        if(pms[i].pos == NA_PAIR){
            cout << "X" << endl;
        }else{
            cout << pms[i].pos.second-1 << " " << pms[i].pos.first-1 << endl;
        }
    }
}

vector<ii> neighbours(ii cell){
    return  {   
                {cell.first, cell.second - 1},
                {cell.first, cell.second + 1},
                {cell.first + 1, cell.second},
                {cell.first - 1, cell.second}
            };
}

void component_dfs(vector<ii> &component, vector<vector<bool>> &visited, ii cell){
    visited[cell.first][cell.second] = true;
    component.push_back(cell);
    for(ii neighbour : neighbours(cell)){
        if(room[neighbour.first][neighbour.second].first != WALL){
            if(!visited[neighbour.first][neighbour.second]){
                component_dfs(component, visited, neighbour);
            }
        }
    }
}

vector<ii> get_component(vector<vector<bool>> &visited, ii cell){
    vector<ii> component;
    component_dfs(component, visited, cell);
    return component;
}

void find_components(){
    vector<vector<bool>> visited(room.size());
    for(int i=0; i<room.size(); i++){
        visited[i].resize(room[i].size());
        for(int j=0; j<room[i].size(); j++){
            visited[i][j] = false;
        }
    }
    for(int i=0; i<room.size(); i++){
        for(int j=0; j<room[i].size(); j++){
            if(room[i][j].first != WALL){
                if(!visited[i][j]){
                    components.push_back(get_component(visited, {i, j}));
                }
            }
        }
    }
}

bool are_adjacent(ii &pos1, ii &pos2){
    if(pos1.first + 1 == pos2.first)
        return pos1.second == pos2.second;
    if(pos1.first - 1 == pos2.first)
        return pos1.second == pos2.second;
    if(pos1.second + 1 == pos2.second)
        return pos1.first == pos2.first;
    if(pos1.second - 1 == pos2.second)
        return pos1.first == pos2.first;
}

// bool are_adjacent(Dev &r1, Dev &r2){
//     return are_adjacent(r1.pos, r2.pos);
// }

int intersection_card(vector<int> &set1, vector<int> &set2){
    static vector<bool> already(skills_mapping.size());
    int items = 0;
    for(int s : set1)
        already[s] = true;

    for(int s : set2)
        if(already[s])
            items++;

    for(int s : set1)
        already[s] = false;
    
    return items;
}

int union_card(vector<int> &set1, vector<int> &set2){
    static vector<bool> already(skills_mapping.size());
    int items = 0;
    for(int s : set1){
        already[s] = true;
        items++;
    }
    for(int s : set2){
        if(!already[s]){
            already[s] = true;
            items++;
        }
    }
    for(int s : set1)
        already[s] = false;

    for(int s : set2)
        already[s] = false;

    return items;
}

int get_wp_score(Dev &r1, Dev &r2){
    int int_card = intersection_card(r1.skills, r2.skills);
    int un_card = union_card(r1.skills, r2.skills);
    return int_card * (un_card - int_card);
}

int get_bonus_score(Dev &r1, Dev &r2){
    return r1.company == r2.company ? (r1.bonus * r2.bonus) : 0;
}

int compute_score(Dev &r1, Dev &r2){
    int score = 0;
    score += get_wp_score(r1, r2);
    // cerr << "wp score: " << score << endl;
    score += get_bonus_score(r1, r2);
    // cerr << "wp score + bonus score: " << score << endl;
    return score;
}

int get_cell_type(ii &cell){
    return room[cell.first][cell.second].first;
}

int get_cell_dev_index(ii cell){
    return room[cell.first][cell.second].second;
}

int compute_wall_score(ii &cell1, ii cell2){
    int score = 0;
    // if(are_adjacent(cell1, cell2)){
    int cell1_type = get_cell_type(cell1);
    int cell2_type = get_cell_type(cell2);
    if(cell1_type == WALL || cell2_type == WALL)
        return 0;
    int dev1_index = get_cell_dev_index(cell1);
    int dev2_index = get_cell_dev_index(cell2);
    if(dev1_index == NOT_ASSIGNED || dev2_index == NOT_ASSIGNED)
        return 0;

    Dev &d1 = cell1_type == DEV ? devs[dev1_index] : pms[dev1_index];
    Dev &d2 = cell2_type == DEV ? devs[dev2_index] : pms[dev2_index];
    
    score += compute_score(d1, d2);
    // }
    return score;
}

bool alone(ii cell){
    int north = get_cell_dev_index({cell.first, cell.second - 1});
    int south = get_cell_dev_index({cell.first, cell.second + 1});
    int east = get_cell_dev_index({cell.first + 1, cell.second});
    int west = get_cell_dev_index({cell.first - 1, cell.second});
    return north == NOT_ASSIGNED && south == NOT_ASSIGNED && east == NOT_ASSIGNED && west == NOT_ASSIGNED;
}

int compute_4_walls_score(ii cell){
    // cerr << "computing score for cell (" << cell.first << ", " << cell.second << ")" << endl;
    int north_score = compute_wall_score(cell, {cell.first, cell.second - 1});
    int south_score = compute_wall_score(cell, {cell.first, cell.second + 1});
    int east_score = compute_wall_score(cell, {cell.first + 1, cell.second});
    int west_score = compute_wall_score(cell, {cell.first - 1, cell.second});
    return north_score + south_score + east_score + west_score;
}


int compute_cell_score(ii cell){
    int east_score = compute_wall_score(cell, {cell.first + 1, cell.second});
    int south_score = compute_wall_score(cell, {cell.first, cell.second + 1});
    return east_score + south_score;
}

int compute_total_score(){
    int total_score = 0;
    for(int i=0; i<room.size(); i++){
        for(int j=0; j<room[i].size(); j++){
            if(i == 0 || i == H+1 || j == 0 || j == W+1)
                continue;
            int cell_score = compute_cell_score({i, j});
            // cerr << "score for cell (" << i << ", " << j << "): " << cell_score << endl;
            total_score += cell_score;
        }
    }
    return total_score;
}

int choose_dev(ii cell){
    // cerr << "CHOOSING DEV FOR CELL (" << cell.first << ", " << cell.second << ")" << endl;
    int chosen_dev = NOT_ASSIGNED;
    if(alone(cell)){
        bool someone_left = false;
        for(int i=0; i<devs.size() && !someone_left; i++)
            if(!used_devs[i])
                someone_left = true;
        if(someone_left){
            while(true){
                chosen_dev = rand() % devs.size();
                if(!used_devs[chosen_dev])
                    return chosen_dev;
            }
        }
    }else{
        int score_improvement = 0;
        for(int i=0; i<devs.size() && i<100000; i++){
            // cerr << "considering " << devs[i].toString() << ", used: " << used_devs[i] << endl;
            if(!used_devs[i]){
                room[cell.first][cell.second].second = i;
                int tmp_score = compute_4_walls_score(cell);
                if(tmp_score > score_improvement){
                    score_improvement = tmp_score;
                    chosen_dev = i;
                }
                // cerr << "score improvement: " << score_improvement << endl; 
            }
        }
    }
    // cerr << "chosen dev: " << chosen_dev << endl; 
    if(chosen_dev == NOT_ASSIGNED){
        //get a random one
        for(int i=0; i<devs.size(); i++)
            if(!used_devs[i]){
                chosen_dev = i;
                break;
            }
    }
    // cerr << "chosen dev: " << devs[chosen_dev].toString() << endl;
    return chosen_dev;
}

int choose_pm(ii cell){
    // cerr << "CHOOSING PM FOR CELL (" << cell.first << ", " << cell.second << ")" << endl;
    int chosen_pm = NOT_ASSIGNED;
    if(alone(cell)){
        bool someone_left = false;
        for(int i=0; i<pms.size() && !someone_left; i++)
            if(!used_pms[i])
                someone_left = true;
        if(someone_left){
            while(true){
                chosen_pm = rand() % pms.size();
                if(!used_pms[chosen_pm])
                    return chosen_pm;
            }
        }
    }else{
        // cerr << "not alone" << endl;
        int score_improvement = 0;
        for(int i=0; i<pms.size() && i<20000; i++){
            // cerr << "considering " << pms[i].toString() << ", used: " << used_pms[i] << endl;
            if(!used_pms[i]){
                room[cell.first][cell.second].second = i;
                int tmp_score = compute_4_walls_score(cell);
                if(tmp_score > score_improvement){
                    score_improvement = tmp_score;
                    chosen_pm = i;
                }
                // cerr << "score improvement: " << score_improvement << endl; 
            }
        }
    }
    // cerr << "chosen dev: " << chosen_pm << endl; 
    if(chosen_pm == NOT_ASSIGNED){
        for(int i=0; i<pms.size(); i++)
            if(!used_pms[i]){
                chosen_pm = i;
                break;
            }
    }
    // cerr << "chosen dev: " << pms[chosen_pm].toString() << endl;
    return chosen_pm;
}

int swap_existing_devs(int dev1_index, int dev2_index, int threshold){
    Dev &d1 = devs[dev1_index];
    Dev &d2 = devs[dev2_index];
    ii d1pos = {d1.pos.first, d1.pos.second};
    ii d2pos = {d2.pos.first, d2.pos.second};
    int old_score = compute_4_walls_score(d1pos) + compute_4_walls_score(d2pos);
    d1.pos = d2pos;
    d2.pos = d1pos;
    room[d1pos.first][d1pos.second].second = dev2_index;
    room[d2pos.first][d2pos.second].second = dev1_index;
    int new_score = compute_4_walls_score(d1pos) + compute_4_walls_score(d2pos);
    if(new_score > old_score + threshold){
        // cerr << "good swap between two existing devs! old score: " << old_score << ", new: score: " << new_score << " -> (+" << new_score - old_score << ")" << endl;
        return new_score - old_score;
    }else{
        d1.pos = d1pos;
        d2.pos = d2pos;
        room[d1pos.first][d1pos.second].second = dev1_index;
        room[d2pos.first][d2pos.second].second = dev2_index;
        return 0;
    }

}

int swap_unused_dev(int dev_index, int unused_dev, int threshold){
    Dev &d1 = devs[dev_index];
    Dev &d2 = devs[unused_dev];
    // cerr << d1.toString() << " <======> " << d2.toString() << endl;
    ii d1pos = {d1.pos.first, d1.pos.second};
    int old_score = compute_4_walls_score(d1pos);
    // cerr << "old score: " << old_score << endl;
    d1.pos = NA_PAIR;
    d2.pos = d1pos;
    room[d1pos.first][d1pos.second].second = unused_dev;
    int new_score = compute_4_walls_score(d1pos);
    // cerr << "new score: " << new_score << endl;

    if(new_score > old_score + threshold){
        // cerr << "good swap with an unused dev! old score: " << old_score << ", new: score: " << new_score << " -> (+" << new_score - old_score << ")" << endl;
        d1.pos = NA_PAIR;
        d2.pos = d1pos;
        used_devs[dev_index] = false;
        used_devs[unused_dev] = true;
        return new_score - old_score;
    }else{
        d1.pos = d1pos;
        d2.pos = NA_PAIR;
        room[d1pos.first][d1pos.second].second = dev_index;
        return 0;
    }
}

int swap_devs(int thresh){
    int dev1_index = rand() % devs.size();
    int dev2_index = rand() % devs.size();
    // cerr << dev1_index << ": " << used_devs[dev1_index] << ", " << dev2_index << ": " << used_devs[dev2_index] << endl;
    if(dev1_index == dev2_index)
        return 0;
    if(!used_devs[dev1_index] && !used_devs[dev2_index])
        return 0;
    if(used_devs[dev1_index] && used_devs[dev2_index]){
        return swap_existing_devs(dev1_index, dev2_index, thresh);
    }else if(used_devs[dev1_index]){
        return swap_unused_dev(dev1_index, dev2_index, thresh);
    }else if(used_devs[dev2_index]){
        return swap_unused_dev(dev2_index, dev1_index, thresh);
    }
}

int swap_existing_pms(int dev1_index, int dev2_index, int threshold){
    Dev &d1 = pms[dev1_index];
    Dev &d2 = pms[dev2_index];
    ii d1pos = {d1.pos.first, d1.pos.second};
    ii d2pos = {d2.pos.first, d2.pos.second};
    int old_score = compute_4_walls_score(d1pos) + compute_4_walls_score(d2pos);
    d1.pos = d2pos;
    d2.pos = d1pos;
    room[d1pos.first][d1pos.second].second = dev2_index;
    room[d2pos.first][d2pos.second].second = dev1_index;
    int new_score = compute_4_walls_score(d1pos) + compute_4_walls_score(d2pos);
    if(new_score > old_score + threshold){
        return new_score - old_score;
        // cerr << "good swap between two existing pms! old score: " << old_score << ", new: score: " << new_score << " -> (+" << new_score - old_score << ")" << endl;
    }else{
        d1.pos = d1pos;
        d2.pos = d2pos;
        room[d1pos.first][d1pos.second].second = dev1_index;
        room[d2pos.first][d2pos.second].second = dev2_index;
        return 0;
    }
}

int swap_unused_pm(int dev_index, int unused_dev, int threshold){
    Dev &d1 = pms[dev_index];
    Dev &d2 = pms[unused_dev];
    // cerr << d1.toString() << " <======> " << d2.toString() << endl;
    ii d1pos = {d1.pos.first, d1.pos.second};
    int old_score = compute_4_walls_score(d1pos);
    // cerr << "old score: " << old_score << endl;
    d1.pos = NA_PAIR;
    d2.pos = d1pos;
    room[d1pos.first][d1pos.second].second = unused_dev;
    int new_score = compute_4_walls_score(d1pos);
    // cerr << "new score: " << new_score << endl;

    if(new_score > old_score + threshold){
        // cerr << "good swap with an unused dev! old score: " << old_score << ", new: score: " << new_score << " -> (+" << new_score - old_score << ")" << endl;
        d1.pos = NA_PAIR;
        d2.pos = d1pos;
        used_pms[dev_index] = false;
        used_pms[unused_dev] = true;
        return new_score - old_score;
    }else{
        d1.pos = d1pos;
        d2.pos = NA_PAIR;
        room[d1pos.first][d1pos.second].second = dev_index;
        return 0;
    }
}

int swap_pms(int thresh){
    int dev1_index = rand() % pms.size();
    int dev2_index = rand() % pms.size();
    if(dev1_index == dev2_index)
        return 0;
    if(!used_pms[dev1_index] && !used_pms[dev2_index])
        return 0;
    if(used_pms[dev1_index] && used_pms[dev2_index]){
        return swap_existing_pms(dev1_index, dev2_index, thresh);
    }else if(used_pms[dev1_index]){
        return swap_unused_pm(dev1_index, dev2_index, thresh);
    }else if(used_pms[dev2_index]){
        return swap_unused_pm(dev2_index, dev1_index, thresh);
    }
}

void compute_sol(){
    for(int i=0; i<room.size(); i++){
        for(int j=0; j<room[i].size(); j++){
            if(rand() % 300 == 0) cerr << (double) (100 * ((i*H) + j)) / (H*W) << "%   ";
            if(room[i][j].first != WALL){
                if(room[i][j].second == NOT_ASSIGNED){
                    if(room[i][j].first == DEV) {
                        int chosen_dev = choose_dev({i, j});
                        if(chosen_dev != NOT_ASSIGNED){
                            room[i][j].second = chosen_dev;
                            used_devs[chosen_dev] = true;
                            devs[chosen_dev].pos = {i, j};
                        }else{
                            room[i][j].second = NOT_ASSIGNED;
                        }
                    } else if (room[i][j].first == PM) {
                        int chosen_pm = choose_pm({i, j});
                        if(chosen_pm != NOT_ASSIGNED){
                            room[i][j].second = chosen_pm;
                            used_pms[chosen_pm] = true;
                            pms[chosen_pm].pos = {i, j};
                        }else{
                            room[i][j].second = NOT_ASSIGNED;
                        }
                    }
                }
            }
        }
    }
    
    // cerr << "devs.size() " << devs.size() << endl;
    // cerr << "pms.size() " << pms.size() << endl;
    int dev_swapping_improvement = 0;
    int pm_swapping_improvement = 0;
    int name_number = 0;
    for(int j=1; j<=CYCLES; j++){
        for(long long int i=0; i < (SWAPS * (CYCLES + j)); i++){
            if(i%5 != 0){
                dev_swapping_improvement += swap_devs(0);
            }else{
                pm_swapping_improvement += swap_pms(0);
            }
            if(i % 10'000'000 == 0) cerr << "swapped " << i / 1'000'000 << " M times, improvement: " << dev_swapping_improvement + pm_swapping_improvement << endl;
            if(i % SWAPS == 0){
                int current_score = compute_total_score();
                string file = "out/" + folder_name + "/" + to_string(current_score) + ".out";
                cerr << "CURRENT SCORE: " << current_score << ", NEW FILE: " << file << endl;
                freopen(file.c_str(), "w", stdout);
                for(int i=0; i<NDEV; i++){
                    if(devs[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", devs[i].pos.second-1, devs[i].pos.first-1);
                    }
                }
                for(int i=0; i<NPM; i++){
                    if(pms[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", pms[i].pos.second-1, pms[i].pos.first-1);
                    }
                }
            }
        }
        int score_before_final_swapping = compute_total_score();
        cerr << "DONE SWAPPING, NOW WE TRY TO ESCAPE THE LOCAL MAX, TOTAL SCORE UNTIL NOW: " << score_before_final_swapping << endl;

        int MAX = 1, MIN = -1;
        for(long long int i=1; i < (SWAPS * (CYCLES / j)); i++){
            int thresh = rand() % (MAX-MIN) + MIN;
            if(i%5 != 0){
                dev_swapping_improvement += swap_devs(thresh);
            }else{
                pm_swapping_improvement += swap_pms(thresh);
            }
            if(i % 10'000'000 == 0) cerr << "swapped " << i / 1'000'000 << " M times, improvement: " << dev_swapping_improvement + pm_swapping_improvement << endl;
            if(i % SWAPS == 0){
                if(i % SWAPS / j == 0 && MAX < 6){
                    MAX++;
                    MIN--;
                    cerr << "INCREASED MAX TO " << MAX << " AND MIN TO " << MIN << endl;
                }
                int current_score = compute_total_score();
                string file = "out/" + folder_name + "/" + to_string(current_score) + ".out";
                cerr << "CURRENT SCORE: " << current_score << ", NEW FILE: " << file << endl;
                freopen(file.c_str(), "w", stdout);
                for(int i=0; i<NDEV; i++){
                    if(devs[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", devs[i].pos.second-1, devs[i].pos.first-1);
                    }
                }
                for(int i=0; i<NPM; i++){
                    if(pms[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", pms[i].pos.second-1, pms[i].pos.first-1);
                    }
                }
            }
        }
        cerr << " ============ DONE CYCLE " << j << " ============ " << endl;
    }
    cerr << "dev swapping improvement: " << dev_swapping_improvement << endl;
    cerr << "pm swapping improvement: " << pm_swapping_improvement << endl;
}

double compute_distance(ii c1, ii c2){
    double x = c1.first - c2.first;
    double y = c1.second - c2.second;
    double dist;
    dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);
    return dist;
}

double get_total_distance(vector<ii> &component, ii cell){
    double distance = 0;
    for(ii target : component){
        if(target != cell){
            distance += compute_distance(cell, target);
        }
    }
    return distance;
}


ii find_central_cell(vector<ii> &component){
    ii result = NA_PAIR;
    double minimum_distance = DBL_MAX;
    for(ii &cell : component){
        double average_distance = get_total_distance(component, cell) / component.size();
        if(average_distance < minimum_distance){
            minimum_distance = average_distance;
            result = cell;
        }
    }
    return result;
}

void bfs(ii source, vector<vector<bool>> &visited){
    queue<ii> q;
    q.push(source);
    visited[source.first][source.second] = true;
    while(!q.empty()){
        ii current = q.front(); q.pop();
        int i = current.first, j = current.second;
        if(room[i][j].first == DEV) {
            int chosen_dev = choose_dev({i, j});
            if(chosen_dev != NOT_ASSIGNED){
                room[i][j].second = chosen_dev;
                used_devs[chosen_dev] = true;
                devs[chosen_dev].pos = {i, j};
            }else{
                room[i][j].second = NOT_ASSIGNED;
            }
        } else if (room[i][j].first == PM) {
            int chosen_pm = choose_pm({i, j});
            if(chosen_pm != NOT_ASSIGNED){
                room[i][j].second = chosen_pm;
                used_pms[chosen_pm] = true;
                pms[chosen_pm].pos = {i, j};
            }else{
                room[i][j].second = NOT_ASSIGNED;
            }
        }
        for(ii neighbour : neighbours(current)){
            if(room[neighbour.first][neighbour.second].first != WALL && !visited[neighbour.first][neighbour.second]){
                visited[neighbour.first][neighbour.second] = true;
                q.push(neighbour);
            }
        }
    }
}

void start_bfs(ii cell){
    vector<vector<bool>> visited(room.size());
    for(int i=0; i<room.size(); i++){
        visited[i].resize(room[i].size());
        for(int j=0; j<room[i].size(); j++){
            visited[i][j] = false;
        }
    }
    bfs(cell, visited);
}

void compute_graph_sol(){
    find_components();
    sort(components.begin(), components.end(), []
        (vector<ii> comp1, vector<ii> comp2){
            return comp1.size() > comp2.size();
        }
    );
    for(vector<ii> &component : components){
        // cerr << "comp size: " << component.size() << endl;
        if(component.size() > 1){
            ii cell = find_central_cell(component);
            // cerr << "central cell : " << "(" << cell.first << ", " << cell.second << ")" << endl;
            start_bfs(cell);
        }
    }

    // cerr << "devs.size() " << devs.size() << endl;
    // cerr << "pms.size() " << pms.size() << endl;
    int dev_swapping_improvement = 0;
    int pm_swapping_improvement = 0;
    int name_number = 0;
    for(int j=1; j<CYCLES; j++){
        for(long long int i=0; i < (SWAPS * (CYCLES + j)); i++){
            if(i%5 != 0){
                dev_swapping_improvement += swap_devs(0);
            }else{
                pm_swapping_improvement += swap_pms(0);
            }
            if(i % 10'000'000 == 0) cerr << "swapped " << i / 1'000'000 << " M times, improvement: " << dev_swapping_improvement + pm_swapping_improvement << endl;
            if(i % SWAPS == 0){
                int current_score = compute_total_score();
                string file = "out/" + folder_name + "/" + to_string(current_score) + ".out";
                cerr << "CURRENT SCORE: " << current_score << ", NEW FILE: " << file << endl;
                freopen(file.c_str(), "w", stdout);
                for(int i=0; i<NDEV; i++){
                    if(devs[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", devs[i].pos.second-1, devs[i].pos.first-1);
                    }
                }
                for(int i=0; i<NPM; i++){
                    if(pms[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", pms[i].pos.second-1, pms[i].pos.first-1);
                    }
                }
            }
        }
        int score_before_final_swapping = compute_total_score();
        cerr << "DONE SWAPPING, NOW WE TRY TO ESCAPE THE LOCAL MAX, TOTAL SCORE UNTIL NOW: " << score_before_final_swapping << endl;

        int MAX = j, MIN = -j;
        for(long long int i=1; i < (SWAPS * (CYCLES - j)); i++){
            int thresh = rand() % (MAX-MIN) + MIN;
            if(i%5 != 0){
                dev_swapping_improvement += swap_devs(thresh);
            }else{
                pm_swapping_improvement += swap_pms(thresh);
            }
            if(i % 10'000'000 == 0) cerr << "swapped " << i / 1'000'000 << " M times, improvement: " << dev_swapping_improvement + pm_swapping_improvement << endl;
            if(i % SWAPS == 0){
                if(i % SWAPS / j == 0 && MAX < 6){
                    MAX++;
                    MIN--;
                    cerr << "INCREASED MAX TO " << MAX << " AND MIN TO " << MIN << endl;
                }
                int current_score = compute_total_score();
                string file = "out/" + folder_name + "/" + to_string(current_score) + ".out";
                cerr << "CURRENT SCORE: " << current_score << ", NEW FILE: " << file << endl;
                freopen(file.c_str(), "w", stdout);
                for(int i=0; i<NDEV; i++){
                    if(devs[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", devs[i].pos.second-1, devs[i].pos.first-1);
                    }
                }
                for(int i=0; i<NPM; i++){
                    if(pms[i].pos == NA_PAIR){
                        printf("X\n");
                    }else{
                        printf("%d %d\n", pms[i].pos.second-1, pms[i].pos.first-1);
                    }
                }
            }
        }
        cerr << " ============ DONE CYCLE " << j << " ============ " << endl;
    }
    cerr << "dev swapping improvement: " << dev_swapping_improvement << endl;
    cerr << "pm swapping improvement: " << pm_swapping_improvement << endl;
}

int main() {
    read_room();
    read_devs();
    read_pms();
    // cerr << "ROOM" << endl;
    // print_room();
    // cerr << "DEVS" << endl;
    // print_devs();
    // cerr << "PMS" << endl;
    // print_pms();


    // compute_sol();
    compute_graph_sol();
    // print_sol();


    int total_score = compute_total_score();
    cerr << "\nTOTAL SCORE: " << total_score << endl;
}