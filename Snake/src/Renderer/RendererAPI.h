#ifndef RENDERER_RENDERERAPI_H_
#define RENDERER_RENDERERAPI_H_

class RendererAPI {
public:
    static void Init();
    static void ClearColor(float r, float g, float b, float a);
    static void Clear();

};

#endif // !RENDERER_RENDERERAPI_H_
