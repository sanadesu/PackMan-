﻿#pragma once
#include "Engine/GameObject.h"
#include <iostream>
#include<vector>

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    static const unsigned int MAP_ROW = 15; //縦
    static const unsigned int MAP_COL = 20; //横
    static  const unsigned int MAX_COSTS = 9999; //最大コスト

    int COSTMAP[MAP_ROW][MAP_COL] = {//[Y,X]?????
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1 },
    { -1,  1, -1, -1, -1, -1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1, -1,  1,  1, -1,  1,  1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1, -1,  1,  1, -1,  1,  1,  1,  1, -1,  1, -1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1, -1,  1,  1, -1,  1,  1,  1,  1, -1,  1, -1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1,  1,  1,  1, -1,  1,  1,  1,  1, -1,  1, -1, -1, -1, -1, -1, -1,  1, -1 },
    { -1,  1,  1,  1,  1, -1,  1,  1,  1,  1, -1,  1, -1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1,  1,  1,  1, -1, -1, -1, -1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1, -1 },
    { -1,  1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1, -1,  1,  1, -1,  1,  1,  1, -1 },
    { -1,  1,  1,  1,  1,  1,  1, -1,  1,  1,  1,  1, -1,  1,  1, -1,  1,  1,  1, -1 },
    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  1,  1,  1, -1 },
    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1,  1,  1,  1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
    };

    // スタート地点からの最小コスト値をいれてくやつ		初期化で全部9999
    int totalCosts[MAP_ROW][MAP_COL];

    int hModel_[3];    //モデル番号
    int map_[20][15];

    int startCellX[3] = {0,0,0};//敵
    int startCellY[3] = {0,0,0};
    int goalCellX = 2;
    int goalCellY = 2;

    int time = 0;
    bool flag = false;

    std::list<std::pair<int, int>> move;
    std::pair<int, int> nextMove[3];

    std::pair<int, int> MapStart;
    std::pair<int, int> MapGoal;
    std::pair<int, int> min;

    std::list<std::pair<int, int>> minCost;
    std::list<std::pair<int, int>> nowCost;
    std::vector<std::vector<std::pair<int, int>>> data;

    enum
    {
        RED = 0,
        PINK,
        CYAN,
        ORANGE
    };
public:

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


    CELL startCell[3] = { startCellY[RED],startCellX[RED], startCellY[PINK],startCellX[PINK], startCellY[ORANGE],startCellX[ORANGE] };		// スタート地点 [Y,X]??????
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
    int GetX();
    int GetY();

    void SetStartCellX(int X, int num);
    void SetStartCellY(int Y,int num);

    void SetGoalCellX(int X);
    void SetGoalCellY(int Y);

    std::pair<int, int> GetListPos();

    void Search(std::pair<int, int> node);

    void InitMap();
    void Dijkstra(cMap cel_, cMap goal);

    std::pair<int, int> GetNextMovePos();
};