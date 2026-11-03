#pragma once

#include <vector>
#include <sstream>
#include <cctype>
#include <fstream>
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

        bool salvarArquivo(string caminho){
            fstream arquivo;
            arquivo.open(caminho, ios::out);
            if (!arquivo.is_open()) {
                cout << "Nao foi possivel salvar o estoque.\n";
                return false;
            }
            arquivo << "ESTOQUE_V1\n" << categorias.size() << '\n';
            for (Categoria categoria : categorias) {
                arquivo << categoria.getNome() << '\n'
                        << categoria.getDescricao() << '\n';
            }
            arquivo << produtos.size() << '\n';
            for (Produto* produto : produtos) {
                produto->salvar(arquivo);
            }
            arquivo.close();
            if (!arquivo) {
                cout << "Nao foi possivel concluir o salvamento.\n";
                return false;
            }
            return true;
        }

        bool carregarArquivo(string caminho){
            fstream arquivo;
            arquivo.open(caminho, ios::in);
            if (!arquivo.is_open()) {
                cout << "Arquivo nao encontrado ou indisponivel. Iniciando sem carregar dados.\n";
                return true;
            }

            string linha, nome, descricao;
            int totalCategorias, totalProdutos;
            if (!getline(arquivo, linha) || linha != "ESTOQUE_V1"
                || !(arquivo >> totalCategorias) || totalCategorias < 0) {
                cout << "Arquivo de estoque invalido.\n";
                return false;
            }
            getline(arquivo, linha); // Consome o Enter apos o numero.
            for (Produto* produto : produtos) {
                delete produto;
            }
            produtos.clear();
            categorias.clear();

            for (int i = 0; i < totalCategorias; i++) {
                if (!getline(arquivo, nome) || nome.empty()
                    || !getline(arquivo, descricao) || descricao.empty()) {
                    cout << "Arquivo de categorias incompleto.\n";
                    return false;
                }
                categorias.push_back(Categoria(nome, descricao));
            }
            if (!(arquivo >> totalProdutos) || totalProdutos < 0) {
                cout << "Quantidade de produtos invalida no arquivo.\n";
                return false;
            }
            getline(arquivo, linha);
            for (int i = 0; i < totalProdutos; i++) {
                string tipo, id, nomeProduto;
                float preco;
                int quantidade, quantidadeCategorias;
                if (!getline(arquivo, tipo) || !getline(arquivo, id)
                    || !getline(arquivo, nomeProduto)
                    || !(arquivo >> preco >> quantidade >> quantidadeCategorias)
                    || preco < 0 || quantidade < 0 || quantidadeCategorias < 0) {
                    cout << "Dados de produto invalidos no arquivo.\n";
                    return false;
                }
                getline(arquivo, linha);
                vector<Categoria> selecionadas;
                for (int j = 0; j < quantidadeCategorias; j++) {
                    if (!getline(arquivo, nome)) {
                        cout << "Categorias do produto incompletas.\n";
                        return false;
                    }
                    bool encontrou = false;
                    for (Categoria categoria : categorias) {
                        if (categoria.getNome() == nome) {
                            selecionadas.push_back(categoria);
                            encontrou = true;
                            break;
                        }
                    }
                    if (!encontrou) {
                        cout << "Categoria desconhecida no arquivo.\n";
                        return false;
                    }
                }
                if (tipo == "Produto") {
                    inserir(new Produto(id, nomeProduto, selecionadas,
                                                 preco, quantidade));
                    continue;
                }
                string tamanho, cor, modelo, material;
                int numeracao = 0;
                if (tipo == "Camisa") {
                    if (!getline(arquivo, tamanho)) {
                        cout << "Tamanho ausente no arquivo.\n";
                        return false;
                    }
                } else if (tipo == "Calca") {
                    if (!(arquivo >> numeracao) || numeracao <= 0) {
                        cout << "Numeracao invalida no arquivo.\n";
                        return false;
                    }
                    getline(arquivo, linha);
                } else if (tipo != "Chapeu") {
                    cout << "Tipo de produto desconhecido no arquivo.\n";
                    return false;
                }
                if (!getline(arquivo, cor) || !getline(arquivo, modelo)
                    || !getline(arquivo, material)) {
                    cout << "Dados da roupa incompletos no arquivo.\n";
                    return false;
                }
                if (tipo == "Camisa") {
                    inserir(new Camisa(id, nomeProduto, selecionadas,
                                     preco, quantidade, tamanho, cor, modelo, material));
                } else if (tipo == "Calca") {
                    inserir(new Calca(id, nomeProduto, selecionadas,
                                     preco, quantidade, numeracao, cor, modelo, material));
                } else {
                    inserir(new Chapeu(id, nomeProduto, selecionadas,
                                     preco, quantidade, cor, modelo, material));
                }
            }
            arquivo.close();
            return true;
        }

        void exibirTitulo(string titulo){
            cout << "\n================================================\n"
                 << "  " << titulo << '\n'
                 << "================================================\n";
        }

        bool lerTexto(string mensagem, string& valor){
            cout << "  > " << mensagem;
            if (!getline(cin, valor) || valor.empty()) {
                cout << "Texto invalido.\n";
                return false;
            }
            return true;
        }

        bool lerInteiro(string mensagem, int& valor){
            string resto;
            cout << "  > " << mensagem;
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
            cout << "  > " << mensagem;
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
            cout << "\n--- CATEGORIAS DISPONIVEIS -----------------------\n";
            if (categorias.empty()) {
                cout << "Nenhuma categoria cadastrada.\n";
                return;
            }
            for (int i = 0; i < categorias.size(); i++) {
                cout << "  [" << i + 1 << "] " << categorias[i].getNome()
                     << ": " << categorias[i].getDescricao() << '\n';
            }
        }

        void exibirPorCategoria(){
            exibirTitulo("PRODUTOS POR CATEGORIA");
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

        bool lerCategorias(vector<Categoria>& selecionadas){
            listarCategorias();
            string linhaCategorias;
            cout << "------------------------------------------------\n"
                 << "  Separe as tags por espacos.\n"
                 << "  Exemplo: inverno camisa roupa_de_frio\n";
            if (!lerTexto("Categorias: ",
                          linhaCategorias)) {
                return false;
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
                        return false;
                    }
                    Categoria categoria(nomeCategoria, descricao);
                    categorias.push_back(categoria);
                    selecionadas.push_back(categoria);
                    cout << "\n  [OK] Categoria cadastrada com sucesso.\n";
                }
            }

            if (selecionadas.empty()) {
                cout << "Selecione pelo menos uma categoria.\n";
                return false;
            }

            return true;
        }

        void cadastrarProduto(){
            int tipo;
            exibirTitulo("CADASTRAR PRODUTO");
            cout << "  [1] Camisa\n  [2] Calca\n  [3] Chapeu\n"
                 << "------------------------------------------------\n";
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
            if (!lerCategorias(selecionadas)) {
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
            cout << "\n  [OK] Produto cadastrado com sucesso.\n";
        }

        void inserir(Produto* p){
            produtos.push_back(p);
        }

        void listarTodos(){
            exibirTitulo("PRODUTOS CADASTRADOS");
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

            exibirTitulo("RELATORIO DE ESTOQUE");
            cout << "Produtos cadastrados: " << produtos.size() << '\n';
            cout << "Total de unidades: " << totalUnidades << '\n';
            cout << "Valor total do estoque: R$ " << valorTotal << '\n';
            cout << "Produtos sem estoque: " << produtosSemEstoque << '\n';
            cout << "------------------------------------------------\n";
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

            produtos[indice]->exibir();
            string tipo = produtos[indice]->getTipo();
            string id, novoNome, cor, modelo, material;
            float preco;
            int quantidade;

            if (!lerTexto("Novo ID: ", id) || !lerTexto("Novo nome: ", novoNome)
                || !lerReal("Novo preco: ", preco)) {
                cout << "Alteracao cancelada.\n";
                return;
            }
            if (preco < 0) {
                cout << "Preco invalido. Alteracao cancelada.\n";
                return;
            }
            if (!lerInteiro("Nova quantidade: ", quantidade)) {
                cout << "Alteracao cancelada.\n";
                return;
            }
            if (quantidade < 0) {
                cout << "Quantidade invalida. Alteracao cancelada.\n";
                return;
            }

            if (tipo != "Produto") {
                if (!lerTexto("Nova cor: ", cor) || !lerTexto("Novo modelo: ", modelo)
                    || !lerTexto("Novo material: ", material)) {
                    cout << "Alteracao cancelada.\n";
                    return;
                }
            }
            vector<Categoria> selecionadas;
            if (!lerCategorias(selecionadas)) {
                cout << "Alteracao cancelada.\n";
                return;
            }

            // Cria a versao atualizada antes de substituir o produto original.
            Produto* atualizado;
            if (tipo == "Camisa") {
                string tamanho;
                if (!lerTexto("Novo tamanho: ", tamanho)) {
                    cout << "Alteracao cancelada.\n";
                    return;
                }
                atualizado = new Camisa(id, novoNome, selecionadas, preco,
                                        quantidade, tamanho, cor, modelo, material);
            } else if (tipo == "Calca") {
                int numeracao;
                if (!lerInteiro("Nova numeracao: ", numeracao)) {
                    cout << "Alteracao cancelada.\n";
                    return;
                }
                if (numeracao <= 0) {
                    cout << "Numeracao invalida. Alteracao cancelada.\n";
                    return;
                }
                atualizado = new Calca(id, novoNome, selecionadas, preco,
                                       quantidade, numeracao, cor, modelo, material);
            } else if (tipo == "Chapeu") {
                atualizado = new Chapeu(id, novoNome, selecionadas, preco,
                                        quantidade, cor, modelo, material);
            } else if (tipo == "Produto") {
                atualizado = new Produto(id, novoNome, selecionadas, preco, quantidade);
            } else {
                cout << "Tipo desconhecido. Alteracao cancelada.\n";
                return;
            }
            delete produtos[indice];
            produtos[indice] = atualizado;
            cout << "\n  [OK] Produto alterado com sucesso.\n";
        }

        void remover(string nome){
            int indice = pesquisar(nome);

            if (indice == -1) {
                cout << "Nenhum produto selecionado.\n";
                return;
            }

            delete produtos[indice];
            produtos.erase(produtos.begin() + indice);
            cout << "\n  [OK] Produto removido com sucesso.\n";
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

            exibirTitulo("RESULTADOS DA PESQUISA");
            cout << "  Mais de um produto encontrado:\n";
            for (int indice : encontrados) {
                cout << "\n  [Indice " << indice << "]" << '\n';
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
