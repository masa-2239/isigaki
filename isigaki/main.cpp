#include "StartScreen.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

static const int FIELD_WIDTH = 25;
static const int VISIBLE_HEIGHT = 20;

static const int BUFFER_HEIGHT = 4;
static const int FIELD_HEIGHT = VISIBLE_HEIGHT + BUFFER_HEIGHT;

static const int MINO_WIDTH = 4;
static const int MINO_HEIGHT = 4;

//ブロックの種類
enum BlockType {
	BLOCK_EMPTY = 0,
	BLOCK_FIXED = 1,
	BLOCK_WALL = 2,
	BLOCK_BOMB = 3, 
};

//テトリスミノの種類
enum
{
	MINO_TYPE_O,
	MINO_TYPE_S,
	MINO_TYPE_Z,
	MINO_TYPE_J,
	MINO_TYPE_L,
	MINO_TYPE_T,
	MINO_TYPE_BOMB,
	MINO_TYPE_MAX
};

//テトリスミノの角度
enum
{
	MINO_ANGLE_0,
	MINO_ANGLE_90,
	MINO_ANGLE_180,
	MINO_ANGLE_270,
	MINO_ANGLE_MAX,
};

// 0:空白, 1:固定されたブロック, 2:外枠(壁・床)
char field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_WIDTH][MINO_HEIGHT] =
{
	// MINO_TYPE_O
	{
		// MINO_ANGLE_0
		{
			0,1,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0
		},
	// MINO_ANGLE_90
	{
		0,0,0,0,
		0,1,1,1,
		0,1,1,0,
		0,0,0,0
	},
	// MINO_ANGLE_180
	{
		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,1,0
	},
	// MINO_ANGLE_270
	{
		0,0,0,0,
		0,1,1,0,
		1,1,1,0,
		0,0,0,0
	}
},
// MINO_TYPE_S
{
	// MINO_ANGLE_0
	{
		0,1,0,0,
		1,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_90
	{
		0,1,0,0,
		1,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_180
	{
		0,1,0,0,
		1,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_270
	{
		0,1,0,0,
		1,1,1,0,
		0,1,0,0,
		0,0,0,0
	}
},
// MINO_TYPE_Z
{
	// MINO_ANGLE_0
	{
		1,1,0,0,
		0,1,0,0,
		0,1,1,0,
		0,0,0,0
	},
	// MINO_ANGLE_90
	{
		0,0,1,0,
		1,1,1,0,
		1,0,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_180
	{
		1,1,0,0,
		0,1,0,0,
		0,1,1,0,
		0,0,0,0
	},
	// MINO_ANGLE_270
	{
		0,0,1,0,
		1,1,1,0,
		1,0,0,0,
		0,0,0,0
	}
},
// MINO_TYPE_J
{
	// MINO_ANGLE_0
	{
		0,0,1,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0
	},
	// MINO_ANGLE_90
	{
		1,1,0,0,
		1,1,1,0,
		0,0,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_180
	{
		0,1,1,0,
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_270
	{
		0,0,0,0,
		1,1,1,0,
		0,1,1,0,
		0,0,0,0
	}
},
// MINO_TYPE_L
{
	// MINO_ANGLE_0
	{
		0,1,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0
	},
	// MINO_ANGLE_90
	{
		0,0,0,0,
		1,1,1,0,
		1,1,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_180
	{
		0,1,1,0,
		0,1,1,0,
		0,0,1,0,
		0,0,0,0
	},
	// MINO_ANGLE_270
	{
		0,1,1,0,
		1,1,1,0,
		0,0,0,0,
		0,0,0,0
	}
},
// MINO_TYPE_T
{
	// MINO_ANGLE_0
	{
		0,1,0,0,
		0,1,0,0,
		1,1,1,0,
		0,0,0,0
	},
	// MINO_ANGLE_90
	{
		1,0,0,0,
		1,1,1,0,
		1,0,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_180
	{
		0,0,0,0,
		1,1,1,0,
		0,1,0,0,
		0,1,0,0
	},
	// MINO_ANGLE_270
	{
		0,0,1,0,
		1,1,1,0,
		0,0,1,0,
		0,0,0,0
	}
},
//MINO_TYPE_BOMB
{
	// MINO_ANGLE_0
	{
		0,3,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_90
	{
		0,3,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_180
	{
		0,3,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	},
	// MINO_ANGLE_270
	{
		0,3,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	}
},
};

void display();
bool isHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle);
void resetMino();
void initField();
int countEmptySpaces();
void executeBombAreaEffect(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle);
void applyGravityToFeld(int targetMinoX);

void initField() {
	memset(field, 0, sizeof(field));
	// 外枠（壁）を2に設定
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		field[i][0] = 2;
		field[i][FIELD_WIDTH - 1] = 2;
	}
	// 外枠（床）を2に設定
	for (int i = 0; i < FIELD_WIDTH; i++) {
		field[FIELD_HEIGHT - 1][i] = 2;
	}
}

// 積み上がったブロックの隙間（空いているマス）の数を計算する関数
int countEmptySpaces() {
	int emptyCount = 0;

	// 外枠（壁と床）の内側だけをループで回す
	for (int i = 3; i < FIELD_HEIGHT - 1; i++) { // 一番下の床(HEIGHT-1)は除外
		for (int j = 1; j < FIELD_WIDTH - 1; j++) { // 左右の壁(0とWIDTH-1)は除外
			// 固定されたブロック(1)でもなく、外枠(2)でもない、空いているマス(0)をカウント
			if (field[i][j] == 0) {
				emptyCount++;
			}
		}
	}
	return emptyCount;
}

void executeBombAreaEffect(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle) {
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (minoShapes[argMinoType][argMinoAngle][i][j] == 3) {
				int centerY = argMinoY + i;
				int centerX = argMinoX + j;

				// ボムブロックの周囲1マス（縦・横・斜め 3x3マス）をループ
				for (int dy = -1; dy <= 1; dy++) {
					for (int dx = -1; dx <= 1; dx++) {
						int targetY = centerY + dy;
						int targetX = centerX + dx;

						// フィールドの内側（壁や床、画面外ではないエリア）であれば消去する
						if (targetY >= 0 && targetY < FIELD_HEIGHT - 1 && targetX > 0 && targetX < FIELD_WIDTH - 1) {
							if (field[targetY][targetX] == 1) {
								field[targetY][targetX] = 0; // ブロックをクリア
							}
						}
					}
				}
			}
		}
	}
}

//ボムが落ちてきた左右5マスの範囲だけに重力を適用させる
void applyGravityToField(int targetMinoX){
	// ボムブロック（配列内でj=1の位置）の左右2マスの5列が対象
	for (int j = targetMinoX - 2; j <= targetMinoX + 3; j++) {
		// 外枠（壁）を越えて範囲外にアクセスしないように防衛ガード
		if (j <= 0 || j >= FIELD_WIDTH - 1) continue;
		// 対象の列を下から上に向かってスキャン
		for (int i = FIELD_HEIGHT - 2; i >= 0; i--) {
			if (field[i][j] == 1) {
				int currentY = i;
				// 下のマスが空欄(0)である限り、1マスずつ真下に落とし込む
				while (currentY + 1 < FIELD_HEIGHT - 1 && field[currentY + 1][j] == 0) {
					field[currentY + 1][j] = 1;
					field[currentY][j] = 0;
					currentY++;
				}
			}
		}
	}
}


int minoType = 0;		//ミノの種類
int minoAngle = 0;		//ミノの角度
int nextMinoType = 0;	//次のミノの種類
int nextMinoAngle = 0;	//次のミノの角度
int minoX = 0;
int minoY = 0;
int score = 0;			// スコア記録用変数

int main() {
	// 壁と操作ボタン
	srand((unsigned int)time(NULL));

	// 初回のNEXTミノ決定（15%の確率でボム）
	if (rand() % 100 < 15) {
		nextMinoType = MINO_TYPE_BOMB;
	}
	else {
		nextMinoType = rand() % (MINO_TYPE_MAX - 1);
	}
	nextMinoAngle = rand() % MINO_ANGLE_MAX;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &cursorInfo);

	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		field[i][0] = 1;
		field[i][FIELD_WIDTH - 1] = 1;
	}
	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		field[FIELD_HEIGHT - 1][i] = 1;
	}

	initField();
	resetMino();

	StartScreen startScreen;
	startScreen.show();

	time_t t = time(NULL);
	system("cls");
	display();

	while (1)
	{
		//ゲーム操作ボタン
		if (_kbhit()) {
			switch (_getch()) {
			case 's': if (!isHit(minoX, minoY + 1, minoType, minoAngle)) ++minoY; break; // 's'キーで下に移動
			case 'a': if (!isHit(minoX - 1, minoY, minoType, minoAngle)) --minoX; break; // 'a'キーで左に移動
			case 'd': if (!isHit(minoX + 1, minoY, minoType, minoAngle)) ++minoX; break; // 'd'キーで右に移動
				// 'l'キーで右回り（時計回り）
			case 'l': if (!isHit(minoX, minoY, minoType, (minoAngle + 1) % MINO_ANGLE_MAX)) {
				minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;
			}
					break;
					// 'k'キーで左回り（反時計回り）
			case'k':
				if (!isHit(minoX, minoY, minoType, (minoAngle + MINO_ANGLE_MAX - 1) % MINO_ANGLE_MAX)) {
					minoAngle = (minoAngle + MINO_ANGLE_MAX - 1) % MINO_ANGLE_MAX;
				}
				break;
			}
			display();
		}

		if (time(NULL) != t)
		{
			t = time(NULL);

			if (isHit(minoX, minoY + 1, minoType, minoAngle))
			{
				if (minoType == MINO_TYPE_BOMB) {
					// 1. 周囲1マスを破壊
					executeBombAreaEffect(minoX, minoY, minoType, minoAngle);
					// 2. 宙に浮いたブロックを重力で真下にカチッと落とす
					applyGravityToField(minoX);
				}
				else {
					for (int i = 0; i < MINO_HEIGHT; i++)
					{
						for (int j = 0; j < MINO_WIDTH; j++)
						{
							if (minoShapes[minoType][minoAngle][i][j]) field[minoY + i][minoX + j] |= 1;
						}
					}
				}

				resetMino();

				// 次のミノが出現位置で衝突しているかをチェック
				if (isHit(minoX, minoY, minoType, minoAngle)) {

					// ただし、出現したのが「ボムブロック」だった場合は即ゲームオーバーにせず、
					// その場で爆発させて周囲を消去し、ゲームを続行できるようにする
					if (minoType == MINO_TYPE_BOMB) {
						executeBombAreaEffect(minoX, minoY, minoType, minoAngle);
						applyGravityToField(minoX);
						resetMino(); // さらにもう一度次のミノを引き直す

						// ボムが爆発してもなお次のミノが置けない場合のみ、本当のゲームオーバーにする
						if (isHit(minoX, minoY, minoType, minoAngle)) {
							goto GAMEOVER_LABEL;
						}
					}
					else {
						// 通常ミノが置けない場合はゲームオーバーへ
						goto GAMEOVER_LABEL;
					}
				}
			}
			else
			{
				++minoY;
			}

			display();
		}
		Sleep(1);
	}

	// ゲームオーバー時の処理をラベル化して共通に管理
GAMEOVER_LABEL:
	display();

	int emptySpaces = countEmptySpaces();

	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
	system("cls");
	std::cout << "==========================" << std::endl;
	std::cout << "\n  　置けなくなりました  " << std::endl;
	std::cout << "                          " << std::endl;
	std::cout << "==========================" << std::endl;

	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "\n  [最終結果]" << std::endl;
	std::cout << "                          " << std::endl;
	std::cout << "  空いているマスの数: " << emptySpaces << " 個" << std::endl;
	std::cout << "                          " << std::endl;
	std::cout << "  ※最大空き容量: " << (FIELD_HEIGHT - 1) * (FIELD_WIDTH - 2) << " 個" << std::endl;
	std::cout << "\n==========================" << std::endl;
	std::cout << "  Press Enter key to exit..." << std::endl;

	while (1) {
		if (_getch() == 13) {
			break;
		}
	}
	return 0;
}

void display() {
	// displayBufferにフィールドの状態をコピー
	memcpy(displayBuffer, field, sizeof(field));

	for (int i = 0; i < MINO_HEIGHT; i++)
	{
		for (int j = 0; j < MINO_WIDTH; j++)
		{
			int targetY = minoY + i;
			int targetX = minoX + j;
			if (targetY >= 0 && targetY < FIELD_HEIGHT && targetX >= 0 && targetX < FIELD_WIDTH) {
				if (minoShapes[minoType][minoAngle][i][j]) {
					displayBuffer[targetY][targetX] = minoShapes[minoType][minoAngle][i][j];
				}
			}
		}
	}

	// 画面のちらつき防止
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(handle, coord);

	// フィールドの描画
	for (int i = 0; i < FIELD_HEIGHT; i++) {
		for (int j = 0; j < FIELD_WIDTH; j++) {

			//上から3マスの範囲は空白にする
			if (i < 3) {
				//ブロックが存在する場合描画する
				if (1 == displayBuffer[i][j]) {
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
					std::cout << "■";
				}
				else if (3 == displayBuffer[i][j]) {
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					std::cout << "●";
				}
				else {
					std::cout << " ";
				}
				continue;
			}

			if (1 == displayBuffer[i][j]) {
				// 通常のブロック
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
				std::cout << "■";
			}
			else if (2 == displayBuffer[i][j]) {
				// 枠のブロック
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				std::cout << "■";
			}
			// 特殊ブロック（値が3）の表示処理
			else if (3 == displayBuffer[i][j]) {
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
				std::cout << "●";
			}
			else {
				// 0: 空白マスに「グリッド線」を入れて位置をわかりやすくする
				SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY); // 暗い灰色

				// 外枠のすぐ内側に線を表示
				if (i < FIELD_HEIGHT - 1 && j > 0 && j < FIELD_WIDTH - 1) {
					std::cout << "|";
				}
				else {
					std::cout << " ";
				}
			}

		}


		// 【右側のサイドパネル】
		int relativeLine = i - BUFFER_HEIGHT;

		if (relativeLine == 5) {
			std::cout << "   NEXT:";
		}
		// 6行目〜9行目を使って、4x4のNEXTミノを描画する
		else if (relativeLine >= 6 && relativeLine < 6 + MINO_HEIGHT) {
			std::cout << "   ";
			int nextLine = relativeLine - 6;
			for (int nextCol = 0; nextCol < MINO_WIDTH; nextCol++) {
				char nextVal = minoShapes[nextMinoType][nextMinoAngle][nextLine][nextCol];
				if (nextVal == 1) {
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
					std::cout << "■";
				}
				// NEXTでの特殊ブロックの表示
				else if (nextVal == 3) {
					SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
					std::cout << "●";
				}
				else {
					std::cout << " ";
				}
			}
		}
		// 上から3行目の位置に現在のスコアを右側表示する
		if (relativeLine == 2) {
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
			std::cout << "  スコア" << score;
		}
		// 操作説明の表示
		else if (relativeLine == 11) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << "  [A]       : Left";
		}
		else if (relativeLine == 13) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << "  [S]       : Down";
		}
		else if (relativeLine == 15) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << "  [D]       : Right";
		}
		else if (relativeLine == 17) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << "  [l]       : Rotate Right";
		}
		else if (relativeLine == 19) {
			SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			std::cout << "  [k]       : Rotate Left";
		}

		std::cout << std::endl;
	}
}

