#include "Grid.h"

Grid::Grid() : Grid(16, 24)
{

}

Grid::Grid(int p_rows, int p_cols) : m_rows(p_rows), m_cols(p_cols), m_currRow(0), m_currCol(0)
{
	std::cout << "This Grid has " << m_rows << " Rows and " << m_cols << " Columns" << '\n';

	m_tetrominoGenerator = std::make_unique<Tetromino>();

	m_gridData.resize(m_rows);
	for (int i = 0;i < m_rows;i++)
	{
		m_gridData[i].resize(m_cols);
		for (int j = 0;j < m_cols;j++)
		{
			m_gridData[i][j] = '.';
		}
	}

	GetColor = [](char letter) 
	{ 
		switch (letter)
		{
			case 't':
			{
				return sf::Color::Magenta;
				break;
			}
			case 's':
			{
				return sf::Color::Yellow;
				break;
			}
			case 'o':
			{
				return sf::Color::Green;
				break;
			}
			case 'l':
			{
				return sf::Color::Red;
				break;
			}
			case 'd':
			{
				return sf::Color::Cyan;
				break;
			}
		}
	};

	// Create a Dummy Shape
	m_currCol = 7;
	m_currentShape = m_tetrominoGenerator->CreateShape('t');
	
	m_incomingTetromino = GetRandomShape();
}

Grid::~Grid()
{
	std::cout << "Grid was Destroyed!" << '\n';
}

void Grid::Update(float deltaTime)
{
	if (BLOCK_MOVE_DOWN_TIME > m_moveDownTimer)
	{
		m_moveDownTimer += deltaTime;
	}
	else
	{
		m_moveDownTimer = 0.0f;
		MoveTetrominoDown();
	}

	DrawGrid();
	DrawTetromineos();

	// Draw Incoming Shape
	std::array<std::array<char, 3>, 3> dummyShape = m_tetrominoGenerator->CreateShape(m_incomingTetromino);
	sf::Color dummyShapeColor = GetColor(m_incomingTetromino);
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (dummyShape[i][j] != '.')
			{
				sf::RectangleShape rectShape(sf::Vector2f(25.0f, 25.0f));
				rectShape.setFillColor(dummyShapeColor);
				rectShape.setPosition(sf::Vector2f(j * 26.0f, i * 26.0f) + sf::Vector2f(50.0f, 650.0f));
				m_windowObv->draw(rectShape);
			}
		}
	}

}

void Grid::DrawGrid()
{
	if (m_windowObv.use_count() != 0)
	{
		for (int i = 0;i < m_rows;i++)
		{
			for (int j = 0;j < m_cols;j++)
			{
				sf::RectangleShape boxShape(sf::Vector2f(24.0f, 24.0f));
				boxShape.setFillColor(sf::Color::Black);
				boxShape.setOutlineThickness(2.0f);
				boxShape.setOutlineColor(sf::Color::White);
				boxShape.setPosition(sf::Vector2f(j * 25.0f, i * 25.0f) + sf::Vector2f(15.0f, 15.0f));
				m_windowObv->draw(boxShape);
			}
		}
	}
}

void Grid::DrawTetromineos()
{
	for (int i = 0;i < m_rows;i++)
	{
		for (int j = 0;j < m_cols;j++)
		{
			if (m_gridData[i][j] != '.')
			{
				sf::RectangleShape shape(sf::Vector2f(23.0f, 23.0f));
				shape.setFillColor(GetColor(m_gridData[i][j]));
				shape.setPosition(sf::Vector2f(j * 25.0f, i * 25.0f) + sf::Vector2f(15.0f, 15.0f));
				m_windowObv->draw(shape);
			}
		}
	}

	// Draw active tetromino
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (m_currentShape[i][j] != '.')
			{
				sf::RectangleShape shape(sf::Vector2f(23.0f, 23.0f));
				shape.setFillColor(GetColor(m_currentShape[i][j]));
				shape.setPosition(sf::Vector2f((m_currCol * 25.0f) + j * 25.0f, (m_currRow * 25.0f) + i * 25.0f) + sf::Vector2f(15.0f, 15.0f));
				m_windowObv->draw(shape);
			}
		}
	}
}

void Grid::SpawnTetromino()
{
	std::vector<std::pair<int, int>> shapeIndexes = GetShapeIndexes(m_currentShape);
	// Transfer all the blocks to grid
	for (std::pair<int, int>& indexPair : shapeIndexes)
	{
		m_gridData[m_currRow + indexPair.first][m_currCol + indexPair.second] = m_currentShape[indexPair.first][indexPair.second];
	}
	// spawn a new tetromino
	m_currCol = 7;
	m_currRow = 0;
	// Shape
	m_currentShape = m_tetrominoGenerator->CreateShape(m_incomingTetromino);
	m_incomingTetromino = GetRandomShape();
	
	shapeIndexes = GetShapeIndexes(m_currentShape);

	for (auto& [i, j] : shapeIndexes)
	{
		if (m_gridData[m_currRow + i][m_currCol + j] != '.')
		{
			std::cout << "Game Over!" << std::endl;
			
			for (int k = 0;k < m_rows;k++)
			{
				std::fill(m_gridData[k].begin(), m_gridData[k].end(), '.');
			}
		}
	}
}

