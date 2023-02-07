//#pragma once
//#include "Engine/GameObject.h"
//#include"Stage.h"
//#include "Player.h"
//
////◆◆◆を管理するクラス
//class Enemy : public GameObject
//{
//    // スタート地点からの最小コスト値をいれてくやつ		初期化で全部9999
//    int totalCosts[15][20];
//    int hModel_;    //モデル番号
//    int map_[20][15] = {0};
//    int mapCost_[20][15] = { 0 };
//    int goalCellY;
//    int goalCellX;
//
//    Player* pPlayer;
//    Stage* pStage;
//    XMFLOAT3 playerPos;
//
//    std::list<std::pair<int, int>> move;
//public:
//    typedef struct tagCell {
//        int row = 0;//Y
//        int col = 0;//X
//    }CELL;
//
//
//    typedef struct tagDirection {
//        int dirRow = 0;
//        int dirCol = 0;
//    }DIRECTION;
//
//    //コンストラクタ
//    Enemy(GameObject* parent);
//
//    //デストラクタ
//    ~Enemy();
//
//    //初期化
//    void Initialize() override;
//
//    //更新
//    void Update() override;
//
//    //描画
//    void Draw() override;
//
//    //開放
//    void Release() override;
//
//    
//    //自分の場所以外最大コストにする
//    void Init(CELL startCell);
//
//    //次の場所に行くときの合計コスト計算
//    void CalcCosts(CELL cell);
//
//    //最短距離表示
//    void Show();
//};