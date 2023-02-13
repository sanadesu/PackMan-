#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include<iostream>
#include<vector>
#include <iomanip>
#include <queue> 
#include "EnemyPac.h"
#include "Player.h"

//#define START CostMap[MapStart.first][MapStart.second]//スタート
//#define GOAL CostMap[MapGoal.first][MapGoal.second]    //ゴール using std::vector;

using std::pair;

const Stage::DIRECTION DIRECTIONS[] = {
                                     {  0, -1 },		// L
                                     {  0, +1 },		// R
                                     { -1,  0 },		// U
                                     { +1,  0 }		    // D
};


//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")//, hModel_(-1)
{

}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    hModel_[0] = Model::Load("Ground2.fbx");
    assert(hModel_[0] >= 0);
    hModel_[1] = Model::Load("Wall2.fbx");
    assert(hModel_[1] >= 0);
    hModel_[2] = Model::Load("GroundGoal.fbx");
    assert(hModel_[2] >= 0);

    CsvReader csv;
    csv.Load("map.csv");

    for (int x = 0; x < MAP_COL; x++)
    {
        //for (int z = 15; z > 0; z--)
        for (int z = 0; z < MAP_ROW; z++)
        {
            map_[x][z] = csv.GetValue(x, z);
        }
    }

    //for (int i = 0; i < 3; i++)
    //goalCell = { goalCellY, goalCellX };?			//ゴール地点
   
                                                        
                                                        
    /* Init(startCell[RED]);
    CalcCosts(startCell[RED]);
    Show();*/

    //for (int i = 0; i < 3; i++)
    {
        map_[goalCellY[0]][goalCellX[0]] = 2;
    }
    


    
}

//更新
void Stage::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");
    EnemyPac* pEnemyPac = (EnemyPac*)FindObject("EnemyPac");

    for (int i = 0; i < 3; i++)
    {
        if (pPlayer->playerID == i)
        {
            MapStart[i].first = (int)pPlayer->GetPosition().z;
            MapStart[i].second = (int)pPlayer->GetPosition().x;
        }
    }
    
  

    ///////ここ!
    //for (int i = 0; i < 3; i++)
    {
        MapGoal[0].first = (int)pEnemyPac->GetPosition().z;
        MapGoal[0].second = (int)pEnemyPac->GetPosition().x;
    }
    for (DIRECTION dir : DIRECTIONS)
    {
       /* MapGoal[1].first = MapGoal[0].first + dir.dirRow;
        MapGoal[1].second = MapGoal[0].second + dir.dirCol;

        if (COSTMAP[MapGoal[1].first][MapGoal[1].second] > 0)
        break

        if (totalCosts[nextRow][nextCol] > totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol])
        {
            totalCosts[nextRow][nextCol] = totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol];
            CalcCosts({ nextRow, nextCol });
        }*/
    }
    

    for (int i = 0; i < 3; i++)
    {
        if (time % 60 == 0 || minCost[i].size() == 0)
        {
            InitMap();

            Dijkstra(CostMap[MapStart[i].first][MapStart[i].second], CostMap[MapGoal[i].first][MapGoal[i].second],i);
            minCost[i].clear();
            //経路を探索
            Search(CostMap[MapGoal[i].first][MapGoal[i].second].cel, i);
            if (minCost[i].size() != 0)
            {
                min[i] = (minCost[i].back());
                minCost[i].pop_back();
            }

            flag = false;


        }
    }
       

        for (int i = 0; i < 3; i++)
        {
           

            if (minCost[i].size() != 0)
            {
                if (min[i].first == (int)pPlayer->GetPosition().z && min[i].second == (int)pPlayer->GetPosition().x)
                {
                    //std::make_pair(minCost.pop_front());
                    min[i] = (minCost[i].back());
                    minCost[i].pop_back();

                    //min.first;
                    //COSTMAP[min.first][min.second] = -2;
                    //COSTMAP[min.second][min.first] = -2;
                }

            }
            else
            {

                minCost[i].clear();
            }
        }
    

    
    
   

        time++;


    for (int row = 0; row < MAP_ROW; row++)
    {
        for (int col = 0; col < MAP_COL; col++)
        {
            if (CostMap[row][col].done == true)
            {
                COSTMAP[row][col] = -2;
            }
            else if (COSTMAP[row][col] == -2)
            {
                COSTMAP[row][col] = 0;
            }
            //CostMap[row][col].done = false;
        }
    }

    for (int row = 0; row < MAP_ROW; row++)
    {
        for (int col = 0; col < MAP_COL; col++)
        {
            CostMap[row][col].done = false;
        }
    }
    ////if (Input::IsKeyDown(DIK_0))
    //{
    //    //リストの最後の値を代入したい
    //    //a = std::make_pair(move.pop_back());
    //    /*nextMove[0] = std::make_pair(11,15);
    //    nextMove[0] = move.front();
    //    move.pop_front();*/
    //   /* move.pop_back().first;
    //    std::pair<int, int> a;
    //    a = std::make_pair(move.pop_back().first, move.pop_back().first);*/
    //    int b = 0;
    //}
    //goalCell = { goalCellY, goalCellX };			//ゴール地点
    //Init(goalCell);
    //CalcCosts(goalCell);
    //Show();
}

