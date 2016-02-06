#include "ClassDefinition.h"

TitleScene::TitleScene()
{
	// タイトルシーンのメニューコマンド群の初期化
	new(title_menu_commands_) Command( L"始める", TITLE_SCENE, COMMAND_START);
	new(title_menu_commands_ + 1) Command( L"終了", TITLE_SCENE, COMMAND_QUIT);

	title_scene_menu_ = MenuWindow( title_menu_commands_, TITLE_MENU_COMMANDS_N, TITLE_SCENE);
}

void TitleScene::DrawScene()
{
	//タイトルロゴの描画
	title_font_(L"さめがめ").drawCenter( Point( Window::Width()/2, 50));

	// タイトルメニューの描画
	title_scene_menu_.DrawMenu();
}