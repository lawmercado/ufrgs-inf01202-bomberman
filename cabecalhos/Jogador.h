/**
 * Estruturas e constantes referentes a entidade Jogador (Bomberman)
 *
 * @author Luís Augusto Weber Mercado
 */
#define MARGEM_INICIAL 25
#define PONTUACAO_POR_MONSTRO 100
#define PONTUACAO_POR_SEGUNDO_RESTANTE 5
#define TAMANHO_PASSO 3
#define NUMERO_VIDAS_INICIAL 3
#define JOGADOR_FRENTE 0
#define JOGADOR_FRENTE_PARADO 1
#define JOGADOR_DIREITA 2
#define JOGADOR_DIREITA_PARADO 3
#define JOGADOR_TRAS 4
#define JOGADOR_TRAS_PARADO 5
#define JOGADOR_ESQUERDA 6
#define JOGADOR_ESQUERDA_PARADO 7

typedef struct Jogador {
    int vidas;
    int pontuacao;
    int nivelAtual;
    int estadoPersonagem;
    int numeroDeBombasSimultaneas;
    int direcaoMovimento;
    Indice indice;
    Posicao posicao;
    Sprite sprite;
} Jogador;

void definirPadroesDoJogador(Jogador *jogador, Recursos *recursos);
void trocarEstadoDoJogador(Jogador* jogador, Recursos* recursos, int estado);
Hitbox obterHitboxDoJogador(Jogador *jogador);
Sprite obterSpriteDoJogadorConformeEstado(Jogador *jogador, Recursos *recursos);