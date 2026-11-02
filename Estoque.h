#pragma once

#include <vector>
#include <sstream>
#include <cctype>
#include "Produto.h"
#include "Camisa.h"
#include "Calca.h"
#include "Chapeu.h"

using namespace std;

class Estoque {
    private:
        vector<Produto*> produtos;
        vector<Categoria> categorias;

    public:
        Estoque(){}

        ~Estoque(){
            for (Produto* produto : produtos) {
                delete produto;
            }
        }

        bool lerTexto(string mensagem, string& valor){
            cout << mensagem;
            if (!getline(cin, valor) || valor.empty()) {
                cout << "Texto invalido.\n";
                return false;
            }
            return true;
        }

        bool lerInteiro(string mensagem, int& valor){
            string resto;
            cout << mensagem;
            if (!(cin >> valor)) {
                cin.clear();
                getline(cin, resto);
                cout << "Numero invalido.\n";
                return false;
            }
            getline(cin, resto);
            return true;
        }

        bool lerReal(string mensagem, float& valor){
            string resto;
            cout << mensagem;
            if (!(cin >> valor)) {
                cin.clear();
                getline(cin, resto);
                cout << "Numero invalido.\n";
                return false;
            }
            getline(cin, resto);
            return true;
        }

        void listarCategorias(){
            if (categorias.empty()) {
                cout << "Nenhuma categoria cadastrada.\n";
                return;
            }
            for (int i = 0; i < categorias.size(); i++) {
                cout << i + 1 << ". " << categorias[i].getNome()
                     << ": " << categorias[i].getDescricao() << '\n';
            }
        }

        void exibirPorCategoria(){
            if (categorias.empty()) {
                cout << "Nenhuma categoria cadastrada.\n";
                return;
            }

            listarCategorias();
            int numero;
            if (!lerInteiro("Numero da categoria: ", numero)) {
                return;
            }
            if (numero < 1 || numero > categorias.size()) {
                cout << "Categoria invalida.\n";
                return;
            }

            string nomeCategoria = categorias[numero - 1].getNome();
            bool encontrou = false;
            cout << "Produtos da categoria: " << nomeCategoria << '\n';
            for (Produto* produto : produtos) {
                for (Categoria categoria : produto->getCategorias()) {
                    if (categoria.getNome() == nomeCategoria) {
                        produto->exibir();
                        cout << '\n';
                        encontrou = true;
                        break;
                    }
                }
            }
            if (!encontrou) {
                cout << "Nenhum produto nesta categoria.\n";
            }
        }

        void cadastrarProduto(){
            int tipo;
            cout << "1. Camisa\n2. Calca\n3. Chapeu\n";
            if (!lerInteiro("Tipo: ", tipo)) {
                return;
            }
            if (tipo < 1 || tipo > 3) {
                cout << "Tipo invalido.\n";
                return;
            }

            string id, nome;
            string cor, modelo, material;
            float preco;
            int quantidade;

            if (!lerTexto("ID: ", id) || !lerTexto("Nome: ", nome)) {
                return;
            }

            if (!lerReal("Preco: ", preco)) {
                return;
            }
            if (preco < 0) {
                cout << "Preco invalido.\n";
                return;
            }
            if (!lerInteiro("Quantidade: ", quantidade)) {
                return;
            }
            if (quantidade < 0) {
                cout << "Quantidade invalida.\n";
                return;
            }

            if (!lerTexto("Cor: ", cor) || !lerTexto("Modelo: ", modelo)
                || !lerTexto("Material: ", material)) {
                return;
            }

            vector<Categoria> selecionadas;
            listarCategorias();
            string linhaCategorias;
            if (!lerTexto("Categorias (separe por espaco e use _ em nomes compostos): ",
                          linhaCategorias)) {
                return;
            }
            istringstream entradaCategorias(linhaCategorias);
            string nomeCategoria;
            while (entradaCategorias >> nomeCategoria) {
                for (char& letra : nomeCategoria) {
                    letra = tolower(static_cast<unsigned char>(letra));
                }
                bool repetida = false;
                for (Categoria categoria : selecionadas) {
                    if (categoria.getNome() == nomeCategoria) {
                        repetida = true;
                    }
                }
                if (repetida) {
                    cout << "Categoria ja selecionada: " << nomeCategoria << ".\n";
                    continue;
                }

                bool encontrada = false;
                for (Categoria categoria : categorias) {
                    if (categoria.getNome() == nomeCategoria) {
                        selecionadas.push_back(categoria);
                        encontrada = true;
                        break;
                    }
                }
                if (!encontrada) {
                    string descricao;
                    cout << "Categoria nova: " << nomeCategoria << ". Informe a descricao.\n";
                    if (!lerTexto("Descricao: ", descricao)) {
                        return;
                    }
                    Categoria categoria(nomeCategoria, descricao);
                    categorias.push_back(categoria);
                    selecionadas.push_back(categoria);
                    cout << "Categoria cadastrada com sucesso.\n";
                }
            }

            if (selecionadas.empty()) {
                cout << "Selecione pelo menos uma categoria. Cadastro cancelado.\n";
                return;
            }

            switch (tipo) {
                case 1: {
                    string tamanho;
                    if (!lerTexto("Tamanho: ", tamanho)) {
                        return;
                    }
                    inserir(new Camisa(id, nome, selecionadas, preco, quantidade,
                                       tamanho, cor, modelo, material));
                    break;
                }
                case 2: {
                    int numeracao;
                    if (!lerInteiro("Numeracao: ", numeracao)) {
                        return;
                    }
                    if (numeracao <= 0) {
                        cout << "Numeracao invalida.\n";
                        return;
                    }
                    inserir(new Calca(id, nome, selecionadas, preco, quantidade,
                                     numeracao, cor, modelo, material));
                    break;
                }
                case 3: {
                    inserir(new Chapeu(id, nome, selecionadas, preco, quantidade,
                                      cor, modelo, material));
                    break;
                }
            }
            cout << "Produto cadastrado com sucesso.\n";
        }

