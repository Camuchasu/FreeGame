#include "Map.h"
#include"Game/GameData.h"
#include"Game/Enemy.h"
#include"Game/Enemy1.h"
#include"Game/Enemy2.h"
#include"Game/Enemy3.h"
#include"Game/Enemy4.h"
#include"Game/Enemy5.h"
//#include"Game/Enemy6.h"
//#include"Game/Enemy7.h"
#include"Game/BossEnemy.h"
#include"Game/Player.h"
#include"Game/TP.h"
#include "Item.h"
#include "Menyu.h"
static int stage1data[MAP_HEIGHT][MAP_WIDTH] = {
    {5,7,7,7,7,7,7,7,7,7,7,7,7,7,7,5,5,5,5,5,5,5,5,5},//1
    {5,1,1,1,1,1,1,2,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5},//2
    {5,1,1,1,1,1,1,5,5,7,7,7,7,7,2,7,7,7,7,7,7,7,7,5},//3
    {5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//4
    {5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//5
    {5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//6
    {5,5,6,2,5,5,5,5,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//7
    {5,5,6,2,5,5,5,5,5,2,7,7,7,7,7,7,7,7,7,7,7,7,7,5},//8
    {5,5,6,2,5,5,5,5,5,2,2,2,2,2,2,1,1,1,1,1,1,1,1,5},//9
    {5,7,7,2,7,7,7,7,7,7,5,5,5,5,5,1,1,1,1,1,1,1,1,5},//10
    {5,1,1,1,1,1,1,1,1,1,7,7,7,7,7,1,1,1,1,1,1,1,1,5},//11
    {5,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,5},//12
    {5,1,1,1,1,1,1,1,1,1,7,7,7,7,7,1,1,1,1,1,1,1,1,5},//13
    {5,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,5},//14
    {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},//15
};
static int stage2data[MAP_HEIGHT][MAP_WIDTH] = {
    {5,7,7,7,7,7,7,7,5,7,7,7,7,7,7,7,7,7,7,7,7,7,7,5},//1
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,2,1,1,1,1,1,1,1,5},//2
    {5,1,1,1,1,1,1,1,7,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5},//3
    {5,1,1,1,1,1,1,1,2,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5},//4
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5},//5
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,7,7,7,7,7,7,7,2,5},//6
    {5,2,7,7,7,7,7,7,5,1,1,1,1,1,1,2,2,2,2,2,2,2,2,5},//7
    {5,2,2,2,2,2,2,2,5,1,1,1,1,1,1,5,5,5,5,5,5,5,2,5},//8
    {5,7,7,7,7,7,7,2,5,7,7,2,7,7,7,5,5,7,7,7,7,7,2,5},//9
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,5},//10
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5,5,1,1,1,1,1,1,5},//11
    {5,1,1,1,1,1,1,1,7,1,1,1,1,1,1,5,5,1,1,1,1,1,1,5},//12
    {5,1,1,1,1,1,1,1,2,1,1,1,1,1,1,7,7,1,1,1,1,1,1,5},//13
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,2,2,1,1,1,1,1,1,5},//14
    {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},//15
};
static int stage3data[MAP_HEIGHT][MAP_WIDTH] = {
    {5,7,7,7,7,7,7,7,5,7,7,7,7,7,7,7,5,7,7,7,7,7,7,5},//1
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5},//2
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5},//3
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5},//4
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5},//5
    {5,2,7,7,7,7,7,7,7,7,7,7,2,7,7,7,7,7,7,7,7,7,2,5},//6
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//7
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//8
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//9
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//10
    {5,2,7,7,7,7,7,7,5,7,7,7,2,7,7,7,5,7,7,7,7,7,2,5},//11
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5},//12
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5},//13
    {5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,5,1,1,1,1,1,1,5},//14
    {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},//15
};
static int stage4data[MAP_HEIGHT][MAP_WIDTH] = {
    {5,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,5},//1
    {5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5},//2
    {5,2,5,7,7,2,7,7,7,7,5,7,7,7,7,7,7,2,7,7,7,5,2,5},//3
    {5,2,5,1,1,1,1,1,1,1,5,2,2,1,1,1,1,1,1,1,1,7,2,5},//4
    {5,2,7,1,1,1,1,1,1,1,5,2,5,1,1,1,1,1,1,1,1,2,2,5},//5
    {5,2,2,1,1,1,1,1,1,1,7,2,5,1,1,1,1,1,1,1,1,5,2,5},//6
    {5,2,5,1,1,1,1,1,1,1,2,2,5,1,1,1,1,1,1,1,1,5,2,5},//7
    {5,2,5,2,7,7,7,7,7,7,7,7,7,7,7,2,7,7,7,7,7,5,2,5},//8
    {5,2,5,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,5,2,5},//9
    {5,2,5,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,7,2,5},//10
    {5,2,5,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,2,2,5},//11
    {5,2,5,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,5,2,5},//12
    {5,2,7,7,7,7,2,7,7,7,7,7,7,7,7,2,7,7,7,7,7,7,2,5},//13
    {5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5},//14
    {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},//15
};
static int stage5data[MAP_HEIGHT][MAP_WIDTH] = {
    {5,5,5,5,5,5,5,5,5,5,5,7,5,5,5,5,5,5,5,5,5,5,5,5},//1
    {5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5},//2
    {5,7,7,7,7,7,7,7,7,7,7,1,7,7,7,7,7,7,7,7,7,7,7,5},//3
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//4
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//5
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//6
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//7
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//8
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//9
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//10
    {5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5},//11
    {5,5,5,5,5,5,5,5,5,1,1,1,1,1,5,5,5,5,5,5,5,5,5,5},//12
    {5,5,5,5,5,5,5,5,5,5,1,1,1,5,5,5,5,5,5,5,5,5,5,5},//13
    {5,5,5,5,5,5,5,5,5,5,5,1,5,5,5,5,5,5,5,5,5,5,5,5},//14
    {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7},//15
};

