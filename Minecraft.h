#pragma once
#include <vector>
#include "Objeto.h"
#include <random>
class Minecraft {
	vector<Objeto> inventario;
	static int jamones;
	char** matriz;
public:
	Minecraft();
	~Minecraft();
	void simulacion();
	void regenerarEntorno();
	void agregarObjeto();
	void eliminarObjeto();
	void listarObjeto();
	void imprimirEntorno();
};

