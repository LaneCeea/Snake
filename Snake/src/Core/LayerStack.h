#ifndef CORE_LAYERSTACK_H_
#define CORE_LAYERSTACK_H_

#include <Core/Layer.h>

#include <vector>

class LayerStack {
public:
    using Container = std::vector<Layer*>;

public:
    LayerStack() = default;
    ~LayerStack();

    void PushLayer(Layer* _LayerPtr);
    void PopLayer(Layer* _LayerPtr);
    void PushOverlay(Layer* _OverlayPtr);
    void PopOverlay(Layer* _OverlayPtr);

    Container::iterator begin()                         { return m_Layers.begin(); }
    Container::const_iterator begin() const             { return m_Layers.begin(); }
    Container::iterator end()                           { return m_Layers.end(); }
    Container::const_iterator end() const               { return m_Layers.end(); }
    Container::reverse_iterator rbegin()                { return m_Layers.rbegin(); }
    Container::const_reverse_iterator rbegin() const    { return m_Layers.rbegin(); }
    Container::reverse_iterator rend()                  { return m_Layers.rend(); }
    Container::const_reverse_iterator rend() const      { return m_Layers.rend(); }
    Container::const_iterator cbegin() const            { return begin(); }
    Container::const_iterator cend() const              { return end(); }
    Container::const_reverse_iterator crbegin() const   { return rbegin(); }
    Container::const_reverse_iterator crend() const     { return rend(); }

private:
    Container m_Layers;
    std::size_t m_InsertOffset = 0;
};

#endif // !CORE_LAYERSTACK_H_
