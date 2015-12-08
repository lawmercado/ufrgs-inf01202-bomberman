#include <stdio.h>
#include <math.h>
#include <allegro5/events.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "../cabecalhos/Jogo.h"

#include "./UtilidadesJogo.c"
#include "./Jogador.c"
#include "./Monstro.c"
#include "./Obstaculo.c"
#include "./Bomba.c"

/**
 * Cria um jogo "do zero"
 * 
 * @param *Jogo jogo Referência ao jogo
 */
void criarNovoJogo( Jogo *jogo )
{
    jogo->modo = JOGO_MODO_RODANDO;
    definirPadroesDoJogo(jogo);
    definirPadroesDoJogador(&jogo->jogador);
    definirPadroesDasBombas(jogo);
}

/**
 * Define os parâmetros default do jogo
 * 
 * @param *Jogo jogo Referência ao jogo
 */
void definirPadroesDoJogo( Jogo *jogo )
{
    jogo->tempo = TEMPO_POR_NIVEL;
    jogo->carregado = false;
    jogo->contadorDeBombas = 0;

    jogo->contadorDeMonstros = 0;
    jogo->contadorDeObstaculos = 0;
    jogo->contadorDeParedes = 0;

    TeclasPressionadas[ALLEGRO_KEY_SPACE] = false; // Reseta a tecla de espaço
    
    int i = 0;
    
    for( i = 0; i < MAXIMO_BOMBAS_PERMITIDAS; i++ )
    {
        jogo->bombas[i].estado = BOMBA_DESATIVADA;
    }
}

/**
 * Conforme o nível, popula as estruturas de jogo
 * 
 * @param *Jogo jogo Referência ao jogo
 * @param integer nivel Nivel a ser carregado
 * 
 * @return bool Se o carregamento foi bem sucedido
 */
