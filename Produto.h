#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Categoria.h"

using namespace std;

class Produto {
    private:
        string id;
        string nome;
        vector<Categoria> categorias;
        float preco = 0;
        int quantidade = 0;
    public:
        Produto(){}

        Produto(string i, string n, vector<Categoria> c, float p, int q){
            id = i;
            nome = n;
            categorias = c;
            preco = p;
            quantidade = q;
        }

        virtual ~Produto(){}

        virtual void exibir()  {
            cout << "ID: " << id << '\n';
            cout << "Nome: " << nome << '\n';
            cout << "Preco: R$ " << preco << '\n';
            cout << "Quantidade: " << quantidade << '\n';
            cout << "Categorias:\n";
            for (Categoria categoria : categorias) {
                cout << "- " << categoria.getNome() << ": "
                     << categoria.getDescricao() << '\n';
            }
        }

        virtual string getTipo(){return "Produto";}

        virtual void salvar(fstream& arquivo){
            arquivo << getTipo() << '\n' << id << '\n' << nome << '\n'
                    << preco << '\n' << quantidade << '\n'
                    << categorias.size() << '\n';
            for (Categoria categoria : categorias) {
                arquivo << categoria.getNome() << '\n';
            }
        }

        string getId(){return id;}
        string getNome(){return nome;}
        vector<Categoria> getCategorias(){return categorias;}
        float getPreco(){return preco;}
        int getQuantidade(){return quantidade;}

        void setId(string i){id = i;}
        void setNome(string n){nome = n;}
        void setCategoria(Categoria c){categorias.push_back(c);}
        void setPreco(float p){preco = p;}
        void setQuantidade(int q){quantidade = q;}
};
