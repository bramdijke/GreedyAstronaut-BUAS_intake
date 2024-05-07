#pragma once

#include "surface.h"

namespace Tmpl8 {
    class Gem
    {
    public:
        Gem(Surface* sprite);
        void Draw(Surface* screen);
        void SetPosition(int x, int y);

    private:
        Surface* m_Sprite;
        int m_X;
        int m_Y;
    };
}