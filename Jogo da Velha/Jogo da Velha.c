#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define TAM 3

int menu();
void opcao(int op, char tabela[][TAM]);
void modeMulti(char tabela[][TAM]);
void jogar(char tabela[][TAM], int jogador);
void nivelFacil(char tabela[][TAM]);
void nivelMedio(char tabela[][TAM]);
int sortearPrimeiroJogador();
void jogadaMedioCPU(char tabela[][TAM], int primeiro);
int verificar(char tabela[][TAM]);
void imprimirTabela(char tabela[][TAM]);
int ataque(char tabela[][TAM]);
int defesa(char tabela[][TAM]);
void jogaRand(char tabela[][TAM], int primeiro);
void nivelDificil(char tabela[][TAM]);
void jogadaDificilCPU(char tabela[][TAM], int primeiro, int i);
void jogadaPlanejada(char tabela[][TAM], int primeiro, int i);

int main(){
	int op, i, j;
	char tabela[TAM][TAM];

	setlocale(LC_ALL, "Portuguese");
	srand((unsigned)time(NULL));

	do{
		for (i = 0; i < TAM; i++){
			for (j = 0; j < TAM; j++){
				tabela[i][j] = '0';
			}
		}
		system("cls");
		op = menu();
		opcao(op, tabela);
	} while (op);

	printf("\n");
	system("pause");
	return 0;
}

int menu(){
	int op;

	do{
		printf("Escolha o modo de jogo:\n");
		printf("1- Multijogador\n");
		printf("2- Jogador Único\n");
		printf("0- Sair\n");
		printf("Opção: ");
		scanf("%i", &op);
	} while (op < 0 || op > 2);

	return op;
}

void opcao(int op, char tabela[][TAM]){
	int nivel;

	switch (op){
	case 1:
		printf("\n");
		modeMulti(tabela);
		system("pause");
		break;

	case 2:
		printf("\n");
		printf("Escolha o nível de jogo:\n");
		printf("1- Fácil\n2- Médio\n3- Difícil\n");
		scanf("%i", &nivel);

		switch (nivel){
		case 1:
			printf("\n");
			nivelFacil(tabela);
			system("pause");
			break;

		case 2:
			printf("\n");
			nivelMedio(tabela);
			system("pause");
			break;

		case 3:
			printf("\n");
			nivelDificil(tabela);
			system("pause");
			break;

		default:
			printf("Digite uma opção válida\n");
			system("pause");
			break;
		}
		
	case 0:
		printf("Até a próxima!\n");
		break;

	default:
		printf("Digite uma opção válida!\n");
		system("pause");
		break;
	}

}

void modeMulti(char tabela[][TAM]){
	int op, jogador, primeiro;

	printf("Escoha de quem irá começar primeiro\n");
	do{
		printf("Jogador 1 digite 1 para ímpar ou 2 para par: ");
		scanf("%i", &op);
	} while (op < 1 || op > 2);

	jogador = rand() % 2;

	if (op == 1 && jogador == 1){
		printf("\nO jogador 1 começa!\n");
		primeiro = 1;
	}
	else if(op == 2 && jogador == 0){
		printf("\nO jogador 1 começa!\n");
		primeiro = 1;
	}
	else{
		printf("\nO jogador 2 começa!\n");
		primeiro = 2;
	}
	
	jogar(tabela, primeiro);

}

void jogar(char tabela[][TAM], int jogador){
	int linha, coluna, i = 0, status;

	imprimirTabela(tabela);

	while (i <= 8){
		
		do{
			printf("Vez do Jogador %i\n", jogador);
			do{
				printf("Digite a linha em que deseja jogar:\n");
				printf("1a Linha\n2a Linha\n3a Linha\n");
				scanf("%i", &linha);
			} while (linha < 1 || linha > 3);

			do{
				printf("Digite a coluna em que deseja jogar:\n");
				printf("1a Coluna\n2a Coluna\n3a Coluna\n");
				scanf("%i", &coluna);
			} while (coluna < 1 || coluna > 3);

			if (tabela[linha - 1][coluna - 1] != '0')
				printf("A posição já está preenchida!\n");

		} while (tabela[linha - 1][coluna - 1] != '0');

		if (jogador == 1){
			tabela[linha - 1][coluna - 1] = 'O';
			jogador = 2;
		}
		else{
			tabela[linha - 1][coluna - 1] = 'X';
			jogador = 1;
		}

		imprimirTabela(tabela);

		status = verificar(tabela);

		if (status == 1){
			printf("O jogador %i venceu!\n", status);
			break;
		}
		if(status == 2){
			printf("O jogador %i venceu!\n", status);
			break;
		}
		i++;
	}

	if (i == 9 && status == 0)
		printf("O jogo terminou empatado!\n");

}

