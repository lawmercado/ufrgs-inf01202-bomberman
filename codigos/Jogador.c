/**
 * Arquivo contento a implementação das funções referentes a entidade jogador
 * 
 * @author Luís Augusto Weber Mercado
 */

Hitbox obterHitboxDoJogador( Jogador *jogador )
{
    Hitbox hitbox;
    hitbox.x = jogador->posicao.x;
    hitbox.y = jogador->posicao.y + MARGEM_INICIAL - TAMANHO_SOMBRA_EM_PX;
    hitbox.xFinal = hitbox.x + TAMANHO_ENTIDADE;
    hitbox.yFinal = hitbox.y + TAMANHO_ENTIDADE;

    return hitbox;
}

bool jogadorAtingeObstaculoFixo(Hitbox hitboxJogador)
{
    Hitbox hitboxObstaculoFixo;
    int i, j;
    bool atingeObstaculoFixo;
    
    for( i = 2; i < ALTURA_MAPA_JOGAVEL; i += 2 )
    {
        for( j = 2; j < LARGURA_MAPA_JOGAVEL; j += 2 )
        {
            hitboxObstaculoFixo.x = j * TAMANHO_ENTIDADE;
            hitboxObstaculoFixo.xFinal = hitboxObstaculoFixo.x + TAMANHO_ENTIDADE;
            hitboxObstaculoFixo.y = i * TAMANHO_ENTIDADE;
            hitboxObstaculoFixo.yFinal = hitboxObstaculoFixo.y + TAMANHO_ENTIDADE;
            
            atingeObstaculoFixo = posicaoSobrepoe(hitboxJogador, hitboxObstaculoFixo);
            
            if( atingeObstaculoFixo )
            {
                printf("Atingiu o obstáculo %d, %d\n", i, j);
                
                return true;
            }
        }
    }
}

bool jogadorAtingeMapaAoIrParaCima( Hitbox hitboxJogador )
{
    Hitbox hitboxMapa;
    hitboxMapa.y = 0;
    hitboxMapa.yFinal = 0 + TAMANHO_ENTIDADE;
    
    return posicaoSobrepoeEmY(hitboxJogador, hitboxMapa) || jogadorAtingeObstaculoFixo(hitboxJogador);
}

bool jogadorAtingeMapaAoIrParaDireita( Hitbox hitboxJogador )
{
    Hitbox hitboxMapa;
    hitboxMapa.x = (LARGURA_MAPA_JOGAVEL + 1) * TAMANHO_ENTIDADE;
    hitboxMapa.xFinal = hitboxMapa.x + TAMANHO_ENTIDADE;

    return posicaoSobrepoeEmX(hitboxJogador, hitboxMapa) || jogadorAtingeObstaculoFixo(hitboxJogador);
}

bool jogadorAtingeMapaAoIrParaBaixo( Hitbox hitboxJogador )
{
    Hitbox hitboxMapa;
    hitboxMapa.y = (ALTURA_MAPA_JOGAVEL + 1) * TAMANHO_ENTIDADE;
    hitboxMapa.yFinal = hitboxMapa.y + TAMANHO_ENTIDADE;

    return posicaoSobrepoeEmY(hitboxJogador, hitboxMapa) || jogadorAtingeObstaculoFixo(hitboxJogador);
}

bool jogadorAtingeMapaAoIrParaEsquerda( Hitbox hitboxJogador )
{
    Hitbox hitboxMapa;
    hitboxMapa.x = 0;
    hitboxMapa.xFinal = TAMANHO_ENTIDADE;

    return posicaoSobrepoeEmX(hitboxJogador, hitboxMapa) || jogadorAtingeObstaculoFixo(hitboxJogador);

}

void alternarEstadoDoPersonagemAoIrParaCima( Jogador *jogador )
{
    if( jogador->estadoPersonagem % 2 == 0 )
    {
        jogador->estadoPersonagem = JOGADOR_TRAS_ESQUERDA;
    }
    else
    {
        jogador->estadoPersonagem = JOGADOR_TRAS_DIREITA;
    }
}

void alternarEstadoDoPersonagemAoIrParaDireita( Jogador *jogador )
{
    if( jogador->estadoPersonagem % 2 == 0 )
    {
        jogador->estadoPersonagem = JOGADOR_DIREITA_ESQUERDA;
    }
    else
    {
        jogador->estadoPersonagem = JOGADOR_DIREITA_DIREITA;
    }
}

void alternarEstadoDoPersonagemAoIrParaBaixo( Jogador *jogador )
{
    if( jogador->estadoPersonagem % 2 == 0 )
    {
        jogador->estadoPersonagem = JOGADOR_FRENTE_ESQUERDA;
    }
    else
    {
        jogador->estadoPersonagem = JOGADOR_FRENTE_DIREITA;
    }
}

void alternarEstadoDoPersonagemAoIrParaEsquerda( Jogador *jogador )
{
    if( jogador->estadoPersonagem % 2 == 0 )
    {
        jogador->estadoPersonagem = JOGADOR_ESQUERDA_ESQUERDA;
    }
    else
    {
        jogador->estadoPersonagem = JOGADOR_ESQUERDA_DIREITA;
    }
}

void desenharJogador( Jogador *jogador, Recursos *recursos )
{
    ALLEGRO_BITMAP *imagem = NULL;
    int flag = 0;

    switch(jogador->estadoPersonagem)
    {
        case JOGADOR_FRENTE_DIREITA:
            imagem = recursos->jogadorFrenteDireita;
            break;

        case JOGADOR_FRENTE_ESQUERDA:
            imagem = recursos->jogadorFrenteDireita;
            flag = ALLEGRO_FLIP_HORIZONTAL;
            break;

        case JOGADOR_DIREITA_DIREITA:
            imagem = recursos->jogadorDireitaDireita;
            break;

        case JOGADOR_DIREITA_ESQUERDA:
            imagem = recursos->jogadorDireitaEsquerda;
            break;

        case JOGADOR_TRAS_DIREITA:
            imagem = recursos->jogadorTrasDireita;
            break;

        case JOGADOR_TRAS_ESQUERDA:
            imagem = recursos->jogadorTrasDireita;
            flag = ALLEGRO_FLIP_HORIZONTAL;
            break;

        case JOGADOR_ESQUERDA_DIREITA:
            imagem = recursos->jogadorDireitaDireita;
            flag = ALLEGRO_FLIP_HORIZONTAL;
            break;

        case JOGADOR_ESQUERDA_ESQUERDA:
            imagem = recursos->jogadorDireitaEsquerda;
            flag = ALLEGRO_FLIP_HORIZONTAL;
            break;
    }
    
    al_draw_bitmap(imagem, jogador->posicao.x, jogador->posicao.y, flag);
}