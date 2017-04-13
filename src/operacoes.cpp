/**
* @file 	operacoes.cpp
* @brief	Arquivo de corpo com as funções para operações no vetor de stats
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    10/04/2017
* @date     10/04/2017
*/

#include "../include/operacoes.h"

/**
* @brief    	Função que calcula os maiores valores de cada elemento de um vetor stats
* @param[in] 	*dados Vetor com os dados
* @param[in]    elementos Quantidade de elementos no vetor
* @param[in]    ano Calcular o maior valor dentro de um dado ano. Passar 0 para calcular todos os anos
* @return    	Vetor de inteiros com os maiores valores
*/
int* max(Stats *dados, int elementos, int ano) {
    static int retorno[21];
    for(int i = 0; i < 21; i++)
        retorno[i] = 0;
    if(ano == 0) {
        for(int j = 0; j < 21; j++)
            for(int i = 0; i < (elementos - 1); i++)
                if(dados[i].nascimentos[j] > retorno[j])
                    retorno[j] = dados[i].nascimentos[j];
    } else { //Compara apenas o ano solicitado
        for(int i = 0; i < (elementos - 1); i++)
            if(dados[i].nascimentos[ano] > retorno[ano])
                retorno[ano] = dados[i].nascimentos[ano];
    }
    return retorno;
}

/**
* @brief    	Função que calcula os menores valores de cada elemento de um vetor stats
* @param[in] 	*dados Vetor com os dados
* @param[in]    elementos Quantidade de elementos no vetor
* @param[in]    ano Calcular o menor valor dentro de um dado ano. Passar 0 para calcular todos os anos
* @return    	Vetor de inteiros com os menores valores
*/
int* min(Stats *dados, int elementos, int ano) {
    static int retorno[21];
    for(int i = 0; i < 21; i++)
        retorno[i] = 0;
    if(ano == 0) {
        for(int j = 0; j < 21; j++) {
            retorno[j] = dados[0].nascimentos[ano];
            for(int i = 1; i < (elementos - 1); i++)
                if(dados[i].nascimentos[j] < retorno[j])
                    retorno[j] = dados[i].nascimentos[j];
        }
    } else { //Compara apenas o ano solicitado
        retorno[ano] += dados[0].nascimentos[ano];
        for(int i = 1; i < (elementos - 1); i++)
            if(dados[i].nascimentos[ano] < retorno[ano])
                retorno[ano] = dados[i].nascimentos[ano];
    }
    return retorno;
}

/**
* @brief    	Função que calcula os valores médios de cada elemento de um vetor stats
* @param[in] 	*dados Vetor com os dados
* @param[in]    elementos Quantidade de elementos no vetor
* @param[in]    ano Calcular o valor médio dentro de um dado ano. Passar 0 para calcular todos os anos
* @return    	Vetor de inteiros com os valores médios
*/
float* avg(Stats *dados, int elementos, int ano) {
    static float retorno[21];
    for(int i = 0; i < 21; i++)
        retorno[i] = 0;
    if(ano == 0) {
        for(int j = 0; j < 21; j++) {
            for(int mun = 0; mun < elementos; mun++)
                retorno[j] += dados[mun].nascimentos[j];
            retorno[j] /= elementos;
        }
    } else { //Compara apenas o ano solicitado
        for(int mun = 0; mun < elementos; mun++)
            retorno[ano] += dados[mun].nascimentos[ano];
        retorno[ano] /= elementos;
    }
    return retorno;
}

/**
* @brief    	Função que calcula os valores de desvio padrão  de cada ano
* @param[in] 	*dados Vetor com os dados
* @param[in]    elementos Quantidade de elementos no vetor
* @param[in]    ano Calcular o desvio padrão dentro de um dado ano. Passar 0 para calcular todos os anos
* @return    	Vetor de inteiros com os valores de desvio padrão 
*/
float* dev(Stats *dados, int elementos, int ano) {
    static float retorno[21];
    for(int i = 0; i < 21; i++)
        retorno[i] = 0;
    for(int ano = 0; ano < 21; ano++) {
        for(int mun = 0; mun < (elementos -1); mun++)
            retorno[ano] += pow((dados[mun].nascimentos[ano] - avg(dados, elementos)[ano]), 2);//somatório de: (Valor do município no ano - média do ano) ^ 2
        retorno[ano] = sqrt(retorno[ano] * (((float)1 / (elementos - 1))));
    }
    return retorno;
}