bool carregarJogoConformeNivel( Jogo *jogo, int nivel )
{
    // Se o jogo foi carregado
    if( !jogo->carregado )
    {
        carregarParedesPadroes(jogo);

        char nomeArquivo[32];
        // Cria a string "personalizada" conforme o nivel
        snprintf(nomeArquivo, sizeof (char) * 32, "./recursos/niveis/nivel%i.txt", nivel);

        FILE *arquivo = fopen(nomeArquivo, "r");
        if( arquivo == NULL )
        {
            printf("ERRO: Não foi possível ler o arquivo do nível %d!\n", nivel);

            return false;
        }

        printf("Carregando arquivo nivel%d.txt...\n", nivel);

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

/**
 * Dado a linha do esqueleto de um nível, popula as estruturas do jogo
 * 
 * @param *Jogo jogo Referência ao jogo
 * @param char[] linha Linha do arquivo
 * @param integer numeroLinha Número da linha do arquivo
 */
void popularJogoConformeLinha( Jogo *jogo, char linha[], int numeroLinha )
{
    int j = 0;

    for( j = 0; j < LARGURA_MAPA_JOGAVEL; j++ )
    {
        switch(linha[j])
        {
            case 'B':
            {
                Indice indice = {(numeroLinha + 1), (j + 1)};

                moverJogadorConformeIndice(&jogo->jogador, indice);
                jogo->jogador.indice = indice;
                jogo->jogador.indiceInicial = indice;

                break;
            }

            case 'S':
            {
                jogo->saida.estado = ENTIDADE_INVISIVEL;
                jogo->saida.posicao.x = (j + 1) * TAMANHO_ENTIDADE;
                jogo->saida.posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->saida.indice.i = (numeroLinha + 1);
                jogo->saida.indice.j = (j + 1);

                break;
            }

            case 'M':
            {
                jogo->monstros[jogo->contadorDeMonstros].posicao.x = (j + 1) * TAMANHO_ENTIDADE;
                jogo->monstros[jogo->contadorDeMonstros].posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->monstros[jogo->contadorDeMonstros].indice.i = (numeroLinha + 1);
                jogo->monstros[jogo->contadorDeMonstros].indice.j = (j + 1);

                definirPadroesDoMonstro(&jogo->monstros[jogo->contadorDeMonstros]);

                jogo->contadorDeMonstros = jogo->contadorDeMonstros + 1;

                break;
            }

            case 'P':
            {
                jogo->paredes[jogo->contadorDeParedes].posicao.x = (j + 1) * TAMANHO_ENTIDADE;
                jogo->paredes[jogo->contadorDeParedes].posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->paredes[jogo->contadorDeParedes].indice.i = (numeroLinha + 1);
                jogo->paredes[jogo->contadorDeParedes].indice.j = (j + 1);

                jogo->contadorDeParedes = jogo->contadorDeParedes + 1;

                break;
            }

            case 'O':
            {
                jogo->obstaculos[jogo->contadorDeObstaculos].posicao.x = (j + 1) * TAMANHO_ENTIDADE;
                jogo->obstaculos[jogo->contadorDeObstaculos].posicao.y = (numeroLinha + 1) * TAMANHO_ENTIDADE;
                jogo->obstaculos[jogo->contadorDeObstaculos].indice.i = (numeroLinha + 1);
                jogo->obstaculos[jogo->contadorDeObstaculos].indice.j = (j + 1);

                definirPadroesDoObstaculo(&jogo->obstaculos[jogo->contadorDeObstaculos]);

                jogo->contadorDeObstaculos = jogo->contadorDeObstaculos + 1;

                break;
            }
        }
    }
}

/**
 * Carrega as paredes do mapa em si, fixas do jogo
 * 
 * @param *Jogo jogo Referência ao jogo
 */
void carregarParedesPadroes( Jogo *jogo )
{
    int i, j;
    
    // Popula as paredes das colunas
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

    // Popula as paredes das linhas
    for( i = 0; i < ALTURA_MAPA_JOGAVEL + 2; i++ )
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

/**
 * Reponsável por tratar os eventos provindos do jogo
 * 
 * @param *Jogo jogo Referência ao jogo
 * @param ALLEGRO_EVENT evento Evento pego pela aplicação
 */
void processarEventoDoJogo( Jogo *jogo, ALLEGRO_EVENT evento )
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
                        processarTickFPSJogoRodando(jogo);
                    }
                    else if( evento.timer.source == aplicacao->timerRelogio )
                    {

                        if( (jogo->jogador.estado == ENTIDADE_MORRENDO && jogo->jogador.tempo == 0) || jogo->tempo == 0 )
                        {
                            trocarEstadoDoJogador(&jogo->jogador, ENTIDADE_FRENTE_PARADA);

                            if( (jogador->vidas - 1) >= 0 )
                            {
                                jogador->vidas--;
                                definirPadroesDoJogo(jogo);
                            }
                            else
                            {
                                jogo->modo = JOGO_MODO_GAMEOVER;
                            }

                        }
                        else
                        {
                            jogo->jogador.tempo--;
                        }

                        jogo->tempo--;
                        
                        int i, j, k; // Variáveis dos índices
                        
                        // Altera os estados dos monstros
                        for( i = 0; i < jogo->contadorDeMonstros; i++ )
                        {
                            if( jogo->monstros[i].estado == ENTIDADE_MORRENDO && jogo->monstros[i].tempo == 0 )
                            {
                                jogo->monstros[i].estado = ENTIDADE_MORTA;
                            }
                            else if( jogo->monstros[i].estado != ENTIDADE_MORTA )
                            {
                                jogo->monstros[i].tempo--;
                            }
                        }

                        // Altera os estados dos obstáculos
                        for( i = 0; i < jogo->contadorDeObstaculos; i++ )
                        {
                            if( jogo->obstaculos[i].estado == ENTIDADE_MORRENDO )
                            {
                                if( jogo->obstaculos[i].tempo == 0 )
                                {
                                    trocarEstadoDoObstaculo(&jogo->obstaculos[i], ENTIDADE_INVISIVEL);
                                }
                                else
                                {
                                    jogo->obstaculos[i].tempo--;
                                }
                            }
                        }
                        
                        // Altera os estados das bombas conforme os segundos passados
                        for( i = 0; i < MAXIMO_BOMBAS_PERMITIDAS; i++ )
                        {
                            if( jogo->bombas[i].estado == BOMBA_PREPARADA )
                            {
                                jogo->bombas[i].tempoAteExplodir--;

                                // Caso tenha explodido
                                if( jogo->bombas[i].tempoAteExplodir == 0 )
                                {
                                    jogo->bombas[i].tempoExplodindo = BOMBA_TEMPO_EXPLOSAO;
                                    jogo->bombas[i].estado = BOMBA_EXPLODINDO;
                                    
                                    // Cria as explosões nas quatro direções
                                    for( j = 0; j < 4; j++ )
                                    {
                                        for( k = 0; k < jogo->bombas[i].raioDeExplosao; k++ )
                                        {
                                            switch(j)
                                            {
                                                case DIRECAO_CIMA:
                                                    jogo->bombas[i].explosoesCima[k].posicao = jogo->bombas[i].posicao;
                                                    jogo->bombas[i].explosoesCima[k].estado = ENTIDADE_VISIVEL;
                                                    jogo->bombas[i].explosoesCima[k].posicao.y -= (k + 1) * TAMANHO_ENTIDADE;
                                                    jogo->bombas[i].explosoesCima[k].indice = obterPosicaoBruta(jogo->bombas[i].explosoesCima[k].posicao);
                                                    break;

                                                case DIRECAO_DIREITA:
                                                    jogo->bombas[i].explosoesDireita[k].posicao = jogo->bombas[i].posicao;
                                                    jogo->bombas[i].explosoesDireita[k].estado = ENTIDADE_VISIVEL;
                                                    jogo->bombas[i].explosoesDireita[k].posicao.x += (k + 1) * TAMANHO_ENTIDADE;
                                                    jogo->bombas[i].explosoesDireita[k].indice = obterPosicaoBruta(jogo->bombas[i].explosoesDireita[k].posicao);

                                                    break;

                                                case DIRECAO_BAIXO:
                                                    jogo->bombas[i].explosoesBaixo[k].posicao = jogo->bombas[i].posicao;
                                                    jogo->bombas[i].explosoesBaixo[k].estado = ENTIDADE_VISIVEL;
                                                    jogo->bombas[i].explosoesBaixo[k].posicao.y += (k + 1) * TAMANHO_ENTIDADE;
                                                    jogo->bombas[i].explosoesBaixo[k].indice = obterPosicaoBruta(jogo->bombas[i].explosoesBaixo[k].posicao);

                                                    break;

                                                case DIRECAO_ESQUERDA:
                                                    jogo->bombas[i].explosoesEsquerda[k].posicao = jogo->bombas[i].posicao;
                                                    jogo->bombas[i].explosoesEsquerda[k].estado = ENTIDADE_VISIVEL;
                                                    jogo->bombas[i].explosoesEsquerda[k].posicao.x -= (k + 1) * TAMANHO_ENTIDADE;
                                                    jogo->bombas[i].explosoesEsquerda[k].indice = obterPosicaoBruta(jogo->bombas[i].explosoesEsquerda[k].posicao);

                                                    break;
                                            }
                                        }
                                    }
                                    
                                    // Verifica qualquer possível impacto da bomba no jogo
                                    verificarImpactoDaBombaNoJogo(&jogo->bombas[i], jogo);
                                }
                            }
                            else if( jogo->bombas[i].estado == BOMBA_EXPLODINDO )
                            {
                                if( jogo->bombas[i].tempoExplodindo <= 0 )
                                {
                                    jogo->bombas[i].estado = BOMBA_DESATIVADA;
                                    jogo->contadorDeBombas--;

                                    for( j = 0; j < 3; j++ )
                                    {
                                        for( k = 0; k < jogo->bombas[i].raioDeExplosao; k++ )
                                        {
                                            jogo->bombas[i].explosoesCima[k].estado = ENTIDADE_INVISIVEL;
                                            jogo->bombas[i].explosoesDireita[k].estado = ENTIDADE_INVISIVEL;
                                            jogo->bombas[i].explosoesBaixo[k].estado = ENTIDADE_INVISIVEL;
                                            jogo->bombas[i].explosoesEsquerda[k].estado = ENTIDADE_INVISIVEL;
                                        }
                                    }
                                }

                                jogo->bombas[i].tempoExplodindo--;
                            }
                        }
                    }

                    break;

                case JOGO_MODO_PAUSADO:
                    if( evento.timer.source == aplicacao->timerFPS )
                    {
                        processarTickFPSJogoPausado(jogo);
                    }

                    break;

                case JOGO_MODO_GAMEOVER:
                    if( evento.timer.source == aplicacao->timerFPS )
                    {
                        processarTickFPSJogoGameOver(jogo);
                    }

                    break;
            }
        }
        
        case ALLEGRO_EVENT_KEY_CHAR:
        {
            switch(jogo->modo)
            {
                case JOGO_MODO_GAMEOVER:
                {
                    if( evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE )
                    {
                        if( al_ustr_size(jogo->jogador.nome) > 0 )
                        {
                            if( !al_ustr_remove_chr(jogo->jogador.nome, al_ustr_size(jogo->jogador.nome) - 1) )
                            {
                                char bufferAuxiliar[TAMANHO_MAXIMO_NOME];
                                
                                al_ustr_to_buffer(jogo->jogador.nome, bufferAuxiliar, al_ustr_size(jogo->jogador.nome) - 1);
                                
                                jogo->jogador.nome = al_ustr_new_from_buffer(bufferAuxiliar, al_ustr_size(jogo->jogador.nome) - 2);
                            }
                        }
                    }
                    else
                    {
                        int unichar = evento.keyboard.unichar;

                        if( unichar >= 32 )
                        {
                            if( al_ustr_size(jogo->jogador.nome) < TAMANHO_MAXIMO_NOME )
                            {
                                al_ustr_append_chr(jogo->jogador.nome, unichar);

                            }
                        }
                    }

                    break;
                }
            }
        }
    }
}

