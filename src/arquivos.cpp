/**
* @file 	arquivos.cpp
* @brief	Arquivo de corpo com a definição de funções para a gravação de arquivos
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    10/04/2017
* @date     10/04/2017
*/

#include "../include/arquivos.h"

/**
* @brief     	Função que abre o arquivo de dados e testa
* @param[in] 	nome String com o caminho/nome do arquivo à ler
* @return    	Retorna a quantidade de linhas no arquivo ou -1 em caso de erro
*/
int testFile(string nome) {
    ifstream entrada(nome);
    if(!entrada)
        return -1; //Falha ao abrir o arquivo
    
    int linhas = 0;
    string lido = "";
    while(!entrada.eof()) {//Conta as linhas do arquivo
        getline(entrada, lido);
        if(lido != "")
            linhas++;
    }
    entrada.close();
    return linhas;
}

/**
* @brief     	Função que carrega o arquivo de dados
* @param[in] 	nome String com o caminho/nome do arquivo à ler
* @param[out]   dados Vetor de Stats com os dados lidos do arquivo
* @param[in]    linhas Número de linhas de dados no arquivo
* @param[out]   *msg Mensagem de retorno
* @return    	Retorna mensagem com o resultado da operação 
*/
bool loadFile(string nome, Stats *dados, int linhas, string& msg) {
    ifstream entrada(nome);
    if(!entrada) {
        msg = "Erro na abertura do arquivo"; //Falha ao abrir o arquivo
        return false;
    }

    msg = "Ok";
    string lido = "";
    entrada.clear();
    entrada.seekg(0);
    getline(entrada, lido);//Descarta a primeira linha (cabeçalho)

    stringstream sa;
    int total_l, teste;//Para verificação de consistência
    for(int i = 0; i < (linhas - 1); i++) {//Lê o arquivo até antes da linha do total
        getline(entrada, lido, '\"');//Descarta a primeira
        getline(entrada, dados[i].codigo, ' ');//Lê o código
        getline(entrada, dados[i].nome, '\"');//Lê o nome
        getline(entrada, lido, ';');//Descarta a leitura do ;
        total_l = 0;
        for(int j = 0; j < 21; j++) {
            sa.clear();
            getline(entrada, lido, ';');
            sa << lido;
            sa >> dados[i].nascimentos[j];
            total_l += dados[i].nascimentos[j];
        }
        //Lê a última coluna (não tem separador)
        getline(entrada, lido);
        sa.clear();
        sa << lido;
        sa >> teste;
        if(total_l != teste) {//Testa se o total somado é igual ao total da linha no arquivo
            msg = "Inconsistência no total da linha ";
            sa.clear();
            sa << (i + 2);//i+2 porque i é zero-based e tem o cabeçalho
            string msg2;
            sa >> msg2;
            msg = msg + msg2;
            break;
        }
    }

    if(msg == "Ok") {
        //Testa consistência dos totais das colunas (última linha)
        int total_c, teste;
        getline(entrada, lido, ';');//Ignora a primeira coluna
        for(int i = 0; i < 21; i++) {//Lê todas as colunas da última linha (totais) e confere
            sa.clear();
            getline(entrada, lido, ';');
            sa << lido;
            sa >> teste;
            total_c = 0;
            for(int j = 0; j < (linhas - 1); j++)
                total_c += dados[j].nascimentos[i];
            if(total_c != teste) {
                msg = "Inconsistência no total da coluna ";
                sa.clear();
                sa << (i + 1);
                string msg2;
                sa >> msg2;
                msg = msg + msg2;
                break;
            }
        }
    }

    entrada.close();
    if(msg == "Ok")
        return true;
    return false;
}

/**
* @brief     	Função que grava as estatísticas em arquivo
* @param[in] 	nome String com o caminho/nome do arquivo à gravar
* @param[in]	*dados Vetor de Stats com os dados
* @param[in]	elementos Número de elementos no vetor
* @param[in]	sep Separador dos campos no arquivo
* @param[in]    cols Colunas à gravar no arquivo
* @return    	Retorna true se gravou e false caso haja erro
*/
bool gravaEstat(string nome, Stats *dados, int elementos, string sep, Colunas cols) {
    ofstream saida(nome);
    if(!saida) return false; //Testa se arquivo foi aberto

    //Captura as estatísticas
    int *maior    = max(dados, elementos);
    int *menor    = min(dados, elementos);
    float *media  = avg(dados, elementos);
    float *desvio = dev(dados, elementos);
    int *total    = sum(dados, elementos);

    //Grava as estatísticas no arquivo
    if(cols == colAll) {//Exibe cabeçalho apenas para colMax
        saida << "Ano" << sep << "Máximo" << sep << "Mínimo" << sep;
        saida << "Média" << sep << "Desvio Padrão" << sep << "Total" << endl;
    }
    for(int ano = 0; ano < 21; ano++) {
        saida << (1994 + ano) << sep;
        switch(cols) {
            case colAll:
                saida << maior[ano] << sep; 
                saida << menor[ano] << sep;
                saida << media[ano] << sep;
                saida << desvio[ano] << sep;
                saida << total[ano];
                break;
            case colTot:
                saida << total[ano] << sep;
                break;
            //TODO - Implementar diversas composições de colunas
        }
        saida << endl;
    }

    saida.close(); //Fecha o arquivo
	return true;
}

