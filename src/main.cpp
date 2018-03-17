#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

enum player {
	white = 0,
	dark = 1
};

player p1 = white, p2 = dark;

int size = 56;
Vector2f offset(28,28);

Sprite f[16]; //figures
std::string position="";

int board[8][8] = {
	{ 0,-1, 0,-1, 0,-1, 0,-1},
	{-1, 0,-1, 0,-1, 0,-1, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 1, 0, 1, 0, 1, 0, 1},
	{ 1, 0, 1, 0, 1, 0, 1, 0} };

int movable_possitions[8][8] = {
	{ 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0 }};


void loadPosition() {
	int k = 0;
	for (int i = 0 ; i < 8 ; i++)
		for (int j = 0 ; j < 8 ; j++) {
			int n = board[i][j];
			if (!n)
				continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			f[k].setTextureRect(IntRect(size * x, size * y, size, size));
			f[k].setPosition(size * j, size * i);
			k++;
		}

	for(int i = 0 ; i < position.length() ; i += 5)
		move(position.substr(i, 4));
}

//TODO
bool canMove(float x, float y) {
	return true;
}

//TODO
bool canJump(float x, float y) {

	return false;
}

int main() {
/** DECLARATIONS **/
	RenderWindow window(VideoMode(504, 504), "The Chess! (press SPACE)");

	Texture t1, t2;
	t1.loadFromFile("../img/pawns.png");
	t2.loadFromFile("../img/board.png");


	for(int i = 0 ; i < 16 ; i++)
		f[i].setTexture(t1);
	Sprite sBoard(t2);

	loadPosition();

	float dx = 0, dy = 0;
	int n = 15;

/*** MAIN CYCLE ***/
	while (window.isOpen()) {
		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

/** DRAG **/
			if (e.type == Event::MouseButtonPressed) {
				for(int i = 0 ; i < 16 ; i++)
					if (f[i].getGlobalBounds().contains(pos.x, pos.y)) {
						n = i;
						dx = pos.x - f[i].getPosition().x;
						dy = pos.y - f[i].getPosition().y;
						cout << "Neco se stalo " << i << endl;
					}
			}

/** DROP **/
			if (e.type == Event::MouseButtonReleased) {
				if (canMove((Mouse::getPosition().x - Vector2f(offset).x), (Mouse::getPosition().y - Vector2f(offset).y))) {
					Vector2i p = Mouse::getPosition(window) - Vector2i(size/2,size/2);
					Vector2f tmp = Vector2f( size*(p.x/size), size*(p.y/size) ); ///< locks to position
					f[n].setPosition(tmp);
				}
				if (canJump(Mouse::getPosition().x, Mouse::getPosition().y)) {
					//TODO
				}
			}

/** DRAW **/
		window.clear();
    	window.draw(sBoard);
		for (int i = 0 ; i < 16 ; i++)
			f[i].move(offset);
    	for (int i = 0 ; i < 16 ; i++)
			window.draw(f[i]);
		window.draw(f[n]);
		for (int i = 0 ; i < 16 ; i++)
			f[i].move(-offset);
 		window.display();
	} // while (window.isOpen())

    return 0;
}
