#include <math.h>
#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define PI 3.14159265359

typedef uint8_t byte;

byte grid[100][100];
byte colliders[100][100];

struct Vec2
{
	byte y, x;
	Vec2(){}
	Vec2(byte dy, byte dx) : x(dx), y(dy){}
};

struct Piece
{
	Vec2 a, b, c, d;
	Piece(){}
	Piece(byte ax, byte ay, byte bx, byte by, byte cx, byte cy, byte dx, byte dy)
		: a(Vec2(ax,ay)), b(Vec2(bx, by)), c(Vec2(cx, cy)), d(Vec2(dx, dy)) {}
	Piece(Vec2 da, Vec2 db, Vec2 dc, Vec2 dd)
		: a(da), b(db), c(dc), d(dd){}
};

enum PIECE_TYPE
{
	S, Z, L, J, SQR, I, T
};

Piece CreatePiece(PIECE_TYPE type)
{
	switch (type)
	{
	case S : return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(0, 4), Vec2(2, 5));
		break;
	case Z: return Piece(Vec2(1, 4), Vec2(1, 5), Vec2(0, 5), Vec2(2, 4));
		break;
	case L: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 6));
		break;
	case J: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 4));
		break;
	case SQR: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(0, 5), Vec2(0, 4));
		break;
	case I: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(1, 7));
		break;
	case T: return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 5));
		break;
	default:
		break;
	}

	printf("invalid piece"); return Piece();
}

void rotate(Piece& piece)
{
	float angle = 90 * (PI / 180);

	float b_offset_x = piece.b.x - piece.a.x;
	float c_offset_x = piece.c.x - piece.a.x;
	float d_offset_x = piece.d.x - piece.a.x;

	float b_offset_y = piece.b.y - piece.a.y;
	float c_offset_y = piece.c.y - piece.a.y;
	float d_offset_y = piece.d.y - piece.a.y;

	float pbx = piece.a.x + (b_offset_x * cosf(angle) - b_offset_y * sinf(angle));
	float pby = piece.a.y + (b_offset_x * sinf(angle) + b_offset_y * cosf(angle));

	float pcx = piece.a.x + (c_offset_x * cosf(angle) - c_offset_y * sinf(angle));
	float pcy = piece.a.y + (c_offset_x * sinf(angle) + c_offset_y * cosf(angle));

	float pdx = piece.a.x + (d_offset_x * cosf(angle) - d_offset_y * sinf(angle));
	float pdy = piece.a.y + (d_offset_x * sinf(angle) + d_offset_y * cosf(angle));

	//Prevents rotating into objects and walls
	if (colliders[(byte)pby][(byte)pbx] != 2 && 
		colliders[(byte)pcy][(byte)pcx] != 2 &&
		colliders[(byte)pdy][(byte)pdx] != 2 &&
		piece.a.x != 1 && piece.a.y != 1)
	{
		piece.b.x = pbx;
		piece.b.y = pby;

		piece.c.x = pcx;
		piece.c.y = pcy;

		piece.d.x = pdx;
		piece.d.y = pdy;
	}
}



struct game_config {

	std::string gameWindowTitle = "tetris 45 paav";
	int frameRateLimit = 60; 

	int normalTimeDelta = 10; 
	int fastTimeDelta = 1;
	int singleLineReward = 1;
	int doubleLineReward = 4;
	int tripleLineReward = 9;
	int fourLineReward = 16;


	int tileScaleX = 2.83;
	int tileScaleY = 2.83;
	int numTilesX = 12;
	int numTilesY = 20;

	int backgroundColorR = 255, backgroundColorG = 220, backgroundColorB = 220;
	std::string gameOverMsg = "GAME OVER";


	std::string keyUP = "I";
	std::string keyDOWN = "K";
	std::string keyLEFT = "J";
	std::string keyRIGHT = "L";
	std::string keyQuit = "SPACEBAR";

	std::string tileSpriteImgPath = "images/tetris_tile.png";

	std::string musicPath = "sounds/tetris_theme.wav";
	std::string fallSoundPath = "sounds/fall.wav";
	std::string lineSoundPath = "sounds/line.wav";
	std::string tetrisSoundPath = "sounds/tetris.wav";

	std::string fontPath = "Forwa_font.TTF";
	int fontSize = 15;
	int fontScaleX = 1.5, fontScaleY = 1.5;
	int fontColorR = 0, fontColorG = 0, fontColorB = 255;

