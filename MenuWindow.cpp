#include "ClassDefinition.h"

MenuWindow::MenuWindow()
{

}

// �R�}���h�̐��ƃR�}���h�Q���󂯎��A���j���[�E�B���h�E�𐶐�
MenuWindow::MenuWindow( Command commands[], int commands_num, SceneType usage_scene)
{
	selected_command_ = 0;	// ������Ԃł͈�ԏ�̃R�}���h��I��

	// ���j���[�E�B���h�E���g�p����V�[����o�^
	usage_scene_ = usage_scene;

	// ���j���[���̃R�}���h�̏�����
	// commands_�ɁA������commands[i]�𖖔��ɑ}��
	for (int i = 0; i < commands_num; i++)
		commands_.push_back(commands[i]);
}

void MenuWindow::DrawMenu()
{
	menu_back_.draw(menu_back_color_);	// �w�i�̕`��

	Point zero(0, 0), delta = Mouse::Delta();

	// �}�E�X�I�[�o�[����Ă���R�}���h��T��
	if (delta != zero)	// �}�E�X�̈ړ��ʂ��[���łȂ�������}�E�X�J�[�\�����������ꂽ�Ƃ݂Ȃ�
	{
		for (int command_i = 0; command_i < TITLE_MENU_COMMANDS_N; command_i++)
			if (commands_[command_i].command_area_.mouseOver)
				selected_command_ = command_i;
	}

	// �L�[�{�[�h�������ꂽ���̓���(�}�E�X����̎��͖���)
	if (delta == zero)
	{
		if (Input::KeyUp.clicked&&selected_command_>0)
			selected_command_--;
		if (Input::KeyDown.clicked&&selected_command_<TITLE_MENU_COMMANDS_N-1)
			selected_command_++;
	}

	// �R�}���h�̕`��
	int commands_area_top = 100;
	for (int command_i = 0; command_i < TITLE_MENU_COMMANDS_N; command_i++)
	{
		if (command_i==selected_command_)
			commands_[command_i].Draw(	commands_area_top+commands_[command_i].command_area_height_*command_i, true);
		else
			commands_[command_i].Draw(	commands_area_top+commands_[command_i].command_area_height_*command_i, false);
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