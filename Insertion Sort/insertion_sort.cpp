#include <iostream>
#include <string>


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
    //algoritmo insertion sort
    /************************************************************/
    int aux;


    int i = 0;
    int j = 0;

    for(i=0;i<n;i++){
       j = i-1;
       while (j>=0 && a[j] > a[j+1]){
            aux = a[j];
            a[j] = a[j+1];
            a[j+1] = aux;
            j--;
       }
    }
    /***********************************************************/

    cout<< endl<< "Sequencia ordenada: ";

    for(i=0;i<n;i++){
        if(i == n-1)
            cout << a[i];
        else
            cout << a[i]<< ", ";

    }
    return 0;
}
