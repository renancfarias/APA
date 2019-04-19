#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;


void stoints (string& s, int &n, int &m)
{
    string buffer;
    for(int i = 0; i < s.size(); i++)
    {
            if (s[i] == ' ')
            {
                n = stoi(buffer);
                buffer.clear();
            }else {
                buffer += s[i];
            }
    }

    m = stoi(buffer);
}


void le_arquivo (string nome, int *n, int *m, vector<int> &peso, vector<int> &valor)
{

    ifstream myfile (nome);
    string linha;

    if (myfile.is_open())
      {
        getline (myfile,linha);
        stoints(linha, *n, *m);
        peso.resize(*n);
        valor.resize(*n);



        for(int i = 0; i<*n; i++)
        {
            getline(myfile, linha);
            stoints(linha, peso[i], valor[i]);

        }

        myfile.close();
      }
}

int knapsack (int n,int m, vector<int> &valor, vector<int> &peso, vector<int> &sol)
{
    int k[n+1][m+1] = {0};
    for (int i = 0; i<=n; i++){
        for (int j = 0; j<=m; j++)
            {
            if(i==0 || j == 0)
                k[i][j] = 0;
            else if(peso[i-1] <= j)
                k[i][j] = max(valor[i-1] + k[i-1][j - peso[i-1]], k[i-1][j]);
            else
                k[i][j] = k[i-1][j];

            }
    }

    int nn= n;
    int mm = m;
    vector<int> vsol;

    while (k[nn][mm] != 0){
        if(k[nn][mm] == k[nn-1][mm])
            nn--;
        else{
           nn--;
           vsol.push_back(nn);
           mm = mm - peso[nn];
        }
    }

    sol = vsol;

    return k[n][m];
}

int main (int argc, char *argv[])
{
    ofstream out ("solucoes.txt");
    static int n;
    static int m;
    vector<int> peso;
    vector<int> valor;
    vector<int> vsol;
    static int sol;

    le_arquivo(argv[1], &n, &m, peso, valor);
    sol = knapsack(n, m, valor, peso, vsol);

    cout << "\ninstancia: " << argv[1] << endl;
    cout << "valor: " << sol << endl;
    cout << "produtos escolhidos: ";

    for(int i = 0; i<vsol.size(); i++)
            cout << vsol[i] + 1 << ' ';

    return 0;

}


