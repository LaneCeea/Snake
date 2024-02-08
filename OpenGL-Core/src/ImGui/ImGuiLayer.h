#ifndef IMGUIAPI_IMGUIAPI_H_
#define IMGUIAPI_IMGUIAPI_H_

#include <Core/Layer.h>

class ImGuiLayer : public Layer {
public:
	ImGuiLayer() : Layer("ImGuiLayer") {}
	~ImGuiLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(double _Dt) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& _Event) override;

	void Begin();
	void End();
};

#endif // !IMGUIAPI_IMGUIAPI_H_
