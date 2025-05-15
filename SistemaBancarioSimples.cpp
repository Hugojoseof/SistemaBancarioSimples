#include <iostream>
#include <string>
using namespace std;

// Classe que representa o Cliente do banco
class Cliente {
private:
    string nome;
    string cpf;
public:
    // Construtor que inicializa nome e cpf
    Cliente(string nome, string cpf) {
        this->nome = nome;
        this->cpf = cpf;
    }

    // Métodos para acessar os dados do cliente
    string getNome() const {
        return nome;
    }

    string getCpf() const {
        return cpf;
    }
};

// Classe que representa a Conta Bancária
class ContaBancaria {
private:
    int numero;
    double saldo;
    Cliente titular; // Composição: uma conta tem um cliente
public:
    // Construtor com saldo padrão como 0.0
    ContaBancaria(int numero, Cliente titular, double saldo = 0.0) 
        : numero(numero), titular(titular), saldo(saldo) {}

    // Deposita um valor na conta
    void depositar(double valor) {
        saldo += valor;
    }

    // Saca um valor da conta, se houver saldo
    void sacar(double valor) {
        if (valor > saldo) {
            cout << "Saldo insuficiente para saque!" << endl;
        } else {
            saldo -= valor;
        }
    }

    // Transfere um valor para outra conta, se houver saldo
    void transferir(double valor, ContaBancaria &destino) {
        if (valor > saldo) {
            cout << "Saldo insuficiente para transferir!" << endl;
        } else {
            saldo -= valor;
            destino.depositar(valor);
            cout << "Transferido: R$ " << valor << " da conta " << numero
                 << " para a conta " << destino.numero << endl;
        }
    }

    // Transfere um valor dividido entre duas contas destino
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
        if (valor > saldo) {
            cout << "Saldo insuficiente para transferir!" << endl;
        } else {
            double metade = valor / 2.0;
            saldo -= valor;
            destino1.depositar(metade);
            destino2.depositar(metade);
            cout << "Transferido: R$ " << metade << " para cada conta ("
                 << destino1.numero << " e " << destino2.numero
                 << ") da conta " << numero << endl;
        }
    }

    // Exibe o saldo atual da conta
    void exibirSaldo() const {
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }

    // Exibe as informações completas da conta
    void exibirInformacoes() const {
        cout << "Titular: " << titular.getNome()
             << ", CPF: " << titular.getCpf() << endl;
        cout << "Numero da Conta: " << numero
             << ", Saldo: R$ " << saldo << endl;
    }
};

// Função principal (demonstração do sistema)
int main() {
    // Criação de clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criação das contas, Ana já com R$1000
    ContaBancaria conta1(1001, cliente1, 1000.0);
    ContaBancaria conta2(1002, cliente2);
    ContaBancaria conta3(1003, cliente3);

    // Exibe saldo inicial da conta da Ana
    conta1.exibirSaldo();

    // Transferência simples para Bruno
    conta1.transferir(200.0, conta2);

    // Transferência dividida entre Bruno e Carla
    conta1.transferir(300.0, conta2, conta3);

    // Exibe informações finais
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
