#include "Fruit.h"
#include "TextureManager.h"

Vector2D Fruit::fruit_src(0, 0);
Vector2D Fruit::fruit_pos(0, 0);

int Fruit::fruit_score = 10;
int Fruit::size = FRUIT_SIZE;

Fruit::~Fruit() {
    FreeTexture();
}

void Fruit::Setup(const char *filePath) {
	fruitTexture = TextureManager::LoadTexture(filePath);
}

void Fruit::setupContinueFruit(std::ifstream &file, const char *filePath) {
    file >> fruit_src.x >> fruit_src.y >> fruit_score;
    file >> fruit_pos.x >> fruit_pos.y;
	fruitTexture = TextureManager::LoadTexture(filePath);
}


void Fruit::Render() {
	SDL_RenderCopy(Game::renderer, fruitTexture, &srcR, &dstR);
}

void Fruit::Update() {
	TextureManager::SetPos(srcR, fruit_src, {size, size});
	TextureManager::SetPos(dstR, fruit_pos, {size, size});
}

void Fruit::recordContinueFruit(std::ofstream &outfile) {
    outfile << fruit_src.x << " " << fruit_src.y << std::endl;
    outfile << fruit_score << std::endl;
    outfile << fruit_pos.x << " " << fruit_pos.y << std::endl;
}

void Fruit::randTypeFruit(){
    fruit_src.x = rand()% 4;
    fruit_score = (fruit_src.x + 1) * 10;
    fruit_src.x *= 20;
}

void Fruit::Respawn() {
    fruit_pos.x = rand()% 40;  // tu 0->39
    fruit_pos.y = rand()% 27;
    fruit_pos.x *= 20;
    fruit_pos.y *= 20;
}

void Fruit::FreeTexture() {
	SDL_DestroyTexture(fruitTexture);
}
