#include"mygraphics.h"
#include <iostream>
#include "Board.h"

int main() {

	int Score = 0;
	Board GameBoard;
	GameBoard.GeneratePiece();

	drawRectangle(305, 10, 625, 470, 108, 108, 147);
	//x = 320, y = 460
	//x = 16, y = 23

	for (int x = 305; x < 625; x += 20)
		for (int y = 10; y < 470; y += 20)
			drawEllipse(x, y, x + 20, y + 20, 0, 0, 0);

	while (true) {

		for (int i = 0; i < 16; i++)
			for (int j = 0; j < 23; j++)
				if (GameBoard.board[j][i] == 1) { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 255, 255, 255); }
				else if (GameBoard.board[j][i] == 2) { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 0, 255, 0); }
				else if (GameBoard.board[j][i] == 3) { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 255, 255, 102); }
				else if (GameBoard.board[j][i] == 4) { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 255, 153, 255); }
				else if (GameBoard.board[j][i] == 5) { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 179, 140, 25); }
				else if (GameBoard.board[j][i] == 6) { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 255, 128, 0); }
				else if (GameBoard.board[j][i] == 7) { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 0, 255, 191); }
				else { drawEllipse((i * 20) + 305, (j * 20) + 10, (i * 20) + 325, (j * 20) + 30, 0, 0, 0); }

		char c = getKey();
		if (c == 'w') { Score++; GameBoard.Rotate(); }
		else if (c == 's') { Score += (GameBoard.Gravity() + 1); }
		else if (c == 'd') { Score++; GameBoard.MoveRight(); }
		else if (c == 'a') { Score++; GameBoard.MoveLeft(); }
		else if (c == 'e') { return 0; }


		if (!GameBoard.Gravity()) {
			Score += (GameBoard.DetecteCompleteLine() * 20);
			if (!GameBoard.GeneratePiece()) { cls(); std::cout << "\n\n\n\n					 Your Scores: " << Score << "\n\n"; return 0; }
		}
		delay(256);
	}

	system("pause");
};