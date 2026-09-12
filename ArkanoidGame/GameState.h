#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	class GameState
	{
	public:
		GameState() = default;
		// крнструктор с иницилизацией
		GameState(GameStateType type, bool isExclusivelyVisible);
		GameState(const GameState& state) = delete;
		GameState(GameState&& state) { *this = std::move(state); }

		~GameState();

		GameState& operator=(const GameState& state) = delete;
		// опретар перемещения с иницилизацией полей
		GameState& operator=(GameState&& state) noexcept
		{
			type = state.type;
			data = state.data;
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}

		GameStateType GetType() const { return type; }
		bool IsExclusivelyVisible() const { return isExclusivelyVisible; }

		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(const sf::Event& event);

	private:
		//иниц. полей при обьявление
		GameStateType type = GameStateType::None;
		void* data = nullptr;
		bool isExclusivelyVisible = false;
	};
}