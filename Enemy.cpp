//#include "Enemy.h"
//#include "Engine/Model.h"
//#include "Engine/Input.h"
//#include "Engine/CsvReader.h"
//#include "Stage.h"
//
//static const unsigned int MAP_ROW = 15; //�c
//static const unsigned int MAP_COL = 20; //��
//static const unsigned int MAX_COSTS = 9999; //�ő�R�X�g
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
////�R���X�g���N�^
//Enemy::Enemy(GameObject* parent)
//    :GameObject(parent, "Enemy"), hModel_(-1)
//{
//}
//
////�f�X�g���N�^
//Enemy::~Enemy()
//{
//}
//
////������
//void Enemy::Initialize()
//{
//    pStage = (Stage*)FindObject("Stage");
//    assert(pStage != nullptr);
//    pPlayer = (Player*)FindObject("Player");
//    assert(pPlayer != nullptr);
//
//    //���f���f�[�^�̃��[�h
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
//    CELL startCell = { (int)transform_.position_.y,(int)transform_.position_.x };		// �X�^�[�g�n�_ [Y,X]??????
//    CELL goalCell = { goalCellY, goalCellX };			//�S�[���n�_
//    Init(startCell);
//    CalcCosts(startCell);
//    Show();
//
//    map_[goalCellY][goalCellX] = 2;
//}
//
////�X�V
//void Enemy::Update()
//{
//    playerPos = pPlayer->GetPosition();
//
//    goalCellY = (int)playerPos.z;
//    goalCellX = (int)playerPos.x;
//
//    //�O��̈ʒu�x�N�g���ɂȂ��H
//    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);
//
//
//    //�E�ړ�
//    if (Input::IsKey(DIK_RIGHT))
//    {
//        transform_.position_.x += 0.1;
//        //�΂߈ړ������邩�炱��͎g���Ȃ�
//        //transform_.rotate_.y = 90.0f;
//    }
//    //���ړ�
//    if (Input::IsKey(DIK_LEFT))
//    {
//        transform_.position_.x -= 0.1;
//    }
//    //��ړ�
//    if (Input::IsKey(DIK_UP))
//    {
//        transform_.position_.z += 0.1;
//    }
//    //���ړ�
//    if (Input::IsKey(DIK_DOWN))
//    {
//        transform_.position_.z -= 0.1;
//    }
//
//    //���݂̈ʒu�x�N�g��
//    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);
//
//    //����̈ړ��x�N�g��
//    XMVECTOR move = nowPosition - prevPosition;
//
//    //�ړ��x�N�g���̒����𑪂�
//    XMVECTOR length = XMVector3Length(move);
//
//    //0.07�ȏ�ړ����Ă��Ȃ��]����
//    if (XMVectorGetX(length) > 0.1f)
//    {
//        //�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
//        move = XMVector3Normalize(move);
//
//        //��ƂȂ鉜�����̃x�N�g��
//        XMVECTOR froat = { 0,0,1,0 };
//
//        //�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
//        move = XMVector3Normalize(move);
//
//        //��ƂȂ鉜�����̃x�N�g��
//        XMVECTOR front = { 0,0,1,0 };
//
//        //front��move�̓��ς����߂�
//        XMVECTOR vecDot = XMVector3Dot(front, move);
//        float dot = XMVectorGetX(vecDot);
//
//        //�����Ă�p�x�����߂�i���W�A���j
//        float angle = acos(dot);
//
//        //front��move�̊O�ς����߂�
//        XMVECTOR cross = XMVector3Cross(front, move);
//
//        //�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
//        if (XMVectorGetY(cross) < 0)
//        {
//            angle *= -1;
//        }
//
//        //���̋��߂��p�x����]������
//        transform_.rotate_.y = angle * 180.0f / 3.14f;
//    }
//
//
//    //�ǂƂ̏Փ˔���
//    int checkX, checkZ;
//
//    //�E
//    checkX = (int)(transform_.position_.x + 0.3f);
//    checkZ = (int)transform_.position_.z;
//    if (pStage->IsWall(checkX, checkZ))
//    {
//        //XMStoreFloat3(&transform_.position_ ,prevPosition);
//        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) - 0.3f);
//    }
//
//    //��
//    checkX = (int)(transform_.position_.x - 0.3f);
//    checkZ = (int)transform_.position_.z;
//    if (pStage->IsWall(checkX, checkZ))
//    {
//        //XMStoreFloat3(&transform_.position_, prevPosition);
//        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) + 0.3f);
//    }
//
//    //��
//    checkX = (int)transform_.position_.x;
//    checkZ = (int)(transform_.position_.z + 0.3);
//    if (pStage->IsWall(checkX, checkZ))
//    {
//        //XMStoreFloat3(&transform_.position_, prevPosition);
//        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) - 0.3f);
//    }
//
//    //��
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
//    //���ς͉s�p������E�Ɉړ����Ă����Ɉړ����Ă����������Ă���
//    //���ǂ�����H
//
//
//}
//
////�`��
//void Enemy::Draw()
//{
//    Model::SetTransform(hModel_, transform_);
//    Model::Draw(hModel_);
//}
//
////�J��
//void Enemy::Release()
//{
//}
//
//
//
////�����̏ꏊ�ȊO�ő�R�X�g�ɂ���
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
////���̏ꏊ�ɍs���Ƃ��̍��v�R�X�g�v�Z
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
////�ŒZ�����\��
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