CVector2D Map::seisei(CELL* outcell)
{
    while (true)
    {
        int x = rand() % 14;
        int y = rand() % 14;
        int t = GetTip(x, y);

        int obj = GetObj(x, y);

        //床か壁かを判定する
        if (t == 1 && obj == -1) {
            if (outcell != nullptr) {
                outcell->x = x;
                outcell->y = y;
            }
          
          return(CVector2D(x * MAP_TIP_SIZE + 50+rand()%6-3, y * MAP_TIP_SIZE + 50 + rand() % 6 - 3));
            break;
        }
    }
    return CVector2D();
}
Map::Map(int stageNunber) :Base(eType_Map)
{
    //画像の複製;
    m_img = COPY_RESOURCE("Map_Tip1", CImage);
    m_img.mp_texture->SetFilter(GL_NEAREST);
    Base* b = Base::FindObject(eType_Player);
    Item* item = dynamic_cast<Item*>(Base::FindObject(eType_Item));

    switch (stageNunber) {
    case 1:
        memcpy(stage, stage1data, sizeof(stage1data));
        break;
    case 2:
        memcpy(stage, stage2data, sizeof(stage2data));
        break;
    case 3:
        memcpy(stage, stage3data, sizeof(stage3data));
        break;
    case 4:
        memcpy(stage, stage4data, sizeof(stage4data));
        break;
    case 5:
        memcpy(stage, stage5data, sizeof(stage5data));
        Base::Add(new BossEnemy(CVector2D(1150, 300), true));
        /*Base::Add(new Enemy(seisei(), true));
        Base::Add(new Enemy3(seisei(), true));
        Base::Add(new Enemy4(seisei(), true));
        Base::Add(new Enemy5(seisei(), true));
        Base::Add(new Enemy1(seisei(), true));
        //ステージのランダム
        break;*/
    }
    //TPの生成
    if (stageNunber < 5) {
        CELL cell;
        Base::Add(new Tp(seisei(&cell)));
        AddObj(cell.x, cell.y, eType_TP);
    }
   
    //プレイヤーの生成位置
    if (stageNunber < 5) {
        CELL cell;
        b->m_pos = seisei(&cell);
        b->m_pos_old = b->m_pos;
        AddObj(cell.x, cell.y, eType_Player);
    }
    else {
        b->m_pos = CVector2D(1160, 1350);
        b->m_pos_old = b->m_pos;
    }
    //アイテムの生成位置
    if (stageNunber < 5) {
        // item->m_pos = ItemManeger();
    }
    //敵の生成//敵が重なる場合があるため一時コメント化
    //for (int i = 1; i <= 3; i++) {
       // Base::Add(new Enemy(seisei(), true));
      //  Base::Add(new Enemy1(seisei(), true));
  //  }
    m_stageNunber = stageNunber;
    //m_Map_Tip = 900;

}

void Map::Draw()
{
    if (Menyu* menyu = dynamic_cast<Menyu*>(Base::FindObject(eType_Menyu))) {
        if (menyu->hyouzi == 0) {//メニューの表示が０であれば、敵の生成をする
            cnt++;
            if (cnt >= 60 * 5) {
                switch (m_stageNunber) {
                case 1:
                    Base::Add(new Enemy(seisei(), true));
                    Base::Add(new Enemy5(seisei(), true));
                    Base::Add(new Enemy4(seisei(), true));
                    break;
                case 2:
                    Base::Add(new Enemy1(seisei(), true));
                    Base::Add(new Enemy4(seisei(), true));
                    break;
                case 3:
                    Base::Add(new Enemy5(seisei(), true));
                    Base::Add(new Enemy1(seisei(), true));

                    break;
                case 4:
                    Base::Add(new Enemy3(seisei(), true));
                    Base::Add(new Enemy(seisei(), true));
                    Base::Add(new Enemy1(seisei(), true));
                    break;

                case 5:
                    //Base::Add(new BossEnemy(CVector2D(1150, 300), true));
                    Base::Add(new Enemy(seisei(), true));
                    Base::Add(new Enemy3(seisei(), true));
                    Base::Add(new Enemy4(seisei(), true));
                    Base::Add(new Enemy5(seisei(), true));
                    Base::Add(new Enemy1(seisei(), true));
                    break;
                }
                cnt = 0;

            }
        }
    }
    //m_background.Draw();
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            //表示させない [i]行 [j]列
            if (stage[i][j] == 0)continue;
            int t = stage[i][j];
            //切り抜き    //左　  //ue  //migi       //sita
            m_img.SetRect(30 * t,  0,  30 * t+30,  30);
            //サイズ
            m_img.SetSize(MAP_TIP_SIZE, MAP_TIP_SIZE);


            //位置設定
            m_img.SetPos(MAP_TIP_SIZE * j - m_scroll.x, MAP_TIP_SIZE * i - m_scroll.y);
            //描画
            m_img.Draw();
        }
    }

}