void nivelFacil(char tabela[][TAM]){
	int primeiro, linha, coluna, i = 0, status;

	primeiro = sortearPrimeiroJogador();

	imprimirTabela(tabela);

	while (i <= 8){

		if (primeiro == 1){
			do{
				printf("Vez do Jogador %i\n\n", primeiro);
				do{
					printf("Digite a linha em que deseja jogar:\n");
					printf("1a Linha\n2a Linha\n3a Linha\n");
					scanf("%i", &linha);
				} while (linha < 1 || linha > 3);

				do{
					printf("Digite a coluna em que deseja jogar:\n");
					printf("1a Coluna\n2a Coluna\n3a Coluna\n");
					scanf("%i", &coluna);
				} while (coluna < 1 || coluna > 3);

				if (tabela[linha - 1][coluna - 1] != '0')
					printf("A posição já está preenchida!\n");

			} while (tabela[linha - 1][coluna - 1] != '0');

			tabela[linha - 1][coluna - 1] = 'O';
			primeiro = 2;
		}
		else{
			printf("Vez do Computador!\n\n");
			jogaRand(tabela, primeiro);
			primeiro = 1;
		}

		imprimirTabela(tabela);

		status = verificar(tabela);
		if (status == 1){
			printf("O jogador %i venceu!\n", status);
			break;
		}
		if (status == 2){
			printf("O Computador venceu!\n", status);
			break;
		}

		i++;
	}
	if (i == 9 && status == 0)
		printf("O jogo terminou empatado!\n");
}

void nivelMedio(char tabela[][TAM]){
	int primeiro, i = 0, linha, coluna, status;

	primeiro = sortearPrimeiroJogador();

	imprimirTabela(tabela);

	while (i <= 8){

		if (primeiro == 1){
			do{
				printf("Vez do Jogador %i\n\n", primeiro);
				do{
					printf("Digite a linha em que deseja jogar:\n");
					printf("1a Linha\n2a Linha\n3a Linha\n");
					scanf("%i", &linha);
				} while (linha < 1 || linha > 3);

				do{
					printf("Digite a coluna em que deseja jogar:\n");
					printf("1a Coluna\n2a Coluna\n3a Coluna\n");
					scanf("%i", &coluna);
				} while (coluna < 1 || coluna > 3);

				if (tabela[linha - 1][coluna - 1] != '0')
					printf("A posição já está preenchida!\n");

			} while (tabela[linha - 1][coluna - 1] != '0');

			tabela[linha - 1][coluna - 1] = 'O';
			primeiro = 2;
		}
		else{
			printf("Vez do Computador!\n\n");
			jogadaMedioCPU(tabela, primeiro);
			primeiro = 1;
		}

		imprimirTabela(tabela);

		status = verificar(tabela);
		if (status == 1){
			printf("O jogador %i venceu!\n", status);
			break;
		}
		if (status == 2){
			printf("O Computador venceu!\n", status);
			break;
		}

		i++;
	}
	if (i == 9 && status == 0)
		printf("O jogo terminou empatado!\n");
}

int sortearPrimeiroJogador(){
	int primeiro, op, jogador;

	printf("Escolha de quem irá começar primeiro\n");
	do{
		printf("Jogador 1 um digite 1 para ímpar ou 2 para par: ");
		scanf("%i", &op);
	} while (op < 1 || op > 2);

	jogador = rand() % 2;

	if (op == 1 && jogador == 1){
		printf("\nO jogador 1 começa!\n");
		primeiro = 1;
	}
	else if (op == 2 && jogador == 0){
		printf("\nO jogador 1 começa!\n");
		primeiro = 1;
	}
	else{
		printf("\nO Computador começa!\n");
		primeiro = 2;
	}

	return primeiro;
}

void jogadaMedioCPU(char tabela[][TAM], int primeiro){
	int status;

	status = ataque(tabela);

	if (status == -1)
	{
		status = 0;
		status = defesa(tabela);
		if (status == -1)
		{
			jogaRand(tabela, primeiro);
		}
	}
}

