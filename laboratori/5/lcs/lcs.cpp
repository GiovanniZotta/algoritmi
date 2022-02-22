#include <vector>
#include <fstream>
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int main(int argc, char const *argv[])
{
    int n, m;
    in >> n >> m;
    string s1, s2;
    in >> s1 >> s2;
    out << lcs(s1, s2);
    return 0;
}
