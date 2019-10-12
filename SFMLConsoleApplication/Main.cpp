#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;
using namespace std;


int main(){
	const string windowTitle = "SFML Console Application";
	const VideoMode videoMode = VideoMode(768, 1024);
	const Color backgroundColor = Color::Black;
	const unsigned int FRAMERATE_LIMIT = 60;
	RenderWindow window(videoMode, windowTitle, Style::Titlebar | Style::Close);
	window.setFramerateLimit(FRAMERATE_LIMIT);
	while(window.isOpen()) {
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed){
				window.close();
			}
		}
		window.clear(backgroundColor);
		window.display();
	}
	return 0;
}