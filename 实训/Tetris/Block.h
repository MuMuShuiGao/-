#pragma once
#include <graphics.h>
#include <vector>

struct Point
{
	int row;
	int col;
};

class Block
{
public:

	Block();
	void drop();
	void moveLeftRight(int offset);
	void rotate(); //��ת
	void draw(int leftMargin, int topMargin);
	static IMAGE** getImage();
	//Point* getSmallBlocks();

	bool blockInMap(const std::vector<std::vector<int>>& map);
	void solidify(std::vector<std::vector<int>>& map);
	int getBlockType();

	Block& operator=(const Block& other);

private:

	int blockType; //���������
	Point smallBlocks[4];
	IMAGE* img;

	static IMAGE* imgs[7]; // int data[7]
	static int size;
};

