#include "ClassDefinition.h"

MainCursor::MainCursor()
{
	// �J�[�\���̏����ʒu�̓t�B�[���h���( 0, 0) ����
	position_x_	= 0;
	position_y_	= 0;
	width_		= BLOCK_MAX_WIDTH;
	height_		= BLOCK_MAX_HEIGHT;
	cursor_		= Rect( width_, height_);
}

void MainCursor::DrawCursor()
{
	// �u���b�N���㉺���E�Ɋg�傷�镪���炷(-5)
	cursor_.setPos(	Window::Width()/2	- BLOCK_MAX_WIDTH*BLOCK_NUM_X/2		+position_x_*width_-5,
					Window::Height()/2	- BLOCK_MAX_HEIGHT*BLOCK_NUM_Y/2	+position_y_*height_-5);
	cursor_.drawFrame( inner_frame_thickness_, outer_frame_thickness_, frame_color_);
}