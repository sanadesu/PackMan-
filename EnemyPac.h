#pragma once
#include "Engine/GameObject.h"
#include"Stage.h"
#include "Player.h"

//◆◆◆を管理するクラス
class EnemyPac : public GameObject
{
    int hModel_;    //モデル番号
    std::pair<int, int> goalPos[3];

    Player* pPlayer;
    Stage* pStage;
    XMFLOAT3 playerPos;

    std::list<std::pair<int, int>> move;
public:
    
    //コンストラクタ
    EnemyPac(GameObject* parent);

    //デストラクタ
    ~EnemyPac();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    int GetGoalPos(int ID);
};