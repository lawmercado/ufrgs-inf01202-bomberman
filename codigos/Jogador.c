/**
 * Arquivo contendo a implementação das funções referentes a entidade jogador
 * 
 * @author Luís Augusto Weber Mercado
 */

void definirPadroesDoJogador( Jogador *jogador )
{
    jogador->vidas = JOGADOR_NUMERO_VIDAS;
    jogador->direcaoMovimento = DIRECAO_NULA;
    jogador->nivelAtual = 1;
    jogador->pontuacao = 0;
    jogador->maximoDeBombasSimultaneas = JOGADOR_BOMBAS_PERMITIDAS_PADRAO;
    trocarEstadoDoJogador(jogador, ENTIDADE_FRENTE_PARADA);
}

Hitbox obterHitboxDoJogador( Jogador *jogador )
{
    Hitbox hitbox;
    hitbox.x = jogador->posicao.x + 5;
    hitbox.y = jogador->posicao.y + JOGADOR_MARGEM_INICIAL - TAMANHO_SOMBRA + 35;
    hitbox.xFinal = hitbox.x + TAMANHO_ENTIDADE - 10;
    hitbox.yFinal = hitbox.y + TAMANHO_ENTIDADE - 45;

    return hitbox;
}

Sprite obterSpriteDoJogadorPeloEstado( Jogador *jogador )
{
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 5;
    sprite.larguraFrame = 50;
    sprite.alturaFrame = 100;
    sprite.direcaoAnimacao = 1;

    switch(jogador->estado)
    {
        case ENTIDADE_TRAS:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = aplicacao->recursos.jogadorTrasSprite;

            break;
        }

        case ENTIDADE_TRAS_PARADA:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = aplicacao->recursos.jogadorTrasParado;

            break;
        }

        case ENTIDADE_DIREITA:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = aplicacao->recursos.jogadorLadoSprite;

            break;
        }

        case ENTIDADE_DIREITA_PARADA:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = aplicacao->recursos.jogadorLadoParado;

            break;
        }

        case ENTIDADE_FRENTE:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = aplicacao->recursos.jogadorFrenteSprite;

            break;
        }

        case ENTIDADE_FRENTE_PARADA:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = aplicacao->recursos.jogadorFrenteParado;

            break;
        }

        case ENTIDADE_ESQUERDA:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = aplicacao->recursos.jogadorLadoSprite;
            sprite.allegroFlag = ALLEGRO_FLIP_HORIZONTAL;

            break;
        }

        case ENTIDADE_ESQUERDA_PARADA:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = aplicacao->recursos.jogadorLadoParado;
            sprite.allegroFlag = ALLEGRO_FLIP_HORIZONTAL;

            break;
        }
        
        case ENTIDADE_MORRENDO:
        case ENTIDADE_MORTA:
        {
            sprite.delayFrame = 10;
            sprite.colunasAnimacao = 2;
            sprite.maximoFrames = 2;
            sprite.imagem = aplicacao->recursos.jogadorMortoSprite;
            
            break;
        }

    }

    return sprite;
}

void trocarEstadoDoJogador( Jogador *jogador, int estado )
{
    // Não atualiza a sprite se o estado não estiver mesmo sendo alterado
    if( jogador->estado != estado )
    {
        switch( estado )
        {
            case ENTIDADE_MORRENDO:
                jogador->tempo = ENTIDADE_TEMPO_MORTA;
                
                break;
        }
        
        jogador->estado = estado;
        jogador->sprite = obterSpriteDoJogadorPeloEstado(jogador);
    }
}

void moverJogadorConformeIndice( Jogador *jogador, Indice indice )
{
    jogador->posicao.x = indice.j * TAMANHO_ENTIDADE;
    jogador->posicao.y = indice.i * TAMANHO_ENTIDADE - JOGADOR_MARGEM_INICIAL + TAMANHO_SOMBRA;
}