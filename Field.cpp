#include "ClassDefinition.h"

Field::Field()
{
	// フィールドの左上の座標(ウィンドウ中央からブロックの大きさ最大時の縦横半数分左上)を計算
	field_top_left_coordinates_ = Point( Window::Width()/2 - BLOCK_MAX_WIDTH*BLOCK_NUM_X/2, Window::Height()/2 - BLOCK_MAX_HEIGHT*BLOCK_NUM_Y/2);

	// インスタンス生成時にフィールドにランダムな色のブロックを配置する
	for (int yi = 0; yi < BLOCK_NUM_Y; yi++)
		for (int xi = 0; xi < BLOCK_NUM_X; xi++)
		{
			Point block_coordinates = Point( field_top_left_coordinates_.x + BLOCK_MAX_WIDTH*xi, field_top_left_coordinates_.y + BLOCK_MAX_HEIGHT*yi);
			blocks_[xi][yi] = Block( block_coordinates, (BlockColor)Random((int)RED, (int)MAGENTA));
		}
}

void Field::DrawField()
{
	for (int yi = 0; yi < BLOCK_NUM_Y; yi++)
		for (int xi = 0; xi < BLOCK_NUM_X; xi++)
			blocks_[xi][yi].DrawBlock();
	cursor_.DrawCursor();
}

// 消去可能なブロックを探索する
void Field::SearchDeletableBlock(int x, int y, BlockColor block_color)
{
	// 現在ポイントしている箇所にブロックがなければ終了
	if (blocks_[x][y].block_color_==BLANK)
		return;

	// 再帰的に呼び出して隣接している同色のブロックを探す(既に探査済みorフィールドの外縁のときはやらない)
	// 左方向への探査
	if (x > 0 && blocks_[x-1][y].block_color_==block_color)
	{
		// 左に同色のブロックが隣接しているなら、そのブロックは消せる
		blocks_[x][y].deletable_ = true;
		// 左に未探査の同色のブロックがあれば再帰的に探査を続ける
		if (!blocks_[x-1][y].deletable_)
			SearchDeletableBlock( x-1, y, block_color);
	}

	// 右方向への探査
	if (x < BLOCK_NUM_X-1 && blocks_[x+1][y].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = true;
		if (!blocks_[x+1][y].deletable_)
			SearchDeletableBlock( x+1, y, block_color);
	}

	// 上方向への探査
	if (y > 0 && blocks_[x][y-1].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = true;
		if (!blocks_[x][y-1].deletable_)
			SearchDeletableBlock( x, y-1, block_color);
	}

	// 下方向への探査
	if (y < BLOCK_NUM_Y-1 && blocks_[x][y+1].block_color_==block_color)
	{
		blocks_[x][y].deletable_ = true;
		if (!blocks_[x][y+1].deletable_)
			SearchDeletableBlock( x, y+1, block_color);
	}
}

void Field::InitializeDeletablity()
{
	for (int yi=0; yi<BLOCK_NUM_Y; yi++)
		for (int xi=0; xi<BLOCK_NUM_X; xi++)
			blocks_[xi][yi].deletable_ = false;
}

// ブロックを消去して、その数を返す
int Field::DeleteBlock()
{
	int num_deleted_block = 0;
	for (int yi = 0; yi < BLOCK_NUM_Y; yi++)
	{
		for (int xi = 0; xi < BLOCK_NUM_X; xi++)
		{
			if (blocks_[xi][yi].deletable_)
			{
				Point block_coordinates = Point( field_top_left_coordinates_.x + BLOCK_MAX_WIDTH*xi, field_top_left_coordinates_.y + BLOCK_MAX_HEIGHT*yi);
				blocks_[xi][yi] = Block( block_coordinates, BLANK);
				num_deleted_block++;
			}
		}
	}
	return num_deleted_block;
}

void Field::CloseUpVerticalSpace()
{
	bool dropped = true;

	while (dropped)
	{
		dropped = false;
		for (int yi = 0; yi < BLOCK_NUM_Y-1; yi++)
		{
			for (int xi = 0; xi < BLOCK_NUM_X; xi++)
			{
				if (blocks_[xi][yi+1].block_color_==BLANK && blocks_[xi][yi].block_color_!=BLANK)
				{
					std::swap( blocks_[xi][yi].block_color_, blocks_[xi][yi+1].block_color_);
					std::swap( blocks_[xi][yi].deletable_, blocks_[xi][yi+1].deletable_);
					dropped = true;
				}
			}
		}
	}
}

void Field::FillBlankColumn()
{
	bool filled = true;

	while (filled)
	{
		filled = false;
		for (int xi = 0; xi < BLOCK_NUM_X - 1; xi++)
		{
			// 一番下が空白ならば、その列は全て空白
			if ( blocks_[xi][BLOCK_NUM_Y-1].block_color_==BLANK && blocks_[xi+1][BLOCK_NUM_Y-1].block_color_!=BLANK)
			{
				for (int yi = 0; yi < BLOCK_NUM_Y; yi++){
					std::swap( blocks_[xi][yi].block_color_, blocks_[xi+1][yi].block_color_);
					std::swap( blocks_[xi][yi].deletable_, blocks_[xi+1][yi].deletable_);
				}
				filled = true;
			}
		}
	}
}