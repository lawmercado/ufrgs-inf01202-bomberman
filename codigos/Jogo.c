#include <allegro5/events.h>
#include <stdio.h>
#include <math.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "../cabecalhos/Jogo.h"

#include "./Jogador.c"
#include "./Monstro.c"

void criarNovoJogo( Aplicacao *aplicacao, Jogo *jogo )
{
    jogo->inicializado = false;
    jogo->modo = JOGO_MODO_RODANDO;
    definirPadroesDoJogo(jogo);
    definirPadroesDoJogador(&jogo->jogador, &aplicacao->recursos);
}

void definirPadroesDoJogo( Jogo *jogo )
{
    jogo->tempo = TEMPO_POR_NIVEL;
    jogo->jogador.pontuacao = 0;
    jogo->carregado = false;
    jogo->contadorDeMonstros = 0;
    jogo->contadorDeObstaculos = 0;
    jogo->contadorDeParedes = 0;
}

bool carregarJogoConformeNivel( Jogo *jogo, int nivel )
{
    if( !jogo->inicializado )
    {
        jogo->inicializado = true;
        jogo->jogador.nivelAtual = nivel;
    }

    if( !jogo->carregado )
    {
        carregarParedesPadroes(jogo);

        char nomeArquivo[32];
        snprintf(nomeArquivo, sizeof (char) * 32, "./recursos/niveis/nivel%i.txt", nivel);

        FILE *arquivo = fopen(nomeArquivo, "r");
        if( arquivo == NULL )
        {
            printf("ERRO: Não foi possível ler o arquivo do nível %d!\n", nivel);
        }

        char linha[LARGURA_MAPA_JOGAVEL + 1];
        bool eNovaLinha = false;
        int contador = 0;

        while(fgets(linha, sizeof (linha), arquivo) != NULL)
        {
            eNovaLinha = (bool) strcmp(linha, "\r\n") == 0;

            // Pula a linha em branco lida pelo fgets
            if( !eNovaLinha )
            {
                popularJogoConformeLinha(jogo, linha, contador);
                contador++;
            }
        }

        fclose(arquivo);

        jogo->carregado = true;

        return true;
    }
}

void popularJogoConformeLinha( Jogo *jogo, char linha[], int numeroLinha )
{
    int i = 0;

    for( i = 0; i < LARGURA_MAPA_JOGAVEL; i++ )
    {
        switch(linha[i])
        {
            case 'B':
                jogo->jogador.posicao.x = (i + 1) * TAMANHO_ENTIDADE;
                jogo->jogador.posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE - MARGEM_INICIAL + TAMANHO_SOMBRA;
                jogo->jogador.indice.i = (numeroLinha + 1);
                jogo->jogador.indice.j = (i + 1);

                break;

            case 'S':
                jogo->saida.visivel = false;
                jogo->saida.posicao.x = (i + 1) * TAMANHO_ENTIDADE;
                jogo->saida.posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->saida.indice.i = (numeroLinha + 1);
                jogo->saida.indice.j = (i + 1);

                break;

            case 'M':
                jogo->monstros[jogo->contadorDeMonstros].posicao.x = (i + 1) * TAMANHO_ENTIDADE;
                jogo->monstros[jogo->contadorDeMonstros].posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->monstros[jogo->contadorDeMonstros].indice.i = (numeroLinha + 1);
                jogo->monstros[jogo->contadorDeMonstros].indice.j = (i + 1);

                jogo->contadorDeMonstros = jogo->contadorDeMonstros + 1;

                break;

            case 'P':
                jogo->paredes[jogo->contadorDeParedes].posicao.x = (i + 1) * TAMANHO_ENTIDADE;
                jogo->paredes[jogo->contadorDeParedes].posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->paredes[jogo->contadorDeParedes].indice.i = (numeroLinha + 1);
                jogo->paredes[jogo->contadorDeParedes].indice.j = (i + 1);

                jogo->contadorDeParedes = jogo->contadorDeParedes + 1;

                break;

            case 'O':
                jogo->obstaculos[jogo->contadorDeObstaculos].visivel = true;
                jogo->obstaculos[jogo->contadorDeObstaculos].posicao.x = (i + 1) * TAMANHO_ENTIDADE;
                jogo->obstaculos[jogo->contadorDeObstaculos].posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->obstaculos[jogo->contadorDeObstaculos].indice.i = (numeroLinha + 1);
                jogo->obstaculos[jogo->contadorDeObstaculos].indice.j = (i + 1);

                jogo->contadorDeObstaculos = jogo->contadorDeObstaculos + 1;

                break;
        }
    }
}

