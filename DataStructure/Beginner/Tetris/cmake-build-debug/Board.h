#include "Piece.h"
#include<time.h>

int Random(int min, int max) {
	int num = 0;
	for (int i = 0; i < 1; i++)
		num = (rand() % (max - min + 1)) + min;
	return num;
}

int AllPieces[7][4][6] = {
		{{0, 4, 1, 2, 0, 0}, {0, 4, 1, 2, 0, 0}, {0, 4, 1, 2, 0, 0}, {0, 4, 1, 2, 0, 0}},
		{{1, 0, 3, 3, 0, 0}, {2, 0, 4, 4, 0, 0}, {1, 0, 3, 3, 0, 0}, {2, 0, 4, 4, 0, 0}},
		{{0, 3, 2, 0, 1, 0}, {0, 4, 0, 2, 1, 0}, {0, 3, 0, 1, 4, 0}, {0, 2, 0, 4, 3, 0}},
		{{0, 3, 0, 1, 2, 0}, {0, 2, 0, 4, 1, 0}, {0, 1, 0, 3, 4, 0}, {0, 4, 0, 2, 3, 0}},
		{{0, 3, 0, 2, 1, 0}, {0, 2, 0, 1, 4, 0}, {0, 1, 0, 4, 3, 0}, {0, 4, 0, 3, 2, 0}},
		{{0, 1, 0, 2, 0, 3}, {0, 1, 0, 2, 0, 4}, {0, 1, 0, 3, 0, 4}, {0, 2, 0, 3, 0, 4}},
		{{0, 1, 0, 2, 3, 0}, {0, 4, 0, 1, 2, 0}, {0, 3, 0, 4, 1, 0}, {0, 2, 0, 3, 4, 0}}
};

int piece = 0, Formation = 0, NewForm[6] = { 0, 0, 0, 0, 0, 0 }, LastForm[6] = { 0, 0, 0, 0, 0, 0 };

struct Board : public Piece {

	int **board;

	Piece ActivePiece;

	Board() {
		board = new int *[23];
		for (int i = 0; i < 23; i++) { board[i] = new int[16]; }
		for (int i = 0; i < 23; i++) { for (int j = 0; j < 16; j++) { board[i][j] = 0; } }
	}

	bool DetecteCompleteLine() {
		bool found = true;
		for (int i = 22; i >= 0; i--) {
			found = true;
			for (int j = 0; j < 16; j++)
				if (board[i][j] == 0) {
					found = false;
					break;
				}
			if (found)
				ResetBoard(i);
		}
		return found;
	}

	void ResetBoard(int row) {
		for (int i = row; i > 0; i--)
			for (int j = 1; j < 16; j++) { board[i][j] = board[i - 1][j]; }
		for (int j = 0; j < 16; j++) { board[0][j] = 0; }
	}

	bool CheckPosition() {
		int *Checker = ActivePiece.GetDimensions();
		int rowNo = ActivePiece.GetCenterX(), ColNo = ActivePiece.GetCenterY();
		for (int i = 0; i < 6; i++) {
			if (ColNo < 16 && rowNo < 23 && board[rowNo][ColNo] != 0) { return false; }
			if (rowNo >= 23) { return false; }
			if (ColNo < 0 || ColNo >= 16) { return false; }
			if (Checker[i] == 0) { rowNo = ActivePiece.GetCenterX(), ColNo = ActivePiece.GetCenterY(); }
			else if (Checker[i] == 1) { ColNo++; }
			else if (Checker[i] == 2) { rowNo--; }
			else if (Checker[i] == 3) { ColNo--; }
			else if (Checker[i] == 4) { rowNo++; }
		}
		if (ColNo < 16 && rowNo < 23 && board[rowNo][ColNo] != 0) { return false; }
		if (rowNo >= 23) { return false; }
		return true;
	}

