#pragma once
#include "Engine/GameObject.h"
#include"Stage.h"
#include "Engine/SphereCollider.h"
//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�
    float nextX[3] = { 0,0,0 };
    float nextY[3] = { 0,0,0 };
    
    bool start = false;
    Stage* pStage;
    
public:
    int playerID;

    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
    //���肠
    //�t�����g
    //�|�b�v�t�����g
    
    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    void SetNextX(float x_);
    void SetNextY(float y_);
};