/**
 * Processa o tick do FPS do jogo
 * 
 * @param *Jogo jogo Referência do jogo
 */
void processarTickFPSJogoRodando( Jogo *jogo )
{
    Jogador *jogador;
    jogador = &jogo->jogador;
    int i = 0;

    if( jogador->estado != ENTIDADE_MORRENDO )
    {
        if( TeclasPressionadas[ALLEGRO_KEY_UP] )
        {
            jogador->direcaoMovimento = DIRECAO_CIMA;

            trocarEstadoDoJogador(jogador, ENTIDADE_TRAS);
        }
        else if( TeclasPressionadas[ALLEGRO_KEY_RIGHT] )
        {
            jogador->direcaoMovimento = DIRECAO_DIREITA;

            trocarEstadoDoJogador(jogador, ENTIDADE_DIREITA);
        }
        else if( TeclasPressionadas[ALLEGRO_KEY_DOWN] )
        {
            jogador->direcaoMovimento = DIRECAO_BAIXO;

            trocarEstadoDoJogador(jogador, ENTIDADE_FRENTE);
        }
        else if( TeclasPressionadas[ALLEGRO_KEY_LEFT] )
        {
            jogador->direcaoMovimento = DIRECAO_ESQUERDA;

            trocarEstadoDoJogador(jogador, ENTIDADE_ESQUERDA);
        }
        else if( TeclasPressionadas[ALLEGRO_KEY_SPACE] )
        {
            plantarBomba(jogo);
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
            if( jogador->estado % 2 == 0 )
            {
                trocarEstadoDoJogador(jogador, jogador->estado + 1);
            }

            jogador->direcaoMovimento = DIRECAO_NULA;
        }

        if( jogador->direcaoMovimento != DIRECAO_NULA )
        {
            alterarPosicaoPelaDirecao(&jogador->posicao, JOGADOR_TAMANHO_PASSO, jogador->direcaoMovimento);

            for( i = 0; i < jogo->contadorDeParedes; i++ )
            {
                if( obterCondicaoDeDestinoPelaDirecao(jogador->indice, jogo->paredes[i].indice, jogador->direcaoMovimento) )
                {
                    if( verificarColisao(obterHitboxDoJogador(jogador), obterHitboxPelaPosicao(jogo->paredes[i].posicao)) )
                    {
                        alterarPosicaoPelaDirecao(&jogador->posicao, JOGADOR_TAMANHO_PASSO, obterDirecaoOposta(jogador->direcaoMovimento));
                    }
                }
            }

            for( i = 0; i < jogo->contadorDeObstaculos; i++ )
            {
                if( jogo->obstaculos[i].estado == ENTIDADE_VISIVEL )
                {
                    if( obterCondicaoDeDestinoPelaDirecao(jogador->indice, jogo->obstaculos[i].indice, jogador->direcaoMovimento) )
                    {
                        if( verificarColisao(obterHitboxDoJogador(jogador), obterHitboxPelaPosicao(jogo->obstaculos[i].posicao)) )
                        {
                            alterarPosicaoPelaDirecao(&jogador->posicao, JOGADOR_TAMANHO_PASSO, obterDirecaoOposta(jogador->direcaoMovimento));
                        }
                    }
                }
            }

            for( i = 0; i < jogo->contadorDeMonstros; i++ )
            {
                if( jogo->monstros[i].estado != ENTIDADE_MORTA && jogo->monstros[i].estado != ENTIDADE_MORRENDO )
                {
                    if( obterCondicaoDeDestinoPelaDirecao(jogador->indice, jogo->monstros[i].indice, jogador->direcaoMovimento) )
                    {
                        if( verificarColisao(obterHitboxDoJogador(jogador), obterHitboxPelaPosicao(jogo->monstros[i].posicao)) )
                        {
                            alterarPosicaoPelaDirecao(&jogador->posicao, JOGADOR_TAMANHO_PASSO, obterDirecaoOposta(jogador->direcaoMovimento));

                            trocarEstadoDoJogador(jogador, ENTIDADE_MORRENDO);
                        }
                    }
                }
            }

            if( jogo->saida.estado == ENTIDADE_INVISIVEL )
            {
                if( obterCondicaoDeDestinoPelaDirecao(jogador->indice, jogo->saida.indice, jogador->direcaoMovimento) )
                {
                    if( verificarColisao(obterHitboxDoJogador(jogador), obterHitboxPelaPosicao(jogo->saida.posicao)) )
                    {
                        alterarPosicaoPelaDirecao(&jogador->posicao, JOGADOR_TAMANHO_PASSO, obterDirecaoOposta(jogador->direcaoMovimento));
                    }
                }
            }
            else if( jogo->saida.estado == ENTIDADE_VISIVEL )
            {
                if( obterCondicaoDeDestinoPelaDirecao(jogador->indice, jogo->saida.indice, jogador->direcaoMovimento) )
                {
                    if( verificarColisao(obterHitboxDoJogador(jogador), obterHitboxPelaPosicao(jogo->saida.posicao)) )
                    {
                        // Atualiza a pontuação
                        jogo->jogador.pontuacao += jogo->tempo * JOGADOR_PONTUACAO_POR_TEMPO;
                        
                        if( jogo->jogador.nivelAtual < JOGADOR_NIVEL_MAXIMO )
                        {
                            jogo->jogador.nivelAtual++;
                            definirPadroesDoJogo(jogo);
                        }
                        else
                        {
                            jogo->modo = JOGO_MODO_GAMEOVER;
                        }
                    }
                }
            }
        }

        // Atualiza o indice do jogador
        jogador->indice = obterPosicaoBrutaDoJogador(obterHitboxDoJogador(jogador));
    }

    Monstro *monstro;
    int j;

    // Movimenta os monstros
    for( i = 0; i < jogo->contadorDeMonstros; i++ )
    {
        if( jogo->monstros[i].estado != ENTIDADE_MORTA && jogo->monstros[i].estado != ENTIDADE_MORRENDO )
        {
            monstro = &jogo->monstros[i];
            alterarPosicaoPelaDirecao(&(monstro->posicao), MONSTRO_TAMANHO_PASSO, monstro->direcaoMovimento);

            for( j = 0; j < jogo->contadorDeParedes; j++ )
            {
                if( obterCondicaoDeDestinoPelaDirecao(monstro->indice, jogo->paredes[j].indice, monstro->direcaoMovimento) )
                {
                    if( verificarColisao(obterHitboxPelaPosicao(monstro->posicao), obterHitboxPelaPosicao(jogo->paredes[j].posicao)) )
                    {
                        alterarPosicaoPelaDirecao(&(monstro->posicao), MONSTRO_TAMANHO_PASSO, obterDirecaoOposta(monstro->direcaoMovimento));

                        monstro->direcaoMovimento = obterDirecaoDiferenteAleatoria(monstro->direcaoMovimento);
                    }
                }
            }

            for( j = 0; j < jogo->contadorDeObstaculos; j++ )
            {
                if( jogo->obstaculos[j].estado == ENTIDADE_VISIVEL )
                {
                    if( obterCondicaoDeDestinoPelaDirecao(monstro->indice, jogo->obstaculos[j].indice, monstro->direcaoMovimento) )
                    {
                        if( verificarColisao(obterHitboxPelaPosicao(monstro->posicao), obterHitboxPelaPosicao(jogo->obstaculos[j].posicao)) )
                        {
                            alterarPosicaoPelaDirecao(&(monstro->posicao), MONSTRO_TAMANHO_PASSO, obterDirecaoOposta(monstro->direcaoMovimento));

                            monstro->direcaoMovimento = obterDirecaoDiferenteAleatoria(monstro->direcaoMovimento);
                        }
                    }
                }
            }

            if( obterCondicaoDeDestinoPelaDirecao(monstro->indice, jogo->saida.indice, monstro->direcaoMovimento) )
            {
                // Apenas se a saída estiver escondida
                if( jogo->saida.estado == ENTIDADE_INVISIVEL )
                {
                    if( verificarColisao(obterHitboxPelaPosicao(monstro->posicao), obterHitboxPelaPosicao(jogo->saida.posicao)) )
                    {
                        alterarPosicaoPelaDirecao(&monstro->posicao, MONSTRO_TAMANHO_PASSO, obterDirecaoOposta(monstro->direcaoMovimento));

                        monstro->direcaoMovimento = obterDirecaoDiferenteAleatoria(monstro->direcaoMovimento);
                    }
                }
            }

            // Verifica se colide com o jogador
            if( verificarColisao(obterHitboxPelaPosicao(monstro->posicao), obterHitboxDoJogador(jogador)) && jogador->estado != ENTIDADE_MORTA )
            {
                alterarPosicaoPelaDirecao(&(monstro->posicao), MONSTRO_TAMANHO_PASSO, obterDirecaoOposta(monstro->direcaoMovimento));

                // Mata o jogador
                trocarEstadoDoJogador(jogador, ENTIDADE_MORRENDO);

            }

            trocarEstadoDoMonstro(monstro, obterEstadoPelaDirecao(monstro->direcaoMovimento));

            // Atualiza o indice do jogador
            monstro->indice = obterPosicaoBruta(monstro->posicao);
        }
    }

    // Verifica as bombas
    for( i = 0; i < jogo->contadorDeBombas; i++ )
    {
        if( jogo->bombas[i].estado == BOMBA_EXPLODINDO )
        {
            verificarImpactoDaBombaNoJogo(&jogo->bombas[i], jogo);
        }
    }
}

