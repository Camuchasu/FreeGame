#pragma once
class GameData {
public:
    static int stage;//����̓��[�v���邽�߂̃v���O������`
    public:
        //���X�e�[�W�ڂ�
        static int s_score;
        //�c�@�̐�
        static const int Zanki_set;
        //�c�@�̐�
        static int zanki;
        static bool Gametry;
        static bool Gameclear;
        static bool Gameover;
        static bool clear;
        static int kazu;
        GameData() = default;
};

