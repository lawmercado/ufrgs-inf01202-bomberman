/**
 * Arquivo contendo os métodos referentes a aplicação em si
 * 
 * @author Luís Augusto Weber Mercado
 */

#include <allegro5/allegro.h>

#include "../cabecalhos/Aplicacao.h"

void inicializar( Aplicacao *aplicacao )
{
    if( !al_init() )
    {
        printf("Falha ao iniciar a Allegro.\n");
        aplicacao->contemErros = true;
    }

    if( !al_init_image_addon() )
    {
        printf("Não foi possível carregar o addon de imagens.\n");
        aplicacao->contemErros = true;
    }

    if( !al_install_keyboard() )
    {
        printf("Falha ao inicializar a integração com o teclado.\n");
        aplicacao->contemErros = true;
    } 
   
    criarJanela(aplicacao);
    criarFilaDeEventos(aplicacao);
    criarTimers(aplicacao);

    al_register_event_source(aplicacao->filaEventos, al_get_keyboard_event_source());
    al_register_event_source(aplicacao->filaEventos, al_get_timer_event_source(aplicacao->timerFPS));
    al_register_event_source(aplicacao->filaEventos, al_get_timer_event_source(aplicacao->timerRelogio));
    al_register_event_source(aplicacao->filaEventos, al_get_display_event_source(aplicacao->janela));
    
    // Seta os defaults da aplicação
    aplicacao->modo = MODO_MENU;
    aplicacao->recursos = obterRecursos();
    
    al_start_timer(aplicacao->timerFPS);
    al_start_timer(aplicacao->timerRelogio);
}

void criarJanela( Aplicacao *aplicacao )
{
    aplicacao->janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if( !aplicacao->janela )
    {
        printf("Falha ao criar a janela.\n");
        aplicacao->contemErros = true;
    }

    al_set_window_title(aplicacao->janela, "Bomberman");

    limparConteudoDaJanela();
}

void limparConteudoDaJanela( )
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void criarFilaDeEventos( Aplicacao *aplicacao )
{
    aplicacao->filaEventos = al_create_event_queue();
    if( !aplicacao->filaEventos )
    {
        printf("Falha ao criar fila de eventos.\n");
        aplicacao->contemErros = true;
    }
}

void criarTimers( Aplicacao *aplicacao )
{
    aplicacao->timerFPS = al_create_timer(1.0 / FPS);
    aplicacao->timerRelogio = al_create_timer(1.0);
}

Recursos obterRecursos( )
{
    Recursos recursos;

    recursos.menuFundo = al_load_bitmap("./recursos/menu/fundo.png");
    recursos.menuIconeSelecao = al_load_bitmap("./recursos/menu/iconeSelecao.png");

    recursos.jogoObstaculoFixo = al_load_bitmap("./recursos/jogo/obstaculoFixo.png");
    recursos.jogadorDireitaDireita = al_load_bitmap("./recursos/jogo/bombermanDireitaDireita.png");
    recursos.jogadorDireitaEsquerda = al_load_bitmap("./recursos/jogo/bombermanDireitaEsquerda.png");
    recursos.jogadorFrenteDireita = al_load_bitmap("./recursos/jogo/bombermanFrenteDireita.png");
    recursos.jogadorTrasDireita = al_load_bitmap("./recursos/jogo/bombermanTrasDireita.png");

    return recursos;
}

void finalizar( Aplicacao* aplicacao )
{
    al_destroy_bitmap(aplicacao->recursos.menuFundo);
    al_destroy_bitmap(aplicacao->recursos.menuIconeSelecao);
    al_destroy_bitmap(aplicacao->recursos.jogoObstaculoFixo);
    al_destroy_bitmap(aplicacao->recursos.jogadorDireitaDireita);
    al_destroy_bitmap(aplicacao->recursos.jogadorDireitaEsquerda);
    al_destroy_bitmap(aplicacao->recursos.jogadorFrenteDireita);
    al_destroy_bitmap(aplicacao->recursos.jogadorTrasDireita);
    al_destroy_event_queue(aplicacao->filaEventos);
    al_destroy_timer(aplicacao->timerFPS);
    al_destroy_timer(aplicacao->timerRelogio);
    al_destroy_display(aplicacao->janela);
}

ALLEGRO_COLOR obterCorDeFundo( )
{
    return al_map_rgb(25, 55, 47);
}