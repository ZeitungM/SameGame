#include "ClassDefinition.h"

Field::Field()
{
	// �t�B�[���h�̍���̍��W(�E�B���h�E��������u���b�N�̑傫���ő厞�̏c������������)���v�Z
	field_top_left_coordinates_ = Point( Window::Width()/2 - BLOCK_MAX_WIDTH*BLOCK_NUM_X/2, Window::Height()/2 - BLOCK_MAX_HEIGHT*BLOCK_NUM_Y/2);

	// �C���X�^���X�������Ƀt�B�[���h�Ƀ����_���ȐF�̃u���b�N��z�u����
	for (int yi = 0; yi < BLOCK_NUM_Y; yi++)
		for (int xi = 0; xi < BLOCK_NUM_X; xi++)
		{
			Point block_coordinates = Point( field_top_left_coordinates_.x + BLOCK_MAX_WIDTH*xi, field_top_left_coordinates_.y + BLOCK_MAX_HEIGHT*yi);
			blocks_[xi][yi] = Block( block_coordinates, (BlockColor)Random((int)RED, (int)MAGENTA));
		}
}

void Field::DrawField()
{
	for (int yi = 0; yi < BLOCK_NUM_Y; yi++)
		for (int xi = 0; xi < BLOCK_NUM_X; xi++)
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
		blocks_[x][y].deletable_ = true;
		// ���ɖ��T���̓��F�̃u���b�N������΍ċA�I�ɒT���𑱂���
		if (!blocks_[x-1][y].deletable_)
			SearchDeletableBlock( x-1, y, block_color);
	}

	// �E�����ւ̒T��
	if (x < BLOCK_NUM_X-1 && blocks_[x+1][y].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = true;
		if (!blocks_[x+1][y].deletable_)
			SearchDeletableBlock( x+1, y, block_color);
	}

	// ������ւ̒T��
	if (y > 0 && blocks_[x][y-1].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = true;
		if (!blocks_[x][y-1].deletable_)
			SearchDeletableBlock( x, y-1, block_color);
	}

	// �������ւ̒T��
	if (y < BLOCK_NUM_Y-1 && blocks_[x][y+1].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = true;
		if (!blocks_[x][y+1].deletable_)
			SearchDeletableBlock( x, y+1, block_color);
	}
}

void Field::InitializeDeletablity()
{
	for (int yi=0; yi<BLOCK_NUM_Y; yi++)
		for (int xi=0; xi<BLOCK_NUM_X; xi++)
			blocks_[xi][yi].deletable_ = false;
}

// �u���b�N���������āA���̐���Ԃ�
int Field::DeleteBlock()
{
	int num_deleted_block = 0;
	for (int yi = 0; yi < BLOCK_NUM_Y; yi++)
	{
		for (int xi = 0; xi < BLOCK_NUM_X; xi++)
		{
			if (blocks_[xi][yi].deletable_)
			{
				Point block_coordinates = Point( field_top_left_coordinates_.x + BLOCK_MAX_WIDTH*xi, field_top_left_coordinates_.y + BLOCK_MAX_HEIGHT*yi);
				blocks_[xi][yi] = Block( block_coordinates, BLANK);
				num_deleted_block++;
			}
		}
	}
	return num_deleted_block;
}

void Field::CloseUpVerticalSpace()
{
	bool dropped = true;

	while (dropped)
	{
		dropped = false;
		for (int yi = 0; yi < BLOCK_NUM_Y-1; yi++)
		{
			for (int xi = 0; xi < BLOCK_NUM_X; xi++)
			{
				if (blocks_[xi][yi+1].block_color_==BLANK && blocks_[xi][yi].block_color_!=BLANK)
				{
					std::swap( blocks_[xi][yi].block_color_, blocks_[xi][yi+1].block_color_);
					std::swap( blocks_[xi][yi].deletable_, blocks_[xi][yi+1].deletable_);
					dropped = true;
				}
			}
		}
	}
}

void Field::FillBlankColumn()
{
	bool filled = true;

	while (filled)
	{
		filled = false;
		for (int xi = 0; xi < BLOCK_NUM_X - 1; xi++)
		{
			// ��ԉ����󔒂Ȃ�΁A���̗�͑S�ċ�
			if ( blocks_[xi][BLOCK_NUM_Y-1].block_color_==BLANK && blocks_[xi+1][BLOCK_NUM_Y-1].block_color_!=BLANK)
			{
				for (int yi = 0; yi < BLOCK_NUM_Y; yi++){
					std::swap( blocks_[xi][yi].block_color_, blocks_[xi+1][yi].block_color_);
					std::swap( blocks_[xi][yi].deletable_, blocks_[xi+1][yi].deletable_);
				}
				filled = true;
			}
		}
	}
}