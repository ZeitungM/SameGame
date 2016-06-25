#include "ClassDefinition.h"

void Main()
{
	// 初期処理
	Window::SetTitle(L"さめがめ");	// ウィンドウのタイトルの設定
	SameGame samegame = SameGame();
	const Point zero = Point( 0, 0);	// マウスが操作されてないと判断する移動量の基準
	Point delta;	// マウスの移動量

	// TODO:while(System::Update())内のループをもっと簡潔に
	while (System::Update())
	{
		// マウスの移動量を取得する
		delta = Mouse::Delta();

		// 現在のシーンに合わせた処理
		switch (samegame.GetCurrentScene())
		{
			case TITLE_SCENE:
				// Enterキーが押されるか 左クリックされたら、選択されているコマンドを実行する
				if (Input::KeyEnter.clicked || Input::MouseL.released)
				{	
					// 選択されているコマンドを取得
					Command selected_command = samegame.title_scene_.title_scene_menu_.GetSelectedCommand();
					// 選択されているコマンドを実行する
					switch (selected_command.GetCommandType())
					{
						// START が選択されていたら、ゲームを開始する(MAIN_SCENEへ)
						case COMMAND_START:
							samegame.SetCurrentScene(MAIN_SCENE);
							break;

						// QUITが選択されていたら、アプリケーションを終了する
						case COMMAND_QUIT:
							System::Exit();
							break;

						default:
							break;
					}

				}
				// タイトルシーンを描画する
				samegame.title_scene_.DrawScene();
				break;
			
			case MAIN_SCENE:

				// メインシーン描画ループ毎の初期化処理
				// 各ブロックの消去可能判定を初期化
				samegame.main_scene_.field_.InitializeDeletablity();

				if (delta!=zero)	// マウスカーソルが動かされたとき、マウスによるカーソル移動
					samegame.main_scene_.MoveCursorByMouse();
				else
				{	
					//	方向キーが押された時の処理
					if (Input::KeyUp.clicked)
						samegame.main_scene_.MoveCursorToUp();
					if (Input::KeyDown.clicked)
						samegame.main_scene_.MoveCursorToDown();				
					if (Input::KeyRight.clicked)
						samegame.main_scene_.MoveCursorToRight();
					if (Input::KeyLeft.clicked)
						samegame.main_scene_.MoveCursorToLeft();
				}

				// 現在ポイントしている地点から消せるブロックを探す
				{
					int tmp_cursor_x = samegame.main_scene_.field_.cursor_.position_x_;
					int tmp_cursor_y = samegame.main_scene_.field_.cursor_.position_y_;
					samegame.main_scene_.field_.SearchDeletableBlock( tmp_cursor_x, tmp_cursor_y,
						samegame.main_scene_.field_.blocks_[tmp_cursor_x][tmp_cursor_y].block_color_ );
				}

				// Enterキーが押されたorマウスの左ボタンがクリックされたら、ポイントしているブロックを消す
				if (Input::KeyEnter.clicked||Input::MouseL.clicked)
				{
					int deleted_block_num = samegame.main_scene_.field_.DeleteBlock();
					samegame.main_scene_.AddScore(deleted_block_num);
					samegame.main_scene_.field_.CloseUpVerticalSpace();
					samegame.main_scene_.field_.FillBlankColumn();
				}
				samegame.main_scene_.JudgeGameOver();

				// メインシーンを描画
				samegame.main_scene_.DrawScene();

				break;

			default:
				break;
		}
	}
}

