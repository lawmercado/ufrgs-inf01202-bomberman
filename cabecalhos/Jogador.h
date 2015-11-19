/**
 * Estruturas e constantes referentes a entidade Jogador (Bomberman)
 *
 * @author Luís Augusto Weber Mercado
 */
#define MARGEM_INICIAL 25
#define PONTUACAO_POR_MONSTRO 100
#define PONTUACAO_POR_SEGUNDO_RESTANTE 5
#define TAMANHO_PASSO_EM_PX 10
#define JOGADOR_FRENTE_DIREITA 0
#define JOGADOR_FRENTE_ESQUERDA 1
#define JOGADOR_DIREITA_DIREITA 2
#define JOGADOR_DIREITA_ESQUERDA 3
#define JOGADOR_TRAS_DIREITA 4
#define JOGADOR_TRAS_ESQUERDA 5
#define JOGADOR_ESQUERDA_DIREITA 6
#define JOGADOR_ESQUERDA_ESQUERDA 7

typedef struct Jogador {
    int vidas;
    int pontuacao;
    int nivelAtual;
    int estadoPersonagem;
    int numeroDeBombasSimultaneas;
    Indice indice;
    Posicao posicao;
} Jogador;

bool jogadorAtingeMapaAoIrParaCima(Hitbox hitboxJogador);
bool jogadorAtingeMapaAoIrParaDireita(Hitbox hitboxJogador);
bool jogadorAtingeMapaAoIrParaBaixo(Hitbox hitboxJogador);
bool jogadorAtingeMapaAoIrParaEsquerda(Hitbox hitboxJogador);
void alternarEstadoDoPersonagemAoIrParaCima(Jogador *jogador);
void alternarEstadoDoPersonagemAoIrParaDireita(Jogador *jogador);
void alternarEstadoDoPersonagemAoIrParaBaixo(Jogador *jogador);
void alternarEstadoDoPersonagemAoIrParaEsquerda(Jogador *jogador);
Hitbox obterHitboxDoJogador(Jogador *jogador);
void desenharJogador(Jogador *jogador, Recursos *recursos);