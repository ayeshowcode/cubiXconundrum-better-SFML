#include <sstream>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

#include <iostream>
#include <ctime>

namespace Sonar
{
    std::array<std::array<std::array<int, GameState::GRID_SIZE>, GameState::GRID_SIZE>, GameState::NUM_SHAPES> GameState::blockShapes = { {
        {{
            {0, 0, 0, 0},
            {1, 1, 1, 1},  // I shape
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }},
        {{
            {0, 1, 0, 0},
            {0, 1, 0, 0},  // T shape
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }}
    } };

    GameState::GameState(GameDataRef data) : _data(data), isDragging(false) {}

    void GameState::Init()
    {
        gameState = STATE_PLAYING;
        turn = PLAYER_PIECE;

        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
        this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);

        _background.setTexture(this->_data->assets.GetTexture("Background"));
        _pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
        _gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

        _pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
        _gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2),
            (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

        for (int x = 0; x < 9; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                _gridArray[x][y] = EMPTY_PIECE;
            }
        }
        generateRandomBlock();
        InitGridPieces();

        // Initialize the block position at the center bottom of the screen
        blockPosition = sf::Vector2f((SCREEN_WIDTH - GRID_SIZE * 55) / 2, SCREEN_HEIGHT - 55 * GRID_SIZE);
    }

    void GameState::generateRandomBlock()
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        int index = std::rand() % NUM_SHAPES;

        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                currentBlock[i][j] = blockShapes[index][i][j];
            }
        }
    }

    void GameState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }

            if (this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->window);
                sf::FloatRect blockBounds(blockPosition.x, blockPosition.y, GRID_SIZE * 55, GRID_SIZE * 55);

                if (blockBounds.contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    isDragging = true;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                isDragging = false;

                // Check if the block is placed within the grid bounds
                sf::FloatRect gridBounds = _gridSprite.getGlobalBounds();
                if (gridBounds.contains(blockPosition))
                {
                    int gridX = (blockPosition.x - gridBounds.left) / 55;
                    int gridY = (blockPosition.y - gridBounds.top) / 55;

                    // Place the block in the grid
                    for (int i = 0; i < GRID_SIZE; i++)
                    {
                        for (int j = 0; j < GRID_SIZE; j++)
                        {
                            if (currentBlock[i][j] == 1 && gridX + i < 9 && gridY + j < 9)
                            {
                                _gridArray[gridX + i][gridY + j] = 1;
                            }
                        }
                    }

                    // Clear completed rows and columns
                    clearCompletedRowsAndColumns();

                    // Generate a new block
                    generateRandomBlock();
                    blockPosition = sf::Vector2f((SCREEN_WIDTH - GRID_SIZE * 55) / 2, SCREEN_HEIGHT - 55 * GRID_SIZE);
                }
            }

            if (event.type == sf::Event::MouseMoved && isDragging)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(this->_data->window);
                blockPosition = static_cast<sf::Vector2f>(mousePos);
            }
        }
    }

    void GameState::Update(float dt) {}

    void GameState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);

        this->_data->window.draw(this->_background);
        this->_data->window.draw(this->_pauseButton);
        this->_data->window.draw(this->_gridSprite);

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (_gridArray[i][j] == 1)
                {
                    this->_data->window.draw(this->_gridPieces[i][j]);
                }
            }
        }

        for (int i = 0; i < GRID_SIZE; i++)
        {
            for (int j = 0; j < GRID_SIZE; j++)
            {
                if (currentBlock[i][j] == 1)
                {
                    sf::Sprite block(this->_data->assets.GetTexture("X Piece"));
                    block.setPosition(blockPosition.x + i * 55, blockPosition.y + j * 55);
                    this->_data->window.draw(block);
                }
            }
        }

        this->_data->window.display();
    }

    void GameState::InitGridPieces()
    {
        sf::Texture& xPieceTexture = this->_data->assets.GetTexture("X Piece");

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                _gridPieces[i][j].setTexture(xPieceTexture);
                _gridPieces[i][j].setPosition(_gridSprite.getPosition().x + i * 55 + 2, _gridSprite.getPosition().y + j * 55 + 2);
            }
        }
    }

    void GameState::clearCompletedRowsAndColumns()
    {
        // Check and clear completed rows
        for (int i = 0; i < 9; i++)
        {
            bool rowComplete = true;
            for (int j = 0; j < 9; j++)
            {
                if (_gridArray[i][j] == EMPTY_PIECE)
                {
                    rowComplete = false;
                    break;
                }
            }
            if (rowComplete)
            {
                for (int j = 0; j < 9; j++)
                {
                    _gridArray[i][j] = EMPTY_PIECE;
                }
            }
        }

        // Check and clear completed columns
        for (int j = 0; j < 9; j++)
        {
            bool columnComplete = true;
            for (int i = 0; i < 9; i++)
            {
                if (_gridArray[i][j] == EMPTY_PIECE)
                {
                    columnComplete = false;
                    break;
                }
            }
            if (columnComplete)
            {
                for (int i = 0; i < 9; i++)
                {
                    _gridArray[i][j] = EMPTY_PIECE;
                }
            }
        }
    }

    void GameState::CheckAndPlacePiece() {}

    void GameState::CheckHasPlayerWon(int player) {}

    void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {}
}