	//TODO: Populate this
	std::map<std::string, sf::Keyboard::Key> KeyNameMap = {
		{"UP", sf::Keyboard::Key::Up},
		{"DOWN", sf::Keyboard::Key::Down},
		{"LEFT", sf::Keyboard::Key::Left},
		{"RIGHT", sf::Keyboard::Key::Right},
		{"W", sf::Keyboard::Key::W},
		{"A", sf::Keyboard::Key::A},
		{"S", sf::Keyboard::Key::S},
		{"D", sf::Keyboard::Key::D},
		{"ESC", sf::Keyboard::Key::Escape},
		{"I", sf::Keyboard::Key::I},
		{"J", sf::Keyboard::Key::J},
		{"K", sf::Keyboard::Key::K},
		{"L", sf::Keyboard::Key::L},
		{"SPACEBAR", sf::Keyboard::Key::Space}
	};

} gconf;

int gameloop(game_config gconf)
{
	
	//16x16 tiles
	sf::Texture tile_tex;
	tile_tex.loadFromFile(gconf.tileSpriteImgPath);

	sf::Sprite tile(tile_tex);
	tile.setScale(gconf.tileScaleX, gconf.tileScaleY);
	
	float tile_size = tile_tex.getSize().x * tile.getScale().x;
	size_t width = tile_size * gconf.numTilesX, height = tile_size * gconf.numTilesY;

	//Music
	sf::Music track;
	track.openFromFile(gconf.musicPath);
	track.play();
	track.setLoop(true);

	//Sound effects
	sf::SoundBuffer buffer;
	buffer.loadFromFile(gconf.fallSoundPath);
	sf::Sound fall;
	fall.setBuffer(buffer);

	sf::SoundBuffer bufferTwo;
	bufferTwo.loadFromFile(gconf.lineSoundPath);
	sf::Sound line;
	line.setBuffer(bufferTwo);

	sf::SoundBuffer bufferThree;
	bufferThree.loadFromFile(gconf.tetrisSoundPath);
	sf::Sound tetris;
	tetris.setBuffer(bufferThree);

	//Setup score counter
	sf::Text score;
	sf::Font font;
	font.loadFromFile(gconf.fontPath);
	score.setFont(font);
	score.setCharacterSize(gconf.fontSize);
	score.setFillColor(sf::Color(gconf.fontColorR, gconf.fontColorG, gconf.fontColorB));
	score.setPosition(10,25);
	sf::Vector2<float> score_scale(gconf.fontScaleX, gconf.fontScaleY);
	score.setScale(score_scale);
	score.setString("Score: 0");

	//Setup window & create first piece
	sf::RenderWindow window(sf::VideoMode(width, height), gconf.gameWindowTitle, sf::Style::Titlebar | sf::Style::Close);
	window.setKeyRepeatEnabled(true);
	window.setFramerateLimit(gconf.frameRateLimit);
	
	Piece piece = CreatePiece(static_cast<PIECE_TYPE>((rand() % 7)));

	unsigned int timer = 0, gamespeed = gconf.normalTimeDelta, scoreCounter = 0;

	while (window.isOpen())
	{
		srand(time(NULL));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(gconf.KeyNameMap[gconf.keyQuit]))
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				//Movement
				if (event.key.code == gconf.KeyNameMap[gconf.keyUP])
				{
					rotate(piece);
				}
				else if (event.key.code == gconf.KeyNameMap[gconf.keyLEFT] &&
					piece.a.x != 0 && piece.b.x != 0 && piece.c.x != 0 && piece.d.x != 0 &&
					(colliders[piece.a.y][piece.a.x - 1]) != 2 && (colliders[piece.b.y][piece.b.x - 1]) != 2 &&
					(colliders[piece.c.y][piece.c.x - 1]) != 2 && (colliders[piece.d.y][piece.d.x - 1]) != 2)
				{
					piece.a.x--;
					piece.b.x--;
					piece.c.x--;
					piece.d.x--;
				}
				else if (event.key.code == gconf.KeyNameMap[gconf.keyRIGHT] &&
					piece.a.x != 11 && piece.b.x != 11 && piece.c.x != 11 && piece.d.x != 11 &&
					(colliders[piece.a.y][piece.a.x + 1]) != 2 && (colliders[piece.b.y][piece.b.x + 1]) != 2 &&
					(colliders[piece.c.y][piece.c.x + 1]) != 2 && (colliders[piece.d.y][piece.d.x + 1]) != 2)
				{
					piece.a.x++;
					piece.b.x++;
					piece.c.x++;
					piece.d.x++;
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				gamespeed = gconf.normalTimeDelta;
			}
		}

		if (sf::Keyboard::isKeyPressed(gconf.KeyNameMap[gconf.keyDOWN]))
		{
			gamespeed = gconf.fastTimeDelta;
		}

		window.clear(sf::Color(gconf.backgroundColorR, gconf.backgroundColorG, gconf.backgroundColorB, 1));


		//Draw the current falling piece
		sf::Sprite piece_tile = tile;

		piece_tile.setPosition(tile_size * piece.a.x, tile_size * piece.a.y);
		window.draw(piece_tile);

		piece_tile.setPosition(tile_size * piece.b.x, tile_size * piece.b.y);
		window.draw(piece_tile);

		piece_tile.setPosition(tile_size * piece.c.x, tile_size * piece.c.y);
		window.draw(piece_tile);

		piece_tile.setPosition(tile_size * piece.d.x, tile_size * piece.d.y);
		window.draw(piece_tile);

		//Refresh the grid-array
		for (size_t i = 0; i < gconf.numTilesY; i++)
		{
			for (size_t j = 0; j < gconf.numTilesX; j++)
			{
				if (colliders[i][j] == 2)
				{
					grid[i][j] = 2;
				}
				else
				{
					grid[i][j] = 0;
				}
			}
		}
		
		//Clock
		if (timer > gamespeed)
		{
			//Collission checks
			if (grid[piece.a.y + 1][piece.a.x] == 2 ||
				grid[piece.b.y + 1][piece.b.x] == 2 ||
				grid[piece.c.y + 1][piece.c.x] == 2 ||
				grid[piece.d.y + 1][piece.d.x] == 2 ||
				piece.a.y+1 == gconf.numTilesY || piece.b.y+1 == gconf.numTilesY || piece.c.y+1 == gconf.numTilesY || piece.d.y+1 == gconf.numTilesY
				)
			{
				fall.play();

				grid[piece.a.y][piece.a.x] = 2;
				grid[piece.b.y][piece.b.x] = 2;
				grid[piece.c.y][piece.c.x] = 2;
				grid[piece.d.y][piece.d.x] = 2;

				colliders[piece.a.y][piece.a.x] = 2;
				colliders[piece.b.y][piece.b.x] = 2;
				colliders[piece.c.y][piece.c.x] = 2;
				colliders[piece.d.y][piece.d.x] = 2;

				piece = CreatePiece(static_cast<PIECE_TYPE>((rand() % 7)));
			}
			else
			{
				grid[piece.a.y + 1][piece.a.x] = 1;
				grid[piece.b.y + 1][piece.b.x] = 1;
				grid[piece.c.y + 1][piece.c.x] = 1;
				grid[piece.d.y + 1][piece.d.x] = 1;

				piece.a.y++;
				piece.b.y++;
				piece.c.y++;
				piece.d.y++;
			}

			//Check if the player has a line or 'tetris'
			byte tetris_row = 0;
			for (size_t i = 0; i < gconf.numTilesY; i++)
			{
				byte blocks_in_a_row = 0;
				for (size_t j = 0; j < gconf.numTilesX; j++)
				{
					if (colliders[i][j] == 2)
					{
						blocks_in_a_row++;
					}
				}
				if (blocks_in_a_row == gconf.numTilesX)
				{
					tetris_row++;
					if (tetris_row >= 4)
					{
						tetris.play();
					}
					else
					{
						line.play();
					}
					for (size_t k = i; k > 0; k--)
					{
						for (size_t l = 0; l < gconf.numTilesX; l++)
						{
							colliders[k][l] = colliders[k - 1][l];
						}
					}

					switch(tetris_row) {
					
						case 1: scoreCounter += gconf.singleLineReward; break;
						case 2: scoreCounter += gconf.doubleLineReward; break;
						case 3: scoreCounter += gconf.tripleLineReward; break;
						case 4: scoreCounter += gconf.fourLineReward; break;
						
					}

					char temp[256];
					sprintf(temp, "Score: %i", scoreCounter);
					score.setString(temp);
				}
			}

			//If game over, then close application
			for (size_t i = 0; i < gconf.numTilesX; i++)
			{
				if (colliders[0][i] == 2)
				{
					window.close();
				}
			}

			timer = 0;

		}
		else
		{
			timer++;
		}

		//Draws all the tiles
		for (size_t i = 0; i < gconf.numTilesY; i++)
		{
			for (size_t j = 0; j < gconf.numTilesX; j++)
			{
				if (grid[i][j] == 1)
				{
					sf::Sprite t = tile;
					t.setPosition(tile_size * j, tile_size * i);
					window.draw(t);
				}
				if (colliders[i][j] == 2)
				{
					sf::Sprite t = tile;
					t.setPosition(tile_size * j, tile_size * i);
					window.draw(t);
				}
			}
		}

		//Draw the score and finally update the window
		window.draw(score);
		window.display();
	}

	return 0;
}

int main()
{
	gameloop(gconf);
}