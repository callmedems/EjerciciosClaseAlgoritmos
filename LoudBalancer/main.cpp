#include <iostream>
#include "loadbalancer.h"
#include "loadbalancer.cpp"

int main() {
    int numServers, maxRequests;

    std::cout << "Ingrese el número de servidores: ";
    std::cin >> numServers;
    std::cout << "Ingrese la carga máxima por servidor: ";
    std::cin >> maxRequests;

    LoadBalancer lb(numServers, maxRequests);

    int option;
    do {
        std::cout << "\n1. Añadir petición\n";
        std::cout << "2. Mostrar estado de los servidores\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> option;

        switch (option) {
            case 1:
                lb.addRequest();
                break;
            case 2:
                lb.printStatus();
                break;
            case 0:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (option != 0);

    return 0;
}
