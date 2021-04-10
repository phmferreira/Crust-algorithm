
#ifndef _PONTO_H_
#define _PONTO_H_

class Ponto {
	public:
		double coord_x;
		double coord_y;
		double coord_z;

		double distancia(Ponto outro);
		double distancia(Ponto *outro);
		void setCoord_x(double x);
		void setCoord_y(double y);
		void setCoord_z(double z);
		Ponto(double x, double y, double z);
		Ponto();
        double produtoEscalar(Ponto* outro);
        Ponto* subtracao(Ponto* outro);
		
};

#endif // #ifndef _PONTO_H_
