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
     int cidade_inicial = 0;
     int total_dist = 0;
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

int calcula_dist (int **matriz, int *sol, int n)
{
    int dist = 0;
    for(int i = 0; i<n; i++)
    {
        dist+=matriz[sol[i]][sol[i+1]];
    }

    return dist;
}

int* swap_arr (int **matriz, int* sol, int n)
{
    cout<< "executando sawp"<< endl;
    static int *new_sol =  (int*) malloc(n*sizeof(int));
    static int *retorno = (int*) malloc(n*sizeof(int));
    static int indice_base = 0;
    static int indice_troca = 1;
    static int custo = calcula_dist(matriz, sol, n);

    static int k = 0;
    static int custo_novo = 0;
    int temp;
    copy(sol, sol+n+1, retorno);
    copy(sol, sol+n+1, new_sol);

    for(indice_base=0; indice_base<n-2; indice_base++)
    {

        for(indice_troca=indice_base+1; indice_troca<n-1; indice_troca++)
        {
            temp = new_sol[indice_base];
            new_sol[indice_base] = new_sol[indice_troca];
            new_sol[indice_troca] = temp;

           // for(int j = 0; j<=n; j++)
           //     cout << new_sol[j] << ' ';

            custo_novo = calcula_dist(matriz, new_sol, n);
           // cout<<endl<<"CUSTO NOVO:" << custo_novo<<endl;

            if(custo_novo<custo)
            {
                custo = custo_novo;
                copy(new_sol, new_sol+n+1, retorno);
            }
        copy(sol, sol+n+1, new_sol);
        custo_novo = 0;
        }

    }
    /*cout<<"Solucao do sawp:" <<endl;
    for(int j = 0; j<=n; j++)
                cout << retorno[j] << ' ';
    cout <<endl;
    */

    return retorno;
}

int* doisOpt (int **matriz, int* sol, int n)
{
    cout<< "executando 2opt"<< endl;
    static int *new_sol =  (int*) malloc(n*sizeof(int));
    //static int *retorno = sol;

    //copy(sol, sol+n+1, new_sol);

    int custo=0;
    int novo_custo=0;

    static int temp;

    custo = calcula_dist(matriz, sol, n);

    static int i, j, k, m;

    for(i=1; i<n-3; i++)
    {

        for(j=i+2; j<n-1; j++)
        {
            int aresta_desc1 = matriz[sol[i-1]][sol[i]];
            int aresta_desc2 = matriz[sol[j]][sol[j+1]];
            int aresta_con1 = matriz[sol[i-1]][sol[j]];
            int aresta_con2 = matriz[sol[i]][sol[j+1]];

            novo_custo = 0;
            novo_custo = custo - (aresta_desc1 + aresta_desc2)
                        + (aresta_con1 + aresta_con2);

            k=i;
            m=j;


            if(novo_custo < custo)
            {
            //  cout<<endl<<"CUSTO NOVO:" << novo_custo<<endl;

                copy(sol, sol+n+1, new_sol);

                //for(k = i, m = j; m>j; k++, m--)
                while (m>k)
                {
                   // cout<< "(i,j): " << i <<' '<< j << endl;
                  //  cout<< "(k,m): " << k <<' '<< m <<endl;
                  //  cout<<endl;
                temp = new_sol[k];
                new_sol[k] = new_sol[m];
                new_sol[m] = temp;
                //retorno = new_sol;
                k++;
                m--;
                }

            }

        }

    }
    /*cout<<"Solucao do 2-opt:" <<endl;
    for(int j = 0; j<=n; j++)
                cout << new_sol[j] << ' ';
    cout <<endl;
    */
    return new_sol;

}

int * VND(int **matriz, int *sol, int n)
{
    int r = 2; //numero de estruturas de vizinhança
    int k = 0; //estrutura corrente
    int *nova_sol;
    while(k<r)
    {
        switch(k)
        {
        case 0:
            nova_sol = swap_arr(matriz, sol, n);
            break;
        case 1:
            nova_sol = doisOpt(matriz, sol, n);
            break;
        }

        if(calcula_dist(matriz, nova_sol, n)<
           calcula_dist(matriz, sol, n))
        {
            copy(nova_sol, nova_sol+n+1, sol);
            k=0;
        }
        else
            k++;
    }

    return sol;
}

int main (int argc, char *argv[])
{

    static int n;
    static string nomeinst;
    static int **m;
    static int *sol;
    static int *sol_otima;

    le_arquivo(argv[1], nomeinst, n, m);

    cout << "Instancia: " <<  nomeinst << endl;
    cout << "n: " <<  n << endl;

    cout << "resultado do nearest neighbor:"<<endl;
    static int dist = nearest_neighbor(sol, m, n);

    cout << "distancia percorrida: " << dist << endl;

    cout <<"solucao: " <<endl;

    for(int j = 0; j<=n; j++)
                cout << sol[j] << ' ';

    cout <<endl;

    cout << "Executando o VND... " << endl;

    sol_otima = VND(m, sol, n);
    cout<< "depois de executar o VND: "<< endl;

    cout<<"Solucao do VND:" <<endl;
    for(int j = 0; j<=n; j++)
                cout << sol_otima[j] << ' ';

    static int dist_vnd = calcula_dist(m, sol_otima, n);
    cout<< endl << "distancia percorrida: " << dist_vnd;

    ofstream fsaida("solucao_" + nomeinst + ".txt");
    fsaida << "Instancia: " <<  nomeinst << endl;
    fsaida << "Solucao: " << dist_vnd;
    fsaida.close();

    return 0;

}