/**
 * Processa o tick do FPS quando o jogo está pausado
 * 
 * @param *Jogo jogo Referência do jogo
 */
void processarTickFPSJogoPausado( Jogo *jogo )
{
    if( TeclasPressionadas[ALLEGRO_KEY_ESCAPE] )
    {
        // Caso aperte novamente o ESC, sai da partida
        aplicacao->modo = MODO_MENU;
    }
    else if( TeclasPressionadas[ALLEGRO_KEY_SPACE] )
    {
        // Caso apertar espaço, volta ao jogo
        jogo->modo = JOGO_MODO_RODANDO;
        
        // Corrige o bug de sair da tela de pause e plantar uma bomba
        TeclasPressionadas[ALLEGRO_KEY_SPACE] = false;
    }
}

/**
 * Processa o tick do FPS quando o jogo está em modo game over
 * 
 * @param *Jogo jogo Referência do jogo
 */
void processarTickFPSJogoGameOver( Jogo *jogo )
{
    if( TeclasPressionadas[ALLEGRO_KEY_ENTER] )
    {
        salvarPontuacaoDoJogador(&jogo->jogador);

        aplicacao->modo = MODO_MENU;
    }
    else if( TeclasPressionadas[ALLEGRO_KEY_ESCAPE] )
    {
        aplicacao->modo = MODO_MENU;
    }
}

