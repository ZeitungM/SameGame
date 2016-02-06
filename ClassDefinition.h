#include <Siv3D.hpp>
#include <new>

#include "Constants.h"

// クラス名 Cursor だとシステム定義のものとかぶる？
class MainCursor{
private:
	int width_, height_;
	int inner_frame_thickness_ = 1;
	int outer_frame_thickness_ = 0;
	Color frame_color_ = Color( 255, 255, 255);
	Rect cursor_;

public:
	int position_x_, position_y_;

	MainCursor();
	void DrawCursor();
};

class Block{
private:
	int outer_frame_thikness_ = 5;

public:
	BlockColor block_color_;
	bool deletable_;
	Rect block_;

	Block();
	Block( Point block_coordinates, BlockColor b_color);
	void DrawBlock();
	void DrawBlock( Color color);
	bool GetMouseOver();
};

class Field{
private:
	Font debug_txt_ = Font(30);
	// フィールドの左上の座標
	Point field_top_left_coordinates_;
	Color block_red_ = Color(255, 0, 0), block_green_ = Color(0, 255, 0), block_blue_ = Color(0, 0, 255);
	Color block_yellow_ = Color(255, 255, 0), block_magenta_ = Color(255, 0, 255);
	Color test_color_ = Color( 255, 255, 255, 204);
	
public:
	Block blocks_[BLOCK_NUM_X][BLOCK_NUM_Y];
	int field_area_right_ = BLOCK_NUM_X - 1, field_area_bottom_ = BLOCK_NUM_Y - 1;	
	MainCursor cursor_;

	Field();
	void DrawField();
	void DisplayScore();
	void SearchDeletableBlock(int x, int y, BlockColor block_color);
	void InitializeDeletablity();
	int DeleteBlock();
	void CloseUpVerticalSpace();
	void FillBlankColumn();
};

class MainScene
{
private:
	int score_;
	Font debug_txt_ = Font(30);
	Font game_over_txt_ = Font(30);
	bool game_over_;

public:
	Field field_;
	MainScene();
	
	void DrawScene();
	void MoveCursorToUp();
	void MoveCursorToDown();
	void MoveCursorToRight();
	void MoveCursorToLeft();
	void MoveCursorByMouse();	
	void AddScore(int deleted_block);
	void DisplayScore();
	void JudgeGameOver();
};


class Command
{
private:
	String command_text_ = L"初期化テスト";
	SceneType usage_scene_;	// コマンドを使用するシーン
	CommandType command_type_;	// コマンドのタイプ
	Font command_text_font_ = Font(30);
	Color selected_color_ = Color( 255, 0, 0, 102);

public:
	int command_area_width_ = 200, command_area_height_ = 50;
	Rect command_area_ = Rect( command_area_width_, command_area_height_);

	Command();
	Command(String command_text, SceneType command_scene, CommandType command_type);
	void Draw(int x_coodinate, int y_coodinate, bool is_selected);
	CommandType GetCommandType();
	SceneType GetUsageScene();
};

class MenuWindow
{
private:
	SceneType usage_scene_;	// メニューウィンドウを使用するシーン

	// メニューの背景
	int menu_back_width_ = 400, menu_back_height_ = 300;
	Color menu_back_color_ = Color( 0, 0, 255, 102);
	Rect menu_back_ = Rect( menu_back_width_, menu_back_height_).setCenter( Window::Center() );

public:
	Command *commands_;
	int selected_command_;

	MenuWindow();
	MenuWindow( Command commands[], int commands_n, SceneType usage_scene);
	void DrawMenu();
	CommandType ExecuteCommand(Command command);
	Command GetSelectedCommand();
	//-
	MenuWindow( int commands_n, SceneType usage_scene);
};

class TitleScene
{
private:
	Font title_font_ = Font(30);
	int menu_back_width_ = 400, menu_back_height_ = 300;	//-不要?
	Rect menu_back_ = Rect( menu_back_width_, menu_back_height_ ).setCenter( Window::Center() );	//-
	Color menu_back_color_ = Color( 0, 0, 255, 102);	//-
	Command title_menu_commands_[TITLE_MENU_COMMANDS_N];
	SceneType scene_type_ = TITLE_SCENE;

public:
	MenuWindow title_scene_menu_;

	TitleScene();
	void DrawScene();
};


class SameGame
{
private:
	SceneType current_scene_;
	Font text_ = Font(30);

public:
	TitleScene title_scene_;
	MainScene main_scene_;

	SameGame();
	void DrawCurrentScene();
	SceneType GetCurrentScene();
	void SetCurrentScene(SceneType scene_type);
};	