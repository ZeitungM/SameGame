#include "ClassDefinition.h"

Block::Block()
{
	block_		 = Rect( BLOCK_USUAL_WIDTH, BLOCK_USUAL_HEIGHT);
	block_color_ = BLANK;
	deletable_	 = false;
}

Block::Block( Point block_coordinates, BlockColor block_color)
{
	block_		 = Rect(block_coordinates, BLOCK_USUAL_WIDTH, BLOCK_USUAL_HEIGHT);
	block_color_ = block_color;
	deletable_	 = false;
}

void Block::DrawBlock( Color block_color)
{
	if (deletable_)
		block_.draw(block_color).drawFrame( 0, outer_frame_thikness_, block_color);
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
			block_.draw(Palette::Red).drawFrame( 0, outer_frame_thikness_, Palette::Red);
		else
			block_.draw(Palette::Red);
		break;

	case GREEN:
		if (deletable_)
			block_.draw(Palette::Green).drawFrame( 0, outer_frame_thikness_, Palette::Green);
		else
			block_.draw(Palette::Green);
		break;

	case BLUE:
		if (deletable_)
			block_.draw(Palette::Blue).drawFrame( 0, outer_frame_thikness_, Palette::Blue);
		else
			block_.draw(Palette::Blue);
		break;

	case YELLOW:
		if (deletable_)
			block_.draw(Palette::Yellow).drawFrame( 0, outer_frame_thikness_, Palette::Yellow);
		else
			block_.draw(Palette::Yellow);
		break;

	case MAGENTA:
		if (deletable_)
			block_.draw(Palette::Magenta).drawFrame( 0, outer_frame_thikness_, Palette::Magenta);
		else
			block_.draw(Palette::Magenta);
		break;

	default:
		break;
	}
}