/**
 * Verifica o impacto da bomba (atingiu alguma entidade) e toma as devidas providências
 * 
 * @param *Bomba bomba Bomba a ser verificada
 * @param *Jogo jogo Referência do jogo
 */
void verificarImpactoDaBombaNoJogo( Bomba *bomba, Jogo *jogo )
{
    int i, j;
    Hitbox hitboxExplosaoCima;
    Hitbox hitboxExplosaoDireita;
    Hitbox hitboxExplosaoBaixo;
    Hitbox hitboxExplosaoEsquerda;

    for( i = 0; i < bomba->raioDeExplosao; i++ )
    {
        hitboxExplosaoCima = obterHitboxPelaPosicao(bomba->explosoesCima[i].posicao);
        hitboxExplosaoDireita = obterHitboxPelaPosicao(bomba->explosoesDireita[i].posicao);
        hitboxExplosaoBaixo = obterHitboxPelaPosicao(bomba->explosoesBaixo[i].posicao);
        hitboxExplosaoEsquerda = obterHitboxPelaPosicao(bomba->explosoesEsquerda[i].posicao);

        if( i > 0 && bomba->explosoesCima[i - 1].estado == ENTIDADE_INVISIVEL )
        {
            bomba->explosoesCima[i].estado = ENTIDADE_INVISIVEL;
        }

        if( i > 0 && bomba->explosoesDireita[i - 1].estado == ENTIDADE_INVISIVEL )
        {
            bomba->explosoesDireita[i].estado = ENTIDADE_INVISIVEL;
        }

        if( i > 0 && bomba->explosoesBaixo[i - 1].estado == ENTIDADE_INVISIVEL )
        {
            bomba->explosoesBaixo[i].estado = ENTIDADE_INVISIVEL;
        }

        if( i > 0 && bomba->explosoesEsquerda[i - 1].estado == ENTIDADE_INVISIVEL )
        {
            bomba->explosoesEsquerda[i].estado = ENTIDADE_INVISIVEL;
        }

        for( j = 0; j < jogo->contadorDeParedes; j++ )
        {
            if( bomba->explosoesCima[i].estado != ENTIDADE_INVISIVEL )
            {
                if( verificarColisao(hitboxExplosaoCima, obterHitboxPelaPosicao(jogo->paredes[j].posicao)) )
                {
                    bomba->explosoesCima[i].estado = ENTIDADE_INVISIVEL;
                }
            }

            if( bomba->explosoesDireita[i].estado != ENTIDADE_INVISIVEL )
            {
                if( verificarColisao(hitboxExplosaoDireita, obterHitboxPelaPosicao(jogo->paredes[j].posicao)) )
                {
                    bomba->explosoesDireita[i].estado = ENTIDADE_INVISIVEL;
                }
            }

            if( bomba->explosoesBaixo[i].estado != ENTIDADE_INVISIVEL )
            {
                if( verificarColisao(hitboxExplosaoBaixo, obterHitboxPelaPosicao(jogo->paredes[j].posicao)) )
                {
                    bomba->explosoesBaixo[i].estado = ENTIDADE_INVISIVEL;
                }
            }

            if( bomba->explosoesEsquerda[i].estado != ENTIDADE_INVISIVEL )
            {
                if( verificarColisao(hitboxExplosaoEsquerda, obterHitboxPelaPosicao(jogo->paredes[j].posicao)) )
                {
                    bomba->explosoesEsquerda[i].estado = ENTIDADE_INVISIVEL;
                }
            }
        }

        for( j = 0; j < jogo->contadorDeObstaculos; j++ )
        {
            if( jogo->obstaculos[j].estado == ENTIDADE_VISIVEL )
            {
                if( bomba->explosoesCima[i].estado != ENTIDADE_INVISIVEL )
                {
                    if( verificarColisao(hitboxExplosaoCima, obterHitboxPelaPosicao(jogo->obstaculos[j].posicao)) )
                    {
                        bomba->explosoesCima[i + 1].estado = ENTIDADE_INVISIVEL;
                        trocarEstadoDoObstaculo(&jogo->obstaculos[j], ENTIDADE_MORRENDO);
                    }
                }

                if( bomba->explosoesDireita[i].estado != ENTIDADE_INVISIVEL )
                {
                    if( verificarColisao(hitboxExplosaoDireita, obterHitboxPelaPosicao(jogo->obstaculos[j].posicao)) )
                    {
                        bomba->explosoesDireita[i + 1].estado = ENTIDADE_INVISIVEL;
                        trocarEstadoDoObstaculo(&jogo->obstaculos[j], ENTIDADE_MORRENDO);
                    }
                }

                if( bomba->explosoesBaixo[i].estado != ENTIDADE_INVISIVEL )
                {
                    if( verificarColisao(hitboxExplosaoBaixo, obterHitboxPelaPosicao(jogo->obstaculos[j].posicao)) )
                    {
                        bomba->explosoesBaixo[i + 1].estado = ENTIDADE_INVISIVEL;
                        trocarEstadoDoObstaculo(&jogo->obstaculos[j], ENTIDADE_MORRENDO);
                    }
                }

                if( bomba->explosoesEsquerda[i].estado != ENTIDADE_INVISIVEL )
                {
                    if( verificarColisao(hitboxExplosaoEsquerda, obterHitboxPelaPosicao(jogo->obstaculos[j].posicao)) )
                    {
                        bomba->explosoesEsquerda[i + 1].estado = ENTIDADE_INVISIVEL;
                        trocarEstadoDoObstaculo(&jogo->obstaculos[j], ENTIDADE_MORRENDO);
                    }
                }
            }
        }

        bool monstroAtingido = false;
        
        for( j = 0; j < jogo->contadorDeMonstros; j++ )
        {
            monstroAtingido = false;
            
            if( jogo->monstros[j].estado != ENTIDADE_MORRENDO && jogo->monstros[j].estado != ENTIDADE_MORTA )
            {
                if( bomba->explosoesCima[i].estado != ENTIDADE_INVISIVEL )
                {
                    if( verificarColisao(hitboxExplosaoCima, obterHitboxPelaPosicao(jogo->monstros[j].posicao)) )
                    {
                        trocarEstadoDoMonstro(&jogo->monstros[j], ENTIDADE_MORRENDO);
                        jogo->jogador.pontuacao += JOGADOR_PONTUACAO_POR_MONSTRO;
                        
                        monstroAtingido = true;
                    }
                }

                if( bomba->explosoesDireita[i].estado != ENTIDADE_INVISIVEL && !monstroAtingido )
                {
                    if( verificarColisao(hitboxExplosaoDireita, obterHitboxPelaPosicao(jogo->monstros[j].posicao)) )
                    {
                        trocarEstadoDoMonstro(&jogo->monstros[j], ENTIDADE_MORRENDO);
                        jogo->jogador.pontuacao += JOGADOR_PONTUACAO_POR_MONSTRO;
                        
                        monstroAtingido = true;
                    }
                }

                if( bomba->explosoesBaixo[i].estado != ENTIDADE_INVISIVEL && !monstroAtingido )
                {
                    if( verificarColisao(hitboxExplosaoBaixo, obterHitboxPelaPosicao(jogo->monstros[j].posicao)) )
                    {
                        trocarEstadoDoMonstro(&jogo->monstros[j], ENTIDADE_MORRENDO);
                        jogo->jogador.pontuacao += JOGADOR_PONTUACAO_POR_MONSTRO;
                        
                        monstroAtingido = true;
                    }
                }

                if( bomba->explosoesEsquerda[i].estado != ENTIDADE_INVISIVEL && !monstroAtingido )
                {
                    if( verificarColisao(hitboxExplosaoEsquerda, obterHitboxPelaPosicao(jogo->monstros[j].posicao)) )
                    {
                        trocarEstadoDoMonstro(&jogo->monstros[j], ENTIDADE_MORRENDO);
                        jogo->jogador.pontuacao += JOGADOR_PONTUACAO_POR_MONSTRO;
                        
                        monstroAtingido = true;
                    }
                }

                if( verificarColisao(obterHitboxDaBomba(bomba), obterHitboxPelaPosicao(jogo->monstros[j].posicao)) && !monstroAtingido )
                {
                    trocarEstadoDoMonstro(&jogo->monstros[j], ENTIDADE_MORRENDO);
                    jogo->jogador.pontuacao += JOGADOR_PONTUACAO_POR_MONSTRO;
                }
            }
        }
        
        if( bomba->explosoesCima[i].estado != ENTIDADE_INVISIVEL )
        {
            if( (jogo->jogador.estado != ENTIDADE_MORRENDO || jogo->jogador.estado != ENTIDADE_MORTA) && verificarColisao(hitboxExplosaoCima, obterHitboxDoJogador(&jogo->jogador)) )
            {
                trocarEstadoDoJogador(&jogo->jogador, ENTIDADE_MORRENDO);
            }

            if( verificarColisao(hitboxExplosaoCima, obterHitboxPelaPosicao(jogo->saida.posicao)) )
            {
                jogo->saida.estado = ENTIDADE_VISIVEL;
            }
        }

        if( bomba->explosoesDireita[i].estado != ENTIDADE_INVISIVEL )
        {
            if( (jogo->jogador.estado != ENTIDADE_MORRENDO || jogo->jogador.estado != ENTIDADE_MORTA) && verificarColisao(hitboxExplosaoDireita, obterHitboxDoJogador(&jogo->jogador)) )
            {
                trocarEstadoDoJogador(&jogo->jogador, ENTIDADE_MORRENDO);
            }

            if( verificarColisao(hitboxExplosaoDireita, obterHitboxPelaPosicao(jogo->saida.posicao)) )
            {
                jogo->saida.estado = ENTIDADE_VISIVEL;
            }
        }

        if( bomba->explosoesBaixo[i].estado != ENTIDADE_INVISIVEL )
        {
            if( (jogo->jogador.estado != ENTIDADE_MORRENDO || jogo->jogador.estado != ENTIDADE_MORTA) && verificarColisao(hitboxExplosaoBaixo, obterHitboxDoJogador(&jogo->jogador)) )
            {
                trocarEstadoDoJogador(&jogo->jogador, ENTIDADE_MORRENDO);
            }

            if( verificarColisao(hitboxExplosaoBaixo, obterHitboxPelaPosicao(jogo->saida.posicao)) )
            {
                jogo->saida.estado = ENTIDADE_VISIVEL;
            }
        }

        if( bomba->explosoesEsquerda[i].estado != ENTIDADE_INVISIVEL )
        {
            if( (jogo->jogador.estado != ENTIDADE_MORRENDO || jogo->jogador.estado != ENTIDADE_MORTA) && verificarColisao(hitboxExplosaoEsquerda, obterHitboxDoJogador(&jogo->jogador)) )
            {
                trocarEstadoDoJogador(&jogo->jogador, ENTIDADE_MORRENDO);
            }

            if( verificarColisao(hitboxExplosaoEsquerda, obterHitboxPelaPosicao(jogo->saida.posicao)) )
            {
                jogo->saida.estado = ENTIDADE_VISIVEL;
            }
        }

        // Se o jogador atingiu a bomba mesmo
        if( (jogo->jogador.estado != ENTIDADE_MORRENDO || jogo->jogador.estado != ENTIDADE_MORTA) && verificarColisao(obterHitboxDaBomba(bomba), obterHitboxDoJogador(&jogo->jogador)) )
        {
            trocarEstadoDoJogador(&jogo->jogador, ENTIDADE_MORRENDO);
        }
    }
}

