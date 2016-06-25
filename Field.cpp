#include "ClassDefinition.h"

const Color Field::BLOCK_RED_	   = Color( 255,   0,   0);
const Color Field::BLOCK_BLUE_    = Color(   0, 255,   0);
const Color Field::BLOCK_GREEN_   = Color(   0,   0, 255);
const Color Field::BLOCK_YELLOW_  = Color( 255, 255,   0);
const Color Field::BLOCK_MAGENTA_ = Color( 255,   0, 255);

Field::Field()
{
	// �t�B�[���h�̍���̍��W(�E�B���h�E��������u���b�N�̑傫���ő厞�̏c������������)���v�Z
	field_top_left_coordinates_ = Point(Window::Width()/2	- Block::MAX_WIDTH_*Field::BLOCK_NUM_X_/2,
										Window::Height()/2	- Block::MAX_HEIGHT_*Field::BLOCK_NUM_Y_/2);

	// �C���X�^���X�������Ƀt�B�[���h�Ƀ����_���ȐF�̃u���b�N��z�u����
	for (int yi = 0; yi < Field::BLOCK_NUM_Y_; yi++)
		for (int xi = 0; xi < Field::BLOCK_NUM_X_; xi++)
		{
			Point block_coordinates = Point(field_top_left_coordinates_.x + Block::MAX_WIDTH_*xi,
											field_top_left_coordinates_.y + Block::MAX_HEIGHT_*yi);
			blocks_[xi][yi] = Block( block_coordinates, (BlockColor)Random((int)RED, (int)MAGENTA));
		}
}

void Field::DrawField()
{
	for (int yi = 0; yi < Field::BLOCK_NUM_Y_; yi++)
		for (int xi = 0; xi < Field::BLOCK_NUM_X_; xi++)
			blocks_[xi][yi].DrawBlock();
	cursor_.DrawCursor();
}

// �����\�ȃu���b�N��T������
void Field::SearchDeletableBlock(int x, int y, BlockColor block_color)
{
	// ���݃|�C���g���Ă���ӏ��Ƀu���b�N���Ȃ���ΏI��
	if (blocks_[x][y].block_color_==BLANK)
		return;

	// �ċA�I�ɌĂяo���ėאڂ��Ă��铯�F�̃u���b�N��T��(���ɒT���ς�or�t�B�[���h�̊O���̂Ƃ��͂��Ȃ�)
	// �������ւ̒T��
	if (x > 0 && blocks_[x-1][y].block_color_==block_color)
	{
		// ���ɓ��F�̃u���b�N���אڂ��Ă���Ȃ�A���̃u���b�N�͏�����
		blocks_[x][y].deletable_ = Block::DELETABLE_;
		// ���ɖ��T���̓��F�̃u���b�N������΍ċA�I�ɒT���𑱂���
		if (!blocks_[x-1][y].deletable_)
			SearchDeletableBlock( x-1, y, block_color);
	}

	// �E�����ւ̒T��
	if (x < Field::BLOCK_NUM_X_-1 && blocks_[x+1][y].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = Block::DELETABLE_;
		if (!blocks_[x+1][y].deletable_)
			SearchDeletableBlock( x+1, y, block_color);
	}

	// ������ւ̒T��
	if (y > 0 && blocks_[x][y-1].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = Block::DELETABLE_;
		if (!blocks_[x][y-1].deletable_)
			SearchDeletableBlock( x, y-1, block_color);
	}

	// �������ւ̒T��
	if (y < Field::BLOCK_NUM_Y_-1 && blocks_[x][y+1].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = Block::DELETABLE_;
		if (!blocks_[x][y+1].deletable_)
			SearchDeletableBlock( x, y+1, block_color);
	}
}

// �S�u���b�N�̏����\�t���O�����Z�b�g����
void Field::InitializeDeletablity()
{
	for (int yi=0; yi<Field::BLOCK_NUM_Y_; yi++)
		for (int xi=0; xi<Field::BLOCK_NUM_X_; xi++)
			blocks_[xi][yi].deletable_ = Block::UNDELETABLE_;
}

// �u���b�N���������āA���̐���Ԃ�
int Field::DeleteBlock()
{
	int num_deleted_block = 0;
	for (int yi = 0; yi < Field::BLOCK_NUM_Y_; yi++)
		for (int xi = 0; xi < Field::BLOCK_NUM_X_; xi++)
			if (blocks_[xi][yi].deletable_)
			{
				Point block_coordinates = Point(field_top_left_coordinates_.x + Block::MAX_WIDTH_*xi,
												field_top_left_coordinates_.y + Block::MAX_HEIGHT_*yi);
				blocks_[xi][yi] = Block( block_coordinates, BLANK);
				num_deleted_block++;
			}

	return num_deleted_block;
}

void Field::CloseUpVerticalSpace()
{
	bool dropped = true;

	while (dropped)
	{
		dropped = false;
		for (int yi = 0; yi < Field::BLOCK_NUM_Y_ - 1; yi++)
			for (int xi = 0; xi < Field::BLOCK_NUM_X_; xi++)
				if (blocks_[xi][yi + 1].block_color_ == BLANK && blocks_[xi][yi].block_color_ != BLANK)
				{
					std::swap(blocks_[xi][yi].block_color_, blocks_[xi][yi + 1].block_color_);
					std::swap(blocks_[xi][yi].deletable_, blocks_[xi][yi + 1].deletable_);
					dropped = true;
				}
	}
}

void Field::FillBlankColumn()
{
	bool filled = true;

	while (filled)
	{
		filled = false;
		for (int xi = 0; xi < Field::BLOCK_NUM_X_ - 1; xi++)
			// ��ԉ����󔒂Ȃ�΁A���̗�͑S�ċ󔒂Ȃ̂ŁA���̉E�ɋ�łȂ��񂪂���΋l�߂�
			if ( blocks_[xi][Field::BLOCK_NUM_Y_-1].block_color_==BLANK && blocks_[xi+1][Field::BLOCK_NUM_Y_-1].block_color_!=BLANK)
			{
				for (int yi = 0; yi < Field::BLOCK_NUM_Y_; yi++)
				{
					std::swap( blocks_[xi][yi].block_color_,blocks_[xi+1][yi].block_color_);
					std::swap( blocks_[xi][yi].deletable_,	blocks_[xi+1][yi].deletable_);
				}
				filled = true;
			}
	}
}