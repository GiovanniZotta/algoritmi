#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

#define NONE -1

struct Building {
    ii pos;
    int id;
    lli lat;
    lli speed;
    int antenna_id;
};

struct Antenna {
    ii pos;
    int id;
    int buildings_attached;
    lli range;
    lli speed;
};

struct pair_hash{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

ii NONE_PAIR = {NONE, NONE};
vector<Building> buildings;
vector<Antenna> antennas;
unordered_map<ii, int, pair_hash> antennas_pos;
unordered_map<ii, bool, pair_hash> covered;
unordered_map<ii, Building, pair_hash> buildings_available;
int W, H, N, M, R;

void read_buildings(){
    int x, y, lat, speed;
    for(int i=0; i<N; i++){
        cin >> x >> y >> lat >> speed;
        Building b;
        b.pos = {x, y};
        b.lat = lat;
        b.speed = speed;
        b.id = i;
        b.antenna_id = NONE;
        buildings.push_back(b);
        buildings_available[{x, y}] = b;
    }
}

void read_antennas(){
    int range, speed;
    for(int i=0; i<M; i++){
        cin >> range >> speed;
        Antenna a;
        a.range = range;
        a.speed = speed;
        a.pos = NONE_PAIR;
        a.id = i;
        a.buildings_attached = 0;
        antennas.push_back(a);
    }
}

int manhattan(int x1, int y1, int x2, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

lli compute_score_b_a(Building &b, Antenna &a){
    int dist = manhattan(b.pos.first, b.pos.second, a.pos.first, a.pos.second);
    return (dist <= a.range) ? (b.speed * a.speed) - (b.lat * dist) : 0;
}

lli compute_building_score(Building &b){
    lli score = 0;
    // Antenna *best_antenna = nullptr;

    // if (b.antenna_id != NONE){
    //     antennas[b.antenna_id].buildings_attached--;
    // }
    for(Antenna &a : antennas){
        lli score_b_a = compute_score_b_a(b, a);
        if (score_b_a > score) {
            score = score_b_a;
            // best_antenna = &a;
        }
        // score = max(score, compute_score_b_a(b, a));
    }
    // if (best_antenna != nullptr){
    //     b.antenna_id = best_antenna->id;
    //     best_antenna->buildings_attached++;
    // } else {
    //     // cerr << "asdasdaadas" << endl;
    // }
    
    return score;
}

lli compute_total_score(){
    lli score = 0;
    for(Building &b : buildings){
        score += compute_building_score(b);
    }
    return score;
}

bool is_valid(ii cell){
    return (cell.first > 0 && cell.first < W && cell.second > 0 && cell.second < H);
}

lli score_new_antenna(Antenna &a, ii cell){
    a.pos = cell;
    lli score = 0;
    int centerx = cell.first;
    int centery = cell.second;
    for(int i = centerx - a.range; i < centerx + a.range; i++){
        for(int j = centery - a.range; j < centery + a.range; j++){
            ii cell = {i, j};
            if(is_valid(cell)){
                if(buildings_available.find(cell) != buildings_available.end() && !covered[cell]){
                    
                }
            }
        }
    }
    return score;
}


void solve(){
    sort(buildings.begin(), buildings.end(), [] (Building &b1, Building &b2) {
        return b1.speed > b2.speed;
    });
    sort(antennas.begin(), antennas.end(), [] (Antenna &a1, Antenna &a2) {
        return double(a1.speed)/(a1.range + (rand() % 3)) > double(a2.speed)/(a2.range + (rand() % 3));
    });
    // sort(antennas.begin(), antennas.end(), [] (Antenna &a1, Antenna &a2) {
    //     // return a1.speed > a2.speed;
    //     if(a1.speed != a2.speed)
    //         return a1.speed > a2.speed;
    //     return a1.range < a2.range;
    // });

    // cerr << "\n =========== BEGIN BUILDINGS ===========" << endl;
    // for(int i=0; i<1000; i++){
    //     cerr << "(" << buildings[i].speed << ", " << buildings[i].lat << ") ";
    // }
    // cerr << " =========== END BUILDINGS ===========" << endl;
    // cerr << " =========== BEGIN ANTENNAS ===========" << endl;
    // for(int i=0; i<1000; i++){
    //     cerr << "(" << antennas[i].speed << ", " << antennas[i].range << ") ";
    // }
    // cerr << "\n =========== END ANTENNAS ===========" << endl;
    // random_shuffle(buildings.begin(), buildings.end());
    // random_shuffle(antennas.begin(), antennas.end());
    // for(int i=0; i<M; i++){
    //     antennas[i].pos = buildings[i].pos;
    // }
    // cerr << "TOTAL SCORE: " << compute_total_score() << endl;
    // int j = 0;
    // for(Antenna &a : antennas){
    //     if (a.buildings_attached < 1){
    //         while(j < buildings.size() && buildings[j].antenna_id != NONE){
    //             j++;
    //         }
    //         if (j < buildings.size()){
    //             // cerr << "!!! MOVING !!!" << endl;
    //             a.pos = buildings[j].pos;
    //         }else
    //             break;
    //     }
    // }



    cout << M << endl;


    for(int i=0; i<M; i++){
        cout << antennas[i].id << " " <<  antennas[i].pos.first << " " <<  antennas[i].pos.second << endl;
    }
    
    cerr << "TOTAL SCORE: " << compute_total_score() << endl;


    
}


int main(int argc, char const *argv[]){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(atoi(argv[1]));
    cin >> W >> H >> N >> M >> R;
    read_buildings();
    read_antennas();
    solve();
    return 0;
}