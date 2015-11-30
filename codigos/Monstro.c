/**
 * Arquivo contendo a implementação das funções referentes a entidade monstro
 * 
 * @author Luís Augusto Weber Mercado
 */

void definirPadroesDoMonstro( Monstro *monstro )
{
    monstro->direcaoMovimento = DIRECAO_BAIXO;
    trocarEstadoDoMonstro(monstro, ENTIDADE_FRENTE);
}

Sprite obterSpriteDoMonstroPeloEstado( Monstro *monstro )
{
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 5;
    sprite.larguraFrame = 50;
    sprite.alturaFrame = 50;
    sprite.direcaoAnimacao = 1;

    switch(monstro->estado)
    {
        case ENTIDADE_TRAS:
        {
            sprite.colunasAnimacao = 6;
            sprite.maximoFrames = 6;
            sprite.imagem = aplicacao->recursos.monstroTrasSprite;

            break;
        }

        case ENTIDADE_DIREITA:
        {
            sprite.colunasAnimacao = 7;
            sprite.maximoFrames = 7;
            sprite.imagem = aplicacao->recursos.monstroLadoSprite;

            break;
        }

        case ENTIDADE_FRENTE:
        {
            sprite.colunasAnimacao = 6;
            sprite.maximoFrames = 6;
            sprite.imagem = aplicacao->recursos.monstroFrenteSprite;

            break;
        }

        case ENTIDADE_ESQUERDA:
        {
            sprite.colunasAnimacao = 7;
            sprite.maximoFrames = 7;
            sprite.imagem = aplicacao->recursos.monstroLadoSprite;
            sprite.allegroFlag = ALLEGRO_FLIP_HORIZONTAL;

            break;
        }
        
        case ENTIDADE_MORTA:
        case ENTIDADE_MORRENDO:
        {
            sprite.delayFrame = 10;
            sprite.colunasAnimacao = 2;
            sprite.maximoFrames = 2;
            sprite.imagem = aplicacao->recursos.monstroMortoSprite;
            
            break;
        }
        
    }

    return sprite;
}

int obterDirecaoDiferenteAleatoria( int direcaoAtual )
{
    int numero = rand() % (3 + 1);

    while (numero == direcaoAtual)
    {
        numero = rand() % (3 + 1);
    }
    
    return numero;
}

void trocarEstadoDoMonstro( Monstro *monstro, int estado )
{
    // Não atualiza a sprite se o estado não estiver mesmo sendo alterado
    if( monstro->estado != estado )
    {
        switch( estado )
        {
            case ENTIDADE_MORRENDO:
                monstro->tempo = ENTIDADE_TEMPO_MORTA;
                
                break;
        }
        
        monstro->estado = estado;
        monstro->sprite = obterSpriteDoMonstroPeloEstado(monstro);
    }
}