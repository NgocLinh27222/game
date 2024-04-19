#include "Snake.h"

#include "Fruit.h"
#include "TextureManager.h"


Snake::~Snake() {
	FreeTexture();
}

void Snake::Setup(const string& filePath) {
	//snake head
	snakeTexture = TextureManager::LoadTexture(filePath);
	head.SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	s_angle = 0;
	s_flip = SDL_FLIP_NONE;

	//tails
	tails.Setup("res/gfx/Snake/body.png", "res/gfx/Snake/last_tail.png",
                "res/gfx/Snake/curve.png", "res/gfx/Snake/curve_tail.png");
	tails.tail[0] = head;
	tails.t_angle[0] = s_angle;
	for (int i = 0; i < tails.total_tail; i++) {
		tails.tail[i + 1] = tails.tail[i] + Vector2D(- TAILS_SIZE, 0);
		tails.t_angle[i + 1] = tails.t_angle[i];
	}

	//score
	score = 0;
	game_score.Setup(GameText::RED_TEXT);
	game_highestScore.Setup(GameText::WHITE_TEXT);
	HighestScore = game_highestScore.getHighestScore();
	game_highestScore.Update(HighestScore, "Highest Score: ");

	//sound
	eating_sound.loadSound("res/audio/sound/eating.mp3");
	lose_sound.loadSound("res/audio/sound/lose.mp3");

	step.SetPos(0, 0);
	isMove = false;
	alive = true;
}

void Snake::Setup2(const string &head_color, const string &body_color, const string &tail_color,
                    const string &curve_color, const string &curveTail_color,
                    const Vector2D &startPos, const int &index, const GameText::TextColor &color) {
	//snake head
	snakeTexture = TextureManager::LoadTexture(head_color);
	head = startPos;
	if (index == 1)
		s_angle = 0;
	else if (index == -1)
		s_angle = 180;

	//tails
	tails.Setup(body_color, tail_color, curve_color, curveTail_color);
	tails.tail[0] = head;
	tails.t_angle[0] = s_angle;
	for (int i = 0; i < tails.total_tail; i++) {
		tails.tail[i + 1] = tails.tail[i] + Vector2D( - index * TAILS_SIZE, 0);
		tails.t_angle[i + 1] = tails.t_angle[i];
	}

	//score
	score = 0;
	game_score.Setup(color);

	//sound
	eating_sound.loadSound("res/audio/sound/eating.mp3");
	lose_sound.loadSound("res/audio/sound/lose.mp3");

	step.SetPos(0, 0);
	dir = RIGHT;
	isMove = false;
	alive = true;
}

void Snake::Update() {
	moveSet();
	if (isMove == true) {
		for (int i = tails.total_tail; i > 0; i--) {
			tails.tail[i] = tails.tail[i - 1];
			tails.t_angle[i] = tails.t_angle[i - 1];
		}
		tails.tail[0] = head;
		tails.t_angle[0] = s_angle;
	}

	CheckCollideFood();
	if (CheckSelfCollide() || CheckCollideBlock())
		alive = false;
//    if(isAliveInBoundaryBlock){
//
//    }

	if (!isAlive())
		Game::isRunning = false;

	if (!Game::isRunning)
		lose_sound.playSound(70);
}

//bool

void Snake::Update2(const Snake &other) {
	if (isMove == true) {
		for (int i = tails.total_tail; i > 0; i--) {
			tails.tail[i] = tails.tail[i - 1];
			tails.t_angle[i] = tails.t_angle[i - 1];
		}
		tails.tail[0] = head;
		tails.t_angle[0] = s_angle;
	}

	CheckCollideFood2(other);
	if (CheckSelfCollide() || CheckCollideBlock())
		alive = false;

	if (!isAlive()) {
		Game::isRunning = false;
	}

	if (!Game::isRunning)
		lose_sound.playSound(70);
}

void Snake::moveSet() {
	Direction();
	Move();
	if (step.x != 0 || step.y != 0) isMove = true;
}

void Snake::moveSet2() {
	Direction2();
	Move();
	if (step.x != 0 || step.y != 0) isMove = true;
}

void Snake::Direction() {
	if (Game::event.type == SDL_KEYDOWN) {
		switch(Game::event.key.keysym.sym) {
			case SDLK_ESCAPE:
				SDL_Texture* pause_texture;
				pause_texture = TextureManager::LoadTexture("res/gfx/Background/pause.png");
				while (true) {
					SDL_RenderCopy(Game::renderer, pause_texture, NULL, NULL);
					SDL_RenderPresent(Game::renderer);
					while (SDL_PollEvent(&Game::event)) {
						switch(Game::event.type) {
							case SDL_QUIT:
								exit(0);
							case SDL_KEYDOWN:
								switch(Game::event.key.keysym.sym) {
									case SDLK_ESCAPE:
										SDL_DestroyTexture(pause_texture);
										return;
								}
						}
					}
				}
				break;
			case SDLK_LEFT:
				Left();
				break;
			case SDLK_RIGHT:
				Right();
				break;
			case SDLK_UP:
				Up();
				break;
			case SDLK_DOWN:
				Down();
				break;
		}
	}
}

