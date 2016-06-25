#include <Siv3D.hpp>
#include <vector>

#include "Constants.h"

class MainCursor
{
private:
	static const int INNER_FRAME_THICKNESS_;
	static const int OUTER_FRAME_THICKNESS_;
	static const Color FRAME_COLOR_;

	int width_;
	int height_;
	Rect cursor_;

public:
	int position_x_;
	int position_y_;

	MainCursor();

	void DrawCursor();
};

class Block
{
private:
	static const int OUTER_FRAME_THICKNESS_;

public:
	static const int USUAL_WIDTH_;
	static const int USUAL_HEIGHT_;
	static const int MAX_WIDTH_;
	static const int MAX_HEIGHT_;
	static const bool DELETABLE_;
	static const bool UNDELETABLE_;

	bool deletable_;
	Rect block_;
	BlockColor block_color_;

	Block();
	Block( Point block_coordinates, BlockColor b_color);

	void DrawBlock();
	void DrawBlock( Color color);
	bool GetMouseOver();
};

class Field
{
private:
	static const Color BLOCK_RED_;
	static const Color BLOCK_BLUE_;
	static const Color BLOCK_GREEN_;
	static const Color BLOCK_YELLOW_;
	static const Color BLOCK_MAGENTA_;

	Point field_top_left_coordinates_;	// フィールドの左上の座標

	// TODO: 使われてる？
	Color block_red_	 = Color( 255,   0,   0);
	Color block_green_	 = Color(   0, 255,   0);
	Color block_blue_	 = Color(   0,   0, 255);
	Color block_yellow_	 = Color( 255, 255,   0);
	Color block_magenta_ = Color( 255,   0, 255);
	
public:
	static const int BLOCK_NUM_X_ = 20;
	static const int BLOCK_NUM_Y_ = 10;
	static const int AREA_RIGHT_ = BLOCK_NUM_X_ - 1;
	static const int AREA_BOTTOM_ = BLOCK_NUM_Y_ - 1;
	int field_area_right_	= BLOCK_NUM_X_ - 1;
	int field_area_bottom_	= BLOCK_NUM_Y_ - 1;
	Block blocks_[BLOCK_NUM_X_][BLOCK_NUM_Y_];	
	MainCursor cursor_;

	Field();

	void DrawField();

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
	bool game_over_;
	Font score_font_ = Font(30);
	Font game_over_txt_ = Font(30);

public:
	Field field_;

	MainScene();
	
	void DrawScene();
	void DisplayScore();

	void AddScore(int deleted_block);

	void MoveCursorToUp();
	void MoveCursorToDown();
	void MoveCursorToRight();
	void MoveCursorToLeft();
	void MoveCursorByMouse();	

	void JudgeGameOver();
};


class Command
{
private:
	static const Color SELECTED_COLOR_;
	static const Rect test_rect;

	String command_text_ = L"コマンド内に表示する文字列";
	SceneType usage_scene_;	// コマンドを使用するシーン
	CommandType command_type_;	// コマンドの種類
	// TODO: Font は static 非対応なので、かわりに FontAsset を導入する
	Font command_text_font_ = Font(30);

public:
	static const int AREA_WIDTH_;
	static const int AREA_HEIGHT_;

	Rect command_area_;

	Command();
	Command(String command_text, SceneType command_scene, CommandType command_type);

	CommandType GetCommandType();
	SceneType GetUsageScene();

	void Draw( int y_coodinate, bool is_selected);
};

class MenuWindow
{
private:
	static const int MENU_BACK_WIDTH_;
	static const int MENU_BACK_HEIGHT_;
	static const Color MENU_BACK_COLOR_;

	SceneType usage_scene_;	// メニューウィンドウを使用するシーン

	// メニューの背景
	Color menu_back_color_ = Color(0, 0, 255, 102);
	Rect menu_back_;

public:
	std::vector<Command> commands_;
	int selected_command_;

	MenuWindow();
	MenuWindow(std::vector<Command> commands, SceneType usage_scene);

	void DrawMenu();
	CommandType ExecuteCommand(Command command);
	Command GetSelectedCommand();
};

class TitleScene
{
private:
	static const int MENU_BACK_WIDTH_;
	static const int MENU_BACK_HEIGHT_;
	static const Color MENU_BACK_COLOR_;
	static const SceneType SCENE_TYPE_;

	Font title_font_ = Font(30);
	Rect menu_back_;
	Color menu_back_color_ =  Color( 0, 0, 255, 102);
	std::vector<Command> title_menu_commands_;
	const SceneType scene_type_ = TITLE_SCENE;

public:
	// TODO:使われてる?(vectorを導入したら不要になるかも)
	static const int COMMANDS_N_ = 2;

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