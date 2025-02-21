#include "Objeto.h"
Objeto::Objeto(string nombre, int durabilidad, bool comestible, int cantidad) {
	this->nombre = nombre;
	this->durabilidad = durabilidad;
	this->comestible = comestible;
	this->cantidad = cantidad;
}
Objeto::Objeto() {

}
string Objeto::getNombre() {
	return this->nombre;
}
void Objeto::setNombre(string nombre) {
	this->nombre = nombre;
}
int Objeto::getDurabilidad() {
	return this->durabilidad;
}
void Objeto::setDurabilidad(int durabilidad) {
	this->durabilidad = durabilidad;
}
bool Objeto::getComestible() {
	return this->comestible;
}
void Objeto::setComestible(bool comestible) {
	this->comestible = comestible;
}
int Objeto::getCantidad() {
	return this->cantidad;
}
void Objeto::setCantidad(int cantidad) {
	this->cantidad = cantidad;
}
void Objeto::toString() {
	cout << nombre << ": " << cantidad << endl;
}