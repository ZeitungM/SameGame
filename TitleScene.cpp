#include "ClassDefinition.h"

const int TitleScene::MENU_BACK_WIDTH_ = 400;
const int TitleScene::MENU_BACK_HEIGHT_ = 300;
// TODO:同種の変数が複数あり 要統合
const Color TitleScene::MENU_BACK_COLOR_ = Color(0, 0, 255, 102);;
const SceneType TitleScene::SCENE_TYPE_ = TITLE_SCENE;

TitleScene::TitleScene()
{
	menu_back_ = Rect( MENU_BACK_WIDTH_, MENU_BACK_HEIGHT_).setCenter(Window::Center());

	// タイトルシーンのメニューコマンド群の初期化
	title_menu_commands_.push_back(Command(L"始める", TITLE_SCENE, COMMAND_START));
	title_menu_commands_.push_back(Command(L"終了", TITLE_SCENE, COMMAND_QUIT));

	title_scene_menu_ = MenuWindow( title_menu_commands_, TITLE_SCENE);
}

void TitleScene::DrawScene()
{
	//タイトルロゴの描画
	title_font_(L"さめがめ").drawCenter( Point( Window::Width()/2, 50));

	// タイトルメニューの描画
	title_scene_menu_.DrawMenu();
}