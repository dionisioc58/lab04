/**
* @file 	arquivos.h
* @brief	Arquivo de cabeçalho com a definição de funções para a gravação de arquivos
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    10/04/2017
* @date     10/04/2017
*/

#ifndef ARQUIVOS_H
    #define ARQUIVOS_H

    #include <iostream>
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::stringstream;

    #include <sstream>

    #include <fstream>
    using std::ifstream;
    using std::ofstream;

    #include "definicoes.h"
    #include "stats.h"
    #include "operacoes.h"

    /*! Opções para as colunas */
    enum Colunas {
        colAll = 0, /*!< Todas */
        colTot = 1 /*!< Total */
    };

    /**
    * @brief     	Função que abre o arquivo de dados
    * @param[in] 	nome String com o caminho/nome do arquivo à ler
    * @return    	Retorna a quantidade de linhas no arquivo ou -1 em caso de erro 
    */
    int testFile(string nome);

    /**
    * @brief     	Função que carrega o arquivo de dados
    * @param[in] 	nome String com o caminho/nome do arquivo à ler
    * @param[out]   dados Vetor de Stats com os dados lidos do arquivo
    * @param[in]    linhas Número de linhas de dados no arquivo
    * @param[out]   *msg Mensagem de retorno
    * @return    	Retorna mensagem com o resultado da operação 
    */
    bool loadFile(string nome, Stats *dados, int linhas, string& msg);

    /**
    * @brief     	Função que grava as estatísticas em arquivo
    * @param[in] 	nome String com o caminho/nome do arquivo à gravar
    * @param[in]	*dados Vetor de Stats com os dados
    * @param[in]	elementos Número de elementos no vetor
    * @param[in]	sep Separador dos campos no arquivo
    * @param[in]    cols Colunas à gravar no arquivo
    * @return    	Retorna true se gravou e false caso haja erro
    */
    bool gravaEstat(string nome, Stats *dados, int elementos, string sep, Colunas cols);

    /**
    * @brief     	Função que carrega o arquivo de alvos
    * @param[in] 	nome String com o caminho/nome do arquivo à ler
    * @param[in]    *dados Vetor de Stats com os dados completos
    * @param[in]    qtde_dados Número de linhas de dados no arquivo
    * @param[out]   *alvos Vetor de Stats com os alvos lidos do arquivo
    * @param[in]    qtde_alvos Número de alvos
    * @return    	Retorna true se não houve erro 
    */
    bool loadAlvos(string nome, Stats *dados, int qtde_dados, Stats *alvos, int qtde_alvos);

    /**
    * @brief     	Função que imprime os dados selecionados
    * @param[in] 	*dados Vetor de Stats com os dados
    * @param[in]    elementos Número de dados
    */
    void imprimeDados(Stats *dados, int elementos);

    /**
    * @brief     	Função que grava as informações completas em arquivo
    * @param[in] 	nome String com o caminho/nome do arquivo à gravar
    * @param[in]	*dados Vetor de Stats com os dados
    * @param[in]	elementos Número de elementos no vetor
    * @param[in]	sep Separador dos campos no arquivo
    * @return    	Retorna true se gravou e false caso haja erro
    */
    bool gravaExtra(string nome, Stats *dados, int elementos, string sep);

    /**
    * @brief     	Função que grava o arquivo de configurações gnuplot para os alvos
    * @param[in] 	nome String com o caminho/nome do arquivo à gravar
    * @param[in]	*dados Vetor de Stats com os alvos
    * @param[in]	elementos Número de elementos no vetor
    * @param[in]	maior Maior valor na escala
    * @param[in]	menor Menor valor na escala
    * @return    	Retorna true se gravou e false caso haja erro
    */
    bool gravaGnuset(string nome, Stats *dados, int elementos, int maior, int menor);

#endif