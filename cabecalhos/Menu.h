/**
 * Estruturas e constantes referentes ao menu
 *
 * @author Luís Augusto Weber Mercado
 */

typedef struct Menu {
    int opcaoIndicada;
    bool haOpcaoSelecionada;
    Sprite sprite;
} Menu;

void definirPadroesDoMenu(Menu *menu);
void processarEventoDoMenu(Menu *menu, ALLEGRO_EVENT evento);
void desenharMenu(Menu *menu);