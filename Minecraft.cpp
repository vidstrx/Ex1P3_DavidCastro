#include "Minecraft.h"
Minecraft::Minecraft() {
    matriz = new char*[3];
    for (int i = 0; i < 3; i++) {
        matriz[i] = new char[3]; // reservando memoria en cada fila
    }
}

void Minecraft::simulacion() {
    cout << "\n-----Minecraft-----\n" << endl;
    regenerarEntorno();
    imprimirEntorno();
    cout << "\nJamones: " << jamones << endl;
    if (jamones == 0) {
        cout << "Has perdido\nTe has quedado sin jamones" << endl;
    } else {
        agregarObjeto();
    }
}

void Minecraft::regenerarEntorno() {
    random_device random;
    mt19937 gen(random());
    uniform_int_distribution<int> distrib(0, 2);
    int numRandom;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            numRandom = distrib(gen);
            switch (numRandom) {
            case 0:
                matriz[i][j] = '0';
                break;
            case 1:
                matriz[i][j] = 'S';
                break;
            case 2:
                matriz[i][j] = 'M';
                break;
            } 
        }
    }
}

void Minecraft::agregarObjeto() {
    int opcion, cantidadSandias = 0, cantidadMadera = 0, cantidadPalos = 0, cantidadMaderaObj = 0;
    Objeto objetoActual, objetoMadera, objetoPalos;
    bool haySandias = false;
    cout << "\n0. Fin\n1. Obtener sandias\n2. Obtener bloques de madera con el hacha\n3. Obtener bloques de madera con la mano\n4. Craftear palos\n5. Craftear hacha de madera\n6. Comer\n7. Ver inventario\nEscoga: ";
    cin >> opcion;

    switch (opcion) {
    case 0:
        cout << "\nHas salido del juego" << endl;
        break;
    case 1:
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matriz[i][j] == 'S') {
                    haySandias = true;
                    cantidadSandias++;
                }
            }
        }

        if (haySandias) {
            jamones--;
            inventario.push_back(Objeto("Sandias", 1, haySandias, cantidadSandias));
            cout << "\nSe agrego Sandias a tu inventario" << endl;
        }
        else {
            cout << "No hay sandias" << endl;
        }
        simulacion();
        break;
    case 2:
        if (hayHacha(inventario)) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (matriz[i][j] == 'M') {
                        cantidadMadera++;
                    }
                }
            }
            for (Objeto objeto : inventario) {
                if (objeto.getNombre() == "Madera") {
                    cantidadMaderaObj = objeto.getCantidad();
                    objetoActual = objeto;
                    break;
                }
            }
            if (cantidadMaderaObj > 0) {
                cantidadMaderaObj -= cantidadMadera;
                objetoActual.setCantidad(cantidadMaderaObj);
            }
            else {
                jamones -= 2;
                inventario.push_back(Objeto("Madera", 1, false, cantidadMadera));
                cout << "\nSe agrego Madera a tu inventario" << endl;
            }
        }
        else {
            cout << "No tienes hachas en tu inventario" << endl;
        }
        simulacion();
        break;
    case 3:
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (matriz[i][j] == 'M') {
                    cantidadMadera++;
                }
            }
        }
        for (Objeto objeto : inventario) {
            if (objeto.getNombre() == "Madera") {
                cantidadMaderaObj = objeto.getCantidad();
                objetoActual = objeto;
                break;
            }
        }
        if (cantidadMaderaObj > 0) {
            cantidadMaderaObj -= cantidadMadera;
            objetoActual.setCantidad(cantidadMaderaObj);
        }
        else {
            jamones -= 4;
            inventario.push_back(Objeto("Madera", 2, false, cantidadMadera));
            cout << "\nSe agrego Madera a tu inventario" << endl;
        }
        simulacion();
        break;
    case 4:
        for (Objeto objeto : inventario) {
            if (objeto.getNombre() == "Madera") {
                cantidadMadera = objeto.getCantidad();
                objetoActual = objeto;
            }
        }

        if (cantidadMadera == 0) {
            cout << "No tienes suficiente madera" << endl;
        }
        else {
            jamones--;
            cantidadMadera = cantidadMadera - 1;
            objetoActual.setCantidad(cantidadMadera);
            inventario.push_back(Objeto("Palos", 3, false, 2));
            cout << "\nSe agrego Palos a tu inventario" << endl;
        }
        simulacion();
        break;
    case 5:
        if (hayHacha(inventario)) {
            cout << "Ya tienes un hacha en tu inventario" << endl;
        }
        else {
            for (Objeto objeto : inventario) {
                if (objeto.getNombre() == "Madera" && objeto.getCantidad() >= 3) {
                    cantidadMadera = objeto.getCantidad();
                    objetoMadera = objeto;
                }
                else if (objeto.getNombre() == "Palos" && objeto.getCantidad() >= 2) {
                    cantidadPalos = objeto.getCantidad();
                    objetoPalos = objeto;
                }
            }
            if (cantidadMadera < 3 || cantidadPalos < 2) {
                cout << "No tienes suficientes materiales para craftear un hacha" << endl;
            }
            else {
                cantidadMadera -= 3;
                cantidadPalos -= 2;
                objetoMadera.setCantidad(cantidadMadera);
                objetoPalos.setCantidad(cantidadPalos);
                jamones--;
                inventario.push_back(Objeto("Hacha de Madera", 4, false, 1));
                cout << "\nSe agrego un Hacha de Madera a tu inventario" << endl;
            }
        }
        simulacion();
        break;
    case 6:
        for (Objeto objeto : inventario) {
            if (objeto.getNombre() == "Sandias") {
                cantidadSandias = objeto.getCantidad();
                objetoActual = objeto;
                break;
            }
        }
        if (cantidadSandias == 0) {
            cout << "No tienes Sandias para comer" << endl;
        }
        else {
            cantidadSandias--;
            jamones += 3;
        }
        simulacion();
        break;
    case 7:
        listarObjeto();
        simulacion();
        break;
    default:
        cout << "Error, ingresa una opcion correcta" << endl;
        simulacion();
        break;
    }
}
void Minecraft::eliminarObjeto() {

}
void Minecraft::listarObjeto() {
    cout << "\n-----INVENTARIO-----" << endl;
    if (inventario.empty()) {
        cout << "No hay nada en tu inventario" << endl;
    } else {
        for (Objeto objeto : inventario) {
            cout << objeto.getNombre() << ": " << objeto.getCantidad() << endl;
        }
    }
    cout << endl;
}
void Minecraft::imprimirEntorno() {
    cout << "Entorno:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matriz[i][j] << ' ';
        }
        cout << endl;
    }
}
Minecraft::~Minecraft() {
    for (int i = 0; i < 3; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}
bool Minecraft::hayHacha(vector<Objeto> inventario) {
    for (Objeto objeto : inventario) {
        if (objeto.getNombre() == "Hacha") {
            return true;
        }
    }
    return false;
}
int Minecraft::jamones = 10;
