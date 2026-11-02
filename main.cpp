#include "Estoque.h"

int main(){
    Estoque estoque;
    int opcao = 0;
    string nome;

    do {
        cout << "\nLoja de roupas\n"
             << "1. Inserir\n"
             << "2. Listar todos\n"
             << "3. Exibir um\n"
             << "4. Alterar\n"
             << "5. Remover\n"
             << "6. Mostrar produtos por categoria\n"
             << "7. Exibir relatorio\n"
             << "8. Sair\n";

        if (!estoque.lerInteiro("Opcao: ", opcao)) {
            if (cin.eof()) {
                break;
            }
            continue;
        }

        switch (opcao) {
            case 1:
                estoque.cadastrarProduto();
                break;
            case 2:
                estoque.listarTodos();
                break;
            case 3:
            case 4:
            case 5:
                if (estoque.lerTexto("Nome ou inicio do nome: ", nome)) {
                    if (opcao == 3) estoque.exibirUm(nome);
                    if (opcao == 4) estoque.alterar(nome);
                    if (opcao == 5) estoque.remover(nome);
                }
                break;
            case 6:
                estoque.exibirPorCategoria();
                break;
            case 7:
                estoque.exibirRelatorio();
                break;
            case 8:
                cout << "Programa encerrado.\n";
                break;
            default:
                cout << "Opcao invalida.\n";
        }
    } while (opcao != 8);

    return 0;
}
