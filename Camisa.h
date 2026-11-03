#pragma once

#include "Produto.h"

class Camisa : public Produto {
    private:
        string tamanho;
        string cor;
        string modelo;
        string material;
    public:
        Camisa(){}

        Camisa(string i, string n, vector<Categoria> c, float p, int q,
               string t, string co, string m, string mat) : Produto(i, n, c, p, q){
            tamanho = t;
            cor = co;
            modelo = m;
            material = mat;
        }

        void exibir() override {
            cout << "------------------------------------------------\n";
            cout << "Tipo: Camisa\n";
            Produto::exibir();
            cout << "Tamanho: " << tamanho << '\n';
            cout << "Cor: " << cor << '\n';
            cout << "Modelo: " << modelo << '\n';
            cout << "Material: " << material << '\n';
            cout << "------------------------------------------------\n";
        }

        string getTipo() override {return "Camisa";}

        void salvar(fstream& arquivo) override {
            Produto::salvar(arquivo);
            arquivo << tamanho << '\n' << cor << '\n' << modelo << '\n' << material << '\n';
        }

        string getTamanho(){return tamanho;}
        string getCor(){return cor;}
        string getModelo(){return modelo;}
        string getMaterial(){return material;}

        void setTamanho(string t){tamanho = t;}
        void setCor(string c){cor = c;}
        void setModelo(string m){modelo = m;}
        void setMaterial(string mat){material = mat;}
};
