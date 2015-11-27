/**
 * Arquivo contendo a implementação das funções referentes a entidade monstro
 * 
 * @author Luís Augusto Weber Mercado
 */

Sprite obterSpriteDoMonstroConformeEstado( Monstro *monstro, Recursos *recursos )
{
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 5;
    sprite.larguraFrame = 50;
    sprite.alturaFrame = 100;
    sprite.direcaoAnimacao = 1;

    switch(monstro->estadoPersonagem)
    {
        case MONSTRO_TRAS:
        {
            sprite.colunasAnimacao = 6;
            sprite.maximoFrames = 6;
            sprite.imagem = recursos->monstroTrasSprite;

            break;
        }

        case MONSTRO_TRAS_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->monstroTrasParado;

            break;
        }

        case MONSTRO_DIREITA:
        {
            sprite.colunasAnimacao = 7;
            sprite.maximoFrames = 7;
            sprite.imagem = recursos->monstroLadoSprite;

            break;
        }

        case MONSTRO_DIREITA_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->monstroLadoParado;

            break;
        }

        case MONSTRO_FRENTE:
        {
            sprite.colunasAnimacao = 6;
            sprite.maximoFrames = 6;
            sprite.imagem = recursos->monstroFrenteSprite;

            break;
        }

        case MONSTRO_FRENTE_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->monstroFrenteParado;

            break;
        }

        case MONSTRO_ESQUERDA:
        {
            sprite.colunasAnimacao = 7;
            sprite.maximoFrames = 7;
            sprite.imagem = recursos->monstroLadoSprite;
            sprite.allegroFlag = ALLEGRO_FLIP_HORIZONTAL;

            break;
        }

        case MONSTRO_ESQUERDA_PARADO:
        {
            sprite.colunasAnimacao = 0;
            sprite.maximoFrames = 0;
            sprite.imagem = recursos->monstroLadoParado;
            sprite.allegroFlag = ALLEGRO_FLIP_HORIZONTAL;

            break;
        }

    }

    return sprite;
}

void trocarEstadoDoMonstro( Monstro *monstro, Recursos *recursos, int estado )
{
    // Não atualiza a sprite se o estado não estiver mesmo sendo alterado
    if( monstro->estadoPersonagem != estado )
    {
        monstro->estadoPersonagem = estado;
        monstro->sprite = obterSpriteDoMonstroConformeEstado(monstro, recursos);
    }
}