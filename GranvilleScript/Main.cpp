#include <iostream>
#include "Operacoes.h";
#include "Interpretador.h";
#include "Compilador.h";
#include "Padronizar.h";

using namespace std;
int main(int argc, char* argv[])
{
	Compilador Compiler;
	Padronizar P;
	Compiler.Leitura("Main.grs");

	cout << endl;
	system("pause");
	
	return 0;
}