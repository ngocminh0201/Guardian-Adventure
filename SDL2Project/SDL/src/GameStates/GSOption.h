#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "GameObject/Text.h"
#include "GameObject/Sound.h"

class GSOption :
	public GameStateBase
{
public:
	GSOption();
	~GSOption();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;
	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<Sprite2D>				m_background;
	std::shared_ptr<MouseButton> button;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_option;
	SDL_Color textColor = { 255, 0, 0, 255 }; // Red color
};