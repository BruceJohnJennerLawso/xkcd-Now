// XCKD "Now" //////////////////////////////////////////////////////////////
// By John Lawson //////////////////////////////////////////////////////////
// Based on the Now comic by XKCD //////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <iostream>

#define version "1.01"

float Get_seconds_of_current_day();
float Get_current_rotation_angle(float day_seconds);

struct tm * ptm;

int main()
{	std::string title = "xkcd-Now ";
	title.append(version);
	sf::RenderWindow window(sf::VideoMode(600, 599), title);
	sf::Texture overlay_tex;	sf::Sprite Overlay_sprite;		
	overlay_tex.loadFromFile("./Data/Now_Overlay.png");		Overlay_sprite.setTexture(overlay_tex);
	sf::Texture spinner_tex;	sf::Sprite Spinner_sprite;
	spinner_tex.loadFromFile("./Data/World_Spinner.png");	Spinner_sprite.setTexture(spinner_tex);
	Spinner_sprite.setOrigin(sf::Vector2f(255.5, 255.5));
	Spinner_sprite.setPosition(300, 299.5);
	sf::RectangleShape Background(sf::Vector2f(600, 599));
	Background.setFillColor(sf::Color::White);
	std::cout << Get_seconds_of_current_day() << std::endl;
	std::cout << Get_current_rotation_angle(Get_seconds_of_current_day()) << std::endl;
	while (window.isOpen())
	{	window.setSize(sf::Vector2u(600, 599));
		Spinner_sprite.setRotation(Get_current_rotation_angle(Get_seconds_of_current_day()));
		sf::Event event;
		while (window.pollEvent(event))
		{	if (event.type == sf::Event::Closed)
			{	window.close();
			}
        }

		window.clear();
		window.draw(Background);
		window.draw(Overlay_sprite);
		window.draw(Spinner_sprite);
		window.display();
	}
	return 0;
}

float Get_seconds_of_current_day()
{	float seconds = 0;
	time_t rawtime;
	time(&rawtime);
	ptm = gmtime(&rawtime);
	seconds += (ptm->tm_hour)*3600;	
	seconds += (ptm->tm_min + 30)*60;
	seconds += ptm->tm_sec;	
	return seconds;
}

float Get_current_rotation_angle(float day_seconds)
{	float angle = 0;
	angle += (day_seconds/86400)*360;
	return angle;
}