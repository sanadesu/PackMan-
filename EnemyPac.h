#pragma once
#include "Engine/GameObject.h"
#include"Stage.h"
#include "Player.h"

//���������Ǘ�����N���X
class EnemyPac : public GameObject
{
    int hModel_;    //���f���ԍ�
    std::pair<int, int> goalPos[3];

    Player* pPlayer;
    Stage* pStage;
    XMFLOAT3 playerPos;

    std::list<std::pair<int, int>> move;
public:
    
    //�R���X�g���N�^
    EnemyPac(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyPac();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    int GetGoalPos(int ID);
};