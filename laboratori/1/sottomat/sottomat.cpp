#include <fstream>
#include <vector>
using namespace std;

int R, C;
int sottoseq(vector<int> arr);
int sottomat(vector<vector<int>> mat, int i, int j);

int main(int argc, char const *argv[])
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> R >> C;
    vector<vector<int>> mat;
    mat.resize(R, vector<int>(C, 0));
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            in >> mat[i][j];
        }
    }

    out << sottomat(mat, R, C) << endl;
}

int sottoseq(vector<int> arr)
{
    int somma = 0, massimo = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        somma = max(somma + arr[i], 0);
        massimo = max(somma, massimo);
    }
    return massimo;
}

int sottomat(vector<vector<int>> mat, int i, int j)
{
    int result = 0;
    vector<int> curr(C, 0);
    for (int i = 0; i < R; i++)
    {
        curr.assign(curr.size(), 0);
        for (int j = i; j < R; j++)
        {
            for (int k = 0; k < C; k++)
                curr[k] += mat[j][k];
            result = max(sottoseq(curr), result);
        }
    }
    return result;
}