/**
 * Desenha todo o jogo
 * 
 * @param *Jogo jogo Referência do jogo
 * 
 */
void desenharJogo( Jogo *jogo )
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    desenharFundo();

    int i, j;

    for( i = 0; i < ALTURA_MAPA_JOGAVEL + 2; i++ ) // + 2 por causa das paredes "fixas"
    {
        for( j = 0; j < jogo->contadorDeParedes; j++ )
        {
            if( jogo->paredes[j].indice.i == i )
            {
                desenharParede(&jogo->paredes[j]);
            }
        }

        for( j = 0; j < jogo->contadorDeBombas; j++ )
        {
            if( jogo->bombas[j].indice.i == i && jogo->bombas[j].estado != BOMBA_DESATIVADA )
            {
                desenharBomba(&jogo->bombas[j]);
            }

        }

        for( j = 0; j < jogo->contadorDeObstaculos; j++ )
        {
            if( jogo->obstaculos[j].indice.i == i && jogo->obstaculos[j].estado != ENTIDADE_INVISIVEL )
            {
                desenharObstaculo(&jogo->obstaculos[j]);
            }
        }

        for( j = 0; j < jogo->contadorDeMonstros; j++ )
        {
            if( jogo->monstros[j].indice.i == i )
            {
                desenharMonstro(&jogo->monstros[j]);
            }

        }

        if( i == jogo->saida.indice.i )
        {
            desenharSaida(&jogo->saida);
        }

        if( i == jogo->jogador.indice.i )
        {
            desenharJogador(&jogo->jogador);
        }

    }

    for( j = 0; j < jogo->contadorDeBombas; j++ )
    {
        if( jogo->bombas[j].estado != BOMBA_DESATIVADA )
        {
            desenharExplosoes(&jogo->bombas[j]);
        }

    }
    
    desenharRodape(jogo);

    if( jogo->modo == JOGO_MODO_PAUSADO )
    {
        desenharOverlayDePausa();
    }

    if( jogo->modo == JOGO_MODO_GAMEOVER )
    {
        desenharOverlayDeGameOver(jogo);
    }

}