int verificar(char tabela[][TAM]){
	int i, j, n, c = 0;
	char letra = 'O';
	int retorno = 1;

	while (c < 2){
		for (i = 0; i < TAM; i++){ //Verificar linhas
			n = 0;
			for (j = 0; j < TAM; j++){
				if (tabela[i][j] == letra){
					n++;
				}
			}
			if (n == 3){
				return retorno;
			}
		}

		for (j = 0; j < TAM; j++){ //Verificar colunas
			n = 0;
			for (i = 0; i < TAM; i++){
				if (tabela[i][j] == letra){
					n++;
				}
			}
			if (n == 3){
				return retorno;
			}
		}

		n = 0;
		for (i = 0; i < TAM; i++){ //Verificar diagonal principal
			if (tabela[i][i] == letra){
				n++;
			}
		}
		if (n == 3){
			return retorno;
		}

		n = 0;
		j = TAM - 1;
		for (i = 0; i < TAM; i++){ //Verificar diagonal secundária
			if (tabela[i][j] == letra){
				n++;
				j--;
			}
		}
		if (n == 3){
			return retorno;
		}

		c++;
		letra = 'X';
		retorno = 2;
	}


	return 0;
}

void imprimirTabela(char tabela[][TAM]){
	int i, j;

	printf("\n");
	for (i = 0; i < TAM; i++){
		for (j = 0; j < TAM; j++){
			printf(" %c ", tabela[i][j]);
			if (j != TAM - 1)
				printf("|");
		}
		printf("\n");
	}
	printf("\n");
}

int ataque(char tabela[][TAM])
{
	int i, j, x, o, ln, col, c;

	//Ataque
	for (i = 0; i < TAM; i++){ //possibilidade de ganho por linha
		o = 0;
		x = 0;
		for (j = 0; j < TAM; j++){
			if (tabela[i][j] == 'X'){
				x++;
			}
			else if (tabela[i][j] == 'O'){
				o++;
			}
			else{
				ln = i;
				col = j;
			}
		}
		if (x == 2 && o == 0){
			tabela[ln][col] = 'X';
			return 1;
		}
	}

	for (j = 0; j < TAM; j++){ //possibilidade de ganho por coluna
		o = 0;
		x = 0;
		for (i = 0; i < TAM; i++){
			if (tabela[i][j] == 'X'){
				x++;
			}
			else if (tabela[i][j] == 'O'){
				o++;
			}
			else{
				ln = i;
				col = j;
			}
		}
		if (x == 2 && o == 0){
			tabela[ln][col] = 'X';
			return 1;
		}
	}

	x = 0;
	ln = 0;
	for (i = 0; i < TAM; i++){ //possibilidade de ganho na diagonal principal
		if (tabela[i][i] == 'X'){
			x++;
		}
		else if (tabela[i][i] == '0'){
			ln = i;
		}
		if (x == 2 && ln != 0){
			tabela[ln][ln] = 'X';
			return 1;
		}
	}

	o = 0;
	c = TAM - 1;
	ln = 0;
	for (i = 0; i < TAM; i++){ //Possibilidade de ganho na diagonal secundária
		if (tabela[i][c] == 'X'){
			x++;
		}
		else if (tabela[i][c] == '0'){
			ln = i;
		}
		if (o == 2 && ln != 0){
			tabela[ln][ln] = 'X';
			return 1;
		}
		c--;
	}

	return -1;
}

int defesa(char tabela[][TAM])
{
	int i, j, x, o, ln, col, c;
	//Defesa
	for (i = 0; i < TAM; i++){ //Possibilidade de perda por linha
		o = 0;
		x = 0;
		for (j = 0; j < TAM; j++){
			if (tabela[i][j] == 'O'){
				o++;
			}
			else if (tabela[i][j] == 'X'){
				x++;
			}
			else{
				ln = i;
				col = j;
			}
		}
		if (o == 2 && x == 0){
			tabela[ln][col] = 'X';
			return 1;
		}
	}

	for (j = 0; j < TAM; j++){ //Possibilidade de perda por coluna
		o = 0;
		x = 0;
		for (i = 0; i < TAM; i++){
			if (tabela[i][j] == 'O'){
				o++;
			}
			else if (tabela[i][j] == 'X'){
				x++;
			}
			else{
				ln = i;
				col = j;
			}
		}
		if (o == 2 && x == 0){
			tabela[ln][col] = 'X';
			return 1;
		}
	}

	o = 0;
	ln = 0;
	for (i = 0; i < TAM; i++){ //Possibilidade de perda na diagonal principal
		if (tabela[i][i] == 'O'){
			o++;
		}
		else if (tabela[i][i] == '0'){
			ln = i;
		}
		if (o == 2 && ln != 0){
			tabela[ln][ln] = 'X';
			return 1;
		}
	}

	ln = 0;
	o = 0;
	c = TAM - 1;
	for (i = 0; i < TAM; i++){ //Possibilidade de perda na diagonal secundária
		if (tabela[i][c] == 'O'){
			o++;
		}
		else if (tabela[i][c] == '0'){
			ln = i;
		}
		if (o == 2 && ln != 0){
			tabela[ln][ln] = 'X';
			return 1;
		}
		c--;
	}

	return -1;
}

