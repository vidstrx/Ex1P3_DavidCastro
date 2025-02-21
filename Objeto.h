#pragma once
#include <iostream>
using namespace std;
class Objeto {
	string nombre;
	int durabilidad;
	bool comestible;
	int cantidad;
public:
	Objeto(string nombre, int durabilidad, bool comestible, int cantidad);
	Objeto();
	string getNombre();
	void setNombre(string nombre);
	int getDurabilidad();
	void setDurabilidad(int durabilidad);
	bool getComestible();
	void setComestible(bool comestible);
	int getCantidad();
	void setCantidad(int cantidad);
	void toString();
};

