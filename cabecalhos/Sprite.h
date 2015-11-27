/**
 * Estruturas e constantes referentes as sprites utilizadas no jogo
 *
 * @author Luís Augusto Weber Mercado
 */

typedef struct Sprite {
    int maximoFrames;
    int frameCorrente;
    int contadorFrame;
    int delayFrame;
    int larguraFrame;
    int alturaFrame;
    int colunasAnimacao;
    int direcaoAnimacao;
    int allegroFlag;
    ALLEGRO_BITMAP *imagem;
    
} Sprite;

