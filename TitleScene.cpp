#include "ClassDefinition.h"

const int TitleScene::MENU_BACK_WIDTH_ = 400;
const int TitleScene::MENU_BACK_HEIGHT_ = 300;
// TODO:����̕ϐ����������� �v����
const Color TitleScene::MENU_BACK_COLOR_ = Color(0, 0, 255, 102);;
const SceneType TitleScene::SCENE_TYPE_ = TITLE_SCENE;

TitleScene::TitleScene()
{
	menu_back_ = Rect( MENU_BACK_WIDTH_, MENU_BACK_HEIGHT_).setCenter(Window::Center());

	// �^�C�g���V�[���̃��j���[�R�}���h�Q�̏�����
	title_menu_commands_.push_back(Command(L"�n�߂�", TITLE_SCENE, COMMAND_START));
	title_menu_commands_.push_back(Command(L"�I��", TITLE_SCENE, COMMAND_QUIT));

	title_scene_menu_ = MenuWindow( title_menu_commands_, TITLE_SCENE);
}

void TitleScene::DrawScene()
{
	//�^�C�g�����S�̕`��
	title_font_(L"���߂���").drawCenter( Point( Window::Width()/2, 50));

	// �^�C�g�����j���[�̕`��
	title_scene_menu_.DrawMenu();
}