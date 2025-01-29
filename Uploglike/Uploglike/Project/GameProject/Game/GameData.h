#pragma once
class GameData {
public:
    static int stage;//これはワープするためのプログラム定義
    public:
        //何ステージ目か
        static int s_score;
        //残機の数
        static const int Zanki_set;
        //残機の数
        static int zanki;
        static bool Gametry;
        static bool Gameclear;
        static bool Gameover;
        static bool clear;
        static int kazu;
        GameData() = default;
};