void jogaRand(char tabela[][TAM], int primeiro)
{
	int ln, col;

	do{
		ln = rand() % 3;
		col = rand() % 3;
	} while (tabela[ln][col] != '0');

	if (primeiro == 1)
	{
		tabela[ln][col] = 'O';
	}
	else
	{
		tabela[ln][col] = 'X';
	}
	
}

void nivelDificil(char tabela[][TAM]){
	int i = 0, primeiro, linha, coluna, status;

	primeiro = sortearPrimeiroJogador();

	imprimirTabela(tabela);

	while (i <= 8){

		if (primeiro == 1){
			do{
				printf("Vez do Jogador %i\n\n", primeiro);
				do{
					printf("Digite a linha em que deseja jogar:\n");
					printf("1a Linha\n2a Linha\n3a Linha\n");
					scanf("%i", &linha);
				} while (linha < 1 || linha > 3);

				do{
					printf("Digite a coluna em que deseja jogar:\n");
					printf("1a Coluna\n2a Coluna\n3a Coluna\n");
					scanf("%i", &coluna);
				} while (coluna < 1 || coluna > 3);

				if (tabela[linha - 1][coluna - 1] != '0')
					printf("A posição já está preenchida!\n");

			} while (tabela[linha - 1][coluna - 1] != '0');

			tabela[linha - 1][coluna - 1] = 'O';
			primeiro = 2;
		}
		else{
			printf("Vez do Computador!\n\n");
			jogadaDificilCPU(tabela, primeiro, i);
			primeiro = 1;
		}

		imprimirTabela(tabela);

		status = verificar(tabela);
		if (status == 1){
			printf("O jogador %i venceu!\n", status);
			break;
		}
		if (status == 2){
			printf("O Computador venceu!\n", status);
			break;
		}

		i++;
	}
	if (i == 9 && status == 0)
		printf("O jogo terminou empatado!\n");

}

void jogadaDificilCPU(char tabela[][TAM], int primeiro, int i){
	int status;

	status = ataque(tabela);

	if (status == -1)
	{
		status = 0;
		status = defesa(tabela);
		if (status == -1)
		{
			jogadaPlanejada(tabela, primeiro, i);
		}
	}
}

void jogadaPlanejada(char tabela[][TAM], int primeiro, int i){ //Jogada planejada da dificuldade <Difícil>
	int ln, col;

	if (i == 0){
		do{
			ln = rand() % 3;
			col = rand() % 3;
		} while (ln == 1 || col == 1);
		tabela[ln][col] = 'X';
		return;
	}
	else if (tabela[1][1] == '0'){
		tabela[1][1] = 'X';
		return;
	}
	else if (tabela[0][0] == 'O' && tabela[2][2] == '0'){
		tabela[2][2] = 'X';
		return;
	}
	else if (tabela[2][2] == 'O' && tabela[0][0] == '0'){
		tabela[0][0] = 'X';
		return;
	}
	else if (tabela[0][2] == 'O' && tabela[2][0] == '0'){
		tabela[2][0] = 'X';
		return;
	}
	else if (tabela[2][0] == 'O' && tabela[0][2] == '0'){
		tabela[0][2] = 'X';
		return;
	}
	else if (tabela[1][1] != '0'){

		if (tabela[0][0] == '0' || tabela[0][2] == '0' || tabela[2][0] == '0' || tabela[2][2] == '0'){
			do{
				ln = rand() % 3;
				col = rand() % 3;
			} while ((ln == 1 || col == 1) && tabela[ln][col] != '0');
			tabela[ln][col] = 'X';
			return;
		}
		else{
			do{
				ln = rand() % 3;
				col = rand() % 3;
			} while ((ln != 1 || col != 1) && tabela[ln][col] != '0');
			tabela[ln][col] = 'X';
			return;
		}
	}	
}