void carregarParedesPadroes( Jogo *jogo )
{
    int i, j;

    for( j = 0; j < LARGURA_MAPA_JOGAVEL + 2; j++ )
    {
        jogo->paredes[jogo->contadorDeParedes].posicao.x = j * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].posicao.y = 0 * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].indice.i = 0;
        jogo->paredes[jogo->contadorDeParedes].indice.j = j;

        jogo->contadorDeParedes = jogo->contadorDeParedes + 1;

        jogo->paredes[jogo->contadorDeParedes].posicao.x = j * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].posicao.y = (ALTURA_MAPA_JOGAVEL + 1) * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].indice.i = (ALTURA_MAPA_JOGAVEL + 1);
        jogo->paredes[jogo->contadorDeParedes].indice.j = j;

        jogo->contadorDeParedes = jogo->contadorDeParedes + 1;
    }

    for( i = 0; i < ALTURA_MAPA_JOGAVEL + 2; i++ ) // +2 por causa das paredes
    {
        jogo->paredes[jogo->contadorDeParedes].posicao.x = 0 * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].posicao.y = i * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].indice.i = i;
        jogo->paredes[jogo->contadorDeParedes].indice.j = 0;

        jogo->contadorDeParedes = jogo->contadorDeParedes + 1;

        jogo->paredes[jogo->contadorDeParedes].posicao.x = (LARGURA_MAPA_JOGAVEL + 1) * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].posicao.y = i * TAMANHO_ENTIDADE;
        jogo->paredes[jogo->contadorDeParedes].indice.i = i;
        jogo->paredes[jogo->contadorDeParedes].indice.j = (LARGURA_MAPA_JOGAVEL + 1);

        jogo->contadorDeParedes = jogo->contadorDeParedes + 1;
    }
}

void carregarJogoConformeJogoSalvo( Jogo *jogo )
{
    if( !jogo->inicializado )
    {
        jogo->inicializado = true;
    }
}

void processarEventoDoJogo( Aplicacao *aplicacao, Jogo *jogo, ALLEGRO_EVENT evento )
{
    Jogador *jogador;
    jogador = &jogo->jogador;
    
    switch(evento.type)
    {
        case ALLEGRO_EVENT_TIMER:
        {
            switch(jogo->modo)
            {
                case JOGO_MODO_RODANDO:
                    if( evento.timer.source == aplicacao->timerFPS )
                    {
                        processarTickFPSJogoRodando(aplicacao, jogo);
                    }
                    else if( evento.timer.source == aplicacao->timerRelogio )
                    {
                        if( jogo->tempo == 0 )
                        {
                            jogo->tempo = TEMPO_POR_NIVEL;
                        }
                        
                        jogo->tempo = jogo->tempo - 1;
                    }

                    break;

                case JOGO_MODO_PAUSADO:
                    if( evento.timer.source == aplicacao->timerFPS )
                    {
                        processarTickFPSJogoPausado(aplicacao, jogo);
                    }
                    
                    break;
            }
        }
    }
}

