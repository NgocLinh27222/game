#include "Score.h"

Score::~Score() {
	Free();
}

void Score::CreateText() {
	score_text.Init(font);
}

void Score::Setup(const GameText::TextColor &color) {
	font = TTF_OpenFont("res/font/EvilEmpire-4BBVK.ttf", 35); // mo font chu voi kich thuoc 35pt
	score_text.SetColor(color);
}

void Score::Render(const Vector2D &pos, const Vector2D &size) {
	TextureManager::SetPos(dst, pos, size);
	score_text.CreateGameText(font, dst);
}

void Score::Render2(const Vector2D &pos, const Vector2D& size) {
	TextureManager::SetPos(dst, pos, size);
	score_text.Render(dst);
}

void Score::Update(const int &score, const string &str) {
	string strScore = str;
	val_str_score = to_string(score);
	strScore += val_str_score;
	score_text.SetText(strScore);
}

int Score::getHighestScore() {
	ifstream file("res/Highest Score.txt");
	int highest_score;
	file >> highest_score;
	file.close();
	return highest_score;
}

void Score::Record(const int &HighestScore) {
	ofstream outfile;
	outfile.open("res/Highest Score.txt", ios::out | ios::trunc);//
        // ios::out:tep duoc mo de ghi du lieu. Neu tep khong ton tai, tao tep moi.
        // ios::trunc: xoa bo noi dung cu
	outfile << HighestScore;
	outfile.close();
}

void Score::Free() {
	score_text.Free();
}
