#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "./cabecalhos/Base.h"

#include "./codigos/Aplicacao.c"
#include "./codigos/Sprite.c"
#include "./codigos/Menu.c"
#include "./codigos/Jogo.c"

int main( )
{
    bool redesenhar = true;
    
    Aplicacao singleton;
    aplicacao = &singleton;
    
    aplicacao->contemErros = false;

    inicializar(aplicacao);

    if( aplicacao->contemErros )
    {
        return -1;
    }

    Menu menu;
    definirPadroesDoMenu(&menu);

    Jogo jogo;
    criarNovoJogo(&jogo);
    
    while(aplicacao->modo != MODO_SAIR)
    {
        while(!al_is_event_queue_empty(aplicacao->filaEventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(aplicacao->filaEventos, &evento);

            switch(evento.type)
            {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                {
                    aplicacao->modo = MODO_SAIR;

                    break;
                }
                
                case ALLEGRO_EVENT_KEY_DOWN:
                {
                    TeclasPressionadas[evento.keyboard.keycode] = true;

                    break;
                }

                case ALLEGRO_EVENT_KEY_UP:
                {
                    TeclasPressionadas[evento.keyboard.keycode] = false;

                    break;
                }

                case ALLEGRO_EVENT_TIMER:
                {
                    if( evento.timer.source == aplicacao->timerFPS )
                    {
                        redesenhar = true;
                    }

                    break;
                }
            }

            switch(aplicacao->modo)
            {
                case MODO_MENU:
                {
                    criarNovoJogo(&jogo); // "Reseta" o jogo
                    
                    processarEventoDoMenu(&menu, evento);

                    if( menu.haOpcaoSelecionada )
                    {
                        aplicacao->modo = menu.opcaoIndicada;
                        limparConteudoDaJanela();
                    }

                    break;
                }

                case MODO_JOGO:
                {
                    definirPadroesDoMenu(&menu); // Reseta o menu
                    
                    carregarJogoConformeNivel(&jogo, jogo.jogador.nivelAtual);
                    processarEventoDoJogo(&jogo, evento);

                    break;
                }
            }

            if( redesenhar && al_is_event_queue_empty(aplicacao->filaEventos) )
            {
                redesenhar = false;

                switch(aplicacao->modo)
                {
                    case MODO_MENU:
                    {
                        desenharMenu(&menu);

                        break;
                    }

                    case MODO_JOGO:
                    {
                        desenharJogo(&jogo);

                        break;
                    }
                }

                al_flip_display();
            }
        }
    }

    finalizar(aplicacao);

    return 0;
}
