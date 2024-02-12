#ifndef RENDERER_VERTEXLAYOUT_H_
#define RENDERER_VERTEXLAYOUT_H_

#include <Core/Log.h>

#include <vector>

enum class ShaderDataType {
    None = 0,
    Float, Float2, Float3, Float4
};

class VertexLayout {
public:
    using Container     = std::vector<ShaderDataType>;
    using Iterator      = Container::iterator;
    using ConstIterator = Container::const_iterator;

public:
    VertexLayout(std::initializer_list<ShaderDataType> _Il);

    static constexpr std::uint32_t GetElementGLType(ShaderDataType _Type);
    static constexpr std::uint32_t GetElementComponentCount(ShaderDataType _Type);
    static constexpr std::size_t GetElementSize(ShaderDataType _Type);

    Iterator begin()                { return m_Layout.begin(); }
    ConstIterator begin() const     { return m_Layout.begin(); }
    Iterator end()                  { return m_Layout.end(); }
    ConstIterator end() const       { return m_Layout.end(); }
    ConstIterator cbegin() const    { return begin(); }
    ConstIterator cend() const      { return end(); }

    std::size_t Stride() const { return m_Stride; }

private:
    Container m_Layout;
    std::size_t m_Stride;
};


constexpr std::uint32_t VertexLayout::GetElementGLType(ShaderDataType _Type) {
	constexpr std::uint32_t _GLFloat = 0x1406;
	
	switch (_Type) {
	case ShaderDataType::None:
		CORE_ERROR("ShaderDataType::None\n");
		return 0;

	case ShaderDataType::Float:		return _GLFloat;
	case ShaderDataType::Float2:	return _GLFloat;
	case ShaderDataType::Float3:	return _GLFloat;
	case ShaderDataType::Float4:	return _GLFloat;

	default:
		CORE_ERROR("Unknown ShaderDataType.\n");
		return 0;
	}
}

constexpr std::uint32_t VertexLayout::GetElementComponentCount(ShaderDataType _Type) {
	switch (_Type) {
	case ShaderDataType::None:
		CORE_ERROR("ShaderDataType::None\n");
		return 0;

	case ShaderDataType::Float:		return 1;
	case ShaderDataType::Float2:	return 2;
	case ShaderDataType::Float3:	return 3;
	case ShaderDataType::Float4:	return 4;

	default:
		CORE_ERROR("Unknown ShaderDataType.\n");
		return 0;
	}
}

constexpr std::size_t VertexLayout::GetElementSize(ShaderDataType _Type) {
	switch (_Type) {
	case ShaderDataType::None:
		CORE_ERROR("ShaderDataType::None\n");
		return 0;

	case ShaderDataType::Float:		return sizeof(float) * 1;
	case ShaderDataType::Float2:	return sizeof(float) * 2;
	case ShaderDataType::Float3:	return sizeof(float) * 3;
	case ShaderDataType::Float4:	return sizeof(float) * 4;

	default:
		CORE_ERROR("Unknown ShaderDataType.\n");
		return 0;
	}
}


#endif // !RENDERER_VERTEXLAYOUT_H_
