#include "Tetromino.h"

#include <array>

Tetromino::Tetromino()
{
}

std::array<std::array<char, 3>, 3> Tetromino::CreateShape(char p_shapeType)
{
	std::array<std::array<char, 3>, 3> ResultShape;
	switch (p_shapeType)
	{
		case 't':
		{
			ReturnShape(shape_T, ResultShape);
			return ResultShape;
			break;
		}
		case 's':
		{
			ReturnShape(shape_S, ResultShape);
			return ResultShape;
			break;
		}
		case 'o':
		{
			ReturnShape(shape_O, ResultShape);
			return ResultShape;
			break;
		}
		case 'l':
		{
			ReturnShape(shape_L, ResultShape);
			return ResultShape;
			break;
		}
		case 'd':
		{
			ReturnShape(shape_D, ResultShape);
			return ResultShape;
			break;
		}
	}
}

void Tetromino::ReturnShape(const char(&InShape)[3][3], std::array<std::array<char, 3>, 3>& outArray)
{
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			outArray[i][j] = InShape[i][j];
		}
	}
}