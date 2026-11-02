#pragma once

#include <string>

using namespace std;

class Categoria {
    private:
        string nome;
        string descricao;
    public:
        Categoria(){}

        Categoria(string n, string d){
            nome = n;
            descricao = d;
        }

        string getNome() const {return nome;}
        string getDescricao() const {return descricao;}

        void setNome(string n){nome = n;}
        void setDescricao(string d){descricao = d;}
};
