#include <allegro5/events.h>
#include <stdio.h>
#include <math.h>

#include "../cabecalhos/Jogo.h"

#include "./Jogador.c"

void definirPadroesDoJogo( Jogo *jogo )
{
    jogo->inicializado = false;
    jogo->carregado = false;
    jogo->jogador.nivelAtual = 1;
    jogo->jogador.estadoPersonagem = JOGADOR_FRENTE_DIREITA;
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
        printf("Carregando o nível %d...\n", nivel);

        char nomeArquivo[32];
        snprintf(nomeArquivo, sizeof (char) * 32, "./niveis/nivel%i.txt", nivel);

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
                jogo->jogador.posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE - MARGEM_INICIAL + TAMANHO_SOMBRA_EM_PX;
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
                jogo->monstros[jogo->contadorDeMonstros].vivo = true;
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
    
    printf("CP %d\n", jogo->contadorDeParedes);
}

void carregarJogoConformeJogoSalvo( Jogo *jogo )
{
    if( !jogo->inicializado )
    {
        jogo->inicializado = true;
    }
}

void processarEventoDoJogo( Jogo *jogo, ALLEGRO_EVENT evento )
{
    Jogador *jogador;
    jogador = &jogo->jogador;
    Hitbox hitboxJogador = obterHitboxDoJogador(jogador);

    if( evento.type == ALLEGRO_EVENT_KEY_CHAR )
    {
        switch(evento.keyboard.keycode)
        {
            case ALLEGRO_KEY_UP:
            {
                hitboxJogador.y -= TAMANHO_PASSO_EM_PX;

                if( !jogadorAtingeMapaAoIrParaCima(hitboxJogador) )
                {
                    jogador->posicao.y -= TAMANHO_PASSO_EM_PX;
                }

                alternarEstadoDoPersonagemAoIrParaCima(jogador);

                break;
            }

            case ALLEGRO_KEY_RIGHT:
            {
                hitboxJogador.x += TAMANHO_PASSO_EM_PX;

                if( !jogadorAtingeMapaAoIrParaDireita(hitboxJogador) )
                {
                    jogador->posicao.x += TAMANHO_PASSO_EM_PX;
                }

                alternarEstadoDoPersonagemAoIrParaDireita(jogador);

                break;
            }

            case ALLEGRO_KEY_DOWN:
            {
                hitboxJogador.y += TAMANHO_PASSO_EM_PX;

                if( !jogadorAtingeMapaAoIrParaBaixo(hitboxJogador) )
                {
                    jogador->posicao.y += TAMANHO_PASSO_EM_PX;
                }

                alternarEstadoDoPersonagemAoIrParaBaixo(jogador);

                break;

            }

            case ALLEGRO_KEY_LEFT:
            {
                hitboxJogador.x -= TAMANHO_PASSO_EM_PX;

                if( !jogadorAtingeMapaAoIrParaEsquerda(hitboxJogador) )
                {
                    jogador->posicao.x -= TAMANHO_PASSO_EM_PX;
                }

                alternarEstadoDoPersonagemAoIrParaEsquerda(jogador);

                break;
            }

            case ALLEGRO_KEY_SPACE:
                // Plantar bomba

                break;
        }

        jogador->indice.i = round(jogador->posicao.y / 50);
        jogador->indice.j = round(jogador->posicao.x / 50);
    }
}

bool posicaoSobrepoeEmX( Hitbox posicao, Hitbox referencia )
{
    if( (referencia.x < posicao.x) && (posicao.x < (referencia.x + TAMANHO_ENTIDADE))
        || (referencia.x < (posicao.x + TAMANHO_ENTIDADE)) && ((posicao.x + TAMANHO_ENTIDADE) < (referencia.x + TAMANHO_ENTIDADE)) )
    {
        printf("Atingiu em x, %f e %f\n", posicao.x, referencia.x);

        return true;
    }

    return false;
}

bool posicaoSobrepoeEmY( Hitbox posicao, Hitbox referencia )
{
    if( (referencia.y < posicao.y) && (posicao.y < (referencia.y + TAMANHO_ENTIDADE))
        || (referencia.y < (posicao.y + TAMANHO_ENTIDADE)) && ((posicao.y + TAMANHO_ENTIDADE) < (referencia.y + TAMANHO_ENTIDADE)) )
    {
        printf("Atingiu em y, %f e %f\n", posicao.y, referencia.y);

        return true;
    }

    return false;
}

bool posicaoSobrepoe( Hitbox posicao, Hitbox referencia )
{
    if( posicaoSobrepoeEmX(posicao, referencia) )
    {
        if( !posicaoSobrepoeEmY(posicao, referencia) )
        {
            if( posicao.y == referencia.y )
            {
                return true;
            }

            return false;
        }

        return true;
    }
    else if( posicaoSobrepoeEmY(posicao, referencia) )
    {
        if( !posicaoSobrepoeEmX(posicao, referencia) )
        {
            if( posicao.x == referencia.x )
            {
                return true;
            }

            return false;
        }

        return true;
    }

    return false;
}

void desenharJogo( Jogo *jogo, Recursos *recursos )
{
    // Pinta a tela com a cor definida
    al_clear_to_color(obterCorDeFundo());

    int i, j, k;
    
    // Desenha as paredes do mapa
    for( i = 0; i < ALTURA_MAPA_JOGAVEL + 2; i++ ) // +2 por causa das paredes
    {
        for( j = 0; j < LARGURA_MAPA_JOGAVEL + 2; j++ ) // +2 por causa das paredes
        {
            if( (i == 0 || i == (ALTURA_MAPA_JOGAVEL + 1)) // Se está na primeira ou na última linha
                || (j == 0 || j == (LARGURA_MAPA_JOGAVEL + 1)) ) // Se está na primeira ou na última coluna
            {
                Posicao posicao = {j * TAMANHO_ENTIDADE, i * TAMANHO_ENTIDADE};

                desenharParede(posicao, recursos);
            }
        }
        
        for( k = 0; k < jogo->contadorDeParedes; k++ )
        {
            if( jogo->paredes[k].indice.i == i )
            {
                desenharParede(jogo->paredes[k].posicao, recursos);
            }
        }
        
        if( i == jogo->jogador.indice.i )
        {
            desenharJogador(&jogo->jogador, recursos);
        }

    }

}

void desenharParede( Posicao posicao, Recursos *recursos )
{
    al_draw_bitmap(recursos->jogoObstaculoFixo, posicao.x, posicao.y, 0);
}