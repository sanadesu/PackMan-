#pragma once
#include "Engine/GameObject.h"
#include"Stage.h"
#include "Engine/SphereCollider.h"
//◆◆◆を管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号
    float nextX[3] = { 0,0,0 };
    float nextY[3] = { 0,0,0 };
    
    bool start = false;
    Stage* pStage;
    
public:
    int playerID;

    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
    //くりあ
    //フロント
    //ポップフロント
    
    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    void SetNextX(float x_);
    void SetNextY(float y_);
};