void desenharFundo( )
{
    int i, j;

    for( i = 0; i < ALTURA_MAPA_JOGAVEL + 2; i++ ) // + 2 por causa das paredes
    {
        for( j = 0; j < LARGURA_MAPA_JOGAVEL + 2; j++ ) // + 2 por causa das paredes
        {
            al_draw_bitmap(aplicacao->recursos.jogoFundo, j * TAMANHO_ENTIDADE, i * TAMANHO_ENTIDADE + TAMANHO_SOMBRA, 0);
        }
    }

}

void desenharRodape( Jogo *jogo )
{
    al_draw_bitmap(aplicacao->recursos.jogoRodape, 0, ALTURA_TELA - ALTURA_RODAPE, 0);

    // Desenha a quantidade de vidas
    al_draw_textf(aplicacao->recursos.fonteCantarellBold, al_map_rgb(229, 227, 185), 110, ALTURA_TELA - ALTURA_RODAPE + 1, ALLEGRO_ALIGN_CENTER, "%d", jogo->jogador.vidas);

    // Calcula o tempo passado
    int horas, minutos, minutosDigito1, minutosDigito2;
    horas = floor(jogo->tempo / 60.0);
    minutos = jogo->tempo % 60;
    minutosDigito1 = floor(minutos / 10.0);
    minutosDigito2 = minutos % 10;
    // Desenha o tempo na tela
    al_draw_textf(aplicacao->recursos.fonteCantarellBold, al_map_rgb(229, 227, 185), 425, ALTURA_TELA - ALTURA_RODAPE + 1, ALLEGRO_ALIGN_CENTER, "%d%d:%d%d", 0, horas, minutosDigito1, minutosDigito2);

    // Desenha a pontuação
    al_draw_textf(aplicacao->recursos.fonteCantarellBold, al_map_rgb(229, 227, 185), 820, ALTURA_TELA - ALTURA_RODAPE + 1, ALLEGRO_ALIGN_RIGHT, "%d", jogo->jogador.pontuacao);
}

