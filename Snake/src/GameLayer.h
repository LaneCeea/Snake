#ifndef SNAKE_GAMELAYER_H_
#define SNAKE_GAMELAYER_H_

#include "Snake.h"

#include <Core/Layer.h>
#include <Core/Timer.h>
#include <Event/KeyEvent.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>

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

	bool OnKeyEvent(KeyEvent& _KeyEvent);

private:
	Snake m_Snake;
	Snake::MoveDirection m_SnakeNextDir;

	Shader m_FlatColorShader;
	Shader m_BasicTextureShader;
	Texture m_ExplosionTexture;

	Timer m_GlobalTimer;
	Timer m_Igt; // in-game timer
	double m_TickInterval;
	double m_CurrentTimeBetweenTick;
	bool m_IsRunning;
};

} // namespace Snake

#endif // !SNAKE_GAMELAYER_H_
