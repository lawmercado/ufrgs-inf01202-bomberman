/**
 * Estruturas e constantes referentes ao menu
 *
 * @author Luís Augusto Weber Mercado
 */

typedef struct Menu {
    int opcaoIndicada;
    bool haOpcaoSelecionada;
} Menu;

void definirPadroesDoMenu();
void processarEventoDoMenu(Menu *menu, ALLEGRO_EVENT evento);
void desenharMenu(Menu *menu);