void desenharParede( Parede *parede )
{
    al_draw_bitmap(aplicacao->recursos.jogoObstaculoFixo, parede->posicao.x, parede->posicao.y, 0);
}

void desenharSaida( Saida *saida )
{
    if( saida->estado == ENTIDADE_INVISIVEL )
    {
        Obstaculo obstaculo;
        obstaculo.posicao = saida->posicao;
        definirPadroesDoObstaculo(&obstaculo);
        desenharObstaculo(&obstaculo);
    }
    else
    {
        al_draw_bitmap(aplicacao->recursos.jogoSaida, saida->posicao.x, saida->posicao.y, 0);
    }
}

void desenharObstaculo( Obstaculo *obstaculo )
{
    atualizarSprite(&obstaculo->sprite);
    desenharSprite(&obstaculo->sprite, obstaculo->posicao);
}

void desenharJogador( Jogador *jogador )
{
    atualizarSprite(&jogador->sprite);
    desenharSprite(&jogador->sprite, jogador->posicao);
}

void desenharMonstro( Monstro *monstro )
{
    if( monstro->estado != ENTIDADE_MORTA )
    {
        atualizarSprite(&monstro->sprite);
        desenharSprite(&monstro->sprite, monstro->posicao);
    }
}

void desenharBomba( Bomba *bomba )
{
    atualizarSprite(&bomba->sprite);

    if( bomba->estado != BOMBA_EXPLODINDO )
    {
        desenharSprite(&bomba->sprite, bomba->posicao);
    }
}

void desenharExplosoes( Bomba *bomba )
{
    atualizarSprite(&bomba->spriteRastro);

    if( bomba->estado == BOMBA_EXPLODINDO )
    {
        desenharSprite(&bomba->spriteRastro, bomba->posicao);

        int i;

        for( i = 0; i < bomba->raioDeExplosao; i++ )
        {
            if( bomba->explosoesCima[i].estado == ENTIDADE_VISIVEL )
            {
                desenharSprite(&bomba->spriteRastro, bomba->explosoesCima[i].posicao);
            }

            if( bomba->explosoesDireita[i].estado == ENTIDADE_VISIVEL )
            {
                desenharSprite(&bomba->spriteRastro, bomba->explosoesDireita[i].posicao);
            }

            if( bomba->explosoesBaixo[i].estado == ENTIDADE_VISIVEL )
            {
                desenharSprite(&bomba->spriteRastro, bomba->explosoesBaixo[i].posicao);
            }

            if( bomba->explosoesEsquerda[i].estado == ENTIDADE_VISIVEL )
            {
                desenharSprite(&bomba->spriteRastro, bomba->explosoesEsquerda[i].posicao);
            }
        }
    }
}

void desenharOverlayDePausa( )
{
    al_draw_filled_rectangle(0, 0, LARGURA_TELA, ALTURA_TELA, al_map_rgba(19, 20, 38, 200));
    al_draw_bitmap(aplicacao->recursos.jogoTelaPausa, 0, 0, 0);
}

void desenharOverlayDeGameOver( Jogo *jogo )
{
    if( jogo->jogador.vidas == 0 )
    {
        al_draw_filled_rectangle(0, 0, LARGURA_TELA, ALTURA_TELA, al_map_rgba(19, 0, 0, 200));
        al_draw_bitmap(aplicacao->recursos.jogoTelaGameOver, 0, 0, 0);
    }
    else
    {
        al_draw_filled_rectangle(0, 0, LARGURA_TELA, ALTURA_TELA, al_map_rgba(0, 20, 0, 200));
        al_draw_bitmap(aplicacao->recursos.jogoTelaVitoria, 0, 0, 0);
    }

    al_draw_textf(aplicacao->recursos.fonteCantarellBold, al_map_rgb(229, 227, 185), (LARGURA_TELA / 2), 260, ALLEGRO_ALIGN_CENTER, "%d", jogo->jogador.pontuacao);
    al_draw_ustr(aplicacao->recursos.fonteCantarellBold, al_map_rgb(229, 227, 185), (LARGURA_TELA / 2), 400, ALLEGRO_ALIGN_CENTER, jogo->jogador.nome);
}