/**
* @brief    	Função que calcula os valores totais de cada ano
* @param[in] 	*dados Vetor com os dados
* @param[in]    elementos Quantidade de elementos no vetor
* @param[in]    ano Calcular o valor total dentro de um dado ano. Passar 0 para calcular todos os anos
* @return    	Vetor de inteiros com os valores totais
*/
int* sum(Stats *dados, int elementos, int ano) {
    static int retorno[21];
    for(int i = 0; i < 21; i++)
        retorno[i] = 0;
    if(ano == 0) {
        for(int j = 0; j < 21; j++) {
            for(int mun = 0; mun < elementos; mun++)
                retorno[j] += dados[mun].nascimentos[j];
        }
    } else { //Compara apenas o ano solicitado
        for(int mun = 0; mun < elementos; mun++)
            retorno[ano] += dados[mun].nascimentos[ano];
    }
    return retorno;
}

/**
* @brief    	Função que calcula a menor taxa de crescimento entre dois anos
* @param[in] 	*dados Vetor com os dados
* @param[in]    elementos Quantidade de elementos no vetor
* @param[in]    ano1 Um dos anos de referência
* @param[in]    ano2 Um dos anos de referência
* @param[out]   tc Estrutura Taxa com os dados da menor taxa de crescimento
* @return    	Retorna true se não houve erro
*/
bool minTc(Stats *dados, int elementos, int ano1, int ano2, Taxa &tc) {
    ano1 -=1994;
    ano2 -=1994;
    if(ano2 < ano1) return false;
    if((ano1 < 0) || (ano2 > 20)) return false;
    
    tc.codigo = dados[0].codigo;
    tc.nome   = dados[0].nome;
    tc.taxa   = tcPerc(dados[0].nascimentos[ano1], dados[0].nascimentos[ano2]);
    for(int i = 1; i < (elementos - 1); i++) {
        float taxa = tcPerc(dados[i].nascimentos[ano1], dados[i].nascimentos[ano2]);
        if(taxa < tc.taxa) {
            tc.codigo = dados[i].codigo;
            tc.nome   = dados[i].nome;
            tc.taxa   = taxa;
        }
    }

    return true;
}

/**
* @brief    	Função que calcula a maior taxa de crescimento entre dois anos
* @param[in] 	*dados Vetor com os dados
* @param[in]    elementos Quantidade de elementos no vetor
* @param[in]    ano1 Um dos anos de referência
* @param[in]    ano2 Um dos anos de referência
* @param[out]   tc Estrutura Taxa com os dados da maior taxa de crescimento
* @return    	Retorna true se não houve erro
*/
bool maxTc(Stats *dados, int elementos, int ano1, int ano2, Taxa &tc) {
    ano1 -=1994;
    ano2 -=1994;
    if(ano2 < ano1) return false;
    if((ano1 < 0) || (ano2 > 20)) return false;
    
    tc.codigo = dados[0].codigo;
    tc.nome   = dados[0].nome;
    tc.taxa   = tcPerc(dados[0].nascimentos[ano1], dados[0].nascimentos[ano2]);
    for(int i = 1; i < (elementos - 1); i++) {
        float taxa = tcPerc(dados[i].nascimentos[ano1], dados[i].nascimentos[ano2]);
        if(taxa > tc.taxa) {
            tc.codigo = dados[i].codigo;
            tc.nome   = dados[i].nome;
            tc.taxa   = taxa;
        }
    }

    return true;
}

/**
* @brief    	Função que calcula a taxa de crescimento percentual entre dois valores
* @param[in]    valor1 Primeiro valor
* @param[in]    valor2 Segundo valor
* @return    	Retorna o valor da taxa de crescimento percentual
*/
float tcPerc(int valor1, int valor2) {
    float ret = (float)valor2 / valor1;
    ret = (ret - 1) * 100;
    return ret;
}