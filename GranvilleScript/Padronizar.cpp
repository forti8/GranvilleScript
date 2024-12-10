#include "Padronizar.h";
#include <iostream>

using namespace std;

string Padronizar::PadraoString(string texto)
{
	string textoReformatado = "";

	for (int i = 1; i < texto.size() - 1; i++)
	{
		textoReformatado += texto[i];
	}

	return textoReformatado;
}