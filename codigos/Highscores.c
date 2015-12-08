/**
 * Arquivo contendo a implementação das funções referentes a tela de pontuações
 * 
 * @author Luís Augusto Weber Mercado
 */

void processarEventoDosHighscores( ALLEGRO_EVENT evento )
{
    if( evento.type == ALLEGRO_EVENT_KEY_DOWN )
    {
        switch(evento.keyboard.keycode)
        {
            case ALLEGRO_KEY_ESCAPE:
                aplicacao->modo = MODO_MENU;

                break;
        }
    }
}

void desenharHighscores( )
{
    al_clear_to_color(al_map_rgb(19, 38, 37));
    
    al_draw_bitmap(aplicacao->recursos.highscoresTela, 0, 0, 0);
    
    int i = 0;
    
    for( i = 0; i < MAXIMO_LISTA_HIGHSCORES; i++ )
    {
        al_draw_textf(aplicacao->recursos.fonteCantarellBoldPequena, al_map_rgb(229, 227, 185), 220, 210 + (30 * i), ALLEGRO_ALIGN_LEFT, "%s", aplicacao->recursos.pontuacoes[i].nome);
        al_draw_textf(aplicacao->recursos.fonteCantarellRegularPequena, al_map_rgb(229, 227, 185), LARGURA_TELA - 220, 210 + (30 * i), ALLEGRO_ALIGN_RIGHT, "%d", aplicacao->recursos.pontuacoes[i].pontos);
    }
}
