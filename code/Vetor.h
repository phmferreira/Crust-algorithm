
#ifndef _PONTO_H_
#define _PONTO_H_
#include "Ponto.h"

class Vetor {
	public:
		Ponto Origem;
		Ponto Destino;

		double produtoEscalar(Vetor outro);
		double produtoEscalar(Vetor *outro);
		Vetor(Ponto* p1, Ponto* p2);
		
};

#endif // #ifndef _PONTO_H_
