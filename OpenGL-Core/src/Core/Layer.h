#ifndef CORE_LAYER_H_
#define CORE_LAYER_H_

#include <Event/Event.h>

#include <string_view>

class Layer {
public:
	Layer(std::string_view _Name = "Layer") : m_DebugName(_Name) {}
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(double _Dt) {}
	virtual void OnImGuiRender() {}
	virtual void OnEvent(Event& _Event) {}

	const std::string_view& Name() const { return m_DebugName; }
protected:
	std::string_view m_DebugName;
};

#endif // !CORE_LAYER_H_
