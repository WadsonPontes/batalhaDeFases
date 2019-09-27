#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int estado = -1;

int nivel = 5;
int experiencia = 0;
float evolucao = 1.05;
int vida = 2000;
int ataque = 100;
int defesa = 100;

int fase = 0;

int inivel = 0;
int iexperiencia = 0;
float ievolucao = 1.05;
int ivida = 1500;
int iataque = 80;
int idefesa = 80;

void imprimirMenu() {
	printf("\n\n==<|MENU|>==\n");
	printf("(1) JOGAR\n");
	printf("(0) SAIR\n");
}

void imprimirOpcoesDeBatalha() {
	printf("\n\n==<|BATALHA|>==\n");
	printf("(1) ATACAR\n");
	printf("(2) FICHA JOGADOR\n");
	printf("(3) FICHA INIMIGO\n");
	printf("(0) DESISTIR\n");
}

void mostrarFichaJogador() {
	printf("\n\n==<|FICHA JOGADOR|>==\n");
	printf("Nivel: %d\n", nivel);
	printf("Vida: %d\n", vida);
	printf("Ataque: %d\n", ataque);
	printf("Defesa: %d\n\n", defesa);
}

void mostrarFichaInimigo() {
	printf("\n\n==<|FICHA INIMIGO|>==\n");
	printf("Nivel: %d\n", inivel);
	printf("Vida: %d\n", ivida);
	printf("Ataque: %d\n", iataque);
	printf("Defesa: %d\n\n", idefesa);
}

void gerarInimigo() {
	inivel++;
	iexperiencia = 0;
	ivida = ivida * ievolucao + rand() % 100 - 45;
	iataque = iataque * ievolucao + rand() % 10 - 4;
	idefesa = idefesa * ievolucao + rand() % 10 - 4;
}

void subirDeNivel() {
	if (experiencia > 99) {
		nivel++;
		experiencia = 0;
		vida = vida * evolucao;
		ataque = ataque * evolucao;
		defesa = defesa * evolucao;
		printf("Voce subiu de nivel!\n");
	}
}

void subirDeNivelInimigo() {
	if (iexperiencia > 99) {
		inivel++;
		iexperiencia = 0;
		ivida = ivida * ievolucao;
		iataque = iataque * ievolucao;
		idefesa = idefesa * ievolucao;
		printf("O inimigo subiu de nivel!\n");
	}
}

void partida() {
	int escolha;
	int avida = vida;
	int aivida = ivida;
	int dano;

	do {
		fase++;
		gerarInimigo();
		avida = vida;
		aivida = ivida;

		if (fase > 1) {
			getchar();
			getchar();
		}

		printf("==<|FASE %d|>==\n", fase);

		do {
			printf("Vida Jogador: %d/%d\n", avida, vida);
			printf("Vida Inimigo: %d/%d\n", aivida, ivida);

			imprimirOpcoesDeBatalha();
			scanf("%d", &escolha);

			switch (escolha) {
				case 0:
					avida = 0;
					break;
				case 1:
					dano = (rand() % (int)(ataque * 2.5) + ataque) - (rand() % (int)(idefesa / 10) + ataque);

					if (dano > 0) {
						aivida -= dano;
						experiencia += 10;
						printf("O inimigo tomou %d de dano!\n", dano);
						if (aivida <= 0)
							printf("O inimigo morreu!\n");
					}
					else {
						iexperiencia += 10;
						printf("O inimigo se defendeu do seu ataque!\n", dano);
					}

					dano = (rand() % (int)(iataque * 2.5) + iataque) - (rand() % (int)(defesa / 10) + iataque);

					if (dano > 0 && aivida > 0) {
						avida -= dano;
						iexperiencia += 10;
						printf("Voce tomou %d de dano!\n", dano);
						if (avida <= 0)
							printf("Voce perdeu!\n");
					}
					else if (aivida > 0) {
						experiencia += 10;
						printf("Voce se defendeu do ataque inimigo!\n", dano);
					}
					break;
				case 2:
					mostrarFichaJogador();
					break;
				case 3:
					mostrarFichaInimigo();
					break;
			}
			subirDeNivel();
			subirDeNivelInimigo();
			printf("\n");

		} while (avida > 0 && aivida > 0);

	} while (avida > 0);
}

int main() {
	time_t t;
	srand((unsigned) time(&t));

	do {
		estado = -1;

		nivel = 5;
		experiencia = 0;
		evolucao = 1.05;
		vida = 2000;
		ataque = 100;
		defesa = 100;

		fase = 0;

		inivel = 0;
		iexperiencia = 0;
		ievolucao = 1.05;
		ivida = 1500;
		iataque = 80;
		idefesa = 80;

		imprimirMenu();
		scanf("%d", &estado);

		if (estado == 1)
			partida();
	} while (estado > 0);
	return 0;
}