#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "EnemyPac.h"
//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    //モデルデータのロード
    hModel_ = Model::Load("Enemy.fbx");
    assert(hModel_ >= 0);

    for (int i = 0; i < 3; i++)
    {
        if (playerID == i)
        {
            transform_.position_ = XMFLOAT3(pStage->GetX(i) + 0.5, 0, (pStage->GetY(i) + 0.5));

        }
    }
   
    
    //nextX = pStage->GetListPos().second;

    //nextY = pStage->GetListPos().first;
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.3f, 0), 0.3f);
    AddCollider(collision);

}

//更新
void Player::Update()
{
    //if (start == false)
    {
        start = true;
        EnemyPac* pEnemyPac;
        pEnemyPac = (EnemyPac*)FindObject("EnemyPac");
        assert(pEnemyPac != nullptr);

        nextX[0] = pStage->GetNextMovePos(playerID).second + 0.5f;
        //nextX = pEnemyPac->GetPosition().x;
        nextY[0] = pStage->GetNextMovePos(playerID).first + 0.5f;
        //nextY = pEnemyPac->GetPosition().z;
    }
    //前回の位置ベクトルになるやつ？
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);
    pStage->SetGoalCellX((int)transform_.position_.x);
    pStage->SetGoalCellY((int)transform_.position_.z);
    if ((int)transform_.position_.x == (int)nextX[0] && (int)transform_.position_.z == (int)nextY[0] )
    {
        EnemyPac* pEnemyPac;
        pEnemyPac = (EnemyPac*)FindObject("EnemyPac");
        assert(pEnemyPac != nullptr);

        nextX[0] = pStage->GetNextMovePos(playerID).second + 0.5f;
        //nextX = pEnemyPac->GetPosition().x;
        nextY[0] = pStage->GetNextMovePos(playerID).first + 0.5f;
        //nextY = pEnemyPac->GetPosition().z;
    }
    if (transform_.position_.x < nextX[0])
    {
        transform_.position_.x += 0.1f;
        if (transform_.position_.x >= nextX[0])
            transform_.position_.x = nextX[0];
    }
    else if (transform_.position_.x > nextX[0])
    {
        transform_.position_.x -= 0.1f;
        if(transform_.position_.x < nextX[0])
            transform_.position_.x = nextX[0];
    }
    if (transform_.position_.z < nextY[0])
    {
        transform_.position_.z += 0.1f;
        if (transform_.position_.z > nextY[0])
            transform_.position_.z = nextY[0];
    }
    else if (transform_.position_.z >= nextY[0])
    {
        transform_.position_.z -= 0.1f;
        if (transform_.position_.z < nextY[0])
            transform_.position_.z = nextY[0];
    }

    transform_.position_.x;
    //右移動
    //if (Input::IsKey(DIK_RIGHT))
    //{
    //    transform_.position_.x += 0.1;
    //    //斜め移動があるからこれは使えない
    //    //transform_.rotate_.y = 90.0f;
    //}
    ////左移動
    //if (Input::IsKey(DIK_LEFT))
    //{
    //    transform_.position_.x -= 0.1;
    //}
    ////上移動
    //if (Input::IsKey(DIK_UP))
    //{
    //    transform_.position_.z += 0.1;
    //}
    ////下移動
    //if (Input::IsKey(DIK_DOWN))
    //{
    //    transform_.position_.z -= 0.1;
    //}

    //現在の位置ベクトル
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);
    
    //今回の移動ベクトル
    XMVECTOR move = nowPosition - prevPosition;

    //移動ベクトルの長さを測る
    XMVECTOR length = XMVector3Length(move);

    //0.07以上移動してたなら回転処理
    if (XMVectorGetX(length) > 0.1f)
    {
        //角度を求めるために長さを１にする（正規化）
        move = XMVector3Normalize(move);

        //基準となる奥向きのベクトル
        XMVECTOR froat = { 0,0,1,0 };

        //角度を求めるために長さを１にする（正規化）
        move = XMVector3Normalize(move);

        //基準となる奥向きのベクトル
        XMVECTOR front = { 0,0,1,0 };

        //frontとmoveの内積を求める
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetX(vecDot);

        //向いてる角度を求める（ラジアン）
        float angle = acos(dot);

        //frontとmoveの外積を求める
        XMVECTOR cross = XMVector3Cross(front, move);

        //外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
        if (XMVectorGetY(cross) < 0)
        {
            angle *= -1;
        }

        //その求めた角度分回転させる
        transform_.rotate_.y = angle * 180.0f / 3.14f;
    }


    //壁との衝突判定
    int checkX, checkZ;
    
    //右
    checkX = (int)(transform_.position_.x + 0.3f);
    checkZ = (int)transform_.position_.z;
    if (pStage->IsWall(checkX, checkZ))
    {
        //XMStoreFloat3(&transform_.position_ ,prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) - 0.3f);
    }

    //左
    checkX = (int)(transform_.position_.x - 0.3f);
    checkZ = (int)transform_.position_.z;
    if (pStage->IsWall(checkX, checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) + 0.3f);
    }

    //上
    checkX = (int)transform_.position_.x;
    checkZ = (int)(transform_.position_.z + 0.3);
    if (pStage->IsWall(checkX, checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) - 0.3f);
    }

    //下
    checkX = (int)transform_.position_.x;
    checkZ = (int)(transform_.position_.z - 0.3);
    if (pStage->IsWall(checkX, checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) + 0.3f);
    }

    /*if (pStage->IsWall((int)transform_.position_.x,(int)transform_.position_.z ))
    {
        XMStoreFloat3(&transform_.position_, prevPosition);
    }*/

    //内積は鋭角だから右に移動しても左に移動しても左を向いている
    //→どうする？


}

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //当たったときの処理

    
}

void Player::SetNextX(float x_)
{
    nextX[0] = x_;
}

void Player::SetNextY(float y_)
{
    nextY[0] = y_;
}
