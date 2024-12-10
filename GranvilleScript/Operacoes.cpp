#include "Operacoes.h";
#include <iostream>

using namespace std;


float Lexico::OperacoesAritimeticas(char operador, float a, float b) 
{
	switch (operador)
	{
	case Lexico::OperadorAdicao:
		return a + b;
	break;

	case Lexico::OperadorSubtracao:
		return a - b;
	break;

	case Lexico::OperadorMultiplicacao:
		return a * b;
	break;

	case Lexico::OperadorDivisao:
		if (b == 0)
			return NAN;
		return a / b;
	break;

	default:
		return 0.0f;
	break;
	}
}

float Lexico::OperacoesAuto(string operador, float x, int b)
{
	if (operador == Lexico::OperadorAutoEncremento)
		return x + 1.0f;

	else if (operador == Lexico::OperadorAutoDecremento)
		return x - 1.0f;

	else if (operador == Lexico::OperadorExponenciacao) {
		float auxiliar = x;
		for (int i = 1; i < b; i++) {
			auxiliar = auxiliar * x;
		}

		return auxiliar;
	}

	return x;
}