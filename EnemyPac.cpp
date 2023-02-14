#include "EnemyPac.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"
#include "Stage.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
EnemyPac::EnemyPac(GameObject* parent)
    :GameObject(parent, "EnemyPac"), hModel_(-1)
{
}

//�f�X�g���N�^
EnemyPac::~EnemyPac()
{
}

//������
void EnemyPac::Initialize()
{
    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);
    pPlayer = (Player*)FindObject("Player");
    assert(pPlayer != nullptr);
    

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);
    //transform_.position_ = XMFLOAT3(pStage->GetX() + -3.5, 0, (pStage->GetY() + 0.5));
    transform_.position_ = XMFLOAT3(18.5, 0, 1.5);

    playerPos = pPlayer->GetPosition();
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.3, 0), 0.3f);
    AddCollider(collision);
}

//�X�V
void EnemyPac::Update()
{
    goalPos[0] = { (int)transform_.position_.z,(int)transform_.position_.x };

   

    pStage->SetStartCellX((int)transform_.position_.x);
    pStage->SetStartCellY((int)transform_.position_.z);
    
    //�O��̈ʒu�x�N�g���ɂȂ��H
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);


    //�E�ړ�
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.position_.x += 0.1;
        //�΂߈ړ������邩�炱��͎g���Ȃ�
        //transform_.rotate_.y = 90.0f;
    }
    //���ړ�
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.position_.x -= 0.1;
    }
    //��ړ�
    if (Input::IsKey(DIK_UP))
    {
        transform_.position_.z += 0.1;
    }
    //���ړ�
    if (Input::IsKey(DIK_DOWN))
    {
        transform_.position_.z -= 0.1;
    }

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
void EnemyPac::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void EnemyPac::Release()
{
}

//�����ɓ�������
void EnemyPac::OnCollision(GameObject* pTarget)
{
    //�G�ɓ��������Ƃ�
    if (pTarget->GetObjectName() == "Player")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_RESULT);
        //KillMe();
        //2
        //678
        //1516

    }
}

int EnemyPac::GetGoalPos(int ID)
{
    return 0;
}
