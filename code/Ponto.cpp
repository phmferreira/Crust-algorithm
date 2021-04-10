#include <math.h>
#include "Ponto.h"

Ponto::Ponto(double x, double y, double z){
	this->coord_x = x;
	this->coord_y = y;
	this->coord_z = z;
}

Ponto::Ponto(){
	this->coord_x = 0;
	this->coord_y = 0;
	this->coord_z = 0;
}

void Ponto::setCoord_x(double x) {
	this->coord_x = x;
}

void Ponto::setCoord_y(double y) {
	this->coord_y = y;
}

void Ponto::setCoord_z(double z) {
	this->coord_z = z;
}

double Ponto::distancia(Ponto outro){
  double d;
   d = sqrt((coord_x-outro.coord_x)*(coord_x-outro.coord_x) +
            (coord_y-outro.coord_y)*(coord_y-outro.coord_y) +
            (coord_z-outro.coord_z)*(coord_z-outro.coord_z) );
  return d;
}

double Ponto::distancia(Ponto *outro){
  double d;
   d = sqrt((coord_x-outro->coord_x)*(coord_x-outro->coord_x) +
            (coord_y-outro->coord_y)*(coord_y-outro->coord_y) +
            (coord_z-outro->coord_z)*(coord_z-outro->coord_z) );
  return d;
}

double Ponto::produtoEscalar(Ponto* outro){
  double product;
  product = (coord_x * outro->coord_x) + (coord_y * outro->coord_y) + (coord_z * outro->coord_z);
  return product;
}

Ponto* Ponto::subtracao(Ponto* outro){
  Ponto* sub = new Ponto();
  sub->coord_x = coord_x - outro->coord_x;
  sub->coord_y = coord_y - outro->coord_y;
  sub->coord_z = coord_z - outro->coord_z;
  return sub;
}

