#include <fstream>
#include <vector>
using namespace std;

int main(){
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	vector<int> a;
    int n;
    in >> n;
    a.resize(n);


    for(int i=0; i<n; i++)
        in >> a[i];


    for(int i=0; i<n; i++)
        out << a[i] << "\n";
	
	in.close();
	out.close();
    
	return 0;
}