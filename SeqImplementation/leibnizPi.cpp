#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/*Secuential LebnizPi*/
int main () {
     int n;                             // Variable de iteracion
     float pi = M_PI;                   // constante de pi
     double sum = 0;                    // Suma de las variables
     
     cout.precision(8);			// presicion de 7 digitos
     cout << "Ingrese n iteraciones: " << endl;
     cin >> n;
     
     for (int i = 0; i < n; i++) {
         cout << i << " ";                       // valor de n
         sum = sum + 4*(pow(-1.00,i)/(1 + 2*i));
         cout << sum << endl;                    // suma unitaria de n
         cout << endl;
     }
     cout.precision(8);	
     cout << sum << endl;
     cout << "Valor de pi con " << n << " iteraciones es " << sum << endl;
     cout << "El error es " << M_PI - sum << endl;
}