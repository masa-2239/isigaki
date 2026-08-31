#include "StartScreen.h"
#include <iostream>
#include <conio.h>

// コンストラクタの実装
StartScreen::StartScreen() {
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    flashCount = 0;
}

// 固定UIの描画
void StartScreen::drawStaticUI() {
    system("cls");

    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    std::cout << "========================================" << std::endl;
    std::cout << "                                        " << std::endl;
    std::cout << "   ########   ######     ##    ##    ## " << std::endl;
    std::cout << "      ##     ##          ##    ##    ## " << std::endl;
    std::cout << "      ##      ######     ##    ######## " << std::endl;
    std::cout << "      ##           ##    ##    ##    ## " << std::endl;
    std::cout << "   ########   ######     ##    ##    ## " << std::endl;
    std::cout << "                                        " << std::endl;
    std::cout << "   ######      ####     #######  ##     " << std::endl;
    std::cout << "   ##    ##   ##  ##         ##  ##     " << std::endl;
    std::cout << "   ######    ########     ###    ##     " << std::endl;
    std::cout << "   ##        ##    ##   ##       ##     " << std::endl;
    std::cout << "   ##        ##    ##   #######  ###### " << std::endl;
    std::cout << "                                        " << std::endl;
    std::cout << "============= BOMB EDITION =============" << std::endl;
    std::cout << "                                        " << std::endl;


    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "  [操作方法]" << std::endl;
    std::cout << "                                        " << std::endl;
    std::cout << "  A : 左移動    D : 右移動    S : 下移動" << std::endl;
    std::cout << "                                        " << std::endl;
    std::cout << "  L : 右回転    K : 左回転" << std::endl;
    std::cout << "  " << std::endl;
    std::cout << "  ※ 15%の確率で周囲を破壊する ● (ボム) が出現！" << std::endl;
    std::cout << "                                        " << std::endl;
    std::cout << "========================================" << std::endl;
}

// 点滅プロンプトの描画
void StartScreen::drawBlinkingPrompt() {
    COORD coord = { 0, 28 };
    SetConsoleCursorPosition(handle, coord);

    if (flashCount % 2 == 0) {
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        std::cout << "    >>> PRESS ENTER TO START <<<     " << std::endl;
    }
    else {
        std::cout << "                                     " << std::endl;
    }
}

// スタート画面の実行ループ
void StartScreen::show() {
    drawStaticUI();

    while (1) {
        drawBlinkingPrompt();

        if (_kbhit()) {
            if (_getch() == 13) { // Enterキー
                break;
            }
        }

        Sleep(400);
        flashCount++;
    }

    system("cls");
}
