#ifndef SNAKE_GAMELAYER_H_
#define SNAKE_GAMELAYER_H_

#include <Core/Layer.h>
#include <Core/Timer.h>

namespace Snake {

class GameLayer : public Layer {
public:
    GameLayer();
    ~GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(double _Dt) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Event& _Event) override;

private:
	Timer m_GlobalTimer;
	Timer m_IGT;
};

} // namespace Snake

#endif // !SNAKE_GAMELAYER_H_
