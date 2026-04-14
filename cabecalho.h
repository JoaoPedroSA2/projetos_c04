#ifndef CABECALHO_H
#define CABECALHO_H
#include <string>
#include <vector>
#include <list>
#include <iostream>


using namespace std;

struct aresta
{
	int origem;
	int destino;
	int peso;
};

struct cidade
{
    string nome;
    int codigo;
    bool possui_centro;
    vector<aresta> adjacentes;
};

void menu();

void cadastro_cidade();
void cadastro_estrada();
void buscar_centro_proximo();
void cadastro_pokemon();
void remover_pokemon();
void listar_pokemon_nome();
void listar_pokemon_tipo();
void contar_pokemon();
void encontrar_pokemon_proximo();


#endif
