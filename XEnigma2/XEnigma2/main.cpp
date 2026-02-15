#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::string fraseOriginal;
std::string fraseLimpia;
std::string mensajeFinal;
char letra;
char rotor1[26], rotor2[26], rotor3[26];
char notch1, notch2, notch3;

//MENU
void menu() {
    std::cout << "======== ENIGMA ========" << "\n";
    std::cout << "1. Cifrar Mensaje" << "\n";
    std::cout << "2. Descifrar Mensaje" << "\n";
    std::cout << "3. Editar Rotores" << "\n";
    std::cout << "4. Salir" << "\n";
}

//CARGA DE ROTORES
void cargarRotores() {
    std::ifstream archivo1("Rotor1.txt");
    if (archivo1.is_open()) {
        for (int i = 0; i < 26; i++) {
            archivo1 >> rotor1[i]; //Añade letra por letra el orden del archivo al rotor1
        }
        archivo1.close(); //Cerramos archivo
    }

    std::ifstream archivo2("Rotor2.txt");
    if (archivo2.is_open()) {
        for (int i = 0; i < 26; i++) {
            archivo2 >> rotor2[i]; //Añade letra por letra el orden del archivo al rotor2
        }
        archivo2.close(); //Cerramos archivo
    }

    std::ifstream archivo3("Rotor3.txt");
    if (archivo3.is_open()) {
        for (int i = 0; i < 26; i++) {
            archivo3 >> rotor3[i]; //Añade letra por letra el orden del archivo al rotor3
        }
        archivo3.close(); //Cerramos archivo
    }
}

//CIFRADO

void limpiarMensaje() {
    std::cout << "Escribe la palabra que quieras cifrar..." << "\n";
    std::cin.ignore();
    std::getline(std::cin, fraseOriginal);
    //LIMPIAR LOS ESPACIOS Y MINUSCULAS
    for (int i = 0; i < fraseOriginal.length(); i++)
    {
        letra = fraseOriginal[i];
        if (letra >= 'a' && letra <= 'z')
        {
            letra = letra - 32;
            fraseLimpia += letra;
        }
        else if (letra >= 'A' && letra <= 'Z')
        {
            fraseLimpia += letra;
        }
    }

    std::cout << fraseLimpia << "\n";

    std::cout << "Cifrando..." << "\n";
}

void cifrar() {
    //Pedimos la posicion en la que se inician los rotores
    char v1, v2, v3;
    std::cout << "Introduce la posicion inicial de los 3 rotores (ejemplo: A B C): ";
    std::cin >> v1 >> v2 >> v3;

    //Convertimos las letras a números (A=0, B=1, etc)
    int p1 = v1 - 'A';
    int p2 = v2 - 'A';
    int p3 = v3 - 'A';

    //Bucle para cifrar letra por letra
    for (int i = 0; i < fraseLimpia.length(); i++) {

        //Convertimos la letra a numero 0-25
        int num = fraseLimpia[i] - 'A';

        //ROTOR1
        int entrada1 = (num + p1) % 26; //Sumamos posición
        char letraR1 = rotor1[entrada1]; //Buscamos en el rotor la letra
        num = (letraR1 - 'A' - p1 + 26) % 26; // Restamos posición

        //ROTOR2
        int entrada2 = (num + p2) % 26;
        char letraR2 = rotor2[entrada2];
        num = (letraR2 - 'A' - p2 + 26) % 26;

        //ROTOR3
        int entrada3 = (num + p3) % 26;
        char letraR3 = rotor3[entrada3];
        num = (letraR3 - 'A' - p3 + 26) % 26;

        //Convertimos el numero en letra para mostrarlo en el mensaje final
        mensajeFinal += (char)(num + 'A');
    }

    std::cout << "Resultado del cifrado: " << mensajeFinal << "\n";

}


void descifrar() {
    std::ifstream archivoEntrada("Cifrado.txt");
    if (!archivoEntrada.is_open()) {
        std::cout << "No se pudo abrir Cifrado.txt para leer.\n";
        return;
    }

    std::string mensajeCifrado;
    std::getline(archivoEntrada, mensajeCifrado); //Leer el archivo
    archivoEntrada.close();

    std::string mensajeDescifrado = "";

    char v1, v2, v3;
    std::cout << "Introduce la posicion inicial de los rotores (ejemplo: A B C): ";
    std::cin >> v1 >> v2 >> v3;

    int p1 = v1 - 'A';
    int p2 = v2 - 'A';
    int p3 = v3 - 'A';

    for (int i = 0; i < mensajeCifrado.length(); i++) {
        if (mensajeCifrado[i] < 'A' || mensajeCifrado[i] > 'Z')
            continue;

        int num = mensajeCifrado[i] - 'A';

        // ROTOR 3 
        for (int j = 0; j < 26; j++) {
            if (rotor3[j] - 'A' == (num + p3) % 26) {
                num = (j - p3 + 26) % 26;
                break;
            }
        }

        // ROTOR 2
        for (int j = 0; j < 26; j++) {
            if (rotor2[j] - 'A' == (num + p2) % 26) {
                num = (j - p2 + 26) % 26;
                break;
            }
        }

        // ROTOR 1
        for (int j = 0; j < 26; j++) {
            if (rotor1[j] - 'A' == (num + p1) % 26) {
                num = (j - p1 + 26) % 26;
                break;
            }
        }

        mensajeDescifrado += (char)(num + 'A');
    }

    //Guardar el mensaje en Cifrado.txt
    std::ofstream archivoSalida("Cifrado.txt");
    if (!archivoSalida.is_open()) {
        std::cout << "No se pudo abrir Cifrado.txt para escribir.\n";
        return;
    }
    archivoSalida << mensajeDescifrado << "\n";
    archivoSalida.close();

    std::cout << "Mensaje descifrado guardado en Cifrado.txt\n";
}


int main()
{
    int opcion = 0;
    while (opcion != 4)
    {
        menu();
        std::cin >> opcion;
        switch (opcion)
        {

        case 1:
            cargarRotores();
            limpiarMensaje();
            cifrar();
            break;
        case 2:
            std::cout << "Descifrando..." << "\n";
            cargarRotores();
            descifrar();
            break;
        case 3:
            std::cout << "Edita los rotores" << "\n";
            break;
        case 4:
            std::cout << "Saliendo..." << "\n";
            break;
        default:
            break;
        }
    }
    return 0;
}