        void inserir(Produto* p){
            produtos.push_back(p);
        }

        void listarTodos(){
            if (produtos.empty()) {
                cout << "Nenhum produto cadastrado.\n";
                return;
            }

            for (Produto* produto : produtos) {
                produto->exibir();
                cout << '\n';
            }
        }

        void exibirRelatorio(){
            int totalUnidades = 0;
            double valorTotal = 0;
            int produtosSemEstoque = 0;

            for (Produto* produto : produtos) {
                totalUnidades += produto->getQuantidade();
                valorTotal += produto->getPreco() * produto->getQuantidade();

                if (produto->getQuantidade() == 0) {
                    produtosSemEstoque++;
                }
            }

            cout << "Relatorio de estoque\n";
            cout << "Produtos cadastrados: " << produtos.size() << '\n';
            cout << "Total de unidades: " << totalUnidades << '\n';
            cout << "Valor total do estoque: R$ " << valorTotal << '\n';
            cout << "Produtos sem estoque: " << produtosSemEstoque << '\n';
        }

        void exibirUm(string nome){
            int indice = pesquisar(nome);

            if (indice == -1) {
                cout << "Nenhum produto selecionado.\n";
                return;
            }

            produtos[indice]->exibir();
        }

        void alterar(string nome){
            int indice = pesquisar(nome);
            if (indice == -1) {
                cout << "Nenhum produto selecionado.\n";
                return;
            }

            string novoNome;
            float novoPreco;
            int novaQuantidade;

            if (!lerTexto("Novo nome: ", novoNome)
                || !lerReal("Novo preco: ", novoPreco)) {
                cout << "Alteracao cancelada.\n";
                return;
            }
            if (novoPreco < 0) {
                cout << "Preco invalido. Alteracao cancelada.\n";
                return;
            }
            if (!lerInteiro("Nova quantidade: ", novaQuantidade)) {
                cout << "Alteracao cancelada.\n";
                return;
            }
            if (novaQuantidade < 0) {
                cout << "Quantidade invalida. Alteracao cancelada.\n";
                return;
            }

            produtos[indice]->setNome(novoNome);
            produtos[indice]->setPreco(novoPreco);
            produtos[indice]->setQuantidade(novaQuantidade);
            cout << "Produto alterado com sucesso.\n";
        }

        void remover(string nome){
            int indice = pesquisar(nome);

            if (indice == -1) {
                cout << "Nenhum produto selecionado.\n";
                return;
            }

            delete produtos[indice];
            produtos.erase(produtos.begin() + indice);
            cout << "Produto removido com sucesso.\n";
        }

        int pesquisar(string nome){
            vector<int> encontrados;

            if (nome.empty()) {
                return -1;
            }

            for (int i = 0; i < produtos.size(); i++) {
                if (produtos[i]->getNome().compare(0, nome.size(), nome) == 0) {
                    encontrados.push_back(i);
                }
            }

            if (encontrados.empty()) {
                return -1;
            }

            if (encontrados.size() == 1) {
                return encontrados[0];
            }

            cout << "Mais de um produto encontrado:\n";
            for (int indice : encontrados) {
                cout << "Indice: " << indice << '\n';
                produtos[indice]->exibir();
                cout << '\n';
            }

            int indice;
            if (!lerInteiro("Digite um dos indices exibidos: ", indice)) {
                return -1;
            }

            for (int encontrado : encontrados) {
                if (indice == encontrado) {
                    return indice;
                }
            }

            cout << "Indice invalido.\n";
            return -1;
        }
};