void processarTickFPSJogoRodando( Aplicacao *aplicacao, Jogo *jogo )
{
    Jogador *jogador;
    jogador = &jogo->jogador;

    if( TeclasPressionadas[ALLEGRO_KEY_UP] )
    {
        jogador->direcaoMovimento = DIRECAO_CIMA;
        
        trocarEstadoDoJogador(jogador, &(aplicacao->recursos), JOGADOR_TRAS);
    }
    else if( TeclasPressionadas[ALLEGRO_KEY_RIGHT] )
    {
        jogador->direcaoMovimento = DIRECAO_DIREITA;
        
        trocarEstadoDoJogador(jogador, &(aplicacao->recursos), JOGADOR_DIREITA);
    }
    else if( TeclasPressionadas[ALLEGRO_KEY_DOWN] )
    {
        jogador->direcaoMovimento = DIRECAO_BAIXO;
        
        trocarEstadoDoJogador(jogador, &(aplicacao->recursos), JOGADOR_FRENTE);
    }
    else if( TeclasPressionadas[ALLEGRO_KEY_LEFT] )
    {
        jogador->direcaoMovimento = DIRECAO_ESQUERDA;
        
        trocarEstadoDoJogador(jogador, &(aplicacao->recursos), JOGADOR_ESQUERDA);
    }
    else if( TeclasPressionadas[ALLEGRO_KEY_SPACE] )
    {

    }
    else if( TeclasPressionadas[ALLEGRO_KEY_ESCAPE] )
    {
        jogo->modo = JOGO_MODO_PAUSADO;
        TeclasPressionadas[ALLEGRO_KEY_ESCAPE] = false; // "Desativa" a tecla
    }
    else
    {
        // As constantes de estado pares referem-se ao bomberman em movimento
        // Só troca caso o jogador esteja "em movimento"
        if( jogador->estadoPersonagem % 2 == 0 )
        {
            trocarEstadoDoJogador(jogador, &(aplicacao->recursos), jogador->estadoPersonagem + 1);
        }
        
        jogador->direcaoMovimento = DIRECAO_NULA;
    }

    if( jogador->direcaoMovimento != DIRECAO_NULA )
    {
        alterarPosicaoConformeDirecao(&jogador->posicao, TAMANHO_PASSO, jogador->direcaoMovimento);
        
        int i = 0;

        for( i = 0; i < jogo->contadorDeParedes; i++ )
        {
            if( obterCondicaoDeDestinoPelaDirecao(jogador->indice, jogo->paredes[i].indice, jogador->direcaoMovimento) )
            {
                if( verificarColisao(obterHitboxDoJogador(jogador), obterHitboxPelaPosicao(jogo->paredes[i].posicao)) )
                {
                    alterarPosicaoConformeDirecao(&jogador->posicao, TAMANHO_PASSO, obterDirecaoOposta(jogador->direcaoMovimento));
                }
            }
        }

        for( i = 0; i < jogo->contadorDeObstaculos; i++ )
        {
            if( obterCondicaoDeDestinoPelaDirecao(jogador->indice, jogo->obstaculos[i].indice, jogador->direcaoMovimento) )
            {
                if( verificarColisao(obterHitboxDoJogador(jogador), obterHitboxPelaPosicao(jogo->obstaculos[i].posicao)) )
                {
                    alterarPosicaoConformeDirecao(&jogador->posicao, TAMANHO_PASSO, obterDirecaoOposta(jogador->direcaoMovimento));
                }
            }
        }
    }
    
    jogador->indice = obterPosicaoBruta(jogador->posicao);
}

bool obterCondicaoDeDestinoPelaDirecao(Indice corpo, Indice alvo, int direcao)
{
    switch(direcao)
    {
        case DIRECAO_CIMA:
        {
            return alvo.i <= corpo.i;
        }
        
        case DIRECAO_DIREITA:
        {
            return alvo.j >= corpo.j;
        }
        
        case DIRECAO_BAIXO:
        {
            return alvo.i >= corpo.i;
        }
        
        case DIRECAO_ESQUERDA:
        {
            return alvo.j <= corpo.j;
        }
    }
}

void alterarPosicaoConformeDirecao(Posicao *posicao, int unidades, int direcao)
{
    switch(direcao)
    {
        case DIRECAO_CIMA:
        {
            posicao->y -= unidades;
            
            break;
        }
        
        case DIRECAO_DIREITA:
        {
            posicao->x += unidades;
            
            break;
        }
        
        case DIRECAO_BAIXO:
        {
            posicao->y += unidades;
            
            break;
        }
        
        case DIRECAO_ESQUERDA:
        {
            posicao->x -= unidades;
            
            break;
        }
    }
}

int obterDirecaoOposta(int direcao)
{
    switch(direcao)
    {
        case DIRECAO_CIMA:
        {
            return DIRECAO_BAIXO;
        }
        
        case DIRECAO_DIREITA:
        {
            return DIRECAO_ESQUERDA;
        }
        
        case DIRECAO_BAIXO:
        {
            return DIRECAO_CIMA;
        }
        
        case DIRECAO_ESQUERDA:
        {
            return DIRECAO_DIREITA;
        }
    }
}

void processarTickFPSJogoPausado( Aplicacao *aplicacao, Jogo *jogo )
{
    if( TeclasPressionadas[ALLEGRO_KEY_ESCAPE] )
    {
        limparConteudoDaJanela();
        // Caso aperte novamente o ESC, sai da partida
        aplicacao->modo = MODO_MENU;
    }
    else if( TeclasPressionadas[ALLEGRO_KEY_SPACE] )
    {
        // Caso apertar espaço, volta ao jogo
        jogo->modo = JOGO_MODO_RODANDO;
    }
}

Indice obterPosicaoBruta( Posicao posicao )
{
    Indice indice = {round(posicao.y / TAMANHO_ENTIDADE), round(posicao.x / TAMANHO_ENTIDADE)};

    return indice;
}

