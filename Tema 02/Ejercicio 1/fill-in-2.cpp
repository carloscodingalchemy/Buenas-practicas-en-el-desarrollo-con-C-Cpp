#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Rellena el nombre de la función de forma descriptiva
void /* nombre_funcion */(const vector<string>& /* nombres */) {
    for (const string& /* nombre */ : /* nombres */) {
        cout << "Hola, " << /* nombre */ << "!" << endl;
    }
}

// Usa nombres descriptivos para las variables
int main() {
    vector<string> /* lista_nombres */ = {"Ana", "Juan", "Luis", "Marta"};
    
    // Llama a la función con un nombre descriptivo
    /* nombre_funcion */(/* lista_nombres */);
    
    return 0;
}
