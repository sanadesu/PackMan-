#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "EnemyPac.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    //���f���f�[�^�̃��[�h
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

//�X�V
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
    //�O��̈ʒu�x�N�g���ɂȂ��H
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
    //�E�ړ�
    //if (Input::IsKey(DIK_RIGHT))
    //{
    //    transform_.position_.x += 0.1;
    //    //�΂߈ړ������邩�炱��͎g���Ȃ�
    //    //transform_.rotate_.y = 90.0f;
    //}
    ////���ړ�
    //if (Input::IsKey(DIK_LEFT))
    //{
    //    transform_.position_.x -= 0.1;
    //}
    ////��ړ�
    //if (Input::IsKey(DIK_UP))
    //{
    //    transform_.position_.z += 0.1;
    //}
    ////���ړ�
    //if (Input::IsKey(DIK_DOWN))
    //{
    //    transform_.position_.z -= 0.1;
    //}

    //���݂̈ʒu�x�N�g��
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);
    
    //����̈ړ��x�N�g��
    XMVECTOR move = nowPosition - prevPosition;

    //�ړ��x�N�g���̒����𑪂�
    XMVECTOR length = XMVector3Length(move);

    //0.07�ȏ�ړ����Ă��Ȃ��]����
    if (XMVectorGetX(length) > 0.1f)
    {
        //�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
        move = XMVector3Normalize(move);

        //��ƂȂ鉜�����̃x�N�g��
        XMVECTOR froat = { 0,0,1,0 };

        //�p�x�����߂邽�߂ɒ������P�ɂ���i���K���j
        move = XMVector3Normalize(move);

        //��ƂȂ鉜�����̃x�N�g��
        XMVECTOR front = { 0,0,1,0 };

        //front��move�̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetX(vecDot);

        //�����Ă�p�x�����߂�i���W�A���j
        float angle = acos(dot);

        //front��move�̊O�ς����߂�
        XMVECTOR cross = XMVector3Cross(front, move);

        //�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
        if (XMVectorGetY(cross) < 0)
        {
            angle *= -1;
        }

        //���̋��߂��p�x����]������
        transform_.rotate_.y = angle * 180.0f / 3.14f;
    }


    //�ǂƂ̏Փ˔���
    int checkX, checkZ;
    
    //�E
    checkX = (int)(transform_.position_.x + 0.3f);
    checkZ = (int)transform_.position_.z;
    if (pStage->IsWall(checkX, checkZ))
    {
        //XMStoreFloat3(&transform_.position_ ,prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) - 0.3f);
    }

    //��
    checkX = (int)(transform_.position_.x - 0.3f);
    checkZ = (int)transform_.position_.z;
    if (pStage->IsWall(checkX, checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f) + 0.3f);
    }

    //��
    checkX = (int)transform_.position_.x;
    checkZ = (int)(transform_.position_.z + 0.3);
    if (pStage->IsWall(checkX, checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.z = (float)((int)(transform_.position_.z + 0.5f) - 0.3f);
    }

    //��
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

    //���ς͉s�p������E�Ɉړ����Ă����Ɉړ����Ă����������Ă���
    //���ǂ�����H


}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget)
{
    //���������Ƃ��̏���

    
}

void Player::SetNextX(float x_)
{
    nextX[0] = x_;
}

void Player::SetNextY(float y_)
{
    nextY[0] = y_;
}
