#pragma once

#include "Produto.h"
using namespace std;

class Chapeu : public Produto {
    private:
        string cor;
        string modelo;
        string material;
    public:
        Chapeu(){}

        Chapeu(string i, string n, vector<Categoria> c, float p, int q,
               string co, string m, string mat) : Produto(i, n, c, p, q){
            cor = co;
            modelo = m;
            material = mat;
        }

        void exibir() override {
            cout << "------------------------------------------------\n";
            cout << "Tipo: Chapeu\n";
            Produto::exibir();
            cout << "Cor: " << cor << '\n';
            cout << "Modelo: " << modelo << '\n';
            cout << "Material: " << material << '\n';
            cout << "------------------------------------------------\n";
        }

        string getTipo() override {return "Chapeu";}

        void salvar(fstream& arquivo) override {
            Produto::salvar(arquivo);
            arquivo << cor << '\n' << modelo << '\n' << material << '\n';
        }

        string getCor(){return cor;}
        string getModelo(){return modelo;}
        string getMaterial(){return material;}

        void setCor(string c){cor = c;}
        void setModelo(string m){modelo = m;}
        void setMaterial(string mat){material = mat;}    
};
