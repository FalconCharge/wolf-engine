// ------------------------------------------------------------
// Class: Grid3D
// Brief: A basic grid class that was found in wolf samples. 
//          I personally don't like it at all. And think I should delete it.
//          But, I'm thinking of adding it to the GO pos when a GO is focused.
// Author: Ben Harper
// Date: 2025-09-06
// ------------------------------------------------------------
#pragma once

#include "wolf.h"

class Grid3D
{
    public:
        Grid3D(int linesPerHalfSpace, float gridSpacing = 1.0f);
        ~Grid3D();

        void update(float dt);
        void render(const glm::mat4& mView, const glm::mat4& mProj);
        void showAxes() { m_showAxes = true; }
        void hideAxes() { m_showAxes = false; }

    private:

        void _createGrid(int linesPerHalfSpace, float gridSpacing);
        void _createAxes();

        wolf::VertexBuffer* m_pVB = 0;
        wolf::VertexDeclaration* m_pDecl = 0;
        wolf::Color4 m_color;

        wolf::VertexBuffer *m_pAxesVB = 0;
        wolf::VertexDeclaration *m_pAxesDecl = 0;

        wolf::Material* m_pMatGrid;
        wolf::Material* m_pMatAxes;

        int m_numVerts = 0;
        bool m_showAxes = true;
};
