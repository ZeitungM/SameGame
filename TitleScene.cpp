#include "ClassDefinition.h"

TitleScene::TitleScene()
{
	// �^�C�g���V�[���̃��j���[�R�}���h�Q�̏�����
	new(title_menu_commands_) Command( L"�n�߂�", TITLE_SCENE, COMMAND_START);
	new(title_menu_commands_ + 1) Command( L"�I��", TITLE_SCENE, COMMAND_QUIT);

	title_scene_menu_ = MenuWindow( title_menu_commands_, TITLE_MENU_COMMANDS_N, TITLE_SCENE);
}

void TitleScene::DrawScene()
{
	//�^�C�g�����S�̕`��
	title_font_(L"���߂���").drawCenter( Point( Window::Width()/2, 50));

	// �^�C�g�����j���[�̕`��
	title_scene_menu_.DrawMenu();
}