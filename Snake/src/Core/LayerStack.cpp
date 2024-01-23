#include "LayerStack.h"

#include <Core/Assert.h>

#include <algorithm>

LayerStack::~LayerStack() {
    for (Layer* _LayerPtr : m_Layers) {
        _LayerPtr->OnDetach();
        delete _LayerPtr;
    }
}

void LayerStack::PushLayer(Layer* _LayerPtr) {
    CORE_TRACE("PushLayer: %s\n", _LayerPtr->Name().data());

    m_Layers.emplace(m_Layers.begin() + m_InsertOffset, _LayerPtr);
    ++m_InsertOffset;
}

void LayerStack::PopLayer(Layer* _LayerPtr) {
    CORE_TRACE("PopLayer: %s\n", _LayerPtr->Name().data());

    auto _Begin = m_Layers.begin();
    auto _Last  = _Begin + m_InsertOffset;
    auto _Where = std::find(_Begin, _Last, _LayerPtr);

    CORE_ASSERT(_Where != _Last, "Cannot find layer.");
    _LayerPtr->OnDetach();
    m_Layers.erase(_Where);
    --m_InsertOffset;
}

void LayerStack::PushOverlay(Layer* _OverlayPtr) {
    CORE_TRACE("PushOverlay: %s\n", _OverlayPtr->Name().data());

    m_Layers.emplace_back(_OverlayPtr);
}

void LayerStack::PopOverlay(Layer* _OverlayPtr) {
    CORE_TRACE("PopOverlay: %s\n", _OverlayPtr->Name().data());

    auto _Begin = m_Layers.begin() + m_InsertOffset;
    auto _Last  = m_Layers.end();
    auto _Where = std::find(_Begin, _Last, _OverlayPtr);

    CORE_ASSERT(_Where != _Last, "Cannot find overlay.");
    _OverlayPtr->OnDetach();
    m_Layers.erase(_Where);
}
