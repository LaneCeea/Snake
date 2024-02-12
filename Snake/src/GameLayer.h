#ifndef SNAKE_GAMELAYER_H_
#define SNAKE_GAMELAYER_H_

#include "Snake.h"

#include <Core/Layer.h>
#include <Core/Timer.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>

#include <memory>

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

	Snake m_Snake;

	std::unique_ptr<VertexArray> m_SquareVao;
	std::unique_ptr<Shader> m_FlatColorShader;

	Timer m_GlobalTimer;
	Timer m_Igt; // in-game timer
	double m_TickInterval;
	double m_CurrentTimeBetweenTick;
};

} // namespace Snake

#endif // !SNAKE_GAMELAYER_H_
