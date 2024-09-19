#include <iostream>
#include <string>
#include <vector>

class Usuario {
public:
    std::string nombre;
    std::string apellido;
    int edad;
    
    Usuario(std::string n, std::string a, int e) : nombre(n), apellido(a), edad(e) {}
};

class Sistema {
private:
    std::vector<Usuario> usuarios;
    
public:
    void agregarUsuario(std::string nombre, std::string apellido, int edad) {
        Usuario nuevoUsuario(nombre, apellido, edad);
        usuarios.push_back(nuevoUsuario);
    }
    
    void buscarUsuario(std::string nombre, std::string apellido) {
        bool encontrado = false;
        for (int i = 0; i < usuarios.size(); ++i) {
            if (usuarios[i].nombre == nombre && usuarios[i].apellido == apellido) {
                std::cout << "Usuario encontrado: " << usuarios[i].nombre << " " << usuarios[i].apellido << ", Edad: " << usuarios[i].edad << std::endl;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            std::cout << "Usuario no encontrado" << std::endl;
        }
    }

    void mostrarUsuariosMayoresDe(int edad) {
        int contador = 0;
        for (int i = 0; i < usuarios.size(); ++i) {
            if (usuarios[i].edad > edad) {
                std::cout << "Usuario: " << usuarios[i].nombre << " " << usuarios[i].apellido << ", Edad: " << usuarios[i].edad << std::endl;
                ++contador;
            }
        }
        if (contador == 0) {
            std::cout << "No hay usuarios mayores de " << edad << std::endl;
        }
    }
};

int main() {
    Sistema sistema;
    sistema.agregarUsuario("Juan", "Pérez", 30);
    sistema.agregarUsuario("Ana", "López", 25);
    sistema.agregarUsuario("Carlos", "Gómez", 40);

    sistema.buscarUsuario("Ana", "López");
    sistema.mostrarUsuariosMayoresDe(35);

    return 0;
}
