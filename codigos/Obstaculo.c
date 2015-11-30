/**
 * Arquivo contendo a implementação das funções referentes a entidade obstáculo
 * 
 * @author Luís Augusto Weber Mercado
 */

void definirPadroesDoObstaculo( Obstaculo *obstaculo )
{
    trocarEstadoDoObstaculo(obstaculo, ENTIDADE_VISIVEL);
}

Sprite obterSpriteDoObstaculoPeloEstado( Obstaculo *obstaculo )
{
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 1;
    sprite.larguraFrame = 50;
    sprite.alturaFrame = 60;
    sprite.direcaoAnimacao = 1;
    sprite.colunasAnimacao = 1;
    sprite.maximoFrames = 1;

    switch(obstaculo->estado)
    {
        case ENTIDADE_MORRENDO:
        {
            sprite.delayFrame = 10;
            sprite.colunasAnimacao = 2;
            sprite.maximoFrames = 2;
            sprite.imagem = aplicacao->recursos.jogoObstaculoDestruidoSprite;
            
            break;
        }
        
        default:
            sprite.imagem = aplicacao->recursos.jogoObstaculo;
        
    }

    return sprite;
}

void trocarEstadoDoObstaculo( Obstaculo *obstaculo, int estado )
{
    // Não atualiza a sprite se o estado não estiver mesmo sendo alterado
    if( obstaculo->estado != estado )
    {
        switch( estado )
        {
            case ENTIDADE_MORRENDO:
                obstaculo->tempo = ENTIDADE_TEMPO_MORTA;
                
                break;
        }
        
        obstaculo->estado = estado;
        obstaculo->sprite = obterSpriteDoObstaculoPeloEstado(obstaculo);
    }
}