void Snake::Direction2() {
	if (Game::event.type == SDL_KEYDOWN) {
		switch(Game::event.key.keysym.sym) {
			case SDLK_ESCAPE: break;
			case SDLK_a:
				Left();
				break;
			case SDLK_d:
				Right();
				break;
			case SDLK_w:
				Up();
				break;
			case SDLK_s:
				Down();
				break;
		}
	}
}

void Snake::Move() {
    head += step;
    if( head.x == -20 )
        head.x = MAP_WIDTH - 20;
    else if( head.x == MAP_WIDTH )
        head.x = 0;
    if( head.y == -20 )
        head.y = MAP_HEIGHT - 20;
    else if( head.y == MAP_HEIGHT )
        head.y = 0;
}

void Snake::Up() {
	if (step.y == 0) {
		step.SetPos(0, -velocity);
		s_angle = -90;
		s_flip = SDL_FLIP_NONE;
	}

}

void Snake::Down() {
	if (step.y == 0) {
		step.SetPos(0, velocity);
		s_angle = 90;
		s_flip = SDL_FLIP_NONE;
	}
}

void Snake::Right() {
	if (step.x == 0) {
		step.SetPos(velocity, 0);
		s_angle = 0;
		s_flip = SDL_FLIP_NONE;
	}
}

void Snake::Left() {
	if (step.x == 0) {
		step.SetPos(-velocity, 0);
		s_angle = 180;
		s_flip = SDL_FLIP_NONE;
	}
}

bool Snake::fruitInsideSnake() {
    for (int i=0; i<=tails.total_tail; i++){
        if (Fruit::fruit_pos == tails.tail[i]){
            std::cout << "qua trong player1\n";
            return true;
        }
    }
    return false;
}

bool Snake::fruitInsideSnake(const Snake &other) {
    for (int i=0; i<=other.tails.total_tail; i++){
        if (Fruit::fruit_pos == other.tails.tail[i]){
            std::cout << "qua trong player2\n";
            return true;
        }
    }
    return false;
}

bool Snake::fruitInsideBlock(){
    if( Map::map_[Fruit::fruit_pos.y/20][Fruit::fruit_pos.x/20] == 1 ) {
        std::cout << "qua trong block\n";
        return true;
    }
    return false;
}

 // check xem ddax anw ch
void Snake::CheckCollideFood() {
	if (head + Vector2D(size, size) > Fruit::fruit_pos
		&& Fruit::fruit_pos + Vector2D(size, size) > head) {
		eating_sound.playSound(60);
		tails.Update();
        score += Fruit::fruit_score;
        Fruit::randTypeFruit();
		do{
            Fruit::Respawn();
		}
		while ( fruitInsideSnake() || fruitInsideBlock() );
	}
}

void Snake::CheckCollideFood2(const Snake &other) {
	if (head + Vector2D(size, size) > Fruit::fruit_pos
		&& Fruit::fruit_pos + Vector2D(size, size) > head) {
		eating_sound.playSound(60);
		tails.Update();
        score += Fruit::fruit_score;
        Fruit::randTypeFruit();
		do{
            Fruit::Respawn();
		}
		while( fruitInsideSnake() || fruitInsideSnake(other) || fruitInsideBlock() );
	}
}

bool Snake::CheckCollideBlock(){
    if(Map::map_[head.y/20][head.x/20] == 1)
        std::cout << "toi dam vao tuong\n";
    return Map::map_[head.y/20][head.x/20] == 1;
}

bool Snake::CheckSelfCollide() {
	for (int i = 1; i <= tails.total_tail; i++) {
		if (head + Vector2D(size, size) > tails.tail[i]
			&& tails.tail[i] + Vector2D(TAILS_SIZE, TAILS_SIZE) > head) {
            std::cout << "toi dam vao chinh minh\n";
			return true;
		}
	}
	return false;
}

void Snake::Render() {
	TextureManager::DrawEx(snakeTexture, head, Vector2D(size, size), s_angle, s_flip);
	tails.Render();
}

int Snake::getScore() {
	return score;
}

void Snake::RenderScore(const Vector2D &pos, const Vector2D &size) {
	game_score.Render(pos, size);
}

void Snake::RenderHighestScore(const Vector2D &pos, const Vector2D &size) {
	game_highestScore.Render(pos, size);
}

void Snake::UpdateScore(string msg) {
	game_score.Update(score, msg);
}

void Snake::UpdateHighestScore() {
	if (score > HighestScore) {
		HighestScore = score;
		game_highestScore.Update(score, "Highest Score: ");
	}
	if (!Game::isRunning) game_highestScore.Record(HighestScore);
}

//Tails Snake::getTails() const {
//    return tails;
//}

void Snake::FreeTexture() {
	SDL_DestroyTexture(snakeTexture);
	tails.FreeTexture();
	game_score.Free();
	game_highestScore.Free();
}
