#include "PlayScene.h"
#include "Stage.h"
#include "EnemyPac.h"
#include "Engine/Camera.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	for (int i = 0; i < 3; i++)
	{
		pPlayer[i] = (Player*)FindObject("Player");

		pPlayer[i] = Instantiate<Player>(this);
		
		pPlayer[i]->playerID = i;
	}
	//pPlayer[1]->playerID = 0;//赤２体になる

	Instantiate<EnemyPac>(this);

	Camera::SetPosition(XMFLOAT3(10, 17, 2));

	Camera::SetTarget(XMFLOAT3(10, 5, 5.2f));
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}