//描画
void Stage::Draw()
{
    for (int x = 0; x < MAP_COL; x++)
    {

        for (int z = 0; z < MAP_ROW; z++)
        {
            int type;//x % 2 && z % 2;
            transform_.position_.x = x;
            transform_.position_.z = z;
            if (COSTMAP[z][x] == -1)
            {
                type = 1;
            }
            else if (COSTMAP[z][x] >= 0)
            {
                type = 0;
            }
            else if (COSTMAP[z][x] == -2)
            {
                type = 2;
            }
            Model::SetTransform(hModel_[type], transform_);
            Model::Draw(hModel_[type]);
        }
    }
}

//開放
void Stage::Release()
{
}


bool Stage::IsWall(int x, int z)
{
    return (map_[x][z] == 1);//0 ? false : true;

    /*if (map_[x][z] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }*/

}

//自分の場所以外最大コストにする
void Stage::Init(CELL startCell)
{
    for (int row = 0; row < MAP_ROW; row++)
    {
        for (int col = 0; col < MAP_COL; col++)
        {
            totalCosts[row][col] = MAX_COSTS;
        }
    }

    totalCosts[startCell.row][startCell.col] = 0;
}


//最短距離表示
void Stage::Show()
{
    for (int row = 0; row < MAP_ROW; row++)
    {

        for (int col = 0; col < MAP_COL; col++)
        {

            if (startCellY[RED] == row && startCellX[RED] == col)
            {
                move.push_back(std::make_pair(startCellY[RED], startCellX[RED]));
                //COSTMAP[startCellY[RED]][startCellX[RED]] = -2;
                //COSTMAP[2][13] = -2;//2 13下 11 16 ↑→
                // 取り出してエネミーにいれて
                // うごかす
                //cout << setw(3) << "g" << totalCosts[row][col] << "|";
                for (DIRECTION dir : DIRECTIONS)
                {
                    int nextRow = row + dir.dirRow;//10 + ? 0
                    int nextCol = col + dir.dirCol;//11 + ? -1
                    if (totalCosts[row][col] > totalCosts[nextRow][nextCol])
                    {
                        startCellY[RED] = nextRow;
                        startCellX[RED] = nextCol;
                    }
                }
            }
            else
            {
                //COSTMAP[startCellY[RED]][startCellX[RED]] = 0;
                //cout << setw(4) << totalCosts[row][col] << "|";

            }
        }
        //cout << "\n";
    }

}

int Stage::GetX(int ID)
{
    return goalCellX[ID];

}

int Stage::GetY(int ID)
{
    return goalCellY[ID];
}

void Stage::SetStartCellX(int X)
{
    startCellX[0] = X;//配列いらん
}

void Stage::SetStartCellY(int Y)
{
    startCellY[0] = Y;//配列いらん
}

void Stage::SetGoalCellX(int X, int num)
{
    goalCellX[num] = X;
}

void Stage::SetGoalCellY(int Y, int num)
{
    goalCellY[num] = Y;
}

std::pair<int, int> Stage::GetListPos()
{
    nextMove[0] = move.front();
    //move.pop_front();
    return move.back();
}

