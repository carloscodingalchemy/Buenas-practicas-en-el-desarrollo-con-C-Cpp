#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>  // Para std::min y std::max

class BankAccount {
private:
    double balance;
    std::mutex mtx;  // Mutex para proteger el acceso al balance

public:
    BankAccount(double initial_balance) : balance(initial_balance) {}

    // Método para obtener el balance (lectura sincrónica)
    double getBalance() {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización para lectura
        return balance;
    }

    // Método para depositar dinero
    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización
        std::cout << "Depositando " << amount << "...\n";
        balance += amount;
        std::cout << "Nuevo balance tras el deposito: " << balance << "\n";
    }

    // Método para retirar dinero
    void withdraw(double amount) {
        std::lock_guard<std::mutex> lock(mtx);  // Sincronización
        if (balance >= amount) {
            std::cout << "Retirando " << amount << "...\n";
            balance -= amount;
            std::cout << "Nuevo balance tras la retirada: " << balance << "\n";
        } else {
            std::cout << "Fondos insuficientes para retirar " << amount << "!\n";
        }
    }

    // Método para transferir dinero entre dos cuentas, evitando el interbloqueo
    void transfer(BankAccount& to, double amount) {
        BankAccount* first = this;
        BankAccount* second = &to;

        // Ordenar las cuentas para evitar interbloqueos
        if (this > &to) {
            std::swap(first, second);
        }

        // Bloqueo en el mismo orden siempre
        std::scoped_lock lock(first->mtx, second->mtx);
        
        if (balance >= amount) {
            std::cout << "Transferencia de " << amount << " de esta cuenta a otra cuenta...\n";
            balance -= amount;
            to.balance += amount;
            std::cout << "Transferencia completada. Nuevo balance: " << balance << "\n";
        } else {
            std::cout << "Fondos insuficientes para transferir " << amount << "!\n";
        }
    }
};

void threadFunction1(BankAccount& account) {
    account.deposit(100);  // Hilo 1: realiza un depósito
}

void threadFunction2(BankAccount& account1, BankAccount& account2) {
    account1.transfer(account2, 50);  // Hilo 2: realiza una transferencia
}

int main() {
    BankAccount account1(200);  // Primera cuenta con $200
    BankAccount account2(100);  // Segunda cuenta con $100

    std::thread t1(threadFunction1, std::ref(account1));  // Hilo para hacer un depósito
    std::thread t2(threadFunction2, std::ref(account1), std::ref(account2));  // Hilo para transferir dinero

    t1.join();
    t2.join();

    return 0;
}
