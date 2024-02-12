#include "VertexLayout.h"

#include <Core/Log.h>

#include <glad/glad.h>

VertexLayout::VertexLayout(std::initializer_list<ShaderDataType> _Il)
    : m_Layout(_Il), m_Stride(0) {
	for (const auto& _Type : _Il) {
		m_Stride += GetElementSize(_Type);
	}
}
