int obterEstadoPelaDirecao( int direcao )
{
    switch(direcao)
    {
        case DIRECAO_CIMA:
        {
            return ENTIDADE_TRAS;
        }

        case DIRECAO_DIREITA:
        {
            return ENTIDADE_DIREITA;
        }

        case DIRECAO_BAIXO:
        {
            return ENTIDADE_FRENTE;
        }

        case DIRECAO_ESQUERDA:
        {
            return ENTIDADE_ESQUERDA;
        }
    }
}

bool obterCondicaoDeDestinoPelaDirecao( Indice corpo, Indice alvo, int direcao )
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

void alterarPosicaoPelaDirecao( Posicao *posicao, int unidades, int direcao )
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

int obterDirecaoOposta( int direcao )
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

Indice obterPosicaoBruta( Posicao posicao )
{
    Indice indice = {round((posicao.y + (TAMANHO_ENTIDADE / 2)) / TAMANHO_ENTIDADE), round((posicao.x + (TAMANHO_ENTIDADE / 2)) / TAMANHO_ENTIDADE)};
    
    return indice;
}

Indice obterPosicaoBrutaDoJogador( Hitbox hitbox )
{
    Indice indice = { ceil( hitbox.y / TAMANHO_ENTIDADE ), ceil( hitbox.x / TAMANHO_ENTIDADE )};
    
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