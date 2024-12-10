#include <iostream>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include "Compilador.h";
#include "Interpretador.h";
#include <vector>
#include "Operacoes.h";
#include "Padronizar.h";

using namespace std;

unordered_map <string, string> Declaracoes::Constantes;
unordered_map <string, string> Declaracoes::Variaveis;


void Compilador::Leitura(const char* ArquivoNome)
{
        FILE* PonteiroArquivo = nullptr;
        Interpretador CompilacaoInterpretar;
        errno_t err = fopen_s(&PonteiroArquivo, ArquivoNome, "r");

        if (err != 0 || PonteiroArquivo == nullptr) 
        {
            cerr << "Erro ao abrir o arquivo!" << endl;
            return;
        }

        fseek(PonteiroArquivo, 0, SEEK_END);
        long Tamanho = ftell(PonteiroArquivo);
        fseek(PonteiroArquivo, 0, SEEK_SET); 
        
        char* buffer = new char[Tamanho + 1];

        size_t bytes_leitura = fread(buffer, 1, Tamanho, PonteiroArquivo);

        buffer[bytes_leitura] = '\0';

        string resultado = "";

        for (int i = 0; i < Tamanho; i++)
        {
            if (buffer[i] == '"' || buffer[i] == '\'') {
                resultado += buffer[i];
                while (true) {
                    i++;
                    if (buffer[i] == '"' || buffer[i] == '\'') break;
                    resultado += buffer[i];
                }
            }

            if (buffer[i] != ' ' and buffer[i] != '\n')
            {
                resultado += buffer[i];
            }
            else
            {
                resultado += '|';
            }
        }

        vector <string> ResultadoInterpretado = CompilacaoInterpretar.OperacaoInterpretada(resultado);
        vector <string> ResultadoConvertido = CompilacaoInterpretar.Conversor(ResultadoInterpretado);
        Compilador::Executor(ResultadoConvertido, ResultadoInterpretado);

        delete[] buffer;

        fclose(PonteiroArquivo);
}

void Compilador::Executor(vector<string> Executavel, vector<string> Conteudo)
{
    const size_t TamanhoVector = Executavel.size();
    bool declaracaoConst = false; bool declaracaoVar = false;
    bool declaracaoConstValue = false; bool declaracaVarValue = false;
    string declaracaoNome;
    string auxiliar;

    Lexico l;
    Padronizar p;

    for (int i = 0; i < TamanhoVector; i++)
    {
        if (Executavel[i] == "constant")
        {
            declaracaoConst = true;
        }
        else if (declaracaoConst)
        {
            declaracaoNome = Conteudo[i];
            declaracaoConst = false;
            declaracaoConstValue = true;
        }
        else if (declaracaoConstValue and true)
        {
            if (Executavel[i] != "operator")
            {

                if (Executavel[i] == "string")
                {
                    Declaracoes::Constantes[declaracaoNome] = p.PadraoString(Conteudo[i]);
                }
                else
                {
                    Declaracoes::Constantes[declaracaoNome] = Conteudo[i];
                }

                declaracaoConstValue = false;
            }
            else if (Executavel[i] == "var")
            {
                declaracaoVar = true;
            }
            else if (declaracaoVar)
            {
                declaracaoNome = Conteudo[i];
                declaracaoVar = false;
                declaracaVarValue = true;
            }
            else if (declaracaVarValue and true)
            {
                if (Executavel[i] != "operator")
                {
                    if (Executavel[i] == "string")
                    {
                        Declaracoes::Variaveis[declaracaoNome] = p.PadraoString(Conteudo[i]);
                    }
                    else
                    {
                        Declaracoes::Variaveis[declaracaoNome] = Conteudo[i];
                    }
                }
            }
            else if (Conteudo[i] != "=")
            {
                cerr << "Erro no operador: \"" << Conteudo[i] << "\" esperado \"=\"";
                break;
            }
        }

        else if (Conteudo[i] == "print")
        {
            if (i + 2 > TamanhoVector or i + 1 > TamanhoVector)
            {
                cerr << "Erro nos parametros: parametros nao declarados";
                break;
            }

            if (Conteudo[i + 1] != l.OperadorSaida)
            {
                cerr << "Erro nos operadores: \"" << Conteudo[i + 1] << "\" esperado \"<<\"";
                break;
            }

            if (Executavel[i + 2] != "ref") cout << p.PadraoString(Conteudo[i + 2]);
            else if (Declaracoes::Constantes.count(Conteudo[i + 2])) cout << Declaracoes::Constantes[Conteudo[i + 2]];
            else if (Declaracoes::Variaveis.count(Conteudo[i + 2])) cout << Declaracoes::Variaveis[Conteudo[i + 2]];
        }

        else if (Conteudo[i] == "input")
        {
            if (i + 2 > TamanhoVector or i + 1 > TamanhoVector)
            {
                cerr << "Erro nos parametros: parametros nao declarados";
                break;
            }

            if (Conteudo[i + 1] != l.OperadorEntrada)
            {
                cerr << "Erro nos operadores: \"" << Conteudo[i + 1] << "\" esperado \">>\"";
                break;
            }

            if (Declaracoes::Variaveis.count(Conteudo[i + 2]) and Executavel[i] != "ref")
            {
                cerr << "Erro ao passar valores: \"" << Executavel[i] << "\" esperado \"var\"";
                break;
            }

            cin >> auxiliar;
            Declaracoes::Variaveis[Conteudo[i + 2]] = auxiliar;
        }
        else if (Conteudo[i] == "line")
        {
            cout << endl;
        }
        else if (Conteudo[i] == "clean") {
            system("cls");
        }
    } 

    return;
}