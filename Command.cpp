#include "ClassDefinition.h"

const int	Command::AREA_WIDTH_ = 200;
const int	Command::AREA_HEIGHT_ = 50;
const Color	Command::SELECTED_COLOR_ = Color(255, 0, 0, 102);
const Rect	Command::test_rect = Rect();

Command::Command()
{

}

Command::Command(String command_text, SceneType command_scene, CommandType command_type)
{
	command_text_	= command_text;
	usage_scene_	= command_scene;
	command_type_	= command_type;
	command_area_	= Rect( Command::AREA_WIDTH_, Command::AREA_HEIGHT_);
}

void Command::Draw( int y_coodinate, bool is_selected)
{
	// Rect���R�}���h��`�悷��ʒu( x_coodinate, y_coodinate)�Ɉړ�
	command_area_.setPos( (Window::Width()-Command::AREA_WIDTH_)/2, y_coodinate);
	
	// �R�}���h��`�悷��(�R�}���h�����R�}���h�`��G���A�ƒ��S�����킹��)
	if (is_selected)	// �I������Ă�����R�}���h�̔w�i��h��Ԃ�
		command_area_.draw(Command::SELECTED_COLOR_);

	command_text_font_(command_text_).drawCenter(command_area_.center);
}

CommandType Command::GetCommandType()
{
	return command_type_;
}

SceneType Command::GetUsageScene()
{
	return usage_scene_;
}
