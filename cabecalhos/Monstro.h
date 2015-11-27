/**
 * Estruturas e constantes referentes a entidade Monstro
 *
 * @author Luís Augusto Weber Mercado
 */
#define MONSTRO_TAMANHO_PASSO 3
#define MONSTRO_FRENTE 0
#define MONSTRO_FRENTE_PARADO 1
#define MONSTRO_DIREITA 2
#define MONSTRO_DIREITA_PARADO 3
#define MONSTRO_TRAS 4
#define MONSTRO_TRAS_PARADO 5
#define MONSTRO_ESQUERDA 6
#define MONSTRO_ESQUERDA_PARADO 7

typedef struct Monstro {
    int estadoPersonagem;
    int direcaoMovimento;
    Indice indice;
    Posicao posicao;
    Sprite sprite;
} Monstro;

Sprite obterSpriteDoMonstroConformeEstado( Monstro *monstro, Recursos *recursos );