void Stage::InitMap()
{
    //Mapを入れる
    for (auto i = 0; i < MAP_ROW; i++)
    {
        for (auto j = 0; j < MAP_COL; j++)
        {
            CostMap[i][j].map = COSTMAP[i][j];
            CostMap[i][j].cost = MAX_COSTS;
            CostMap[i][j].cel = { i, j };
        }
    }

    for (int i = 0; i < 3; i++)
    {
        //スタートのコストを0にする
        CostMap[MapStart[i].first][MapStart[i].second].cost = 0;
        //スタートのルートを確定する
        CostMap[MapStart[i].first][MapStart[i].second].done = true;
        CostMap[MapStart[i].first][MapStart[i].second].prevNode;
        //ゴールのルートを確定する
        CostMap[MapGoal[i].first][MapGoal[i].second].done = true;
    }
    
}

//Dijkstra探索
//引数 : cell    今いるセル
//引数 : gorl_    ゴール地点
void Stage::Dijkstra(cMap cel_, cMap goal,int ID)
{
    //4方向にやる
    for (const auto& dir : DIRECTIONS)
    {
        int nextRow = cel_.cel.first + dir.dirRow;
        int nextCol = cel_.cel.second + dir.dirCol;
        //mapが0かマイナスならそこは探索しない
        if (CostMap[nextRow][nextCol].map < 0)
        {
            continue;
        }
        if (CostMap[nextRow][nextCol].cost > CostMap[cel_.cel.first][cel_.cel.second].cost + CostMap[nextRow][nextCol].map)
        {
            CostMap[nextRow][nextCol].prevNode = CostMap[cel_.cel.first][cel_.cel.second].cel;
            CostMap[nextRow][nextCol].cost = CostMap[cel_.cel.first][cel_.cel.second].cost + CostMap[nextRow][nextCol].map;
            Dijkstra(CostMap[nextRow][nextCol], CostMap[MapGoal[ID].first][MapGoal[ID].second],ID);
        }
    }
    return;
}


void Stage::Search(pair<int, int> node,int ID)
{
    //for (int i = 0; i < 3; i++)
    {
        if (node.first > 0)
        {
            if (node.first != MapStart[ID].first || node.second != MapStart[ID].second)
            {
                CostMap[MapStart->first][MapStart->second].prevNode = { -100,-100 };
                CostMap[node.first][node.second].done = true;
                nowCost[ID].push_back({ CostMap[node.first][node.second].cel.first, CostMap[node.first][node.second].cel.second });
                
                //if(nowCost[ID].size() < 40000)
                if (CostMap[node.first][node.second].prevNode.first != -100 && CostMap[node.first][node.second].prevNode.second != -100 )
                {
                    Search(CostMap[node.first][node.second].prevNode, ID);
                    /*if (CostMap[node.first][node.second].cel.first != CostMap[MapGoal.first][MapGoal.second].cel.first && 
                        CostMap[node.first][node.second].cel.second != CostMap[MapGoal.first][MapGoal.second].cel.second
                       || nowCost[ID].size() <= 2)
                    {
                        
                    }*/
                }
            }
        }

        if (node.first == MapGoal[ID].first && node.second == MapGoal[ID].second)
        {
            if (minCost[ID].size() == 0 || minCost[ID].size() > nowCost[ID].size())
            {
                minCost[ID].clear();
                minCost[ID] = nowCost[ID];
                nowCost[ID].clear();
            }
            else
            {
                nowCost[ID].clear();
            }
        }
        //i += 2;//////
    }
}


//次の場所に行くときの合計コスト計算
void Stage::CalcCosts(CELL cell)
{
    for (DIRECTION dir : DIRECTIONS)
    {
        int nextRow = cell.row + dir.dirRow;
        int nextCol = cell.col + dir.dirCol;

        if (COSTMAP[nextRow][nextCol] < 0)
        {
            continue;
        }

        if (totalCosts[nextRow][nextCol] > totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol])
        {
            totalCosts[nextRow][nextCol] = totalCosts[cell.row][cell.col] + COSTMAP[nextRow][nextCol];
            CalcCosts({ nextRow, nextCol });
        }
    }
}


std::pair<int, int> Stage::GetNextMovePos(int ID)
{
    return min[ID];
}