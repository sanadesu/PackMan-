#pragma once
#include "Engine/GameObject.h"
#include"Stage.h"
#include "Engine/SphereCollider.h"
//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_[3];    //���f���ԍ�
    float nextX[3] = { 0,0,0 };
    float nextY[3] = { 0,0,0 };
    
    bool start = false;
    Stage* pStage;
    std::pair<int, int> pos[3] = {};
    
    bool first = false;
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

    std::pair<int, int> GetPos(int ID);
};