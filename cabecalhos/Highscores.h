/**
 * Estruturas e constantes referentes a tela de highscores
 *
 * @author Luís Augusto Weber Mercado
 */

#define TAMANHO_MAXIMO_NOME 20
#define MAXIMO_LISTA_HIGHSCORES 10

typedef struct Highscore {
    char nome[20];
    int pontos;
} Highscore;

void processarEventoDosHighscores(ALLEGRO_EVENT evento);
void desenharHighscores();