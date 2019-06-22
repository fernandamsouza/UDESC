#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"

int main(int argc, char *argv[]){
	if (argc <3) {
		help();
	} else {
	if(strcmp(argv[1],"transpo")==0) {
		if (argc !=4) {
		help();
		} else {
			escreve(argv[3],transposta(leitura(argv[2])));
		}
	}
	if(strcmp(argv[1],"soma")==0) {
		if (argc !=5) {
		help();
		} else {
			escreve(argv[4], soma(leitura(argv[2]),leitura(argv[3])));
		}
	}
	
	if(strcmp(argv[1],"sub")==0) {
		if (argc!=5) {
		help();
		} else {
			escreve(argv[4],subtracao(leitura(argv[2]),leitura(argv[3])));
		}
	}
	
	if(strcmp(argv[1],"multi")==0) {
		if (argc!= 5) {
		help();
		} else {
			escreve(argv[4],multiplicacao(leitura(argv[2]),leitura(argv[3])));
		}
	}
	
	if(strcmp(argv[1],"multiesc")==0) {
		if (argc != 5) {
			help();
		} else {
			escreve(argv[4],multiplicacao_escalar(leitura(argv[2]),inteiro(argv[3])));	
		}
	}
	
	if(strcmp(argv[1],"iguais")==0) {
		if (argc != 4) {
			help();
		} else {
			iguais(leitura(argv[2]),leitura(argv[3]));	
		}
	}
	
	if(strcmp(argv[1],"simetrica")==0) {
		if (argc!= 3) {
			help();
		} else {
			simetrica(leitura(argv[2]));
		}
	}
	}
	return 0;
}
