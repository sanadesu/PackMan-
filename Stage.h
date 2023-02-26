#pragma once
#include "Engine/GameObject.h"
#include <iostream>
#include<vector>

enum Enemy
{
    RED = 0,
    PINK,
    ORANGE,
    BLUE,
    ENEMY_MAX
};

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    static const unsigned int MAP_ROW = 15; //縦
    static const unsigned int MAP_COL = 20; //横
    static  const unsigned int MAX_COSTS = 9999; //最大コスト

    int COSTMAP[MAP_ROW][MAP_COL] = {//[Y,X]?????
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1,  1,  1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1, -1, -1,  1, -1, -1,  1,  1,  1, -1,  1, -1, -1, -1,  1, -1, -1,  1, -1 },
    { -1,  1,  1,  1,  1,  1, -1,  1, -1, -1, -1,  1, -1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1, -1, -1, -1,  1, -1,  1,  1,  1,  1,  1, -1,  1, -1,  1, -1, -1,  1, -1 },
    { -1,  1,  1,  1, -1,  1, -1,  1, -1, -1, -1,  1, -1,  1, -1,  1,  1,  1,  1, -1 },
    { -1, -1, -1,  1,  1,  1,  1,  1, -1,  1, -1,  1,  1,  1, -1,  1,  1, -1,  1, -1 },
    { -1,  1,  1,  1,  1, -1, -1,  1, -1,  1,  1,  1,  1, -1, -1,  1,  1, -1,  1, -1 },
    { -1,  1, -1, -1,  1,  1,  1,  1, -1,  1, -1,  1,  1,  1, -1,  1, -1, -1,  1, -1 },
    { -1,  1,  1, -1,  1, -1, -1,  1, -1, -1, -1,  1, -1,  1, -1,  1,  1,  1,  1, -1 },
    { -1, -1,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  1, -1, -1, -1, -1 },
    { -1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1, -1, -1, -1,  1,  1,  1,  1, -1,  1,  1,  1,  1, -1, -1, -1, -1,  1, -1 },
    { -1,  1,  1,  1,  1,  1, -1, -1,  1,  1,  1, -1, -1,  1,  1,  1,  1,  1,  1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
    };

    // スタート地点からの最小コスト値をいれてくやつ		初期化で全部9999
    int totalCosts[MAP_ROW][MAP_COL];

    int hModel_[ENEMY_MAX];    //モデル番号
    int map_[20][15];

    int startCellX[ENEMY_MAX] = {0,0,0,0};
    int startCellY[ENEMY_MAX] = {0,0,0,0};
    int goalCellX[ENEMY_MAX] = { 9,9,9,10};//敵の位置x
    int goalCellY[ENEMY_MAX] = { 8,7,6,7 };//敵の位置y
    XMFLOAT3 enemyPos[ENEMY_MAX];

    /*int goalCellX[3] = { 1,9,18 };
    int goalCellY[3] = { 1,7,13 };*/

    int time = 0;
    bool flag = false;

    std::list<std::pair<int, int>> move;
    std::pair<int, int> nextMove[ENEMY_MAX];

    std::pair<int, int> min[ENEMY_MAX];

    std::list<std::pair<int, int>> minCost[ENEMY_MAX];
    std::list<std::pair<int, int>> nowCost[ENEMY_MAX];
    std::vector<std::vector<std::pair<int, int>>> data;

    
public:
    std::pair<int, int> MapStart[ENEMY_MAX];
    std::pair<int, int> MapGoal[ENEMY_MAX];

    typedef struct tagCell {
        int row;
        int col;
    }CELL;


    typedef struct tagDirection {
        int dirRow;
        int dirCol;
    }DIRECTION;

    struct cMap {
        std::pair<int, int> prevNode = { -1, -1 };
        bool done = false;//確定ノードかどうか
        int map;//マップ
        int cost;//最小コスト     //first   ROW
        //second  COL
        std::pair<int, int> cel;

    }CostMap[MAP_ROW][MAP_COL];


    CELL startCell[ENEMY_MAX] = { startCellY[RED],startCellX[RED], startCellY[PINK],startCellX[PINK], startCellY[ORANGE],startCellX[ORANGE], startCellY[BLUE],startCellX[BLUE]};		// スタート地点 [Y,X]??????
    CELL goalCell;

    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //かべ
    bool IsWall(int x, int z);

    //自分の場所以外最大コストにする
    void Init(CELL startCell);

    //次の場所に行くときの合計コスト計算
    void CalcCosts(CELL cell);

    //最短距離表示
    void Show();

    //プレイヤークラスで使ったゲッター。スタート位置。
    int GetX(int ID);
    int GetY(int ID);

    void SetStartCellX(int X);
    void SetStartCellY(int Y);

    void SetGoalCellX(int X, int num);
    void SetGoalCellY(int Y, int num);

    std::pair<int, int> GetListPos();

    void Search(std::pair<int, int> node,int ID);

    void InitMap();
    void Dijkstra(cMap cel_, cMap goal,int ID);

    std::pair<int, int> GetNextMovePos(int ID);

    void SetEnemyPos(XMFLOAT3 pos, int enemyID) { enemyPos[enemyID] = pos; }

};