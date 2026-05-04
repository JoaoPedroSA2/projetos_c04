#include "cabecalho.h"
#include <iostream>
#include <vector>
#include <list>
#define INF 999999

vector<cidade> cidades;
vector<list<aresta> > grafo;

void dijkstra_centro_proximo(vector<cidade> cidades, int origem)
{
	int n = cidades.size(); //n vertices
	
	int pai[n];
	int distancia[n];
	bool visitado[n];
	int atual;
	int destino = -1;
	
	vector<aresta>::iterator it;


	for(int i = 0; i < n; i++)
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
		
		if(cidades[atual].possui_centro)
		{
			destino = atual;
			break;
		}

		for(it = cidades[atual].adjacentes.begin(); it != cidades[atual].adjacentes.end(); it++)
		{
			int d = it->destino, p = it->peso;

			if(!visitado[d] && distancia[atual] != INF && distancia[atual] + p < distancia[d])
			{
				distancia[d] = distancia[atual] + p;
				pai[d] = atual;
			}
		}
		
		int menor_distancia = INF;
		for(int i = 0; i < n; i++)
		{
			if(!visitado[i] && distancia[i] < menor_distancia)
			{
				menor_distancia = distancia[i];
				atual = i;
			}
		}
	}
	   
	atual = destino;

	vector<int> caminho;

	while (atual != -1)
	{
	    caminho.push_back(atual);
	    atual = pai[atual];
	}
	
	cout << "Rota:" << endl;
	
	// imprime origem -> destino
	for (int i = (int)caminho.size() - 1; i >= 0; i--)
	{
	    cout << cidades[caminho[i]].nome;
	    if (i != 0) cout << " -> ";
	}
	
	cout << endl;
	
	cout << "Distancia total: " << distancia[destino] << endl;
}

void cadastro_cidade()
{
	int n;

	cout << "Quantas cidades deseja cadastrar?" << endl;	

	cin >> n;

	for(int i = 0; i < n; i++)
	{
		cidade c;

		cout << "Digite o nome da cidade: " << endl;
		getline(cin >> ws, c.nome);
		
		c.codigo = cidades.size(); 
		
		cout << "A cidade possui um centro Pokemon? (1 para sim, 0 para nao)" << endl;
		cin >> c.possui_centro;

		cidades.push_back(c);
	}

	cout << "Cidades cadastradas" << endl;
	vector<cidade>::iterator it;

	for(it = cidades.begin(); it != cidades.end(); it++)
	{
		cout << "Cidade: " << it->nome << "| Codigo: " << it->codigo << "| Possui centro Pokemon: " << it->possui_centro << endl;
	}
}

void cadastro_estrada()
{
	if(cidades.empty())
	{
		cout << "Nenhuma cidade cadastrada, cadastre cidades primeiro" << endl;
		return;
	}

	int origem, destino, peso;
	
	cout << "--Cadastro das estradas--" << endl;
	cout << "Digite: origem, destino, peso (-1, -1, -1 para parar)" << endl;
	
	while(cin >> origem >> destino >> peso &&(origem != -1 && destino != -1 && peso != -1))
	{
		aresta a;
		a.origem = origem;
		a.destino = destino;
		a.peso = peso;

		cidades[origem].adjacentes.push_back(a);
	}
	
	cout << "Cadastro concluido" << endl;  	 
	
}

void buscar_centro_proximo()
{
	int origem;
	
	cout << "Digite o codigo da cidade de origem" << endl;
	cin >> origem;
	
	dijkstra_centro_proximo(cidades, origem);
	
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

