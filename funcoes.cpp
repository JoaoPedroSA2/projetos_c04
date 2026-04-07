#include "cabecalho.h"
#include <iostream>
#include <vector>
#include <list>

vector<cidade> cidades;
vector<list<aresta> > grafo;
const int INF = 999999;

int dijkstra_centro_proximo(list<aresta> grafo[], int vertices, int origem, int destino)
{
	int pai[vertices];
	int distancia[vertices];
	bool visitado[vertices];
	int atual;
	
	list<aresta>::iterator it;


	for(int i = 0; i < vertices; i++)
	{
		distancia[i] = INF;
		pai[i] = -1;
		visitado[i] = false;
	}

	distancia[origem] = 0;

	atual = origem;

	while(!visitado[atual])
	{
		visitado[atual] = true;	

		for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)
		{
			int d = it->destino, p = it->peso;

			if(!visitado[d] && distancia[atual] + p < distancia[d])
			{
				distancia[d] = distancia[atual] + p;
				pai[d] = atual;
			}
		}
		
		int menor_distancia = INF;
		for(int i = 0; i < vertices; i++)
		{
			if(!visitado[i] && distancia[i] < menor_distancia)
			{
				menor_distancia = distancia[i];
				atual = i;
			}
		}
	}

	atual = destino;
	while(atual != origem)
	{
		cout << atual + 1 << " <- ";
		atual = pai[atual];
	}
	cout << atual + 1 << endl;
	return distancia[destino];

}

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
	int n;

	cout << "Quantas cidades deseja cadastrar?" << endl;	

	cin >> n;

	for(int i = 0; i < n; i++)
	{
		cidade c;
		int quant_adjacentes; 
		int codigo_adjacente;
		int peso;

		cout << "Digite o nome da cidade: " << endl;
		getline(cin >> ws, c.nome);

		cout << "Digite o codigo da cidade: " << endl;
		cin >> c.codigo;

		cout << "A cidade possui um centro Pokemon? (1 para sim, 0 para nao)" << endl;
		cin >> c.possui_centro;

		cout << "Digite o numero de cidades adjacentes: " << endl;
		cin >> quant_adjacentes;

		for(int j = 0; j < quant_adjacentes; j++)
		{
			cout << "Digite o codigo da cidade adjacente: " << endl;
			cin >> codigo_adjacente;

			cout << "Digite o peso da estrada para a cidade adjacente: " << endl;
			cin >> peso;

			aresta a;
			a.destino = codigo_adjacente;
			a.peso = peso;
			a.origem = c.codigo;
			c.adjacentes.push_back(a);
		}

		cidades.push_back(c);
	}

	cout << "Cidades cadastradas" << endl;
	vector<cidade>::iterator it;

	for(it = cidades.begin(); it != cidades.end(); it++)
	{
		cout << "Nome: " << (*it).nome << " | Codigo: " << (*it).codigo << " | Possui centro Pokemon: " << (*it).possui_centro << " | Quantidade de cidades adjacentes: " << (*it).adjacentes.size() << endl;
		if (!(*it).adjacentes.empty())
		{
			cout << "  Cidades adjacentes:" << endl;
			list<aresta>::iterator it_adj;
			for(it_adj = (*it).adjacentes.begin(); it_adj != (*it).adjacentes.end(); it_adj++)
			{
				cout << "    Codigo: " << it_adj->destino << " | Peso da estrada: " << it_adj->peso << endl;
			}
		}
		cout << endl;
	}
}

void cadastro_estrada()
{
	aresta a;
	int peso;

	grafo.clear();
	grafo.resize(cidades.size());

	for(int i = 0; i < cidades.size(); i++)
	{
		list<aresta>::iterator it_adj;
		for(it_adj = cidades[i].adjacentes.begin(); it_adj != cidades[i].adjacentes.end(); it_adj++)
		{
			a.destino = it_adj->destino;
			peso = it_adj->peso;
			a.peso = peso;
			a.origem = cidades[i].codigo;

			bool existe = false;

			list<aresta>::iterator it;
			for(it = grafo[i].begin(); it != grafo[i].end(); it++)
			{
				if (it->destino == a.destino)
				{
					existe = true;
					break;
				}
			}
			if(!existe)
			{
				grafo[i].push_back(a);
			}
		}
	}

	cout << "Estradas cadastradas" << endl;
}

void buscar_centro_proximo()
{
	
	vector<bool> visitado(cidades.size(), false);
	vector<int> anterior(cidades.size(), -1);
	vector<int> pai(cidades.size(), -1);
	vector<int> distancia (cidades.size(), INF);
	list<int> fila;
	int centro_encontrado = -1;
	int indice_atual = -1;
	int atual;

	if(cidades.empty())
	{
		cout << "Nenhuma cidade cadastrada, retornando ao menu" << endl << endl;
		return;
	}

	int codigo_atual;
	cout << "Digite o codigo da cidade atual: " << endl;
	cin >> codigo_atual;

	for(int i = 0; i < cidades.size(); i++)
	{
		if(cidades[i].codigo == codigo_atual)
		{
			indice_atual = i;
			break;
		}
	}

	if(indice_atual == -1)
	{
		cout << "Codigo de cidade invalido, retornando ao menu" << endl << endl;
		return;
	}

	distancia[indice_atual] = 0;

	fila.push_back(indice_atual);
	visitado[indice_atual] = true;

	while(!fila.empty())
	{
		atual = fila.front();
		fila.pop_front();

		if(cidades[atual].possui_centro)
		{
			centro_encontrado = atual;
			break;
		}

		list<aresta>::iterator it;
		for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)
		{
			int adj = it->destino;
			int indice_adj = -1;

			for(int k = 0; k < (int)cidades.size();k++)
			{
				if(cidades[k].codigo == adj)
				{
					indice_adj = k;
					break;
				}
			}

			if(indice_adj != -1 && !visitado[indice_adj])
			{
				fila.push_back(indice_adj);
				visitado[indice_adj] = true;
				anterior[indice_adj] = atual;

			}
		}
	}
	
	if (centro_encontrado == -1)
	{
		cout << "Nenhum centro Pokemon encontrado, retornando ao menu" << endl << endl;
		return;
	}

	vector<int> caminho;
	atual = centro_encontrado;

	while(atual != -1)
	{
		caminho.push_back(atual);
		atual = anterior[atual];
	}
	
	cout << "Rota para o centro Pokemon mais proximo: " << endl;
	for (int i = caminho.size() -1; i >= 0; i--)
	{
		cout << cidades[caminho[i]].nome << " (Codigo: " << cidades[caminho[i]].codigo << ")" << endl;
	}


	cout << endl;
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