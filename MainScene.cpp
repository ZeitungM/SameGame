#include "ClassDefinition.h"

MainScene::MainScene()
{
	score_ = 0;
	game_over_ = false;
}

void MainScene::DrawScene()
{
	// �t�B�[���h�̕`��
	field_.DrawField();
	// �X�R�A�̕\��
	DisplayScore();

	if (game_over_){
		game_over_txt_(L"Game Over\nEsc�L�[�ŏI��").drawCenter(360, Palette::White);
	}
}

// �������u���b�N�̐��ɉ����ăX�R�A�����Z����
void MainScene::AddScore(int num_deleted_block)
{
	if (num_deleted_block>=2)
		score_ += (num_deleted_block-2)*(num_deleted_block-2);
}

void MainScene::DisplayScore()
{
	debug_txt_( L"Score:", score_).draw();
}

void MainScene::MoveCursorByMouse()
{
	for (int yi=0; yi<BLOCK_NUM_Y; yi++)
		for (int xi = 0; xi < BLOCK_NUM_X; xi++)
		{
			if (field_.blocks_[xi][yi].GetMouseOver())
			{
				field_.cursor_.position_x_ = xi;
				field_.cursor_.position_y_ = yi;
			}
		}
}

void MainScene::MoveCursorToRight()
{
	field_.cursor_.position_x_ = field_.cursor_.position_x_+1;
	if (field_.cursor_.position_x_>=BLOCK_NUM_X)
		field_.cursor_.position_x_ = 0;
}

void MainScene::MoveCursorToLeft()
{
	field_.cursor_.position_x_ = field_.cursor_.position_x_-1;
	if (field_.cursor_.position_x_<0)
		field_.cursor_.position_x_ = BLOCK_NUM_X-1;
}

void MainScene::MoveCursorToUp()
{
	field_.cursor_.position_y_ = field_.cursor_.position_y_-1;
	if (field_.cursor_.position_y_<0)
		field_.cursor_.position_y_ = BLOCK_NUM_Y-1;
}

void MainScene::MoveCursorToDown()
{
	field_.cursor_.position_y_ = field_.cursor_.position_y_+1;
	if (field_.cursor_.position_y_>=BLOCK_NUM_Y)
		field_.cursor_.position_y_ = 0;
}

// �Q�[���I�[�o�[�̔���
void MainScene::JudgeGameOver()
{
	for (int yi = 0; yi<BLOCK_NUM_Y; yi++)
		for (int xi = 0; xi<BLOCK_NUM_X; xi++)
			// ���F���אڂ��Ă���ӏ���1�ł�����΃Q�[���I�[�o�[�ł͂Ȃ�
			if (field_.blocks_[xi][yi].block_color_!=BLANK&&
				((xi >= 1 && field_.blocks_[xi][yi].block_color_ == field_.blocks_[xi - 1][yi].block_color_)||
				 (xi < BLOCK_NUM_X-1&&field_.blocks_[xi][yi].block_color_ == field_.blocks_[xi + 1][yi].block_color_)||
				 (yi >= 1 && field_.blocks_[xi][yi].block_color_ == field_.blocks_[xi][yi-1].block_color_)||
				 (xi < BLOCK_NUM_Y-1&&field_.blocks_[xi][yi].block_color_ == field_.blocks_[xi][yi+1].block_color_)) )
				return ;

	game_over_ = true;
}