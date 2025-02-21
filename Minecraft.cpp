#include "Minecraft.h"
Minecraft::Minecraft() {
    matriz = new char*[3];
    for (int i = 0; i < 3; i++) {
        matriz[i] = new char[3]; // reservando memoria en cada fila
    }
    regenerarEntorno();
}
void Minecraft::simulacion() {
    int opcion, cantidadSandias = 0, cantidadMadera = 0;
    bool haySandias = false;
    cout << "\n-----Minecraft-----\n" << endl;
    imprimirEntorno();
    cout << "\nJamones: " << jamones << endl;
    cout << "\n0. Fin\n1. Obtener sandias\n2. Obtener bloques de madera con el hacha\n3. Obtener bloques de madera con la mano\n4. Craftear palos\n5. Craftear hacha de madera\n6. Comer\n7. Ver inventario\nEscoga: ";
    cin >> opcion;

    switch (opcion) {
    case 0:
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
            inventario.push_back(Objeto("Sandias",1,haySandias,cantidadSandias));
        } else {
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
            jamones -= 2;
            inventario.push_back(Objeto("Madera", 1, false, cantidadMadera));
        } else {
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
        jamones -= 4;
        inventario.push_back(Objeto("Madera", 2, false, cantidadMadera));
        simulacion();
        break;
    case 4:
        Objeto objetoActual;
        int cantidad = 0;
        for (Objeto objeto : inventario) {
            if (objeto.getNombre() == "Madera") {
                cantidad = objeto.getCantidad();
                objetoActual = objeto;
                break;
            }
        }

        if (cantidad == 0) {
            cout << "No tienes suficiente madera" << endl;
        } else {
            jamones--;
            cantidad--;
            objetoActual.setCantidad(cantidad);
            inventario.push_back(Objeto("Palos", 3, false, 2));
        }
        break;
    case 5:

        break;
    case 6:
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

}
void Minecraft::eliminarObjeto() {

}
void Minecraft::listarObjeto() {
    cout << "\n-----INVENTARIO-----" << endl;
    if (inventario.empty()) {
        cout << "No hay nada en tu inventario" << endl;
    } else {
        for (Objeto objeto : inventario) {
            objeto.toString();
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
