#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#ifndef DECLARACOES_H
#define DECLARACOES_H

struct Declaracoes {
	static unordered_map<string, string> Constantes;
	static unordered_map<string, string> Variaveis;
};

#endif

class Compilador 
{
	public:
		void Leitura(const char* NomeArquivo);
		void Executor(vector<string> Executavel, vector<string> Conteudo);
};