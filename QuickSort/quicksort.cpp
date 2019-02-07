#include<vector>
#include<fstream>



using namespace std;


void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int a[], int inicio, int fim)
{
    int pivo = a[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++)
    {

        if (a[j] <= pivo)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[fim]);
    return (i + 1);
}


 /* a[]: Array a ser ordenado,
    inicio : Indice inicial,
    fim : Indice final */
void quickSort(int a[], int inicio, int fim)
{
    if (inicio < fim)
    {
        // pi = indice da particao
        int pi = partition(a, inicio, fim);

        // ordena os elementos ,separadamente,
        // antes e depois da particao
        quickSort(a, inicio, pi - 1);
        quickSort(a, pi + 1, fim);
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

   quickSort(arr, 0, arr_size - 1);

   ofstream out("data_out.txt",ios::out | ios::trunc);

   for (int i = 0; i<arr_size; i++)
    out << arr[i] << endl;

   out.close();

   puts("Programa executado com sucesso. Pressione <enter> para sair.");
   getchar();

   return 0;
}
