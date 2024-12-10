#include "Interpretador.h";
#include <iostream>
#include <typeinfo>
#include <vector>
#include <sstream>
#include "Operacoes.h";

using namespace std;
vector<string> Interpretador::OperacaoInterpretada(string texto)
{
	vector <string> saida;
	istringstream f(texto);
	string s;
	
	while (getline(f, s, '|'))
	{
		saida.push_back(s);
	}

	return saida;
}

string Interpretador::Tipagem(string texto,string anterior)
{
	Lexico Lex;
	bool condicaoStringA = (texto.find_first_of("\"") == 0 and texto.find_last_of("\"") == texto.length() - 1);
	bool condicaoStringB = (texto.find_first_of("\'") == 0 and texto.find_last_of("\'") == texto.length() - 1);

	if (texto == "and" or texto == "or") return "logicOperator";
	else if (texto == "const") return "constant";
	else if (Interpretador::Numerico(texto)) return "number";
	else if (Interpretador::Operador(texto)) return "operator";
	else if (condicaoStringA or condicaoStringB) return "string";
	else if (texto == "var") return "var";

	if (anterior == "const" and !(condicaoStringA or condicaoStringB)) return "constantName";
	else if (anterior == "var" and !(condicaoStringA or condicaoStringB)) return "varName";

	return "ref";
}

bool Interpretador::Numerico(string texto)
{
	stringstream ss(texto);
	double d;
	ss >> d;

	return ss.eof() && !ss.fail();
}

bool Interpretador::Operador(string Operador)
{
	Lexico L;
	if (Operador.size() > 1) {
		if (Operador == L.OperadorAutoEncremento) return true;
		else if (Operador == L.OperadorAutoDecremento) return true;
		else if (Operador == L.OperadorExponenciacao) return true;
		else if (Operador == L.OperadorComparacaoIgual) return true;
		else if (Operador == L.OperadorComperacaoDiferente) return true;
		else if (Operador == L.OperadorSaida) return true;
	}

	char OperadorChar = Operador[0];

	switch (OperadorChar) {
	case L.OperadorAdicao:
		return true;
	break;

	case L.OperadorSubtracao:
		return true;
	break;

	case L.OperadorMultiplicacao:
		return true;
	break;

	case L.OperadorDivisao:
		return true;
	break;

	case L.OperadorAtribuicao:
		return true;
	break;

	default:
		return false;
	break;
	}
}

vector<string> Interpretador::Conversor(vector <string> TextoSeparado)
{
	size_t TamanhoVector = TextoSeparado.size();
	vector <string> Resultado;
	string auxiliar = "";
	string a = "";

	for (int i = 0; i < TamanhoVector; i++) {
		a = Tipagem(TextoSeparado[i], auxiliar);
		Resultado.push_back(a);
		auxiliar = TextoSeparado[i];
	}

	return Resultado;
}
