#include "../cabecalhos/Menu.h"

void definirPadroesDoMenu(Menu *menu)
{
	menu->haOpcaoSelecionada = false;
	menu->opcaoIndicada = MODO_JOGO;
    
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 5;
    sprite.larguraFrame = 100;
    sprite.alturaFrame = 100;
    sprite.direcaoAnimacao = 1;

    sprite.colunasAnimacao = 3;
    sprite.maximoFrames = 3;
    sprite.imagem = aplicacao->recursos.menuBombaSprite;
    
    menu->sprite = sprite;
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

void desenharMenu(Menu *menu)
{
    al_clear_to_color(obterCorDeFundo());
    
    Posicao posicao;
    posicao.x = 166;
    posicao.y = 123;
    
    atualizarSprite(&menu->sprite);
    
	al_draw_bitmap(aplicacao->recursos.menuTela, 0, 0, 0);
	al_draw_bitmap(aplicacao->recursos.menuIndicador, 275, 290 + (80 * (menu->opcaoIndicada - 1)), 0);
    desenharSprite(&menu->sprite, posicao);
}
