#include "ClassDefinition.h"

Command::Command()
{

}

Command::Command(String command_text, SceneType command_scene, CommandType command_type)
{
	command_text_	= command_text;
	usage_scene_	= command_scene;
	command_type_	= command_type;
}

void Command::Draw( int y_coodinate, bool is_selected)
{
	// Rectをコマンドを描画する位置( x_coodinate, y_coodinate)に移動
	command_area_.setPos( (Window::Width()-command_area_width_)/2, y_coodinate);
	
	// コマンドを描画する(コマンド名をコマンド描画エリアと中心を合わせる)
	if (is_selected)	// 選択されていたらコマンドの背景を塗りつぶす
		command_area_.draw(selected_color_);
	command_text_font_(command_text_).drawCenter( command_area_.center);
}

CommandType Command::GetCommandType()
{
	return command_type_;
}

SceneType Command::GetUsageScene()
{
	return usage_scene_;
}
