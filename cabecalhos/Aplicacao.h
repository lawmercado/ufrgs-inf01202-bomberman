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
    ALLEGRO_BITMAP *menuTela;
    ALLEGRO_BITMAP *menuIndicador;
    
    ALLEGRO_BITMAP *jogoFundo;
    ALLEGRO_BITMAP *jogoRodape;
    ALLEGRO_BITMAP *jogoObstaculo;
    ALLEGRO_BITMAP *jogoObstaculoFixo;
    ALLEGRO_BITMAP *jogoTelaPausa;
    ALLEGRO_BITMAP *jogadorFrenteSprite;
    ALLEGRO_BITMAP *jogadorFrenteParado;
    ALLEGRO_BITMAP *jogadorTrasSprite;
    ALLEGRO_BITMAP *jogadorTrasParado;
    ALLEGRO_BITMAP *jogadorLadoSprite;
    ALLEGRO_BITMAP *jogadorLadoParado;
    ALLEGRO_BITMAP *monstroFrenteSprite;
    ALLEGRO_BITMAP *monstroFrenteParado;
    ALLEGRO_BITMAP *monstroTrasSprite;
    ALLEGRO_BITMAP *monstroTrasParado;
    ALLEGRO_BITMAP *monstroLadoSprite;
    ALLEGRO_BITMAP *monstroLadoParado;
    
    ALLEGRO_FONT *fonteCantarellRegular;
    ALLEGRO_FONT *fonteCantarellBold;
} Recursos;

typedef struct Aplicacao {
    int modo;
    Recursos recursos;
    bool contemErros;
    ALLEGRO_DISPLAY *janela;
    ALLEGRO_EVENT_QUEUE *filaEventos;
    ALLEGRO_TIMER *timerFPS;
    ALLEGRO_TIMER *timerRelogio;
    int teclasPressionadas[];
} Aplicacao;

bool TeclasPressionadas[ALLEGRO_KEY_MAX];
        
void inicializar(Aplicacao *aplicacao);
void criarJanela(Aplicacao *aplicacao);
void limparConteudoDaJanela();
void criarFilaDeEventos(Aplicacao *aplicacao);
void criarTimers(Aplicacao *aplicacao);
Recursos obterRecursos();
void finalizar(Aplicacao *aplicacao);