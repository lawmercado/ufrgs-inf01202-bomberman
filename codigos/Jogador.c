/**
 * Arquivo contendo a implementação das funções referentes a entidade jogador
 * 
 * @author Luís Augusto Weber Mercado
 */

void definirPadroesDoJogador( Jogador *jogador, Recursos *recursos )
{
    jogador->vidas = NUMERO_VIDAS_INICIAL;
    jogador->direcaoMovimento = DIRECAO_NULA;
    jogador->nivelAtual = 1;
    trocarEstadoDoJogador(jogador, recursos, JOGADOR_FRENTE_PARADO);
}

Hitbox obterHitboxDoJogador( Jogador *jogador )
{
    Hitbox hitbox;
    hitbox.x = jogador->posicao.x + 5;
    hitbox.y = jogador->posicao.y + MARGEM_INICIAL - TAMANHO_SOMBRA + 35;
    hitbox.xFinal = hitbox.x + TAMANHO_ENTIDADE - 10;
    hitbox.yFinal = hitbox.y + TAMANHO_ENTIDADE - 45;

    return hitbox;
}

Sprite obterSpriteDoJogadorConformeEstado( Jogador *jogador, Recursos *recursos )
{
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 5;
    sprite.larguraFrame = 50;
    sprite.alturaFrame = 100;
    sprite.direcaoAnimacao = 1;

    switch(jogador->estadoPersonagem)
    {
        case JOGADOR_TRAS:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = recursos->jogadorTrasSprite;

            break;
        }

        case JOGADOR_TRAS_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->jogadorTrasParado;

            break;
        }

        case JOGADOR_DIREITA:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = recursos->jogadorLadoSprite;

            break;
        }

        case JOGADOR_DIREITA_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->jogadorLadoParado;

            break;
        }

        case JOGADOR_FRENTE:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = recursos->jogadorFrenteSprite;

            break;
        }

        case JOGADOR_FRENTE_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->jogadorFrenteParado;

            break;
        }

        case JOGADOR_ESQUERDA:
        {
            sprite.colunasAnimacao = 8;
            sprite.maximoFrames = 8;
            sprite.imagem = recursos->jogadorLadoSprite;
            sprite.allegroFlag = ALLEGRO_FLIP_HORIZONTAL;

            break;
        }

        case JOGADOR_ESQUERDA_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->jogadorLadoParado;
            sprite.allegroFlag = ALLEGRO_FLIP_HORIZONTAL;

            break;
        }

    }

    return sprite;
}

void trocarEstadoDoJogador( Jogador *jogador, Recursos *recursos, int estado )
{
    // Não atualiza a sprite se o estado não estiver mesmo sendo alterado
    if( jogador->estadoPersonagem != estado )
    {
        jogador->estadoPersonagem = estado;
        jogador->sprite = obterSpriteDoJogadorConformeEstado(jogador, recursos);
    }
}