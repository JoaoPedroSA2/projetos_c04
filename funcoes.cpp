#include "cabecalho.h"
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#define INF 999999

list<aresta> grafo[100];
cidade cidades[100];
int total_cidades = 0;
node * root_nome = NULL;
node * root_tipo = NULL;
list<pokemon> pontos;

void insert_nome(struct node * & current, pokemon data){
  if(current == NULL){
    current = new struct node;
    current->data = data;
    current->left = NULL;
    current->right = NULL;
  } else if( data.nome < current->data.nome){
    insert_nome(current->left, data);
  } else {
    insert_nome(current->right, data);
  }
}
void insert_tipo(struct node * & current, pokemon data){
  if(current == NULL){
    current = new struct node;
    current->data = data;
    current->left = NULL;
    current->right = NULL;
  } else if( data.tipo < current->data.tipo){
    insert_tipo(current->left, data);
  } else {
    insert_tipo(current->right, data);
  }
}

void show_in_order_nome(struct node * current) {
  if (current->data.nome != "") {
    if (current->left != NULL) {
      show_in_order_nome(current->left);
    }
    cout << "Nome: " << current->data.nome << " | " << " Tipo: " << current->data.tipo << " | " << " Numero: " << current->data.numero << " | " << " Localizacao: " << current->data.loc_x << "," << current->data.loc_y << endl;
    if (current->right != NULL) {
      show_in_order_nome(current->right);
    }
  }
  else {
	cout << "Nenhum pokemon cadastrado!" << endl;
  }
}

void show_in_order_tipo(struct node * current) {
  if (current->data.tipo != "") {
    if (current->left != NULL) {
      show_in_order_tipo(current->left);
    }
    cout << "tipo: " << current->data.tipo << " | " << " Nome: " << current->data.nome << " | " << " Numero: " << current->data.numero << " | " << " Localizacao: " << current->data.loc_x << "," << current->data.loc_y << endl;
    if (current->right != NULL) {
      show_in_order_tipo(current->right);
    }
  }
  else {
	cout << "Nenhum pokemon cadastrado!" << endl;
  }
}

void percorrer_arv(node * root)
{
	if(root == NULL)
	{
		return;
	}
	
	pontos.push_back({root->data.nome, root->data.tipo, root->data.numero, root->data.loc_x, root->data.loc_y});

	percorrer_arv(root->left);
	percorrer_arv(root->right);
}


void percorrer_tipo(node * root, string tipo, int &cont)
{

	if(root == NULL)
	{
		return;
	}
	if(root->data.tipo == tipo)
	{
		cont++;
	}

	percorrer_tipo(root->left, tipo, cont);
	percorrer_tipo(root->right, tipo, cont);
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

node * search(node * current, string data){
  if(current == NULL){
    return NULL;
  } else if(data == current->data.nome){
     return current;
  } else {
    if(data < current->data.nome){
      return search(current->left, data);
    } else {
      return search(current->right, data);
    }
  }
}

void destruct(node * & current) {
  if (current != NULL) {
    if (current->left != NULL) {
      destruct(current->left);
    }
    if (current->right != NULL) {
      destruct(current->right);
    }
    delete(current);
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

float distancia_quadrada(pokemon p1, pokemon p2){
	return sqrt((p1.loc_y-p2.loc_y)*(p1.loc_y-p2.loc_y) + (p1.loc_x-p2.loc_x)*(p1.loc_x-p2.loc_x));
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
		
		cidades[total_cidades].codigo = total_cidades; 
		
		cout << "A cidade possui um centro Pokemon? (1 para sim, 0 para nao)" << endl;
		cin >> cidades[total_cidades].possui_centro;

		total_cidades++;
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

		node * encontrado = search(root_nome, infos.nome);

		if(encontrado != NULL) {
			cout << "Pokemon ja cadastrado!" << endl;
			continue;
		}

		cout << "Digite o tipo do pokemon" << endl;
		getline(cin >> ws, infos.tipo);

		cout << "Digite o numero do pokemon" << endl;
		cin >> infos.numero;


		cout << "Digite a localizacao do pokemon (x y)" << endl;
		cin >> infos.loc_x >> infos.loc_y;

		insert_nome(root_nome, infos);
		insert_tipo(root_tipo, infos);
		cout << "Pokemon cadastrado" << endl;
	}
}

void remover_pokemon()
{
	string remover_pok;

	if(root_nome == NULL && root_tipo == NULL) {
		cout << "Nenhum pokemon cadastrado!" << endl;
		return;
	}
	else
	{
		cout << "Digite o nome do pokemon a ser removido" << endl;
		getline(cin >> ws, remover_pok);
		
		int resultado = remove(root_nome, remover_pok);
		
		if (resultado) {
			cout << "Pokemon removido com sucesso!" << endl;
		} else {
			cout << "Pokemon nao encontrado!" << endl;
		}
	}
}

void listar_pokemon_nome()
{
	show_in_order_nome(root_nome);
}

void listar_pokemon_tipo()
{
	show_in_order_tipo(root_tipo);
}

void contar_pokemon()
{
	string tipo;
	int cont;

	if(root_tipo == NULL) {
		cout << "Nenhum pokemon cadastrado!" << endl;
		return;
	}

	cout << "Digite o tipo do pokemon a ser contado" << endl;
	getline(cin >> ws, tipo);

	cont = 0;
	percorrer_tipo(root_tipo, tipo, cont);

	cout << "Quantidade de pokemons do tipo " << tipo << ": " << cont << endl;
}

void encontrar_pokemon_proximo()
{
	percorrer_arv(root_nome);

	list<pokemon>::iterator it;
	pokemon loc;
	float dist;
	float distancias[100];
	int i;

	cout << "Digite a localizacao (x y)" << endl;
	cin >> loc.loc_x >> loc.loc_y;

	i = 0;
	for(it = pontos.begin(); it != pontos.end(); it++)
	{
		dist = distancia_quadrada(loc, *it);

		if(dist < 100)
		{
			cout << "Pokemon: " << it->nome << " encontrado em (" << it->loc_x << ", " << it->loc_y << ") a distancia de " << dist << " metros" << endl;
		}
	}
}

void destruir()
{
	destruct(root_nome);
	destruct(root_tipo);
}

