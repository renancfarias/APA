#include<vector>
#include<fstream>



using namespace std;

// Mescla dois subarrays of arr[].
// O primeiro subarray eh arr[l..m]
// O segundo subarray eh arr[m+1..r]

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* cria arrays auxiliares */
    int L[n1], R[n2];

    /* Copia os dados para os arrays L[] e R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Mescla os dois arrays de volta para arr[l..r]*/
    i = 0; // índice inicial do primeiro subarray
    j = 0; // indice inicial dp segundo subarray
    k = l; // indice inicial do subarray mescaldo
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copia os elementos restantes de L[], se houver */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* copia os elementos de R[], se houver*/
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l: indice da esquerda
   r: indice da direita
   arr: array a ser ordenado */

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;

        // ordena as duas metades
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int main()
{

    std::vector<int> numbers;

	ifstream in("data_in.txt",ios::in);

	int number;

        while (in >> number) {

		numbers.push_back(number);
	}

	in.close();

   int arr_size = numbers.size();
   int arr[arr_size];

   int j = 0;
   for (auto i = numbers.begin(); i != numbers.end(); ++i){
    arr[j] = *i;
    j++;
   }

   mergeSort(arr, 0, arr_size - 1);

   ofstream out("data_out.txt",ios::out | ios::trunc);

   for (int i = 0; i<arr_size; i++)
    out << arr[i] << endl;

   out.close();

   puts("Programa executado com sucesso. Pressione <enter> para sair.");
   getchar();

   return 0;
}
