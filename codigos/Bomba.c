/**
 * Arquivo contendo a implementação das funções referentes a entidade bomba
 * 
 * @author Luís Augusto Weber Mercado
 */

void definirPadroesDasBombas( Jogo *jogo )
{
    int i = 0;
    
    for( i = 0; i < MAXIMO_BOMBAS_PERMITIDAS; i++ )
    {
        jogo->bombas[i].estado = BOMBA_DESATIVADA;
        jogo->bombas[i].raioDeExplosao = BOMBA_RAIO_EXPLOSAO_PADRAO;
    }
}

void plantarBomba(Jogo *jogo)
{
    int i = 0;
    int j = 0;
    
    // Se não atingiu o máximo de bombas permitidas
    if( jogo->contadorDeBombas < jogo->jogador.maximoDeBombasSimultaneas )
    {
        jogo->contadorDeBombas++;
        
        for( i = 0; i < jogo->contadorDeBombas; i++ )
        {
            if( jogo->bombas[i].estado == BOMBA_DESATIVADA )
            {
                prepararBomba(&jogo->bombas[i], obterPosicaoBrutaDoJogador(obterHitboxDoJogador(&jogo->jogador)));
            }
        }
        
    }
}

void prepararBomba(Bomba *bomba, Indice indice)
{
    bomba->indice = indice;
    bomba->estado = BOMBA_PREPARADA;
    bomba->posicao.x = indice.j * TAMANHO_ENTIDADE;
    bomba->posicao.y = indice.i * TAMANHO_ENTIDADE;
    bomba->tempoAteExplodir = BOMBA_TEMPO_ATE_EXPLODIR;
    bomba->sprite = obterSpriteDaBomba();
    bomba->spriteRastro = obterSpriteDoRastro();
    
}

Hitbox obterHitboxDaBomba(Bomba *bomba)
{
    if( bomba->estado == BOMBA_EXPLODINDO && bomba->tempoAteExplodir == 0 )
    {
        // Retornar hitbox considerando explosao
    }
    
    return obterHitboxPelaPosicao(bomba->posicao);
    
}

Sprite obterSpriteDaBomba()
{
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 5;
    sprite.larguraFrame = 50;
    sprite.alturaFrame = 50;
    sprite.direcaoAnimacao = 1;
    sprite.colunasAnimacao = 3;
    sprite.maximoFrames = 3;
    sprite.imagem = aplicacao->recursos.jogoBombaSprite;
    
    return sprite;
}

Sprite obterSpriteDoRastro()
{
    Sprite sprite;

    sprite.allegroFlag = 0; // Indica que (por padrão), não haverá flags ao desenhar a imagem
    sprite.frameCorrente = 0;
    sprite.contadorFrame = 0;
    sprite.delayFrame = 8;
    sprite.larguraFrame = 50;
    sprite.alturaFrame = 50;
    sprite.direcaoAnimacao = 1;
    sprite.colunasAnimacao = 3;
    sprite.maximoFrames = 3;
    sprite.imagem = aplicacao->recursos.jogoRastroSprite;
    
    return sprite;
}