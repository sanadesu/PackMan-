////#include "Stage.h"
////#include "Engine/Model.h"
////#include "Engine/CsvReader.h"
////
////const unsigned int MAP_ROW = 15; //縦
////const unsigned int MAP_COL = 20; //横
////const unsigned int MAX_COSTS = 9999; //最大コスト
////
//////int COSTMAP[MAP_ROW][MAP_COL] = {//[Y,X]?????
//////    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1, -1, -1, -1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//////    { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
//////};
////
////const Stage::DIRECTION DIRECTIONS[] = {
////                                     {  0, -1 },		// L
////                                     {  0, +1 },		// R
////                                     { -1,  0 },		// U
////                                     { +1,  0 }		// D
////};
////
////// スタート地点からの最小コスト値をいれてくやつ		初期化で全部9999
////int totalCosts[MAP_ROW][MAP_COL];
////
////
//////コンストラクタ
////Stage::Stage(GameObject* parent)
////    :GameObject(parent, "Stage")//, hModel_(-1)
////{
////
////}
////
//////デストラクタ
////Stage::~Stage()
////{
////}
////
//////初期化
////void Stage::Initialize()
////{
////    //モデルデータのロード
////    hModel_[0] = Model::Load("Ground2.fbx");
////    assert(hModel_[0] >= 0);
////    hModel_[1] = Model::Load("Wall2.fbx");
////    assert(hModel_[1] >= 0);
////    hModel_[2] = Model::Load("GroundGoal.fbx");
////    assert(hModel_[2] >= 0);
////
////    CsvReader csv;
////    csv.Load("map.csv");
////
////    for (int x = 0; x < MAP_COL; x++)
////    {
////        //for (int z = 15; z > 0; z--)
////        for (int z = 0; z < MAP_ROW; z++)
////        {
////
////            map_[x][z] = csv.GetValue(x, z);
////        }
////    }
////
////    CsvReader csvCost;
////    csvCost.Load("mapCost.csv");
////
////    for (int x = 0; x < MAP_COL; x++)
////    {
////        //for (int z = 15; z > 0; z--)
////        for (int z = 0; z < MAP_ROW; z++)
////        {
////
////            mapCost_[x][z] = csvCost.GetValue(x, z);
////        }
////    }
////
////    CELL startCell = { startCellY,startCellX };		// スタート地点 [Y,X]??????
////    CELL goalCell = { goalCellY, goalCellX };			//ゴール地点
////    Init(startCell);
////    CalcCosts(startCell);
////    Show();
////
////    map_[goalCellY][goalCellX] = 2;
////}
////
//////更新
////void Stage::Update()
////{
////}
////
//////描画
////void Stage::Draw()
////{
////    for (int x = 0; x < MAP_COL; x++)
////    {
////
////        for (int z = 0; z < MAP_ROW; z++)
////        {
////            int type;//x % 2 && z % 2;
////            transform_.position_.x = x;
////            transform_.position_.z = z;
////            if (mapCost_[z][x] == 1)
////            {
////                type = 1;
////            }
////            else if (mapCost_[z][x] >= -1)
////            {
////                type = 0;
////            }
////            else if (mapCost_[z][x] == 0)
////            {
////                type = 2;
////            }
////            Model::SetTransform(hModel_[type], transform_);
////            Model::Draw(hModel_[type]);
////        }
////    }
////}
////
//////開放
////void Stage::Release()
////{
////}
////
////
////bool Stage::IsWall(int x, int z)
////{
////    return (map_[x][z] == 1);//0 ? false : true;
////
////    /*if (map_[x][z] == 1)
////    {
////        return true;
////    }
////    else
////    {
////        return false;
////    }*/
////
////}
////
//////自分の場所以外最大コストにする
////void Stage::Init(CELL startCell)
////{
////    for (int row = 0; row < MAP_ROW; row++)
////    {
////        for (int col = 0; col < MAP_COL; col++)
////        {
////            totalCosts[row][col] = MAX_COSTS;
////        }
////    }
////
////    totalCosts[startCell.row][startCell.col] = 0;
////}
////
//////次の場所に行くときの合計コスト計算
////void Stage::CalcCosts(CELL cell)
////{
////    for (DIRECTION dir : DIRECTIONS)
////    {
////        int nextRow = cell.row + dir.dirRow;
////        int nextCol = cell.col + dir.dirCol;
////
////        if (mapCost_[nextRow][nextCol] < 0)
////        {
////            continue;
////        }
////
////        if (totalCosts[nextRow][nextCol] > totalCosts[cell.row][cell.col] + mapCost_[nextRow][nextCol])
////        {
////            totalCosts[nextRow][nextCol] = totalCosts[cell.row][cell.col] + mapCost_[nextRow][nextCol];
////
////            CalcCosts({ nextRow, nextCol });
////        }
////    }
////}
////
//////最短距離表示
////void Stage::Show()
////{
////    for (int row = 0; row < MAP_ROW; row++)
////    {
////
////        for (int col = 0; col < MAP_COL; col++)
////        {
////
////            if (goalCellY == row && goalCellX == col)
////            {
////                mapCost_[goalCellY][goalCellX] = -2;
////                //cout << setw(3) << "g" << totalCosts[row][col] << "|";
////                for (DIRECTION dir : DIRECTIONS)
////                {
////                    int nextRow = row + dir.dirRow;//10 + ? 0
////                    int nextCol = col + dir.dirCol;//11 + ? -1
////                    if (totalCosts[row][col] > totalCosts[nextRow][nextCol])
////                    {
////                        goalCellY = nextRow;
////                        goalCellX = nextCol;
////
////                    }
////                }
////            }
////            else
////            {
////                //cout << setw(4) << totalCosts[row][col] << "|";
////
////            }
////        }
////        //cout << "\n";
////    }
////
////}
////
////int Stage::GetX()
////{
////    return startCellX;
////
////}
////
////int Stage::GetY()
////{
////    return startCellY;
////}
//
//
//
//
//
//#include<iostream>
//#include<vector>
//#include <iomanip>
//#include <queue> 
//#define START CostMap[MAP_START.first][MAP_START.second]//スタート
//#define GOAL CostMap[MAP_GOAL.first][MAP_GOAL.second]    //ゴール using std::vector;
//using std::cout;
//using std::pair;
//
//const std::pair<int, int> MAP_START = { 2, 1 };    //スタート座標
//const std::pair<int, int> MAP_GOAL = { 5, 10 };    //ゴールの座標 const unsigned int MAP_ROW = 15;//縦
//const unsigned int MAP_COL = 20;//横
//const unsigned int MAP_COST = 999;//コスト初期化 //前方宣言
//void Search(pair<int, int> node);
////配列0 UP
////配列1 DOWN
////配列2 LEFT
////配列3 RIGHT
////first ROW
////seco  COL const std::pair<int, int> DIRECCIONS[] = {
//{ -1, 0 },
//{ +1, 0 },
//{ 0, -1 },
//{ 0, +1 }
//}; 
//struct cMap{
//pair<int, int> prevNode = { -1, -1 };     bool done = false;//確定ノードかどうか
//int map;//マップ
//int cost;//最小コスト     //first   ROW
////second  COL
//std::pair<int, int> cel;
// }CostMap[MAP_ROW][MAP_COL]; const int Map[MAP_ROW][MAP_COL] = {
//{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
//{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//{ -1,  1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  3,  1, -1, -1, -1,  1,  1, -1 },
//{ -1,  1,  2, -1,  1, -1,  1,  1,  1, -1,  1,  3,  1,  1, -1,  1, -1,  1,  1, -1 },
//{ -1,  1,  1, -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//{ -1,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1, -1, -1, -1,  1,  1,  1,  1,  1, -1 },
//{ -1,  1,  1, -1,  1,  1, -1,  1,  1,  1,  1,  1,  1, -1,  1,  1, -1,  1,  1, -1 },
//{ -1,  1,  1, -1,  1,  1,  1,  2,  2,  2,  1,  1,  1,  1,  1,  1, -1,  1,  1, -1 },
//{ -1,  1,  1, -1,  1,  1, -1,  1,  2,  1,  1,  1,  1, -1,  1,  2, -1,  1,  1, -1 },
//{ -1,  1,  1,  1,  1,  1, -1, -1, -1,  1,  1, -1, -1, -1,  2,  2,  1,  1,  1, -1 },
//{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//{ -1,  1,  1, -1,  1, -1,  1,  1,  1,  1,  3,  3,  1,  1, -1,  1, -1,  1,  1, -1 },
//{ -1,  1,  1, -1, -1, -1,  1,  1, -1, -1, -1, -1,  1,  1, -1, -1, -1,  1,  1, -1 },
//{ -1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, -1 },
//{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
// };
// void InitMap()
// {
//	 //Mapを入れる
//	 for (auto i = 0; i < MAP_ROW; i++)
//	 {
//		 for (auto j = 0; j < MAP_COL; j++)
//		 {
//			 CostMap[i][j].map = Map[i][j];
//			 CostMap[i][j].cost = MAP_COST;             CostMap[i][j].cel = { i, j };
//		 }
//	 }     //スタートのコストを0にする
//	 START.cost = 0;
//	 //スタートのルートを確定する
//	 START.done = true;     //ゴールのルートを確定する
//	 GOAL.done = true;
// }
// //Dijkstra探索
////引数 : cell    今いるセル
////引数 : gorl_    ゴール地点
// void Dijkstra(cMap cel_, cMap goal)
// {
//	 //4方向にやる
//	 for (const auto& dir : DIRECCIONS)
//	 {
//		 int nextRow = cel_.cel.first + dir.first;
//		 int nextCol = cel_.cel.second + dir.second;
//		 //mapが0かマイナスならそこは探索しない
//		 if (CostMap[nextRow][nextCol].map < 0)
//		 {
//			 continue;
//		 }         if (CostMap[nextRow][nextCol].cost > CostMap[cel_.cel.first][cel_.cel.second].cost + CostMap[nextRow][nextCol].map)
//		 {
//			 CostMap[nextRow][nextCol].prevNode = CostMap[cel_.cel.first][cel_.cel.second].cel;
//			 CostMap[nextRow][nextCol].cost = CostMap[cel_.cel.first][cel_.cel.second].cost + CostMap[nextRow][nextCol].map;
//			 Dijkstra(CostMap[nextRow][nextCol], GOAL);
//		 }
//	 }
// } 
//
// void Search(pair<int, int> node)
// {
//	 if (node.first > 0)
//	 {
//		 CostMap[node.first][node.second].done = true;
//		 Search(CostMap[node.first][node.second].prevNode);
//	 }
// } 
// void Show()
// {
//	 for (int row = 0; row < MAP_ROW; row++)
//	 {
//		 cout << "|";
//		 for (int col = 0; col < MAP_COL; col++)
//		 {
//			 if (CostMap[row][col].done == true)
//			 {
//				 if (CostMap[row][col].cost < 10)
//				 {
//					 cout << std::setw(3) << "g" << CostMap[row][col].cost << "|";
//				 }
//				 else
//				 {
//					 cout << std::setw(2) << "g" << CostMap[row][col].cost << "|";
//				 }
//			 }
//			 else
//			 {
//				 cout << std::setw(4) << CostMap[row][col].cost << "|";
//			 }
//		 }
//		 cout << "\n";
//	 }
// } int main()
// {
//	 InitMap();
//	 //Show();
//	 //cout << "--------------------\n";
//	 Dijkstra(START, GOAL);
//	 //経路を探索
//	 Search(GOAL.cel);
//	 Show();     system("pause");
//	 return 0;
// }