#define TITLE_MENU_COMMANDS_N 2

#define BLOCK_NUM_X	20
#define BLOCK_NUM_Y	10
#define BLOCK_USUAL_WIDTH	20
#define BLOCK_USUAL_HEIGHT	20
#define BLOCK_MAX_WIDTH		30
#define BLOCK_MAX_HEIGHT	30

// �u���b�N�̐F(�󔒁A�ԁA�΁A�A���A��)
enum BlockColor {	BLANK,
					RED,
					GREEN,
					BLUE,
					YELLOW,
					MAGENTA };

// �e�V�[���̖��O( �^�C�g���V�[���A ���C���V�[��)
enum SceneType {	TITLE_SCENE,
					MAIN_SCENE };

// ���j���[�R�}���h( �X�^�[�g�A �I���)
enum CommandType {	COMMAND_START,
					COMMAND_QUIT};