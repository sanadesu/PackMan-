//#pragma once
//#include "Engine/GameObject.h"
//#include"Stage.h"
//#include "Player.h"
//
////���������Ǘ�����N���X
//class Enemy : public GameObject
//{
//    // �X�^�[�g�n�_����̍ŏ��R�X�g�l������Ă����		�������őS��9999
//    int totalCosts[15][20];
//    int hModel_;    //���f���ԍ�
//    int map_[20][15] = {0};
//    int mapCost_[20][15] = { 0 };
//    int goalCellY;
//    int goalCellX;
//
//    Player* pPlayer;
//    Stage* pStage;
//    XMFLOAT3 playerPos;
//
//    std::list<std::pair<int, int>> move;
//public:
//    typedef struct tagCell {
//        int row = 0;//Y
//        int col = 0;//X
//    }CELL;
//
//
//    typedef struct tagDirection {
//        int dirRow = 0;
//        int dirCol = 0;
//    }DIRECTION;
//
//    //�R���X�g���N�^
//    Enemy(GameObject* parent);
//
//    //�f�X�g���N�^
//    ~Enemy();
//
//    //������
//    void Initialize() override;
//
//    //�X�V
//    void Update() override;
//
//    //�`��
//    void Draw() override;
//
//    //�J��
//    void Release() override;
//
//    
//    //�����̏ꏊ�ȊO�ő�R�X�g�ɂ���
//    void Init(CELL startCell);
//
//    //���̏ꏊ�ɍs���Ƃ��̍��v�R�X�g�v�Z
//    void CalcCosts(CELL cell);
//
//    //�ŒZ�����\��
//    void Show();
//};