bool Grid::RotateCurrentTetromino()
{
	std::array<std::array<char, 3>, 3> rotatedShape = {};

	// Transpose the matrix
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rotatedShape[j][i] = m_currentShape[i][j];
		}
	}

	// Reverse the rows
	std::reverse(std::begin(rotatedShape), std::end(rotatedShape));

	// Check if the rotated shape is out of bounds?
	std::vector<std::pair<int, int>> shapeIndexes = GetShapeIndexes(rotatedShape);
	for (std::pair<int, int>& indexPair : shapeIndexes)
	{
		if (m_currRow + indexPair.first >= m_rows || m_currRow + indexPair.first < 0 || m_currCol + indexPair.second >= m_cols || m_currCol + indexPair.second < 0)
		{
			std::cout << "Invalid Rotation Detected!" << '\n';
			return false;
		}
		else if (m_gridData[m_currRow + indexPair.first][m_currCol + indexPair.second] != '.')
		{
			std::cout << "Invalid Rotation Detected!" << '\n';
			return false;
		}
	}

	//Assign the rotated shape to the current shape
	std::move(&rotatedShape[0][0], &rotatedShape[0][0] + 3 * 3, &m_currentShape[0][0]);


	return true;
}

bool Grid::MoveTetrominoDown()
{
	std::vector<std::pair<int, int>> shapeIndexes = GetShapeIndexes(m_currentShape);

	if (!shapeIndexes.empty())
	{
		for (std::pair<int, int>& indexPair : shapeIndexes)
		{
			bool bisNotInBounds = (m_currRow + indexPair.first + 1) >= m_rows;
			if (bisNotInBounds)
			{
				// Spawn a New Tetromino
				SpawnTetromino();
				CheckCompleteRow();
				return false;
			}
			else
			{
				bool bisSomethingUnder = m_gridData[(m_currRow + indexPair.first + 1)][m_currCol + indexPair.second] != '.';
				if (bisSomethingUnder)
				{
					// Spawn a New Tetromino
					SpawnTetromino();
					CheckCompleteRow();
					return false;
				}
			}
		}
		m_currRow += 1;
		return true;
	}
	return false;
}

bool Grid::MoveTetrominoSideways(bool bisLeft)
{
	int value = bisLeft ? -1 : 1;
	std::vector<std::pair<int, int>> shapeIndexes = GetShapeIndexes(m_currentShape);

	if (!shapeIndexes.empty())
	{
		for (std::pair<int, int>& indexPair : shapeIndexes)
		{
			if ((m_currCol + indexPair.second + value) >= m_cols || (m_currCol + indexPair.second + value) < 0)
			{
				return false;
			}
			else if (m_gridData[m_currRow + indexPair.first][(m_currCol + indexPair.second + value)] != '.')
			{
				return false;
			}
		}

		m_currCol += value;
		return true;
	}

	return false;
}

std::vector<std::pair<int, int>> Grid::GetShapeIndexes(std::array<std::array<char, 3>, 3>& p_inShape)
{
	std::vector<std::pair<int, int>> result;
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (p_inShape[i][j] != '.')
			{
				result.push_back(std::make_pair(i,j));
			}
		}
	}

	return result;
}

int Grid::GenerateRandomShapeIndex()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 4);

	return distr(gen);
}

bool Grid::CheckCompleteRow()
{
	// Start from Bottom and go up
	for (int i = m_rows - 1; i > -1;i--)
	{
		bool bisRowComplete = true;
		for (int k = m_cols - 1; k > -1; k--)
		{
			if (m_gridData[i][k] == '.')
			{
				bisRowComplete = false;
				break;
			}
		}

		// if you find a complete row than remove that entire row
		if (bisRowComplete)
		{
			for (int j = 0; j < m_cols; j++)
			{
				m_gridData[i][j] = '.';
			}
			// move all the upper blocks down by 1 unit.
			for (int l = i; l > -1; l--)
			{
				for (int m = m_cols - 1; m > -1; m--)
				{
					if ((l + 1) < m_rows)
					{
						if (m_gridData[l + 1][m] == '.')
						{
							std::swap(m_gridData[l][m], m_gridData[l + 1][m]);
						}
					}
				}
			}
			return true;
		}
	}
	return false;
}

char Grid::GetRandomShape()
{
	int randIndex = GenerateRandomShapeIndex();
	char shapes[5] = { 'l', 't', 's', 'o', 'd' };
	return shapes[randIndex];
}
