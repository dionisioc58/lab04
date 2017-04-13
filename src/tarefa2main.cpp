/**
* @file     tarefa2main.cpp
* @brief 	Arquivo fonte para execução do projeto
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    10/04/2017
* @date     10/04/2017
* @sa       http://stackoverflow.com/questions/5907031/printing-the-correct-number-of-decimal-points-with-cout
*/

#include <iostream>
using std::cerr;
using std::endl;
using std::cout;

#include <iomanip>

#include "../include/stats.h"
#include "../include/definicoes.h"
#include "../include/operacoes.h"
#include "../include/arquivos.h"

/**
* @brief        Função principal do programa
* @param[in]	argc	Quantidade de argumentos
* @param[in]    *argv[]	Argumento com o caminho/nome do arquivo de dados a ser lido
* @return		Retorno
*/
int main(int argc, char* argv[]) {
    //Testa argumentos
    if(argc < 2) {
        cerr << COR_VERMELHO << "Argumentos inválidos!" << COR_RESET << endl;
        return 1;
    }

    //Testa arquivo
    cout << COR_VERDE << "Abrindo arquivo... " << COR_RESET;
    int linhas = testFile(argv[1]);
    if(linhas == -1) {
        cerr << COR_VERMELHO << "Erro na abertura do arquivo." << COR_RESET << endl;
        return 2;
    }
    linhas--; //Despreza o cabeçalho
    cout << COR_VERDE << linhas << " linhas de dados" << COR_RESET << endl;

    //Carrega arquivo
    cout << COR_VERDE << "Carregando o arquivo... " << COR_RESET;
    Stats *dados = new Stats[linhas];
    int retorno = 0;
    string msg = "";
    if(!loadFile(argv[1], dados, linhas, msg)) {
        cout << COR_VERMELHO << msg << COR_RESET << endl;
        delete[] dados;
        return 3;
    }
    cout << COR_VERDE << "Ok" << COR_RESET << endl;        
        
    //Grava o arquivo de estatísticas
    cout << COR_VERDE << "Gravando arquivo estatisticas.csv... " << COR_RESET;
    if(!gravaEstat("./data/estatisticas.csv", dados, (linhas -1), ";", colAll)) {
        cout << COR_VERMELHO << "Erro ao gravar" << COR_RESET << endl;
        delete[] dados;
        return 4;
    }
    cout << COR_VERDE << "Ok" << COR_RESET << endl;

    //Grava o arquivo de totais
    cout << COR_VERDE << "Gravando arquivo totais.dat... " << COR_RESET;
    if(!gravaEstat("./data/totais.dat", dados, (linhas -1), " ", colTot)) {
        cout << COR_VERMELHO << "Erro ao gravar" << COR_RESET << endl;
        delete[] dados;
        return 5;        
    }
    cout << COR_VERDE << "Ok" << COR_RESET << endl;

    //Gera histograma
    cout << COR_VERDE << "Gerando histograma... " << COR_RESET;
    int ret = system("gnuplot -e '' ./data/histograma.gnuplot");
    if(ret == 0)
        cout << COR_VERDE << "Ok" << COR_RESET << endl;
    else {
        retorno = 5;
        cout << COR_VERMELHO << "Erro ao gerar" << COR_RESET << endl;
    }

    //Calcula menor taxa de crescimento
    int ano1 = 2013, ano2 = 2014;
    Taxa tq;
    if(minTc(dados, linhas, ano1, ano2, tq)) {
        cout << COR_VERDE << "Município com maior taxa de queda " << ano1 << "-" << ano2 << ": " << COR_RESET;
        cout << std::fixed << std::setprecision(2);
        cout << COR_VERDE << tq.nome << "(" << tq.taxa << "%)" << COR_RESET << endl;
    } else
        cout << COR_VERMELHO << "Erro ao calcular taxa de queda" << COR_RESET << endl;

    //Calcular maior taxa de crescimento
    if(maxTc(dados, linhas, ano1, ano2, tq)) {
        cout << COR_VERDE << "Município com maior taxa de crescimento " << ano1 << "-" << ano2 << ": " << COR_RESET;
        cout << std::fixed << std::setprecision(2);
        cout << COR_VERDE << tq.nome << "(" << tq.taxa << "%)" << COR_RESET << endl;
    } else
        cout << COR_VERMELHO << "Erro ao calcular taxa de crescimento" << COR_RESET << endl;
    
    delete[] dados;

    return retorno;
}