#include "../cabecalhos/Menu.h"

void definirPadroesDoMenu(Menu *menu)
{
	menu->haOpcaoSelecionada = false;
	menu->opcaoIndicada = MODO_JOGO;
}

void processarEventoDoMenu(Menu *menu, ALLEGRO_EVENT evento)
{
	if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch(evento.keyboard.keycode)
		{
			case ALLEGRO_KEY_UP:
				if( menu->opcaoIndicada != MODO_JOGO )
				{
					menu->opcaoIndicada--;
				}
				
				break;

			case ALLEGRO_KEY_DOWN:
				if( menu->opcaoIndicada != MODO_SAIR )
				{
					menu->opcaoIndicada++;
				}
			   
				break;
			case ALLEGRO_KEY_ENTER:
			case ALLEGRO_KEY_SPACE:
				menu->haOpcaoSelecionada = true;
				
				break;
		}
	}
}

void desenharMenu(Menu *menu, Recursos *recursos)
{
    al_clear_to_color(obterCorDeFundo());
	al_draw_bitmap(recursos->menuFundo, 0, 0, 0);
	al_draw_bitmap(recursos->menuIconeSelecao, 380, 290 + (80 * (menu->opcaoIndicada - 1)), 0);
}
