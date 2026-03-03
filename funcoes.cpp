#include "cabecalho.h"
#include <iostream>

void menu()
{
	int op;

	do{
		cout << "----POKEDEX----" << endl;
		cout << "1) Cadastrar cidade" << endl;
		cout << "2) Cadastrar estrada" << endl;
		cout << "3) Buscar centro Pokemon mais proximo" << endl;
		cout << "4) Cadastrar Pokemon" << endl;
		cout << "5) Remover Pokemon" << endl;
		cout << "6) Listar Pokemons (ordem alfabetica de nome)" << endl;
		cout << "7) Lista Pokemons (ordem alfabetica de tipo)" << endl;
		cout << "8) Contar Pokemons de cada tipo" << endl;
		cout << "9) Encontrar Pokemons proximos" << endl;
		cout << "10) Sair" << endl << endl;
		
		
		cout << "Selecione uma opcao" << endl;
		cin >> op;
		
		while (op < 1 || op > 10)
		{
			cout << "Opcao invalida, digite novamente!" << endl;
			
			cin >> op;
		}	
		
		switch (op)
		{
			case 1:
				cadastro_cidade();
				break;
			case 2:
				cadastro_estrada();
				break;
			case 3:
				buscar_centro_proximo();
				break;
			case 4: 
				cadastro_pokemon();
				break;
			case 5:
				remover_pokemon();
				break;
			case 6:
				listar_pokemon_nome();
				break;
			case 7:
				listar_pokemon_tipo();
				break;
			case 8:
				contar_pokemon();
				break;
			case 9:
				encontrar_pokemon_proximo();
				break;
			case 10:
				cout << "Saindo do programa..." << endl;
				break;
		}
	} while (op != 10);	
}

void cadastro_cidade()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void cadastro_estrada()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void buscar_centro_proximo()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void cadastro_pokemon()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void remover_pokemon()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void listar_pokemon_nome()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void listar_pokemon_tipo()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void contar_pokemon()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}

void encontrar_pokemon_proximo()
{
	cout << " Funcionalidade em construcao, retornando ao menu" << endl << endl;
}