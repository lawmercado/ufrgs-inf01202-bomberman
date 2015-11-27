/**
 * Arquivo contento a implementação das funções referentes às sprites
 * 
 * @author Luís Augusto Weber Mercado
 */

#include "../cabecalhos/Sprite.h"

void atualizarSprite(Sprite *sprite)
{
    if( ++(sprite->contadorFrame) >= sprite->delayFrame )
    {
        sprite->frameCorrente += sprite->direcaoAnimacao;
        
        if( sprite->frameCorrente >= sprite->maximoFrames )
        {
            sprite->frameCorrente = 0;
        }
        else if( sprite->frameCorrente <= 0 )
        {
            sprite->frameCorrente = sprite->maximoFrames - 1;
        }
        
        sprite->contadorFrame = 0;
    }
}

void desenharSprite(Sprite *sprite, Posicao posicao)
{
    al_draw_bitmap_region(sprite->imagem, sprite->frameCorrente * sprite->larguraFrame, 0, sprite->larguraFrame, sprite->alturaFrame, posicao.x, posicao.y, sprite->allegroFlag);
}