int Map::GetTip(const CVector2D& pos, int* tx, int* ty)
{
    //列を計算
    int x = pos.x / MAP_TIP_SIZE;
    //列の制限
    if (x < 0) x = 0;
    if (x > MAP_WIDTH - 1) x = MAP_WIDTH - 1;
    //行を計算
    int y = pos.y / MAP_TIP_SIZE;
    //行の制限
    if (y < 0) y = 0;
    if (y > MAP_HEIGHT - 1) y = MAP_HEIGHT - 1;
    //行と列の出力
    if (ty) *ty = y * MAP_TIP_SIZE;
    if (tx) *tx = x * MAP_TIP_SIZE;
    //チップデータを返却
    return stage[y][x];
}
int Map::GetTip(int x, int y)
{
    return stage[y][x];

}

void Map::AddObj(int x, int y, int type)
{
    MapObjData data;
    data.cell.x = x;
    data.cell.y = y;
    data.type = type;
    m_ObjList.push_back(data);
}

int Map::GetObj(int x, int y)
{
    for (MapObjData& data : m_ObjList) {
        if (data.cell.x == x && data.cell.y == y) {
            return data.type;
        }
    }
    return -1;
}

int Map::CollisionPoint(const CVector2D& pos)
{


    //1点のみ検証
    int t = GetTip(pos);
    if (t != 0)return 1;
    return 0;
}

int Map::CollisionRect(const CVector2D& pos, const CRect& rect)
{
    CRect r = CRect(
        pos.x + rect.m_left,
        pos.y + rect.m_top,
        pos.x + rect.m_right,
        pos.y + rect.m_bottom);
    int t;
    t = GetTip(CVector2D(r.m_left, r.m_top));
    if (t >= 5) return t;
    t = GetTip(CVector2D(r.m_right, r.m_top));
    if (t >= 5) return t;
    t = GetTip(CVector2D(r.m_left, r.m_bottom));
    if (t >= 5) return t;
    t = GetTip(CVector2D(r.m_right, r.m_bottom));
    if (t >= 5) return t;
    return 0;
}
bool Map::CalcRoot(const CELL pos, const CELL& end, int step, int step_data[MAP_HEIGHT][MAP_WIDTH], RootData& root)
{
    //マップ外は無視
    if (pos.x < 0 || pos.x >= MAP_WIDTH || pos.y < 0 || pos.y >= MAP_HEIGHT) return false;

    //壁は無視
    if (GetTip(pos.x, pos.y) >= 5) return false;

    //既に近道がある
    if (step >= step_data[pos.y][pos.x]) return false;

    //経路更新
    step_data[pos.y][pos.x] = step;

    //目的地に到着
    if (pos == end) {
        root.size = min(root.size, step + 1);
        root.root[step] = pos;
        return true;
    }


    //周りのマスを調べる（上下左右の４方向）
    bool f = false;
    CELL dir[4] = {
        {1,0},  //→
        {0,1},  //↓
        {-1,0}, //←
        {0,-1}, //上
    };

    for (int i = 0; i < 4; i++) {
        if (CalcRoot(pos + dir[i], end, step + 1, step_data, root))
            f = true;
    }
    if (f) {
        root.root[step] = pos;
    }
    return f;
}

RootData Map::CalcRoot(const CVector2D& start, const CVector2D& end)
{

    RootData root;
    //移動量格納
    int step_data[MAP_HEIGHT][MAP_WIDTH];
    //一旦最大距離で初期化(最大25ステップまで)
    const int max_step = 25;
    root.root.resize(max_step);
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            step_data[i][j] = max_step;

    int step = 0;
    CELL s = GetCell(start);
    CELL e = GetCell(end);
    if (CalcRoot(s, e, step, step_data, root)) {
        //余剰分の経路データを削除
        if (root.root.size() > root.size)
            root.root.erase(root.root.begin() + root.size, root.root.end());
        //経路発見フラグON
        root.isFound = true;
    }
    return root;
}

CELL Map::GetCell(const CVector2D& pos)
{
    CELL c;
    //列を計算
    c.x = pos.x / MAP_TIP_SIZE;
    //列の制限
    if (c.x < 0) c.x = 0;
    if (c.x > MAP_WIDTH - 1) c.x = MAP_WIDTH - 1;
    //行を計算
    c.y = pos.y / MAP_TIP_SIZE;
    //行の制限
    if (c.y < 0) c.y = 0;
    if (c.y > MAP_HEIGHT - 1) c.y = MAP_HEIGHT - 1;
    return c;
}
//Boss stage