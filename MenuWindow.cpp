#include "ClassDefinition.h"

MenuWindow::MenuWindow()
{

}

// コマンドの数を受け取り、メニューウィンドウを生成( テキストは決め打ち、 テスト用)
MenuWindow::MenuWindow( int commands_num, SceneType usage_scene)
{
	selected_command_ = 0;	// 初期状態では一番上のコマンドを選択

	usage_scene_ = usage_scene;

	// メニュー内のコマンドの数だけメモリを動的確保
	commands_ = (Command *)malloc(sizeof(Command)*commands_num);

	// コマンドのテキストを初期化
	String command_start_text	= L"スタート";
	String command_quit_text	= L"終了";
	
	// commands[i]の各要素に対して引数付きコンストラクタで初期化
	new(this->commands_)	Command( command_start_text, usage_scene, COMMAND_START);
	new(this->commands_+1)	Command( command_quit_text,	 usage_scene, COMMAND_QUIT);
}

// コマンドの数とコマンド群を受け取り、メニューウィンドウを生成
MenuWindow::MenuWindow( Command commands[], int commands_num, SceneType usage_scene)
{
	selected_command_ = 0;	// 初期状態では一番上のコマンドを選択

	// メニューウィンドウを使用するシーンを登録
	usage_scene_ = usage_scene;

	// メニュー内のコマンドの初期化
	// メニュー内のコマンドの数だけメモリを動的確保
	commands_ = (Command *)malloc(sizeof(Command)*commands_num);

	// this->commands[i]の各要素に、引数のcommands[i]を代入
	for (int i = 0; i<commands_num; i++)
		new(commands_+i)Command(commands[i]);
}

void MenuWindow::DrawMenu()
{
	menu_back_.draw(menu_back_color_);	// 背景の描画

	Point zero(0, 0), delta = Mouse::Delta();

	//どの項目がマウスオーバーされているか探す
	if (delta != zero)	// マウスの移動量がゼロでなかったらマウスカーソルが動かされたとみなす
	{
		// TODO: 配列の長さを取得して終了条件にぶちこむ
		//ci番目のコマンドがマウスオーバーされていたらselectedを更新
		for (int command_i = 0; command_i < TITLE_MENU_COMMANDS_N; command_i++)
			if (commands_[command_i].command_area_.mouseOver)
				selected_command_ = command_i;
	}

	// キーボードが押された時の動作(マウス操作の時は無効)
	if (delta == zero)
	{
		if (Input::KeyUp.clicked&&selected_command_>0)
			selected_command_--;
		if (Input::KeyDown.clicked&&selected_command_<TITLE_MENU_COMMANDS_N-1)
			selected_command_++;
	}

	// コマンドの描画
	for (int command_i = 0; command_i < TITLE_MENU_COMMANDS_N; command_i++)
	{
		// TODO: マジックナンバー撲滅、座標の指定が甘いので微妙に中心からずれる
		if (command_i==selected_command_)
			commands_[command_i].Draw( 200, 100+50*command_i, true);
		else
			commands_[command_i].Draw( 200, 100+50*command_i, false);
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