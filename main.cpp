#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#define N 30
#define M 50
#define H 6

using namespace std;

//GLOBALS
int _time, _lvl = 24, _gameover, _jump, _crouch, _dir, _obs_time = -23, _score;
char _marker[N + 10][M + 10];

void Display1();
void Display2();
void DrawBorder();
void DrawGround();
void Delay();
void Print();
void DrawMe();
void UndrawMe();
void GenerateObstacle();
void GenerateObstacle2();
void Clrscr();
void Run();
void Shift();

int main() {
	Run();
	return 0;
}

void Display1() {
	cout << "Press any key to start the game...\n";
	while (1) {
		if (kbhit()) {
			char c = getch();
			Clrscr();
			return;
		}
	}
}

void Display2() {
	cout << "Controls:\n\n\n    Press x for jump\n    Press c for crouch\n\n\n";
	cout << "Press any key to continue...\n";
	while (1) {
		if (kbhit()) {
			char c = getch();
			Clrscr();
			return;
		}
	}
}

void DrawBorder() {
	for (int i = 0; i <= M + 1; i++)
		_marker[0][i] = _marker[N + 1][i] = '*';
	for (int i = 0; i <= N + 1; i++)
		_marker[i][0] = _marker[i][M + 1] = '*';
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			_marker[i][j] = ' ';
}

void DrawGround() {
	for (int i = 25; i <= N; i++)
		for (int j = 1; j <= M; j++)
			_marker[i][j] = (j % 4 == _time ? '>' : '*');
}

void Delay(double cnt) {
	for (double i = 0; i < cnt; i++) ;
}

void Print() {
	Shift();
	DrawGround();
	if (_score - _obs_time > 20) {
		int ok = rand() % 3;
		if (ok == 2) {
			int tip = rand() % 2;
			if (tip == 0)
				GenerateObstacle();
			else GenerateObstacle2();
			_obs_time = _score;	
		}
	}
	DrawMe();
	string S = "";
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= M + 1; j++)
			S += _marker[i][j];
		S += '\n';	
	}
	cout << "Your Score : " << _score << '\n';
	cout << S;
	UndrawMe();
	Delay(10000000);
	Clrscr();
}

void DrawMe() {
	if (_jump) {
		if (_lvl == 15 && _dir == -1)
			_dir = 1;
		_lvl += _dir;
	}
	if (_crouch) {
		if (_lvl == 28 && _dir == 1)
			_dir = -1;
		_lvl += _dir;
	}
	if (_lvl == 24)
		_jump = _crouch = 0;
	for (int i = _lvl; i > _lvl - H; i--) {
		if (_marker[i][4] == '<' || _marker[i][5] == '<') {
			_gameover = 1;
			return;
		}
		if (_marker[i][4] == ' ')
			_marker[i][4] = _marker[i][5] = 'o';
	}
	if (_lvl == 23 && _dir == -1)
		_marker[24][4] = _marker[24][5] = 'o';
	if (_lvl == 22 && _dir == -1)
		_marker[24][4] = _marker[24][5] = _marker[23][4] = _marker[23][5] = 'o';
	if (_lvl == 15)
		_marker[15][4] = _marker[15][5] = ' ';
	if (_lvl == 28)
		_marker[24][3] = _marker[24][6] = _marker[23][3] = _marker[23][6] = 'o';
}

void UndrawMe() {
	for (int i = _lvl; i > _lvl - H; i--)
		_marker[i][4] = _marker[i][5] = ' ';
	if (_lvl == 23)
		_marker[24][4] = _marker[24][5] = ' ';
	if (_lvl == 22)
		_marker[24][4] = _marker[24][5] = _marker[23][4] = _marker[23][5] = ' ';
	if (_lvl == 28)
		_marker[24][3] = _marker[24][6] = _marker[23][3] = _marker[23][6] = ' ';
}

void GenerateObstacle() {
	int h = rand() % 6 + 2;
	for (int i = 24; i > 24 - h; i--)
		_marker[i][M] = '<';
}

void GenerateObstacle2() {
	int h = rand() % 3;
	for (int i = 21 - h; i > 0; i--)
		_marker[i][M] = '<';
	return;
}

void Clrscr() {
	system("CLS");
}

void Shift() {
	for (int i = 1; i < 25; i++)
		for (int j = 1; j < M; j++)
			_marker[i][j] = _marker[i][j + 1];
	for (int i = 1; i < 25; i++)
		_marker[i][M] = ' ';
}

void Run() {
	srand(time(NULL));
	Display1();
	Display2();
	DrawBorder();
	while (!_gameover) {
		_score++;
		_time--;
		_time = (_time + 4) % 4;
		while (kbhit()) {
			char c = getch();
			if (c == 'x' && !_jump && !_crouch) {
				_jump = 1;
				_dir = -1;
			}
			if (c == 'c' && !_jump && !_crouch) {
				_crouch = 1;
				_dir = 1;
			}
		}
		Print();
	}
	cout << "GAME OVER!";
}
