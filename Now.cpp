// XCKD "Now" //////////////////////////////////////////////////////////////
// By John Lawson //////////////////////////////////////////////////////////
// Based on the Now comic by XKCD //////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define version "1.04"

float Get_seconds_of_current_day();
float Get_current_rotation_angle(float day_seconds);

sf::Clock * dt_timer;

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
	const sf::Vector2u WSize(600,599);
	dt_timer = new sf::Clock();
	long double dt = 0;
	Spinner_sprite.setRotation(Get_current_rotation_angle(Get_seconds_of_current_day()));
	window.clear();
	window.draw(Background);
	window.draw(Overlay_sprite);
	window.draw(Spinner_sprite);	
	while (window.isOpen())
	{	sf::Time Elapsed_time;
		Elapsed_time = dt_timer->restart();
		dt += Elapsed_time.asSeconds();
		window.setSize(WSize);
		sf::Event event;
		while (window.pollEvent(event))
		{	if (event.type == sf::Event::Closed)
			{	window.close();
			}
        }
		if(dt >= 4.000000000000000000000)
		{	dt = 0.000000000000000000000;
			Spinner_sprite.setRotation(Get_current_rotation_angle(Get_seconds_of_current_day()));
			window.clear();
			window.draw(Background);
			window.draw(Overlay_sprite);
			window.draw(Spinner_sprite);
			window.display();
		}
		window.display();
	}	delete dt_timer;
	return 0;
}

float Get_seconds_of_current_day()
{	float seconds = 0;
	time_t rawtime;
	time(&rawtime);
	ptm = gmtime(&rawtime);
	seconds += (ptm->tm_hour)*3600;	
	seconds += (ptm->tm_min + 24)*60;
	seconds += ptm->tm_sec;	
	return seconds;
}

float Get_current_rotation_angle(float day_seconds)
{	float angle = 0;
	angle += (day_seconds/86400)*360;
	return angle;
}
