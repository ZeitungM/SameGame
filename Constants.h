#define TITLE_MENU_COMMANDS_N 2

#define BLOCK_NUM_X	20
#define BLOCK_NUM_Y	10
#define BLOCK_USUAL_WIDTH	20
#define BLOCK_USUAL_HEIGHT	20
#define BLOCK_MAX_WIDTH		30
#define BLOCK_MAX_HEIGHT	30

// ブロックの色(空白、赤、緑、青、黄、紫)
enum BlockColor {	BLANK,
					RED,
					GREEN,
					BLUE,
					YELLOW,
					MAGENTA };

// 各シーンの名前( タイトルシーン、 メインシーン)
enum SceneType {	TITLE_SCENE,
					MAIN_SCENE };

// メニューコマンド( スタート、 終わる)
enum CommandType {	COMMAND_START,
					COMMAND_QUIT};