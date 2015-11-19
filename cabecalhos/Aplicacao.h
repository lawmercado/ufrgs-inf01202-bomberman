/**
 * Estruturas e constantes referentes a aplicação (janela, eventos etc)
 *
 * @author Luís Augusto Weber Mercado
 */

#define LARGURA_TELA 850
#define ALTURA_TELA 610
#define FPS 60

#define MODO_MENU 0
#define MODO_JOGO 1
#define MODO_HIGHSCORES 2
#define MODO_SAIR 3

typedef struct Recursos {
    ALLEGRO_BITMAP *menuFundo;
    ALLEGRO_BITMAP *menuIconeSelecao;
    ALLEGRO_BITMAP *jogoObstaculoFixo;
    ALLEGRO_BITMAP *jogadorDireitaDireita;
    ALLEGRO_BITMAP *jogadorDireitaEsquerda;
    ALLEGRO_BITMAP *jogadorFrenteDireita;
    ALLEGRO_BITMAP *jogadorTrasDireita;
} Recursos;

typedef struct Aplicacao {
    int modo;
    Recursos recursos;
    bool contemErros;
    ALLEGRO_DISPLAY *janela;
    ALLEGRO_EVENT_QUEUE *filaEventos;
    ALLEGRO_TIMER *timerFPS;
    ALLEGRO_TIMER *timerRelogio;
} Aplicacao;

void inicializar(Aplicacao *aplicacao);
void criarJanela(Aplicacao *aplicacao);
void limparConteudoDaJanela();
void criarFilaDeEventos(Aplicacao *aplicacao);
void criarTimers(Aplicacao *aplicacao);
Recursos obterRecursos();
void finalizar(Aplicacao *aplicacao);