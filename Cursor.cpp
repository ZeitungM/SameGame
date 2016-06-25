#include "ClassDefinition.h"

const int MainCursor::INNER_FRAME_THICKNESS_ = 1;
const int MainCursor::OUTER_FRAME_THICKNESS_ = 0;
const Color MainCursor::FRAME_COLOR_ = Color( 255, 255, 255);

MainCursor::MainCursor()
{
	// カーソルの初期位置はフィールド上の( 0, 0) 左上
	position_x_	= 0;
	position_y_	= 0;
	width_		= Block::MAX_WIDTH_;
	height_		= Block::MAX_HEIGHT_;
	cursor_		= Rect( width_, height_);
}

void MainCursor::DrawCursor()
{
	// ブロックが上下左右に拡大する分(-5)、左上にずらす
	cursor_.setPos(	Window::Width()/2	- Block::MAX_WIDTH_*Field::BLOCK_NUM_X_/2	+position_x_*width_-5,
					Window::Height()/2	- Block::MAX_HEIGHT_*Field::BLOCK_NUM_Y_/2	+position_y_*height_-5);
	cursor_.drawFrame( MainCursor::INNER_FRAME_THICKNESS_, MainCursor::OUTER_FRAME_THICKNESS_, MainCursor::FRAME_COLOR_);
}