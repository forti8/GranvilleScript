#include <iostream>
#include <vector>

using namespace std;

class Lexico
{
private:

public:
	static const char OperadorAdicao = '+';
	static const char OperadorSubtracao = '-';
	static const char OperadorDivisao = '/';
	static const char OperadorMultiplicacao = '*';
	static const char OperadorAtribuicao = '=';

	string AlfabetoNumerico = "0123456789";
	string Alfabeto = "abcdefghijklmnopqrstuvwxyz";

	const vector <string> TiposNativos = { "int" };
	const vector <string> PalavrasReservadas = {"const", "print"};
	const string OperadorAutoEncremento = "++"; // variavel + 1;
	const string OperadorAutoDecremento = "--"; // varievel - 1;
	const string OperadorExponenciacao = "**"; // variavel * variavel;
	const string OperadorComparacaoIgual = "==";
	const string OperadorSaida = "<<";
	const string OperadorEntrada = ">>";

	const string OperadorComperacaoDiferente = "!=";

	float OperacoesAritimeticas(char operador, float a, float b);
	float OperacoesAuto(string operador, float x, int b = 0);
};