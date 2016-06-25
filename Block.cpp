#include "ClassDefinition.h"

const int Block::OUTER_FRAME_THICKNESS_ = 5;
const int Block::USUAL_WIDTH_ = 20;
const int Block::USUAL_HEIGHT_ = 20;
const int Block::MAX_WIDTH_ = 30;
const int Block::MAX_HEIGHT_ = 30;
const bool Block::DELETABLE_ = true;
const bool Block::UNDELETABLE_ = false;

Block::Block()
{
	block_		 = Rect( Block::USUAL_WIDTH_, Block::USUAL_HEIGHT_);
	block_color_ = BLANK;
	deletable_	 = Block::UNDELETABLE_;
}

Block::Block( Point block_coordinates, BlockColor block_color)
{
	block_		 = Rect(block_coordinates, Block::USUAL_WIDTH_, Block::USUAL_HEIGHT_);
	block_color_ = block_color;
	deletable_	 = Block::UNDELETABLE_;
}

void Block::DrawBlock( Color block_color)
{
	if (deletable_)
		block_.draw(block_color).drawFrame( 0, Block::OUTER_FRAME_THICKNESS_, block_color);
	else
		block_.draw(block_color);
}

// ブロックがマウスオーバーされているかを返す
bool Block::GetMouseOver()
{
	return block_.mouseOver;
}

void Block::DrawBlock()
{
	switch (block_color_)
	{
	case RED:
		if (deletable_)
			block_.draw(Palette::Red).drawFrame( 0, Block::OUTER_FRAME_THICKNESS_, Palette::Red);
		else
			block_.draw(Palette::Red);
		break;

	case GREEN:
		if (deletable_)
			block_.draw(Palette::Green).drawFrame( 0, Block::OUTER_FRAME_THICKNESS_, Palette::Green);
		else
			block_.draw(Palette::Green);
		break;

	case BLUE:
		if (deletable_)
			block_.draw(Palette::Blue).drawFrame( 0, Block::OUTER_FRAME_THICKNESS_, Palette::Blue);
		else
			block_.draw(Palette::Blue);
		break;

	case YELLOW:
		if (deletable_)
			block_.draw(Palette::Yellow).drawFrame( 0, Block::OUTER_FRAME_THICKNESS_, Palette::Yellow);
		else
			block_.draw(Palette::Yellow);
		break;

	case MAGENTA:
		if (deletable_)
			block_.draw(Palette::Magenta).drawFrame( 0, Block::OUTER_FRAME_THICKNESS_, Palette::Magenta);
		else
			block_.draw(Palette::Magenta);
		break;

	default:
		break;
	}
}