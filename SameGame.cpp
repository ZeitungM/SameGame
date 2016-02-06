#include "ClassDefinition.h"

SameGame::SameGame()
{
	// 初期画面はタイトルシーンとする
	current_scene_ = TITLE_SCENE;
}

void SameGame::DrawCurrentScene()
{
	// 現在のシーンを描画する
	switch (current_scene_)
	{
	// タイトルシーンの描画
	case TITLE_SCENE:
		title_scene_.DrawScene();		
		break;
	
	// メイン画面の描画
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