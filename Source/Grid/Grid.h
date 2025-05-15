#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <array>
#include <random>

#include "Tetromino/Tetromino.h"
#include "Global/PPD.h"

class Grid
{
public:
	// Default constructor
	Grid();
	// A constructor that takes in rows and columns
	Grid(int p_rows, int p_cols);
	// Destructor
	~Grid();
	// We do not allow copying or moving of grid object
	Grid(const Grid& Other) = delete;
	Grid(Grid&& Other) = delete;
	Grid& operator = (Grid other) = delete;

	// Set Window 
	inline void SetWindow(std::shared_ptr<sf::RenderWindow>& window) { m_windowObv = window; }

	void Update(float deltaTime);

	void DrawGrid();
	void DrawTetromineos();
	void SpawnTetromino();
	bool RotateCurrentTetromino();
	bool MoveTetrominoDown();
	bool MoveTetrominoSideways(bool bisLeft);
	std::vector<std::pair<int, int>> GetShapeIndexes(std::array<std::array<char, 3>, 3>& p_inShape);
	int GenerateRandomShapeIndex();

	bool CheckCompleteRow();

	inline char GetIncomingShape() const { return m_incomingTetromino; }

	char GetRandomShape();

protected:
	int m_rows;
	int m_cols;

	std::unique_ptr<Tetromino> m_tetrominoGenerator;

	std::shared_ptr<sf::RenderWindow> m_windowObv;

	std::vector<std::vector<char>> m_gridData;

private:
	std::function<sf::Color(char)> GetColor;
	std::array<std::array<char, 3>, 3> m_currentShape;
	
	int m_currRow, m_currCol;

	float m_moveDownTimer = 0.0f;

	char m_incomingTetromino;
};