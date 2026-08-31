#pragma once
#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <Windows.h>

class StartScreen {
private:
    HANDLE handle;
    int flashCount;

    // 内部で使用するプライベート関数の宣言
    void drawStaticUI();
    void drawBlinkingPrompt();

public:
    // コンストラクタと公開関数の宣言
    StartScreen();
    void show();
};

#endif // STARTSCREEN_H
