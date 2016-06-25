#include "ClassDefinition.h"

const int MenuWindow::MENU_BACK_WIDTH_ = 400;
const int MenuWindow::MENU_BACK_HEIGHT_ = 300;
const Color MenuWindow::MENU_BACK_COLOR_ = Color(0, 0, 255, 102);

MenuWindow::MenuWindow()
{

}

// コマンドの数とコマンド群を受け取り、メニューウィンドウを生成
MenuWindow::MenuWindow(std::vector<Command> commands, SceneType usage_scene)
{
	// 初期状態では一番上のコマンドを選択
	selected_command_ = 0;	// TODO: マジックナンバー

	menu_back_ = Rect( MenuWindow::MENU_BACK_WIDTH_, MenuWindow::MENU_BACK_HEIGHT_).setCenter(Window::Center());

	// メニューウィンドウを使用するシーンを設定
	usage_scene_ = usage_scene;

	// メニュー内のコマンドの初期化
	// commands_に、引数のcommands[i]を末尾に挿入
	for (int i = 0; i < commands.size(); i++)
		commands_.push_back(commands[i]);
}

void MenuWindow::DrawMenu()
{
	menu_back_.draw(menu_back_color_);	// 背景の描画

	Point zero(0, 0), delta = Mouse::Delta();
	int commands_n = (int)commands_.size();

	// マウスオーバーされているコマンドを探す
	if (delta != zero)	// マウスの移動量がゼロでなかったらマウスカーソルが動かされたとみなす
	{
		for (int command_i = 0; command_i < commands_n; command_i++)
			if (commands_[command_i].command_area_.mouseOver)
				selected_command_ = command_i;
	}

	// キーボードが押された時の動作(マウス操作の時は無効)
	if (delta == zero)
	{
		if (Input::KeyUp.clicked&&selected_command_>0)
			selected_command_--;
		if (Input::KeyDown.clicked&&selected_command_< commands_n - 1)
			selected_command_++;
	}

	// コマンドの描画
	int commands_area_top = 100;
	for (int command_i = 0; command_i < commands_n; command_i++)
	{
		if (command_i == selected_command_)
			commands_[command_i].Draw(commands_area_top + commands_[command_i].Command::AREA_HEIGHT_*command_i, true);
		else
			commands_[command_i].Draw(commands_area_top + commands_[command_i].Command::AREA_HEIGHT_*command_i, false);
	}
}

CommandType MenuWindow::ExecuteCommand(Command command)
{
	switch (command.GetCommandType())
	{
		case COMMAND_START:
			break;
	
		case COMMAND_QUIT:
			System::Exit();
			break;

		default:
			break;
	}
	return command.GetCommandType();
}

Command MenuWindow::GetSelectedCommand()
{
	return commands_[selected_command_];
}