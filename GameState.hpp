#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <array>

namespace Sonar
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		static const int GRID_SIZE = 4;  // Grid size for the Tetris block
		static const int NUM_SHAPES = 2; // Number of different shapes
		static std::array<std::array<std::array<int, GRID_SIZE>, GRID_SIZE>, NUM_SHAPES> blockShapes; // Block shapes

		std::array<std::array<int, GRID_SIZE>, GRID_SIZE> currentBlock; // Current block
		sf::Vector2f blockPosition; // Position of the current block

		void generateRandomBlock(); // Function to generate a random block
		void InitGridPieces();
		bool canMove(int dx, int dy); // Function to check if the block can move to the new position
		void CheckAndPlacePiece();
		void CheckHasPlayerWon(int turn);
		void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);
		void clearCompletedRowsAndColumns();

		GameDataRef _data;
		int scoreint;
		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;
		sf::Sprite blockSprite;
		sf::Sprite _gridPieces[9][9];
		sf::Font font;
		sf::Text score;
		int _gridArray[9][9];
		int turn;
		int gameState;
		bool isDragging;
	};
}
