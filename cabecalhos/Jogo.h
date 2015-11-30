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

/**
 * Estruturas e constantes referentes a entidade Bomba
 *
 */
#define BOMBA_RAIO_EXPLOSAO_PADRAO 1
#define RAIO_MAXIMO_EXPLOSAO 3
#define BOMBA_TEMPO_ATE_EXPLODIR 3
#define BOMBA_PREPARADA 0
#define BOMBA_EXPLODINDO 1
#define BOMBA_TEMPO_EXPLOSAO 2
#define BOMBA_DESATIVADA -1

typedef struct Explosao {
    int estado;
    Indice indice;
    Posicao posicao;
} Explosao;

typedef struct Bomba {
    int raioDeExplosao;
    int tempoAteExplodir;
    int tempoExplodindo;
    int estado;
    Sprite sprite;
    Sprite spriteRastro;
    Explosao explosoesCima[RAIO_MAXIMO_EXPLOSAO];
    Explosao explosoesDireita[RAIO_MAXIMO_EXPLOSAO];
    Explosao explosoesBaixo[RAIO_MAXIMO_EXPLOSAO];
    Explosao explosoesEsquerda[RAIO_MAXIMO_EXPLOSAO];
    Indice indice;
    Posicao posicao;
} Bomba;

typedef struct Saida {
    int estado;
    Indice indice;
    Posicao posicao;
} Saida;

typedef struct Parede {
    Indice indice;
    Posicao posicao;
} Parede;

typedef struct Obstaculo {
    int estado;
    int tempo;
    Sprite sprite;
    Indice indice;
    Posicao posicao;
} Obstaculo;

/**
 * Estruturas e constantes referentes a entidade Monstro
 *
 * @author Luís Augusto Weber Mercado
 */
#define MONSTRO_TAMANHO_PASSO 1

typedef struct Monstro {
    int estado;
    int direcaoMovimento;
    int tempo;
    Indice indice;
    Posicao posicao;
    Sprite sprite;
} Monstro;

/**
 * Estruturas e constantes referentes a entidade Jogador (Bomberman)
 *
 * @author Luís Augusto Weber Mercado
 */
#define JOGADOR_MARGEM_INICIAL 25
#define JOGADOR_PONTUACAO_POR_MONSTRO 100
#define JOGADOR_PONTUACAO_POR_TEMPO 5
#define JOGADOR_TAMANHO_PASSO 3
#define JOGADOR_NUMERO_VIDAS 3
#define JOGADOR_BOMBAS_PERMITIDAS_PADRAO 1

typedef struct Jogador {
    int vidas;
    int pontuacao;
    int nivelAtual;
    int estado;
    int maximoDeBombasSimultaneas;
    int direcaoMovimento;
    int tempo;
    Indice indice;
    Indice indiceInicial;
    Posicao posicao;
    Sprite sprite;
} Jogador;

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
#define ENTIDADE_FRENTE 0
#define ENTIDADE_FRENTE_PARADA 1
#define ENTIDADE_DIREITA 2
#define ENTIDADE_DIREITA_PARADA 3
#define ENTIDADE_TRAS 4
#define ENTIDADE_TRAS_PARADA 5
#define ENTIDADE_ESQUERDA 6
#define ENTIDADE_ESQUERDA_PARADA 7
#define ENTIDADE_MORTA 8
#define ENTIDADE_MORRENDO 9
#define ENTIDADE_VISIVEL 10
#define ENTIDADE_INVISIVEL 11
#define ENTIDADE_TEMPO_MORTA 2
#define MAXIMO_BOMBAS_PERMITIDAS 5
#define MAXIMO_MONSTROS_PERMITIDOS 5

typedef struct Jogo {
    bool carregado;
    bool inicializado;
    int modo;
    Jogador jogador;
    int tempo;
    Saida saida;
    Bomba bombas[MAXIMO_BOMBAS_PERMITIDAS];
    int contadorDeBombas;
    Monstro monstros[MAXIMO_MONSTROS_PERMITIDOS];
    int contadorDeMonstros;
    Parede paredes[135];
    int contadorDeParedes;
    Obstaculo obstaculos[135];
    int contadorDeObstaculos;
} Jogo;

void criarNovoJogo(Jogo *jogo);
void definirPadroesDoJogo(Jogo *jogo);
bool carregarJogoConformeNivel(Jogo *jogo, int nivel);
void carregarParedesPadroes();
void popularJogoConformeLinha(Jogo *jogo, char linha[], int numeroLinha);
void processarEventoDoJogo(Jogo *jogo, ALLEGRO_EVENT evento);
void processarTickFPSJogoRodando(Jogo* jogo);
void processarTickFPSJogoPausado(Jogo* jogo);
void verificarImpactoDaBombaNoJogo(Bomba *bomba, Jogo *jogo);

void definirPadroesDoJogador(Jogador *jogador);
void trocarEstadoDoJogador(Jogador *jogador, int estado);
Hitbox obterHitboxDoJogador(Jogador *jogador);
Sprite obterSpriteDoJogadorPeloEstado(Jogador *jogador);

void definirPadroesDasBombas(Jogo *jogo);
void plantarBomba(Jogo *jogo);
void prepararBomba(Bomba *bomba, Indice indice);
Sprite obterSpriteDaBomba();
Hitbox obterHitboxDaBomba(Bomba *bomba);
Sprite obterSpriteDoRastro();

void trocarEstadoDoMonstro(Monstro *monstro, int estado);
int obterDirecaoDiferenteAleatoria(int direcaoAtual);
Sprite obterSpriteDoMonstroPeloEstado(Monstro *monstro);

void trocarEstadoDoObstaculo(Obstaculo *obstaculo, int estado);
void definirPadroesDoObstaculo(Obstaculo *obstaculo);
Sprite obterSpriteDoObstaculoPeloEstado(Obstaculo *obstaculo);

Indice obterPosicaoBruta(Posicao posicao);
Indice obterPosicaoBrutaDoJogador(Hitbox hitbox);
Hitbox obterHitboxPelaPosicao(Posicao posicao);
bool verificarColisao(Hitbox corpo, Hitbox alvo);
bool obterCondicaoDeDestinoPelaDirecao(Indice corpo, Indice alvo, int direcao);
void alterarPosicaoPelaDirecao(Posicao *posicao, int unidades, int direcao);
int obterDirecaoOposta(int direcao);

void desenharJogo(Jogo *jogo);
void desenharFundo();
void desenharParede(Parede *parede);
void desenharObstaculo(Obstaculo *obstaculo);
void desenharJogador(Jogador *jogador);
void desenharRodape(Jogo *jogo);
void desenharSaida(Saida *saida);
void desenharMonstro(Monstro* monstro);
void desenharBomba(Bomba* bomba);
void desenharOverlayDePausa();