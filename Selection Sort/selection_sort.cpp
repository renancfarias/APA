#include<iostream>

using namespace std;

int main (){

    int n;

    cout << "Digite o numero de elementos da sequencia: ";
    cin >> n;
    cout << endl << "Digite os numeros da sequencia: "<< endl;

    string s[n];
    int a[n];

    for(int i = 0; i<n; i++){
        cin >> s[i];
    }

    for(int i = 0; i<n ;i++){
        a[i] = stoi (s[i],nullptr,10);
    }

    /*************************************************************/
    //algoritmo selection sort
    /************************************************************/
    int i;
    int j;
    int i_min;

    for(i = 0; i<n; i++){
        i_min = i;
        for(j = i + 1; j<n;j++){
            if (a[j]<a[i_min])
                i_min = j;
        }
        if (i_min != i){
            int aux;
            aux = a[i];
            a[i] = a[i_min];
            a[i_min] = aux;
        }

    }

    /************************************************************/

       cout<< endl<< "Sequencia ordenada: ";

    for(i=0;i<n;i++){
        if(i == n-1)
            cout << a[i];
        else
            cout << a[i]<< ", ";

    }

    return 0;
}
