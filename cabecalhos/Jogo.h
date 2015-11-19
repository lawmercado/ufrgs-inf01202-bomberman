/**
 * Estruturas e constantes referentes ao jogo
 *
 * @author Luís Augusto Weber Mercado
 */

typedef struct Posicao {
    float x;
    float y;
} Posicao;

typedef struct Indice {
    int i;
    int j;
} Indice;

typedef struct Hitbox {
    float x;
    float xFinal;
    float y;
    float yFinal;
} Hitbox;

#include "./Jogador.h"

/**
 * Estruturas e constantes referentes a entidade Bomba
 *
 */
#define RAIO_DA_EXPLOSAO_EM_PX 1
#define SEGUNDOS_ATE_BOMBA_EXPLODIR 3

typedef struct Bomba {
    int raioDeExplosao;
    int tempoAteExplodir;
    bool estaParaExplodir;
    Indice indice;
    Posicao posicao;
} Bomba;

typedef struct Saida {
    bool visivel;
    Indice indice;
    Posicao posicao;
} Saida;

typedef struct Monstro {
    bool vivo;
    Indice indice;
    Posicao posicao;
} Monstro;

typedef struct Parede {
    Indice indice;
    Posicao posicao;
} Parede;

typedef struct Obstaculo {
    bool visivel;
    Indice indice;
    Posicao posicao;
} Obstaculo;

/**
 * Estruturas e constantes referentes ao level
 *
 */
#define LARGURA_MAPA_JOGAVEL 15
#define ALTURA_MAPA_JOGAVEL 9
#define TAMANHO_ENTIDADE 50
#define TAMANHO_SOMBRA_EM_PX 10

typedef struct Jogo {
    bool carregado;
    bool inicializado;
    Jogador jogador;
    Saida saida;
    Bomba bombas[5];
    Monstro monstros[5];
    int contadorDeMonstros;
    Parede paredes[135];
    int contadorDeParedes;
    Obstaculo obstaculos[135];
    int contadorDeObstaculos;
    
} Jogo;

void definirPadroesDoJogo(Jogo *jogo);
bool carregarJogoConformeNivel(Jogo *jogo, int nivel);
void popularJogoConformeLinha(Jogo *jogo, char linha[], int numeroLinha);
void processarEventoDoJogo(Jogo *jogo, ALLEGRO_EVENT evento);
bool posicaoSobrepoeEmX(Hitbox posicao, Hitbox referencia);
bool posicaoSobrepoeEmY(Hitbox posicao, Hitbox referencia);
bool posicaoSobrepoe(Hitbox posicao, Hitbox referencia);
void desenharJogo(Jogo *jogo, Recursos *recursos);
void desenharParede(Parede *parede, Recursos *recursos);
void desenharObstaculo(Obstaculo *obstaculo, Recursos *recursos);
ALLEGRO_COLOR obterCorDeFundo();