#include "ClassDefinition.h"

SameGame::SameGame()
{
	// ������ʂ̓^�C�g���V�[���Ƃ���
	current_scene_ = TITLE_SCENE;
}

void SameGame::DrawCurrentScene()
{
	// ���݂̃V�[����`�悷��
	switch (current_scene_)
	{
	// �^�C�g���V�[���̕`��
	case TITLE_SCENE:
		title_scene_.DrawScene();		
		break;
	
	// ���C����ʂ̕`��
	case MAIN_SCENE:
		main_scene_.DrawScene();
		break;

	default:
		break;
	}
}

SceneType SameGame::GetCurrentScene()
{
	return current_scene_;
}

void SameGame::SetCurrentScene(SceneType scene_type)
{
	current_scene_ = scene_type;
}