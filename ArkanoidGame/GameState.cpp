#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateWin.h"
#include <cassert>

namespace ArkanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
			data = std::make_unique<GameStateMainMenuData>();
			break;
		case GameStateType::Playing:
			data = std::make_unique<GameStatePlayingData>();
			break;
		case GameStateType::GameOver:
			data = std::make_unique<GameStateGameOverData>();
			break;
		case GameStateType::Win:
			data = std::make_unique<GameStateWinData>();
			break;
		case GameStateType::ExitDialog:
			data = std::make_unique<GameStatePauseMenuData>();
			break;
		default:
			assert(false);
			break;
		}

		if (data)
		{
			data->Init();
		}
	}

	GameState::~GameState()
	{
		
	}

	GameState& GameState::operator=(GameState&& state) noexcept
	{
		if (this == &state) return *this;

		type = state.type;
		data = std::move(state.data);
		isExclusivelyVisible = state.isExclusivelyVisible;

		return *this;
	}

	void GameState::Update(float timeDelta)
	{
		data->Update(timeDelta);
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		data->Draw(window);
	}

	void GameState::HandleWindowEvent(const sf::Event& event)
	{
		data->HandleWindowEvent(event);
	}
}