/**
* @brief     	Função que carrega o arquivo de alvos
* @param[in] 	nome String com o caminho/nome do arquivo à ler
* @param[in]    *dados Vetor de Stats com os dados completos
* @param[in]    qtde_dados Número de linhas de dados no arquivo
* @param[out]   *alvos Vetor de Stats com os alvos lidos do arquivo
* @param[in]    qtde_alvos Número de alvos
* @return    	Retorna true se não houve erro 
*/
bool loadAlvos(string nome, Stats *dados, int qtde_dados, Stats *alvos, int qtde_alvos) {
    ifstream entrada(nome);
    if(!entrada)
        return false;

    entrada.clear();
    entrada.seekg(0);
    for(int i = 0; i < qtde_alvos; i++) {
        getline(entrada, alvos[i].codigo);
        for(int j = 0; j < qtde_dados; j++)
            if(alvos[i].codigo == dados[j].codigo) {//Se existe, copia as informações de dados para alvos
                alvos[i].nome = dados[j].nome;
                for(int k = 0; k < 21; k++)
                    alvos[i].nascimentos[k] = dados[j].nascimentos[k];
            }
    }
    return true;
}

/**
* @brief     	Função que imprime os dados selecionados
* @param[in] 	*dados Vetor de Stats com os dados
* @param[in]    elementos Número de dados
*/
void imprimeDados(Stats *dados, int elementos) {
    for(int i = 0; i < elementos; i++)
        cout << COR_VERDE << "......{ " << dados[i].nome << " }" << COR_RESET << endl;
}

/**
* @brief     	Função que grava as informações completas em arquivo
* @param[in] 	nome String com o caminho/nome do arquivo à gravar
* @param[in]	*dados Vetor de Stats com os dados
* @param[in]	elementos Número de elementos no vetor
* @param[in]	sep Separador dos campos no arquivo
* @return    	Retorna true se gravou e false caso haja erro
*/
bool gravaExtra(string nome, Stats *dados, int elementos, string sep) {
    ofstream saida(nome);
    if(!saida) return false; //Testa se arquivo foi aberto

    //Grava as estatísticas no arquivo
    float percentual;
    int menor = 0, maior = 0;
    for(int ano = 1; ano < 21; ano++) {
        saida << (ano + 1994) << sep;
        for(int mun = 0; mun < (elementos - 1); mun++) {//Até o penúltimo com o separador
            percentual = tcPerc(dados[mun].nascimentos[ano], dados[mun].nascimentos[ano - 1]);
            saida << percentual << sep;
            if(percentual > maior) maior = (int)percentual;
            if(percentual < menor) menor = (int)percentual;
        }
        saida << tcPerc(dados[elementos - 1].nascimentos[ano], dados[elementos - 1].nascimentos[ano - 1]) << endl;//Último fica sem o separador
    }
    saida.close(); //Fecha o arquivo

    //Grava arquivo de configurações do gnuplot
    return gravaGnuset("./data/extra.gnuplot", dados, elementos, maior, menor);
}

/**
* @brief     	Função que grava o arquivo de configurações gnuplot para os alvos
* @param[in] 	nome String com o caminho/nome do arquivo à gravar
* @param[in]	*dados Vetor de Stats com os alvos
* @param[in]	elementos Número de elementos no vetor
* @param[in]	maior Maior valor na escala
* @param[in]	menor Menor valor na escala
* @return    	Retorna true se gravou e false caso haja erro
*/
bool gravaGnuset(string nome, Stats *dados, int elementos, int maior, int menor) {
    ofstream saida(nome);
    if(!saida) return false; //Testa se arquivo foi aberto
    saida << "reset" << endl;
    saida << "set key on" << endl;
    saida << "set grid" << endl;
    saida << "set terminal png size 640,480 enhanced font 'Helvetica,12'" << endl;
    saida << "set output './data/extra.png'" << endl;
    saida << "set title 'Taxa de crescimento por ano no RN (1994-2014) (filtrado)'" << endl;
    saida << "set xrange[1994:2014]" << endl;
    saida << "set xtics 1" << endl;
    saida << "set xtic rotate by -90 scale 0" << endl;
    saida << "set ytic 20" << endl;
    saida << "set xlabel 'Anos'" << endl;
    saida << "set ylabel 'Taxa de crescimento (%)'" << endl;
    stringstream sa;
    string num;
    saida << "set yrange[";
    saida << (menor - 2);//-2 Para dar espaço (melhor visualização)
    saida << ":";
    saida << (maior + 2);//+2 Para dar espaço (melhor visualização)
    saida << "]" << endl;
    saida << "plot ";
    for(int i = 0; i < elementos; i++) {
        sa.clear();
        sa << (i + 2);
        sa >> num;
        saida << "'./data/extra.dat' using 1:" + num + " title '" + dados[i].nome + "' lw 2 with lines, ";
    }
    saida << endl;
    return true;
}