//#include "Enemy.h"
//#include "Engine/Model.h"
//#include "Engine/Input.h"
//#include "Engine/CsvReader.h"
//#include "Stage.h"
//
//static const unsigned int MAP_ROW = 15; //縦
//static const unsigned int MAP_COL = 20; //横
//static const unsigned int MAX_COSTS = 9999; //最大コスト
//
//static const Enemy::DIRECTION DIRECTIONS[] = {
//                                     {  0, -1 },		// L
//                                     {  0, +1 },		// R
//                                     { -1,  0 },		// U
//                                     { +1,  0 }		// D
//};
//
//
//
////コンストラクタ
//Enemy::Enemy(GameObject* parent)
//    :GameObject(parent, "Enemy"), hModel_(-1)
//{
//}
//
////デストラクタ
//Enemy::~Enemy()
//{
//}
//
////初期化
//void Enemy::Initialize()
//{
//    pStage = (Stage*)FindObject("Stage");
//    assert(pStage != nullptr);
//    pPlayer = (Player*)FindObject("Player");
//    assert(pPlayer != nullptr);
//
//    //モデルデータのロード
//    hModel_ = Model::Load("Enemy.fbx");
//    assert(hModel_ >= 0);
//    transform_.position_ = XMFLOAT3(pStage->GetX() + 0.5, 0, (pStage->GetY() + 0.5));
//    transform_.position_ = XMFLOAT3(3, 0, 3);
//
//    playerPos = pPlayer->GetPosition();
//
//    CsvReader csv;
//    csv.Load("map.csv");
//
//    for (int x = 0; x < MAP_COL; x++)
//    {
//        //for (int z = 15; z > 0; z--)
//        for (int z = 0; z < MAP_ROW; z++)
//        {
//
//            map_[x][z] = csv.GetValue(x, z);
//        }
//    }
//
//    goalCellY = (int)playerPos.z;
//    goalCellX = (int)playerPos.x;
//
//    CELL startCell = { (int)transform_.position_.y,(int)transform_.position_.x };		// スタート地点 [Y,X]??????
//    CELL goalCell = { goalCellY, goalCellX };			//ゴール地点
//    Init(startCell);
//    CalcCosts(startCell);
//    Show();
//
//    map_[goalCellY][goalCellX] = 2;
//}
//
////更新
//void Enemy::Update()
//{
//    playerPos = pPlayer->GetPosition();
//
//    goalCellY = (int)playerPos.z;
//    goalCellX = (int)playerPos.x;
//
//    //前回の位置ベクトルになるやつ？
//    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);
//
//
//    //右移動
//    if (Input::IsKey(DIK_RIGHT))
//    {
//        transform_.position_.x += 0.1;
//        //斜め移動があるからこれは使えない
//        //transform_.rotate_.y = 90.0f;
//    }
//    //左移動
//    if (Input::IsKey(DIK_LEFT))
//    {
//        transform_.position_.x -= 0.1;
//    }
//    //上移動
//    if (Input::IsKey(DIK_UP))
//    {
//        transform_.position_.z += 0.1;
//    }
//    //下移動
//    if (Input::IsKey(DIK_DOWN))
//    {
//        transform_.position_.z -= 0.1;
//    }
//
//    //現在の位置ベクトル
//    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);
//
//    //今回の移動ベクトル
//    XMVECTOR move = nowPosition - prevPosition;
//
//    //移動ベクトルの長さを測る
//    XMVECTOR length = XMVector3Length(move);
//
//    //0.07以上移動してたなら回転処理
//    if (XMVectorGetX(length) > 0.1f)
//    {
//        //角度を求めるために長さを１にする（正規化）
//        move = XMVector3Normalize(move);
//
//        //基準となる奥向きのベクトル
//        XMVECTOR froat = { 0,0,1,0 };
//
//        //角度を求めるために長さを１にする（正規化）
//        move = XMVector3Normalize(move);
//
//        //基準となる奥向きのベクトル
//        XMVECTOR front = { 0,0,1,0 };
//
//        //frontとmoveの内積を求める
//        XMVECTOR vecDot = XMVector3Dot(front, move);
//        float dot = XMVectorGetX(vecDot);
//
//        //向いてる角度を求める（ラジアン）
//        float angle = acos(dot);
//
//        //frontとmoveの外積を求める
//        XMVECTOR cross = XMVector3Cross(front, move);
//
//        //外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
//        if (XMVectorGetY(cross) < 0)
//        {
//            angle *= -1;
//        }
//
//        //その求めた角度分回転させる
//        transform_.rotate_.y = angle * 180.0f / 3.14f;
//    }
//
//
//    //壁との衝突判定
//    int checkX, checkZ;
//
//    //右
//    checkX = (int)(transform_.position_.x + 0.3f);
//    checkZ = (int)transform_.position_.z;
//    if (pStage->IsWall(checkX, checkZ))
//    {
//        //XMStoreFloat3(&transform_.position_ ,prevPosition);
//        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) - 0.3f);
//    }
//
//    //左
//    checkX = (int)(transform_.position_.x - 0.3f);
//    checkZ = (int)transform_.position_.z;
//    if (pStage->IsWall(checkX, checkZ))
//    {
//        //XMStoreFloat3(&transform_.position_, prevPosition);
//        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) + 0.3f);
//    }
//
//    //上
//    checkX = (int)transform_.position_.x;
//    checkZ = (int)(transform_.position_.z + 0.3);
//    if (pStage->IsWall(checkX, checkZ))
//    {
//        //XMStoreFloat3(&transform_.position_, prevPosition);
//        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) - 0.3f);
//    }
//
//    //下
//    checkX = (int)transform_.position_.x;
//    checkZ = (int)(transform_.position_.z - 0.3);
//    if (pStage->IsWall(checkX, checkZ))
//    {
//        //XMStoreFloat3(&transform_.position_, prevPosition);
//        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) + 0.3f);
//    }
//
//    /*if (pStage->IsWall((int)transform_.position_.x,(int)transform_.position_.z ))
//    {
//        XMStoreFloat3(&transform_.position_, prevPosition);
//    }*/
//
//    //内積は鋭角だから右に移動しても左に移動しても左を向いている
//    //→どうする？
//
//
//}
//
////描画
//void Enemy::Draw()
//{
//    Model::SetTransform(hModel_, transform_);
//    Model::Draw(hModel_);
//}
//
////開放
//void Enemy::Release()
//{
//}
//
//
//
////自分の場所以外最大コストにする
//void Enemy::Init(CELL startCell)
//{
//    for (int row = 0; row < MAP_ROW; row++)
//    {
//        for (int col = 0; col < MAP_COL; col++)
//        {
//            totalCosts[row][col] = MAX_COSTS;
//        }
//    }
//
//    totalCosts[startCell.row][startCell.col] = 0;
//}
//
////次の場所に行くときの合計コスト計算
//void Enemy::CalcCosts(CELL cell)
//{
//    for (DIRECTION dir : DIRECTIONS)
//    {
//        int nextRow = cell.row + dir.dirRow;
//        int nextCol = cell.col + dir.dirCol;
//
//        if (COSTMAP[nextRow][nextCol] < 0)
//        {
//            continue;
//        }
//
//        if (totalCosts[nextRow][nextCol] > totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol])
//        {
//            totalCosts[nextRow][nextCol] = totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol];
//
//            CalcCosts({ nextRow, nextCol });
//        }
//    }
//}
//
////最短距離表示
//void Enemy::Show()
//{
//    for (int row = 0; row < MAP_ROW; row++)
//    {
//
//        for (int col = 0; col < MAP_COL; col++)
//        {
//            /*int a = 0;
//            a = col;*/
//            if (goalCellY == row && goalCellX == col)
//            {
//                move.push_back(std::make_pair(goalCellY, goalCellX));
//                COSTMAP[goalCellY][goalCellX] = -2;
//                //cout << setw(3) << "g" << totalCosts[row][col] << "|";
//                for (DIRECTION dir : DIRECTIONS)
//                {
//                    int nextRow = row + dir.dirRow;//10 + ? 0
//                    int nextCol = col + dir.dirCol;//11 + ? -1
//                    if (totalCosts[row][col] > totalCosts[nextRow][nextCol])
//                    {
//                        goalCellY = nextRow;
//                        goalCellX = nextCol;
//                    }
//                }
//            }
//            else
//            {
//                //cout << setw(4) << totalCosts[row][col] << "|";
//
//            }
//        }
//        //cout << "\n";
//    }
//
//}
