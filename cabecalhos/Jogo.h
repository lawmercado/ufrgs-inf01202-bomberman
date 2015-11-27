/**
 * Estruturas e constantes referentes ao jogo
 *
 * @author Luís Augusto Weber Mercado
 */

typedef struct Hitbox {
    int x;
    int xFinal;
    int y;
    int yFinal;
} Hitbox;

#include "./Jogador.h"
#include "./Monstro.h"

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
#define ALTURA_RODAPE 60
#define TAMANHO_ENTIDADE 50
#define TAMANHO_SOMBRA 10
#define JOGO_MODO_RODANDO 0
#define JOGO_MODO_PAUSADO 1
#define JOGO_MODO_GAMEOVER 2
#define TEMPO_POR_NIVEL 180
#define DIRECAO_CIMA 0
#define DIRECAO_DIREITA 1
#define DIRECAO_BAIXO 2
#define DIRECAO_ESQUERDA 3
#define DIRECAO_NULA -1

typedef struct Jogo {
    bool carregado;
    bool inicializado;
    int modo;
    Jogador jogador;
    int tempo;
    Saida saida;
    Bomba bombas[5];
    Monstro monstros[5];
    int contadorDeMonstros;
    Parede paredes[135];
    int contadorDeParedes;
    Obstaculo obstaculos[135];
    int contadorDeObstaculos;
} Jogo;

void criarNovoJogo(Aplicacao *aplicacao, Jogo *jogo);
void definirPadroesDoJogo(Jogo *jogo);
bool carregarJogoConformeNivel(Jogo *jogo, int nivel);
void carregarParedesPadroes();
void popularJogoConformeLinha(Jogo *jogo, char linha[], int numeroLinha);
void processarEventoDoJogo(Aplicacao *aplicacao, Jogo *jogo, ALLEGRO_EVENT evento);
void processarTickFPSJogoRodando(Aplicacao* aplicacao, Jogo* jogo);
void processarTickFPSJogoPausado(Aplicacao* aplicacao, Jogo* jogo);

Indice obterPosicaoBruta(Posicao posicao);
Hitbox obterHitboxPelaPosicao(Posicao posicao);
bool verificarColisao(Hitbox corpo, Hitbox alvo);
bool obterCondicaoDeDestinoPelaDirecao(Indice corpo, Indice alvo, int direcao);
void verificarColisaoComEntidades( Jogo *jogo, Hitbox hitbox, Indice indice, Posicao *posicao, int unidades, int direcao);
void alterarPosicaoConformeDirecao(Posicao *posicao, int unidades, int direcao);
int obterDirecaoOposta(int direcao);

void desenharJogo(Jogo *jogo, Recursos *recursos);
void desenharFundo(Recursos *recursos);
void desenharParede(Parede *parede, Recursos *recursos);
void desenharObstaculo(Obstaculo *obstaculo, Recursos *recursos);
void desenharJogador(Jogador *jogador);
void desenharRodape(Jogo *jogo, Recursos *recursos);
void desenharOverlayDePausa(Recursos *recursos);