#include"Encode.h"
#include"Job.h"
#include"Machine.h"
#include<cstdlib>
#include<time.h>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;
#define N 50
#define M 15
#define OP 5
int OperateTime[N*OP][M];
int InitCode[M][N];

vector<int> DecisionPoint;


void AddToTable(int timepoint){

	//要确保这些值不重复
	for(int i=0;i<DecisionPoint.size();i++){
		if(DecisionPoint[i]==timepoint){
			return;
		}
	}
	DecisionPoint.push_back(timepoint);
}

int main(){
	//随机数初始化
	srand((unsigned)time(NULL));
	int i, j;
	for (i = 0; i < N*OP; i++)
	{
		for (j = 0; j < M; j++)
		{
			OperateTime[i][j] = rand() % 11 + 1;
		}
	}
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			InitCode[i][j] = rand() % 50 + 1;
		}
	}
	/*所有工件都在0时刻到达系统，初始化加工开始**********/
	Job job[N];
	for(int i=0;i<N;i++){
		job[i]=Job(i);
	}
	Machine machine[M];
	for(int j=0;j<M;j++){
		machine[j]=Machine(j);
	}
	Encode Chromos=Encode(InitCode);
	
	int CurTime = 0;
	machine[0].InsertBuffer(1);
	machine[0].InsertBuffer(2);
	machine[0].InsertBuffer(3);
	/*初始化结束****************************************/
	int t = 5;
	int ans[5];
	while (t--)
	{
		while (true){

			/**对于工件来说，可能正好加工完，要转移到下一个工序里**/
			for (int i = 0; i<M; i++){
				//if(工件的当前加工完成，需要转移到下个机器上加工){	  
				if (job[i].GetCurOps().endTime == CurTime){
					/**如果是最后一道工序**/
					if (job[i].GetCurOpsIndex() == OP - 1){
						job[i].moveToNextStage();
						break;
					}

					/**找到下一个可加工的机器**/
					int m_index;
					int col = i*OP + (job[i].GetCurOpsIndex() + 1);
					for (int row = 0; row<M; row++){
						if (OperateTime[col][row] != 0){
							m_index = row;
							break;
						}
					}
					/**把 jobi加到下一个机器的缓冲区里面**/
					machine[m_index].InsertBuffer(i + 1);
					job[i].moveToNextStage();
				}
			}

			//if( 所有工件都加工完毕) 
			if (job[0].GetCurOpsIndex() == OP && job[1].GetCurOpsIndex() == OP && job[2].GetCurOpsIndex() == OP)
				break;

			/**对于机器来说，可能是选择工件调度**/
			for (int j = 0; j<M; j++){
				//if(IsIdle(j)){
				if (machine[j].GetCompleteTime() <= CurTime && !machine[j].IsEmpty()){

					// 根据编码，从中间挑选出最合适的工件,机器开始加工
					int * jobSequence = Chromos.GetSegment(j);
					int CurBest = machine[j].StartOperate(jobSequence, 3) - 1; //索引到数组映射要-1

					//开始加工
					//int ProcessTime = GetTime(CurBest,job[CurBest].GetCurrentOps(),j)
					int ProcessTime = OperateTime[CurBest*OP + job[CurBest].GetCurOpsIndex()][j];  //得到处理时间
					job[CurBest].SetCurOps(CurTime, ProcessTime);						   //设置工序的加工区间
					machine[j].SetCompleteTime(CurTime + ProcessTime);					   //设置机器下一次的完成时间

					//记录下一个决策点时间
					AddToTable(CurTime + ProcessTime);
				}
			}

			//选择下一个决策点
			//CurTime = SelectNextFromTable();
			sort(DecisionPoint.begin(), DecisionPoint.end());
			CurTime = DecisionPoint[0];
			DecisionPoint.erase(DecisionPoint.begin(), DecisionPoint.begin() + 1);
		}
		ans[t] = CurTime;
	}
	int temp = ans[0];
	for (i = 0; i < 5; i++)
	{
		if (temp < ans[i])
			temp = ans[i];
	}
	cout << temp << endl;
	exit(0);
	//printf("%d",job[1].GetCurOps().endTime);
}