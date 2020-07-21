#include <iostream>
#include <cmath>
#include <cstdlib>
#include <functional>   // std::ref
#include <vector>
#include <thread>
#include <math.h>

void Compute_Pi(double& acum, unsigned a, unsigned b, size_t& flag, size_t id){
	
	/*Busy waiting*/
	while(flag != id);
	   //std::cout << "flag: " << flag <<"id: " << id << "\n";
	
	for (unsigned i = a; i < b; i++) {
		//std::cout << i << " "; //Valor de la iteracion
		acum = acum + 4*(pow(-1.00, i) / (1 + 2 * i));
		//std::cout << "Pi vale: " << acum << "\n"; //suma unitaria 
	}
	flag++;
}	


int main(int argc, char const *argv[]) {
	double acum = 0;
	size_t flag = 0;
	float pi = M_PI;                   // constante de pi
		/*variable de iteracion*/
	unsigned n = std::atoi(argv[1]);
	unsigned p = std::thread::hardware_concurrency();
	std::vector<std::thread> task(p);
   	std::vector<unsigned> chunk_size (p);
   	unsigned base = n / p;
	unsigned k = n % p;

	for(size_t i = 0; i < p; i++){
      	chunk_size[i] = base;
   	}
	//Distribución de carga, sí es necesaría
	if (k != 0) {
	   	unsigned i = 0;
	   	while(k > 0) {
	      	chunk_size[i] = chunk_size[i] + 1;
	      	k--;
	      	i = (i+1) % p;
      	}
	}

	for (size_t i = 0; i <= p; i++) {
	   	unsigned a = i * chunk_size[i];
      	unsigned b = (i+1) * chunk_size[i]; 
		task[i] = std::thread(Compute_Pi, std::ref(acum),a, b, std::ref(flag), i);
	}
	
	for (auto& t : task) {
      // Esperamos a que los hilos terminen la tarea asignada para unirlos. 
    	t.join(); 
   	}
	std::cout.precision(10);
	std::cout << "acum final: " << acum << "\n";
	std::cout << "------------------------------\n";
	std::cout << "Error es: " << M_PI - acum << "\n";
	return 0;
}
