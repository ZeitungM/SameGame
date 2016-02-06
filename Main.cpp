#include <Siv3D.hpp>
#include "ClassDefinition.h"

void Main()
{
	Window::SetTitle(L"���߂���");
	SameGame samegame = SameGame();
	const Point zero = Point( 0, 0);
	Point delta;

	while (System::Update())
	{
		delta = Mouse::Delta();

		// ���݂̃V�[���ɍ��킹������
		switch (samegame.GetCurrentScene())
		{
		case TITLE_SCENE:
			// Enter�L�[��������邩�A���N���b�N���ꂽ��
			if (Input::KeyEnter.clicked || Input::MouseL.released)
			{	
				// �I������Ă���R�}���h�ɍ��킹���������s��
				Command selected_command = samegame.title_scene_.title_scene_menu_.GetSelectedCommand();
				switch (selected_command.GetCommandType())
				{
				case COMMAND_START:
					samegame.SetCurrentScene(MAIN_SCENE);
					break;

				case COMMAND_QUIT:
					System::Exit();
					break;

				default:
					break;
				}

			}
			samegame.title_scene_.DrawScene();
			break;
			
		case MAIN_SCENE:

			// ���C���V�[���`�惋�[�v���̏���������
			// �e�u���b�N�̏����\�����������
			samegame.main_scene_.field_.InitializeDeletablity();

			if (delta!=zero)	// �}�E�X�J�[�\�����������ꂽ�Ƃ�
				samegame.main_scene_.MoveCursorByMouse();
			else
			{	
				//	�����L�[�������ꂽ���̏���
				if (Input::KeyUp.clicked)
					samegame.main_scene_.MoveCursorToUp();
				if (Input::KeyDown.clicked)
					samegame.main_scene_.MoveCursorToDown();				
				if (Input::KeyRight.clicked)
					samegame.main_scene_.MoveCursorToRight();
				if (Input::KeyLeft.clicked)
					samegame.main_scene_.MoveCursorToLeft();
			}

			// ���݃|�C���g���Ă���n�_���������u���b�N��T��
			{
				int tmp_cursor_x = samegame.main_scene_.field_.cursor_.position_x_;
				int tmp_cursor_y = samegame.main_scene_.field_.cursor_.position_y_;
				samegame.main_scene_.field_.SearchDeletableBlock( tmp_cursor_x, tmp_cursor_y, samegame.main_scene_.field_.blocks_[tmp_cursor_x][tmp_cursor_y].block_color_ );
			}

			// Enter�L�[�������ꂽor�}�E�X�̍��{�^�����N���b�N���ꂽ��A�|�C���g���Ă���u���b�N������
			if (Input::KeyEnter.clicked||Input::MouseL.clicked)
			{
				int deleted_block_num = samegame.main_scene_.field_.DeleteBlock();
				samegame.main_scene_.AddScore(deleted_block_num);
				samegame.main_scene_.field_.CloseUpVerticalSpace();
				samegame.main_scene_.field_.FillBlankColumn();
			}
			samegame.main_scene_.JudgeGameOver();

			// ���C���V�[����`��
			samegame.main_scene_.DrawScene();

			break;

		default:
			break;
		}
	}
}
