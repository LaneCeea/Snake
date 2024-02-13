#ifndef RENDERER_RENDERER_H_
#define RENDERER_RENDERER_H_

#include <Renderer/VertexArray.h>

struct RendererData {
    VertexArray SquareVao;
    VertexArray CubeVao;
};

class Renderer {
public:
    static void Init();
    static void DrawSquare();

private:
    static RendererData s_Data;
};

#endif // !RENDERER_RENDERER_H_
