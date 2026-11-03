#include "Estoque.h"

int main(){
    Estoque estoque;
    if (!estoque.carregarArquivo("estoque.txt")) {
        return 1;
    }
    int opcao = 0;
    string nome;

    do {
        cout << "\n================================================\n"
             << "              Derzu - Sea Class\n"
             << "             Controle de estoque\n"
             << "================================================\n"
             << "  [1] Cadastrar produto\n"
             << "  [2] Listar todos os produtos\n"
             << "  [3] Pesquisar produto\n"
             << "  [4] Alterar produto\n"
             << "  [5] Remover produto\n"
             << "  [6] Mostrar produtos por categoria\n"
             << "  [7] Exibir relatorio\n"
             << "------------------------------------------------\n"
             << "  [8] Sair\n"
             << "================================================\n";

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
                if (opcao == 3) estoque.exibirTitulo("PESQUISAR PRODUTO");
                if (opcao == 4) estoque.exibirTitulo("ALTERAR PRODUTO");
                if (opcao == 5) estoque.exibirTitulo("REMOVER PRODUTO");
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
                break;
            default:
                cout << "Opcao invalida.\n";
        }
    } while (opcao != 8);

    if (!estoque.salvarArquivo("estoque.txt")) {
        return 1;
    }
    estoque.exibirTitulo("ATE A PROXIMA!");
    cout << "  Estoque salvo. Programa encerrado.\n";
    return 0;
}
