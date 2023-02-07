#include "PlayScene.h"
#include "Stage.h"
#include "Player.h"
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
	Instantiate<Player>(this);
	Instantiate<EnemyPac>(this);
	

	Camera::SetPosition(XMFLOAT3(10, 13, -2));

	Camera::SetTarget(XMFLOAT3(10, 5, 3));
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