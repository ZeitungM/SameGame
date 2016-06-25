#include "ClassDefinition.h"

const int MainCursor::INNER_FRAME_THICKNESS_ = 1;
const int MainCursor::OUTER_FRAME_THICKNESS_ = 0;
const Color MainCursor::FRAME_COLOR_ = Color( 255, 255, 255);

MainCursor::MainCursor()
{
	// �J�[�\���̏����ʒu�̓t�B�[���h���( 0, 0) ����
	position_x_	= 0;
	position_y_	= 0;
	width_		= Block::MAX_WIDTH_;
	height_		= Block::MAX_HEIGHT_;
	cursor_		= Rect( width_, height_);
}

void MainCursor::DrawCursor()
{
	// �u���b�N���㉺���E�Ɋg�傷�镪(-5)�A����ɂ��炷
	cursor_.setPos(	Window::Width()/2	- Block::MAX_WIDTH_*Field::BLOCK_NUM_X_/2	+position_x_*width_-5,
					Window::Height()/2	- Block::MAX_HEIGHT_*Field::BLOCK_NUM_Y_/2	+position_y_*height_-5);
	cursor_.drawFrame( MainCursor::INNER_FRAME_THICKNESS_, MainCursor::OUTER_FRAME_THICKNESS_, MainCursor::FRAME_COLOR_);
}