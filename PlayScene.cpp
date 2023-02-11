#include "PlayScene.h"
#include "Stage.h"
#include "EnemyPac.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	for (int i = 0; i < 3; i++)
	{
		pPlayer[i] = (Player*)FindObject("Player");

		pPlayer[i] = Instantiate<Player>(this);
		
		pPlayer[i]->playerID = i;
	}
	Instantiate<EnemyPac>(this);

	Camera::SetPosition(XMFLOAT3(10, 13, -2));

	Camera::SetTarget(XMFLOAT3(10, 5, 3));
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}