#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <algorithm>


/*
*
*	Return Shape Function is unnecessary
*	This was done to test out std::array
* 
*/

class Tetromino
{
public:
	Tetromino();
	~Tetromino() = default;

	std::array<std::array<char, 3>, 3> CreateShape(char p_shapeType);
	void ReturnShape(const char (&InShape)[3][3], std::array<std::array<char, 3>, 3>& outArray);

protected:
	char shape_L[3][3] = {
		{'.', 'l', '.'},
		{'.', 'l', '.'},
		{'.', 'l', 'l'}
	};

	char shape_T[3][3] = {
		{'t', 't', 't'},
		{'.', 't', '.'},
		{'.', '.', '.'}
	};

	char shape_O[3][3] = {
		{'o', 'o', '.'},
		{'o', 'o', '.'},
		{'.', '.', '.'}
	};

	char shape_S[3][3] = {
		{'.', 's', 's'},
		{'s', 's', '.'},
		{'.', '.', '.'}
	};

	char shape_D[3][3] = {
		{'.', '.', '.'},
		{'d', 'd', 'd'},
		{'.', '.', '.'}
	};
};