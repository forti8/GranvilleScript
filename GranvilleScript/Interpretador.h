#include <iostream>
#include <vector>
using namespace std;

class Interpretador {
	public:
		vector<string> OperacaoInterpretada(string texto);
		vector<string> Conversor(vector<string> TextoSeparado);
		string Tipagem(string texto, string anterior);
		bool Numerico(string texto);
		bool Operador(string Operador);
};

