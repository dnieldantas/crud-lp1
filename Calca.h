#pragma once

#include "Produto.h"

class Calca : public Produto {
    private:
        int numeracao = 0;
        string cor;
        string modelo;
        string material;
    public:
        Calca(){}

        Calca(string i, string n, vector<Categoria> c, float p, int q,
              int num, string co, string m, string mat) : Produto(i, n, c, p, q){
            numeracao = num;
            cor = co;
            modelo = m;
            material = mat;
        }

        void exibir() override {
            cout << "------------------------------------------------\n";
            cout << "Tipo: Calca\n";
            Produto::exibir();
            cout << "Numeracao: " << numeracao << '\n';
            cout << "Cor: " << cor << '\n';
            cout << "Modelo: " << modelo << '\n';
            cout << "Material: " << material << '\n';
            cout << "------------------------------------------------\n";
        }

        string getTipo() override {return "Calca";}

        void salvar(fstream& arquivo) override {
            Produto::salvar(arquivo);
            arquivo << numeracao << '\n' << cor << '\n' << modelo << '\n' << material << '\n';
        }

        int getNumeracao(){return numeracao;}
        string getCor(){return cor;}
        string getModelo(){return modelo;}
        string getMaterial(){return material;}

        void setNumeracao(int n){numeracao = n;}
        void setCor(string c){cor = c;}
        void setModelo(string m){modelo = m;}
        void setMaterial(string mat){material = mat;}
};
