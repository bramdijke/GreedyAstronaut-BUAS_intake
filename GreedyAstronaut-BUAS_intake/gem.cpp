#include "gem.h"

namespace Tmpl8 {
    Gem::Gem(Surface* sprite) : m_Sprite(sprite), m_X(0), m_Y(0) {}

    void Gem::Draw(Surface* screen)
    {
        m_Sprite->CopyTo(screen, m_X, m_Y);
    }

    void Gem::SetPosition(int x, int y)
    {
        m_X = x;
        m_Y = y;
    }
}