/* 
 * todo 
 */

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int tickRate = 60;

ostream& operator<<(ostream& os, const sf::Vector2f v) {
	os << "{" << v.x << ", " << v.y << "}";
	return os;
}

ostream& operater<<(ostream& os, const Entity e) {
	os << "Entity: pos " << e.pos << " vel " << e.vel << " acc " << e.acc << endl; 
	return os;
}

class Entity {
	public:
		sf::Vector2f pos;
		sf::Vector2f vel(0, 0);
		sf::Vector2f acc(0, 0);
		Entity(float x, float y) {
			pos.x = x;
			pos.y = y;
		}	
		Entity(float px, float py, float vx, float vy): Entity(px, py) {
			vel.x = vx;
			vel.y = vy;
		}
		Entity(float px, float py, float vx, float vy, float ax, float ay): Entity(px, py, vx, vy) {
			acc.x = ax;
			acc.y = ay;
		}
};

bool checkCollision(sf::RectangleShape shape1, sf::RectangleShape shape2) {
	sf::Vector2f size1 = shape1.getSize();
	sf::Vector2f size2 = shape2.getSize();
	cout << size1 << endl;
	cout << shape1.getPosition() << endl;
	return true;
}

class Game {
	public:
		sf::RenderWindow window(sf::VideoMode(640, 480),"game");
		Entity player(200, 200);
		sf::RectangleShape playerShape(sf::Vector2f(200, 200));

	void update() {
		//get input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.vel.x = -player.maxspeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.vel.y = -player.maxspeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.vel.x = -player.maxSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.vel.y = player.maxSpeed;
		}
		else {
			player.vel.x = 0;
			player.vel.y = 0;
		}

		//update pos and vel 
		player.vel.x += player.acc.x;
		player.vel.y += player.acc.y;
		player.pos.x += player.vel.x;
		player.pos.y += player.vel.y;
	}

	void render() {
		playerShape.setPosition(player.pos.x, player.pos.y);
		
		window.clear();
		window.draw(playerShape);
	}

	void startGameLoop() {
		sf::Clock clock;
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			update();
			render();			

			sf::Time elapsed = clock.getElapsedTime();
			while(elapsed.asMilliseconds() < 1000/tickRate) {
				elapsed = clock.getElapsedTime();
			}
			clock.restart();
		}
	}
};

int main() {
	Game game;
	game.startGameLoop();
	return 0;
}
