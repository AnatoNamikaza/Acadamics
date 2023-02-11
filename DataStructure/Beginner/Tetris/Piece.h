#include<iostream>

class Piece {

private:

	int CenterX, CenterY;
	int *Dimensions;
	int Color;

public:

	Piece(int const cX = 0, int const cY = 0, int const color = 0, const int *arr = nullptr) {
		Dimensions = new int[6];
		if (color != 0)
			Color = color;
		if (cX != 0)
			CenterX = cX;
		if (cY != 0)
			CenterY = cY;
		if (arr)
			for (int i = 0; i < 6; i++)
				Dimensions[i] = arr[i];
	}

	void SetDimensions(int *dir) { for (int i = 0; i < 6; i++) { Dimensions[i] = dir[i]; } };

	void SetCenterX(int const cPX) { CenterX = cPX; }

	void SetCenterY(int const cPY) { CenterY = cPY; }

	void SetColor(int const color) { Color = color; }

	int* GetDimensions() const { return this->Dimensions; }

	int GetColor() const { return Color; }

	int GetCenterX() const { return CenterX; }

	int GetCenterY() const { return CenterY; }

	void SetData(int const cPX, int const cPY, int const color, const int *arr) {
		CenterX = 0, CenterY = 0, Color = 0, Dimensions = new int[6]{ 0 };
		if (cPX != 0) { CenterX = cPX; }
		if (cPY != 0) { CenterY = cPY; }
		if (color != 0) { Color = color; }
		if (arr) { for (int i = 0; i < 6; i++) { Dimensions[i] = arr[i]; } }
	}

	~Piece() { delete[] Dimensions, Dimensions = nullptr; }
};