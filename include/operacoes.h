/**
* @file 	operacoes.h
* @brief	Arquivo cabeçalho com a definição de funções para operações no vetor de stats
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    10/04/2017
* @date     10/04/2017
*/

#ifndef OPERACOES_H
    #define OPERACOES_H

    #include <cmath>

    #include "stats.h"

    /**
    * @brief    	Função que calcula os maiores valores de cada elemento de um vetor stats
    * @param[in] 	*dados Vetor com os dados
    * @param[in]    elementos Quantidade de elementos no vetor
    * @param[in]    ano Procurar o maior valor dentro de um dado ano. Passar 0 para comparar todos os anos
    * @return    	Vetor de inteiros com os maiores valores
    */
    int* max(Stats *dados, int elementos, int ano = 0);

    /**
    * @brief    	Função que calcula os menores valores de cada elemento de um vetor stats
    * @param[in] 	*dados Vetor com os dados
    * @param[in]    elementos Quantidade de elementos no vetor
    * @param[in]    ano Procurar o menor valor dentro de um dado ano. Passar 0 para comparar todos os anos
    * @return    	Vetor de inteiros com os menores valores
    */
    int* min(Stats *dados, int elementos, int ano = 0);

    /**
    * @brief    	Função que calcula os valores médios de cada elemento de um vetor stats
    * @param[in] 	*dados Vetor com os dados
    * @param[in]    elementos Quantidade de elementos no vetor
    * @param[in]    ano Calcular o valor médio dentro de um dado ano. Passar 0 para calcular todos os anos
    * @return    	Vetor de inteiros com os valoes médios
    */
    float* avg(Stats *dados, int elementos, int ano = 0);

    /**
    * @brief    	Função que calcula os valores de desvio padrão  de cada ano
    * @param[in] 	*dados Vetor com os dados
    * @param[in]    elementos Quantidade de elementos no vetor
    * @param[in]    ano Calcular o desvio padrão dentro de um dado ano. Passar 0 para calcular todos os anos
    * @return    	Vetor de inteiros com os valores de desvio padrão 
    */
    float* dev(Stats *dados, int elementos, int ano = 0);

    /**
    * @brief    	Função que calcula os valores totais de cada ano
    * @param[in] 	*dados Vetor com os dados
    * @param[in]    elementos Quantidade de elementos no vetor
    * @param[in]    ano Calcular o valor total dentro de um dado ano. Passar 0 para calcular todos os anos
    * @return    	Vetor de inteiros com os valoes totais
    */
    int* sum(Stats *dados, int elementos, int ano = 0);

    /**
    * @brief    	Função que calcula a menor taxa de crescimento entre dois anos
    * @param[in] 	*dados Vetor com os dados
    * @param[in]    elementos Quantidade de elementos no vetor
    * @param[in]    ano1 Um dos anos de referência
    * @param[in]    ano2 Um dos anos de referência
    * @param[out]   tc Estrutura Taxa com os dados da menor taxa de crescimento
    * @return    	Retorna true se não houve erro
    */
    bool minTc(Stats *dados, int elementos, int ano1, int ano2, Taxa &tc);

    /**
    * @brief    	Função que calcula a maior taxa de crescimento entre dois anos
    * @param[in] 	*dados Vetor com os dados
    * @param[in]    elementos Quantidade de elementos no vetor
    * @param[in]    ano1 Um dos anos de referência
    * @param[in]    ano2 Um dos anos de referência
    * @param[out]   tc Estrutura Taxa com os dados da maior taxa de crescimento
    * @return    	Retorna true se não houve erro
    */
    bool maxTc(Stats *dados, int elementos, int ano1, int ano2, Taxa &tc);

    /**
    * @brief    	Função que calcula a taxa de crescimento percentual entre dois valores
    * @param[in]    valor1 Primeiro valor
    * @param[in]    valor2 Segundo valor
    * @return    	Retorna o valor da taxa de crescimento percentual
    */
    float tcPerc(int valor1, int valor2);

#endif