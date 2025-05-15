#include "TetrisGame.h"

int main()
{
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(430, 800), "Tetris Game");
	std::shared_ptr<Grid> m_grid = std::make_shared<Grid>(24,16);
	m_grid->SetWindow(window);

	sf::Clock g_clock;
	float deltaTime = 0.0f;

	//sf::Font font;
	//if (!font.loadFromFile("Resources/Fonts/OpenSans-Light.ttf"))
	//{
	//	system("pause");
	//}

	//sf::Text text("Made By R.Haris Nauman v0.2", font, 11);
	//sf::Text footer("Next Tetromino : ", font, 20);
	//footer.setPosition(sf::Vector2f(20.0f, 620.0f));


	while (window->isOpen())
	{
		deltaTime = g_clock.restart().asSeconds();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "Pressed Spacebar!" << '\n';
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					m_grid->RotateCurrentTetromino();
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Down)
				{
					// Move the Current Tetromino down
					m_grid->MoveTetrominoDown();
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					m_grid->MoveTetrominoSideways(true);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					m_grid->MoveTetrominoSideways(false);
				}
			}
		}

		window->clear();
		m_grid->Update(deltaTime);
		//window->draw(text);
		//window->draw(footer);
		window->display();
	}
}