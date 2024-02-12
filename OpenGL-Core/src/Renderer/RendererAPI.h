#ifndef RENDERER_RENDERERAPI_H_
#define RENDERER_RENDERERAPI_H_

#include <Renderer/VertexArray.h>

#include <cstdint>

class RendererAPI {
public:
    static void Init();
    static void ClearColor(float r, float g, float b, float a);
    static void Clear();
    static void SetViewPort(std::uint32_t w, std::uint32_t h);
    static void Draw(const VertexArray& _Vao);
};

#endif // !RENDERER_RENDERERAPI_H_
