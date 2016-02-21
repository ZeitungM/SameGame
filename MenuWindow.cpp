#include "ClassDefinition.h"

MenuWindow::MenuWindow()
{

}

// �R�}���h�̐����󂯎��A���j���[�E�B���h�E�𐶐�( �e�L�X�g�͌��ߑł��A �e�X�g�p)
MenuWindow::MenuWindow( int commands_num, SceneType usage_scene)
{
	selected_command_ = 0;	// ������Ԃł͈�ԏ�̃R�}���h��I��

	usage_scene_ = usage_scene;

	// ���j���[���̃R�}���h�̐������������𓮓I�m��
	commands_ = (Command *)malloc(sizeof(Command)*commands_num);

	// �R�}���h�̃e�L�X�g��������
	String command_start_text	= L"�X�^�[�g";
	String command_quit_text	= L"�I��";
	
	// commands[i]�̊e�v�f�ɑ΂��Ĉ����t���R���X�g���N�^�ŏ�����
	new(this->commands_)	Command( command_start_text, usage_scene, COMMAND_START);
	new(this->commands_+1)	Command( command_quit_text,	 usage_scene, COMMAND_QUIT);
}

// �R�}���h�̐��ƃR�}���h�Q���󂯎��A���j���[�E�B���h�E�𐶐�
MenuWindow::MenuWindow( Command commands[], int commands_num, SceneType usage_scene)
{
	selected_command_ = 0;	// ������Ԃł͈�ԏ�̃R�}���h��I��

	// ���j���[�E�B���h�E���g�p����V�[����o�^
	usage_scene_ = usage_scene;

	// ���j���[���̃R�}���h�̏�����
	// ���j���[���̃R�}���h�̐������������𓮓I�m��
	commands_ = (Command *)malloc(sizeof(Command)*commands_num);

	// this->commands[i]�̊e�v�f�ɁA������commands[i]����
	for (int i = 0; i<commands_num; i++)
		new(commands_+i)Command(commands[i]);
}

void MenuWindow::DrawMenu()
{
	menu_back_.draw(menu_back_color_);	// �w�i�̕`��

	Point zero(0, 0), delta = Mouse::Delta();

	//�ǂ̍��ڂ��}�E�X�I�[�o�[����Ă��邩�T��
	if (delta != zero)	// �}�E�X�̈ړ��ʂ��[���łȂ�������}�E�X�J�[�\�����������ꂽ�Ƃ݂Ȃ�
	{
		// TODO: �z��̒������擾���ďI�������ɂԂ�����
		//ci�Ԗڂ̃R�}���h���}�E�X�I�[�o�[����Ă�����selected���X�V
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
	for (int command_i = 0; command_i < TITLE_MENU_COMMANDS_N; command_i++)
	{
		// TODO: �}�W�b�N�i���o�[�o�ŁA���W�̎w�肪�Â��̂Ŕ����ɒ��S���炸���
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