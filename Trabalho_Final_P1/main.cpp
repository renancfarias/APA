#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

void le_arquivo (const string &nome, string &nomeinst, int &n, int **&ma)
{
    ifstream myfile (nome);
    string linha;
    string word;
    size_t found; // determina se encoutrou  substring
    int**matrix;

    int i = 0;
    int j = 0;

    while(myfile)
    {
        getline(myfile,linha);
        istringstream stream(linha);

        stream >> word;

        if(!word.compare("NAME:"))
        {
            stream >> nomeinst;
        }
        else if(!word.compare("DIMENSION:"))
        {
            stream >> n;
        }
        else if(!word.compare("EDGE_WEIGHT_SECTION"))
        {
            break;
        }
    }

    matrix = (int**)malloc(n*sizeof(int*));
    for(int i = 0; i<n; i++)
        matrix[i] = (int*)malloc(n*sizeof(int));

        while(myfile){
            getline(myfile,linha);
            istringstream snum(linha);
            for(int j=0; j<n; j++)
            {
                snum >> matrix[i][j];
            }
            i++;
            if(i>=n)
                break;
        }

      ma = matrix;
      myfile.close();
}


int nearest_neighbor(int *&solucao, int **&matriz, int n)
{
     solucao = (int*)malloc((n+1)*sizeof(int));
     int *visitados = (int*)malloc((n)*sizeof(int));

     int s_index = 0;
     int menor_dist = INT_MAX;
     int kmenor_dist;
     int cidade_inicial = 0;
     int total_dist;
     int cidade_atual;
     int prox_cidade;

     cidade_atual = cidade_inicial;

     while(s_index < n)
     {
         menor_dist = INT_MAX;
         for(int i = 0; i<n; i++)
         {

             if((matriz[cidade_atual][i] != 0)&&(visitados[i]==0))
                if(matriz[cidade_atual][i]<menor_dist)
                {
                 menor_dist = matriz[cidade_atual][i];
                 prox_cidade = i;
                }

         }
         if(menor_dist!=INT_MAX)
            total_dist += menor_dist;
         visitados[cidade_atual] = 1;
         solucao[s_index] = cidade_atual;
         s_index++;
         cidade_atual = prox_cidade;
     }
         total_dist+= matriz[cidade_atual][cidade_inicial];
         solucao[s_index] = cidade_inicial;

         return total_dist;

}



int main (int argc, char *argv[])
{

    static int n;
    static string nomeinst;
    static int **m;
    static int *sol;

    le_arquivo(argv[1], nomeinst, n, m);

    static int dist = nearest_neighbor(sol, m, n);

    cout << "\ninstancia: " <<  nomeinst << endl;
    cout << "\nn: " <<  n << endl;
    cout << "distancia total: " << dist << endl;

    for(int j = 0; j<=n; j++)
                cout << sol[j] << ' ';

    return 0;

}


