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

class Agent: public Entity {
	public:
		sf::RectangleShape shape;
		float maxSpeed;
		sf::Vector2f velocity;
};

class Wall: public Entity {
	public:
		sf::RectangleShape shape;
		sf::Vector2f size;
		Wall(float x, float y, float width, float height): Entity(x, y) {
			size.x = width;
			size.y = height;
		}	
};

bool checkCollision(sf::RectangleShape shape1, sf::RectangleShape shape2) {
	sf::Vector2f size1 = shape1.getSize();
	sf::Vector2f size2 = shape2.getSize();
	cout << size1 << endl;
	cout << shape1.getPosition() << endl;
	return true;
}

void update(Agent& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.x -= player.speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.y -= player.speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.x += player.speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.y += player.speed;
	}
}

void render(sf::RenderWindow& window, Entity& entities) {
	//render each entity in list of entities somehow
	//make sure to round doubles to ints before rendering.
	//does this mean we need the shapes as seperate from the objects?
	//we could go through a list of shapes instead of objects...
	//could have a pointer to a shape for each object
	//need to keep sprites in mind. not always going to be shapes.
	//probably need to get the answer from the internet.
	//wait on this for now.
}

int main() {
	sf::RenderWindow window(
			sf::VideoMode(640, 480),
			"whatup");
	Agent player(400, 200);
	player.shape = sf::RectangleShape(sf::Vector2f(40,40));
	player.speed = 1;

	Wall wall(100,100);
	wall.shape = sf::RectangleShape(sf::Vector2f(20,100));
	
	cout << checkCollision(player.shape, wall.shape) << endl;

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		update(player);

		player.shape.setPosition(player.x, player.y);
		wall.shape.setPosition(wall.x, wall.y);
		window.clear();
		window.draw(player.shape);
		window.draw(wall.shape);
		window.display();

		
		sf::Time elapsed = clock.getElapsedTime();
		while(elapsed.asMilliseconds() < 1000/tickRate) {
			elapsed = clock.getElapsedTime();
		}
		clock.restart();
	}
	return 0;
}