	void MakePiece() {
		int *Checker = ActivePiece.GetDimensions();
		int rowNo = ActivePiece.GetCenterX(), ColNo = ActivePiece.GetCenterY();
		for (int i = 0; i < 6; i++) {
			if (Checker[i] == 0) {
				rowNo = ActivePiece.GetCenterX(), ColNo = ActivePiece.GetCenterY();
			}
			else if (Checker[i] == 1 && ColNo < 16 && board[rowNo][ColNo + 1] == 0) {
				ColNo++;
			}
			else if (Checker[i] == 2 && rowNo >= 0 && board[rowNo - 1][ColNo] == 0) {
				rowNo--;
			}
			else if (Checker[i] == 3 && ColNo >= 0 && board[rowNo][ColNo - 1] == 0) {
				ColNo--;
			}
			else if (Checker[i] == 4 && rowNo < 23 && board[rowNo + 1][ColNo] == 0) {
				rowNo++;
			}
			board[rowNo][ColNo] = ActivePiece.GetColor();
		}
	}

	void ClearPiece() {
		int *Checker = ActivePiece.GetDimensions();
		int rowNo = ActivePiece.GetCenterX(), ColNo = ActivePiece.GetCenterY();
		for (int i = 0; i < 6; i++) {
			if (Checker[i] == 0) {
				rowNo = ActivePiece.GetCenterX(); ColNo = ActivePiece.GetCenterY();
			}
			else if (Checker[i] == 1 && ColNo < 16) {
				ColNo++;
			}
			else if (Checker[i] == 2 && rowNo >= 0) {
				rowNo--;
			}
			else if (Checker[i] == 3 && ColNo >= 0) {
				ColNo--;
			}
			else if (Checker[i] == 4 && rowNo < 23) {
				rowNo++;
			}
			board[rowNo][ColNo] = 0;
		}
	}

	bool GeneratePiece() {
		srand(time(0));
		bool val = false;
		if (board[4][8] == 0) {
			piece = Random(0, 6), Formation = Random(0, 3);
			for (int k = 0; k < 6; k++)
				LastForm[k] = AllPieces[piece][Formation][k];
			ActivePiece.SetData(4, 8, Random(1, 7), LastForm);
			val = CheckPosition();
			if (val) { MakePiece(); }
		}
		return val;
	}

	void Rotate() {
		ClearPiece();
		Formation = (Formation+1) % 4;
		for (int k = 0; k < 6; k++) { NewForm[k] = AllPieces[piece][Formation][k]; }
		ActivePiece.SetDimensions(NewForm);
		if (!CheckPosition()) { ActivePiece.SetDimensions(LastForm); }
		MakePiece();
	}

	bool Gravity() {
		bool Activated = false;
		ClearPiece();
		if (ActivePiece.GetCenterX() < 23 && ActivePiece.GetCenterX() != 22) {
			ActivePiece.SetCenterX(ActivePiece.GetCenterX() + 1), Activated = true;
			if (!CheckPosition()) { ActivePiece.SetCenterX(ActivePiece.GetCenterX() - 1), Activated = false; }
		}
		MakePiece();
		return Activated;
	}

	void MoveRight() {
		ClearPiece();
		if (ActivePiece.GetCenterY() < 16 && board[ActivePiece.GetCenterX()][ActivePiece.GetCenterY()+1] == 0) {
			ActivePiece.SetCenterY(ActivePiece.GetCenterY() + 1);
			if (!CheckPosition()) { ActivePiece.SetCenterY(ActivePiece.GetCenterY() - 1); }
		}
		MakePiece();
	}

	void MoveLeft() {
		ClearPiece();
		if (ActivePiece.GetCenterY() > -1 && board[ActivePiece.GetCenterX()][ActivePiece.GetCenterY() - 1] == 0) {
			ActivePiece.SetCenterY(ActivePiece.GetCenterY() - 1);
			if (!CheckPosition()) { ActivePiece.SetCenterY(ActivePiece.GetCenterY() + 1); }
		}
		MakePiece();
	}

	void ClearBoard() { for (int i = 0; i < 23; i++) { for (int j = 0; j < 16; j++) { board[i][j] = 0; } } }

	void PrintBoard() {
		for (int i = 0; i < 23; i++) {
			for (int j = 0; j < 16; j++)
				std::cout << board[i][j] << ' ';
			std::cout << '\n';
		}
		std::cout << std::endl;
	}

	~Board() {
		for (int i = 0; i < 23; i++) { delete[] board[i], board[i] = nullptr; }
		delete[] board, board = nullptr;
	}
};