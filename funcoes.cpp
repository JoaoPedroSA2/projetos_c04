#include "cabecalho.h"
#include <iostream>
#include <vector>
#include <list>
#define INF 999999

list<aresta> grafo[100];
cidade cidades[100];
int total_cidades = 0;
node * root = NULL;

void insert(struct node * & current, pokemon data){
  if(current == NULL){
    current = new struct node;
    current->data = data;
    current->left = NULL;
    current->right = NULL;
  } else if( data.nome < current->data.nome){
    insert(current->left, data);
  } else {
    insert(current->right, data);
  }
}

void show_in_order(struct node * current) {
  if (current != NULL) {
    if (current->left != NULL) {
      show_in_order(current->left);
    }
    cout << "Nome: " << current->data.nome << " | " << " Tipo: " << current->data.tipo << " | " << " Numero: " << current->data.numero << " | " << " Localizacao: " << current->data.loc_x << "," << current->data.loc_y << endl;
    if (current->right != NULL) {
      show_in_order(current->right);
    }
  }
  else {
	cout << "Nenhum pokemon cadastrado!" << endl;
  }
}

node * find_less_save_right(node * & current) {
  if(current->left != NULL) {
    return find_less_save_right(current->left);
  } else {
    node * copy = current;
    current = current->right;
    return copy;
  }
}

int remove(node * & current, string data){
  if(current == NULL){
    return 0;
  } else if(data == current->data.nome){
    node * temp = current;
    if (current->right == NULL) {
      current = current->left;
    } else if (current->left == NULL) {
      current = current->right;
    } else {
      temp = find_less_save_right(current->right);
      current->data.nome = temp->data.nome;
    }
    delete(temp);
    return 1;
  } else {
    if(data < current->data.nome){
      return remove(current->left, data);
    } else {
      return remove(current->right, data);
    }
  }
}


void dijkstra_centro_proximo(list<aresta> grafo[], int origem)
{
	int n = total_cidades; //n vertices
	
	int pai[n];
	int distancia[n];
	bool visitado[n];
	int atual;
	int destino = -1;
	
	list<aresta>::iterator it;


	for(int i = 0; i < n; i++)
	{
		distancia[i] = INF;
		pai[i] = -1;
		visitado[i] = false;
	}

	distancia[origem] = 0;

	atual = origem;
	
	while(atual != -1 && !visitado[atual])
	{
		visitado[atual] = true;
		
		if(cidades[atual].possui_centro)
		{
			destino = atual;
			break;
		}

		for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)
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

	list<int> caminho;

	if(destino == -1)
	{
		cout << "Nenhum centro Pokemon encontrado!" << endl;
		return;
	}

	while (atual != -1)
	{
	    caminho.push_back(atual);
	    atual = pai[atual];
	}
	
	cout << "Rota:" << endl;
	
	// imprime origem -> destino
	int contador = 0;

	list<int>::reverse_iterator it_caminho;
	
	for (it_caminho = caminho.rbegin(); it_caminho != caminho.rend(); ++it_caminho)
	{
	    cout << cidades[*it_caminho].nome;
	    if (contador < (int)caminho.size() - 1) cout << " -> ";
	    contador++;
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
		cout << "Digite o nome da cidade: " << endl;
		getline(cin >> ws, cidades[total_cidades].nome);
		
		cidades[total_cidades].codigo = total_cidades++; 
		
		cout << "A cidade possui um centro Pokemon? (1 para sim, 0 para nao)" << endl;
		cin >> cidades[total_cidades - 1].possui_centro;
	}

	cout << "Cidades cadastradas" << endl;
	for(int i = 0; i < total_cidades; i++)
	{
		cout << "Cidade: " << cidades[i].nome << "| Codigo: " << cidades[i].codigo << "| Possui centro Pokemon: " << cidades[i].possui_centro << endl;
	}
}

void cadastro_estrada()
{
	if(total_cidades == 0)
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

		grafo[origem].push_back(a);
		
		// Adiciona na direção inversa (bidirecional)
		aresta a_inversa;
		a_inversa.origem = destino;
		a_inversa.destino = origem;
		a_inversa.peso = peso;
		
		grafo[destino].push_back(a_inversa);
	}
	
	cout << "Cadastro concluido" << endl;  	 
	
}

void buscar_centro_proximo()
{
	int origem;
	
	cout << "Digite o codigo da cidade de origem" << endl;
	cin >> origem;
	
	dijkstra_centro_proximo(grafo, origem);
	
}

void cadastro_pokemon()
{
	pokemon infos;
	int q;

	cout << "Quantos pokemons deseja cadastrar?" << endl;
	cin >> q;

	for(int i = 0; i < q; i++)
	{
		cout << "Digite o nome do pokemon" << endl;
		getline(cin >> ws, infos.nome);

		cout << "Digite o tipo do pokemon" << endl;
		getline(cin >> ws, infos.tipo);

		cout << "Digite o numero do pokemon" << endl;
		cin >> infos.numero;

		cout << "Digite a localizacao do pokemon (x y)" << endl;
		cin >> infos.loc_x >> infos.loc_y;

		insert(root, infos);
		cout << "Pokemon cadastrado" << endl;
	}
}

void remover_pokemon()
{
	string remover_pok;

	if(root == NULL) {
		cout << "Nenhum pokemon cadastrado!" << endl;
		return;
	}
	else
	{
		cout << "Digite o nome do pokemon a ser removido" << endl;
		getline(cin >> ws, remover_pok);
		
		int resultado = remove(root, remover_pok);
		
		if (resultado) {
			cout << "Pokemon removido com sucesso!" << endl;
		} else {
			cout << "Pokemon nao encontrado!" << endl;
		}
	}
}

void listar_pokemon_nome()
{
	show_in_order(root);
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