Hitbox obterHitboxPelaPosicao( Posicao posicao )
{
    Hitbox hitbox;
    hitbox.x = posicao.x;
    hitbox.y = posicao.y;
    hitbox.xFinal = posicao.x + TAMANHO_ENTIDADE;
    hitbox.yFinal = posicao.y + TAMANHO_ENTIDADE;

    return hitbox;
}

bool verificarColisao( Hitbox corpo, Hitbox alvo )
{
    return (
        alvo.x < corpo.xFinal &&
        alvo.xFinal > corpo.x &&
        alvo.y < corpo.yFinal &&
        alvo.yFinal > corpo.y
        );
}

void desenharJogo( Jogo *jogo, Recursos *recursos )
{
    desenharFundo(recursos);

    int i, j;

    for( i = 0; i < ALTURA_MAPA_JOGAVEL + 2; i++ ) // + 2 por causa das paredes "fixas"
    {
        for( j = 0; j < jogo->contadorDeParedes; j++ )
        {
            if( jogo->paredes[j].indice.i == i )
            {
                desenharParede(&jogo->paredes[j], recursos);
            }
        }

        for( j = 0; j < jogo->contadorDeObstaculos; j++ )
        {
            if( jogo->obstaculos[j].indice.i == i )
            {
                desenharObstaculo(&jogo->obstaculos[j], recursos);
            }
        }

        for( j = 0; j < jogo->contadorDeMonstros; j++ )
        {
            if( jogo->monstros[j].indice.i == i )
            {
                // Desenhar
            }

        }

        if( i == jogo->jogador.indice.i )
        {
            desenharJogador(&jogo->jogador);
        }

    }

    desenharRodape(jogo, recursos);
    
    if( jogo->modo == JOGO_MODO_PAUSADO )
    {
        desenharOverlayDePausa(recursos);
    }

}

void desenharFundo( Recursos *recursos )
{
    int i, j;

    for( i = 0; i < ALTURA_MAPA_JOGAVEL + 2; i++ ) // + 2 por causa das paredes
    {
        for( j = 0; j < LARGURA_MAPA_JOGAVEL + 2; j++ ) // + 2 por causa das paredes
        {
            al_draw_bitmap(recursos->jogoFundo, j * TAMANHO_ENTIDADE, i * TAMANHO_ENTIDADE + TAMANHO_SOMBRA, 0);
        }
    }

}

void desenharRodape(Jogo *jogo, Recursos *recursos)
{
    al_draw_bitmap(recursos->jogoRodape, 0, ALTURA_TELA - ALTURA_RODAPE, 0);
    
    // Desenha a quantidade de vidas
    al_draw_textf(recursos->fonteCantarellBold, al_map_rgb(229, 227, 185), 110, ALTURA_TELA - ALTURA_RODAPE + 1, ALLEGRO_ALIGN_CENTER, "%d", jogo->jogador.vidas);
    
    // Calcula o tempo passado
    int horas, minutos, minutosDigito1, minutosDigito2;
    horas = floor(jogo->tempo / 60.0);
    minutos = jogo->tempo % 60;
    minutosDigito1 = floor(minutos / 10.0);
    minutosDigito2 = minutos % 10;
    // Desenha o tempo na tela
    al_draw_textf(recursos->fonteCantarellBold, al_map_rgb(229, 227, 185), 425, ALTURA_TELA - ALTURA_RODAPE + 1, ALLEGRO_ALIGN_CENTER, "%d%d:%d%d", 0, horas, minutosDigito1, minutosDigito2);
    
    // Desenha a pontuação
    al_draw_textf(recursos->fonteCantarellBold, al_map_rgb(229, 227, 185), 790, ALTURA_TELA - ALTURA_RODAPE + 1, ALLEGRO_ALIGN_LEFT, "%d", jogo->jogador.pontuacao);
}

void desenharParede( Parede *parede, Recursos *recursos )
{
    al_draw_bitmap(recursos->jogoObstaculoFixo, parede->posicao.x, parede->posicao.y, 0);
}

void desenharObstaculo( Obstaculo *obstaculo, Recursos *recursos )
{
    al_draw_bitmap(recursos->jogoObstaculo, obstaculo->posicao.x, obstaculo->posicao.y, 0);
}

void desenharJogador( Jogador *jogador )
{
    atualizarSprite(&jogador->sprite);
    desenharSprite(&jogador->sprite, jogador->posicao);
}

void desenharOverlayDePausa( Recursos *recursos )
{
    al_draw_filled_rectangle(0, 0, LARGURA_TELA, ALTURA_TELA, al_map_rgba(19, 20, 38, 200));
    al_draw_bitmap(recursos->jogoTelaPausa, 0, 0, 0);
}