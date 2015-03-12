// XCKD "Now" //////////////////////////////////////////////////////////////////
// By John Lawson //////////////////////////////////////////////////////////////
// Based on the Now comic by XKCD //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>


#ifdef _WIN64
	#define WINDOWS
#elif _WIN32
	#define WINDOWS
#elif __APPLE__
// this is unsupported for the moment
#elif __linux
	#define LINUX
#endif


#define version "1.05"

float Get_seconds_of_current_day();
float Get_current_rotation_angle(float day_seconds);

sf::Clock * dt_timer;
struct tm * ptm;

int main()
{	std::string title = "xkcd-Now ";
	title.append(version);
	sf::RenderWindow window(sf::VideoMode(600, 599), title);
	window.setFramerateLimit(20);
	
	sf::Texture overlay_tex;		
	sf::Texture spinner_tex;	
	#ifdef WINDOWS
		overlay_tex.loadFromFile("./Data/Now_Overlay.png");		
		spinner_tex.loadFromFile("./Data/World_Spinner.png");
		// these should flag an error if they cant load either
		// maybe we could link with Win32 and send a message box
	#else
		// we're on some sort of unix based OS, probably linux or OSX
		// we at least cover the bases for linux, and if we can figure out what
		// OSX needs, we add it
		if(!overlay_tex.loadFromFile("/usr/share/xkcd_now/Data/Now_Overlay.png"))
		{	std::cout << "Unable to load /usr/share/xkcd_now/Data/Now_Overlay.png" << std::endl;
			return -2;
		}	
		if(!spinner_tex.loadFromFile("/usr/share/xkcd_now/Data/World_Spinner.png"))
		{	std::cout << "Unable to load /usr/share/xkcd_now/Data/World_Spinner.png" << std::endl;
			return -3;
		}						
		// load the two png textures used in the program and flag the error
		// if they fail to load
	#endif
	
	
	sf::Sprite Overlay_sprite;	
	Overlay_sprite.setTexture(overlay_tex);
	// set the overlay (the part with the times of day and ok to call parts)
	// which will stay as it is throughout the whole program
	sf::Sprite Spinner_sprite;
	Spinner_sprite.setTexture(spinner_tex);
	Spinner_sprite.setOrigin(sf::Vector2f(255.5, 255.5));
	Spinner_sprite.setPosition(300, 299.5);
	// set the texture of the spinner (the part with all of the continents that
	// rotates around in the center)
	// center its origin so the origin isnt at the top left corner
	// and lastly, set its position in the middle of the window
	
	sf::RectangleShape Background(sf::Vector2f(600, 599));
	Background.setFillColor(sf::Color::White);
	// draws a white background for us because that looks better
	// I think this could potentially be done in a different way through the
	// sf window
	
	const sf::Vector2u WSize(600,599);
	// constant values for the size of the window
	dt_timer = new sf::Clock();
	// doesnt need to be a pointer, this should be just a normal sf::Clock instead
	long double dt = 0;
	Spinner_sprite.setRotation(Get_current_rotation_angle(Get_seconds_of_current_day()));

		
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
		Spinner_sprite.setRotation(Get_current_rotation_angle(Get_seconds_of_current_day()));
		// rotate around the polar projection of the continents depending on the
		// current time of day
			
		window.clear();
		window.draw(Background);
		window.draw(Overlay_sprite);
		window.draw(Spinner_sprite);
		// clear the window and draw everything all over again
		window.display();
	}
	delete dt_timer;
	// augh good grief
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
