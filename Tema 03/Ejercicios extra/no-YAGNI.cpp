#include <iostream>
#include <string>
#include <vector>
#include <map>

// Clase para gestionar usuarios
class Usuario {
private:
    std::string nombre;
    std::string apellido;
    int edad;
    std::map<std::string, std::string> datosExtra;  // Datos adicionales que no se usan actualmente

public:
    Usuario(const std::string& n, const std::string& a, int e) 
        : nombre(n), apellido(a), edad(e) {}

    // Métodos innecesarios para este ejemplo simple
    void agregarDatoExtra(const std::string& clave, const std::string& valor) {
        datosExtra[clave] = valor;
    }

    std::string obtenerDatoExtra(const std::string& clave) const {
        auto it = datosExtra.find(clave);
        if (it != datosExtra.end()) {
            return it->second;
        } else {
            return "Dato no encontrado";
        }
    }

    // Método innecesariamente complejo para imprimir detalles del usuario
    void imprimirDetalles(bool mostrarDatosExtra = false) const {
        std::cout << "Nombre: " << nombre << ", Apellido: " << apellido << ", Edad: " << edad << std::endl;

        if (mostrarDatosExtra) {
            for (const auto& par : datosExtra) {
                std::cout << par.first << ": " << par.second << std::endl;
            }
        }
    }
};

int main() {
    Usuario usuario("Juan", "Pérez", 30);

    // Llamada innecesaria, pues no se está usando en este contexto
    usuario.agregarDatoExtra("Nacionalidad", "Mexicana");

    usuario.imprimirDetalles();
    
    return 0;
}