bool isHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle) {
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (minoShapes[argMinoType][argMinoAngle][i][j]) {
				int targetY = argMinoY + i;
				int targetX = argMinoX + j;

				// 画面外のバッファ（0〜3行目）にいるときも、左右の壁や配列外（0未満）との衝突を防ぐ
				if (targetY < 0 || targetY >= FIELD_HEIGHT || targetX < 0 || targetX >= FIELD_WIDTH) {
					return true;
				}
				if (field[targetY][targetX]) {
					return true;
				}
			}
		}
	}
	return false;
}

void resetMino() {
	minoX = FIELD_WIDTH / 2 - MINO_WIDTH / 2;;
	minoY = 0;

	//次のミノを現在のミノにする
	minoType = nextMinoType;
	minoAngle = nextMinoAngle;

	//次のミノをワンダムで生成する
	nextMinoType = rand() % MINO_TYPE_MAX;
	nextMinoAngle = rand() % MINO_ANGLE_MAX;

	//15%の確率で特殊ブロックをNEXTにセット、それ以外は通常
	if (rand() % 100 < 15) {nextMinoType = MINO_TYPE_BOMB;
	}
	else {nextMinoType = rand() % (MINO_TYPE_MAX - 1);
	}
	nextMinoAngle = rand() % MINO_ANGLE_MAX;
}