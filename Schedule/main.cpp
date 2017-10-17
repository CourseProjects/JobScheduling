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

	//Ҫȷ����Щֵ���ظ�
	for(int i=0;i<DecisionPoint.size();i++){
		if(DecisionPoint[i]==timepoint){
			return;
		}
	}
	DecisionPoint.push_back(timepoint);
}

int main(){
	//�������ʼ��
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
	/*���й�������0ʱ�̵���ϵͳ����ʼ���ӹ���ʼ**********/
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
	/*��ʼ������****************************************/
	int t = 5;
	int ans[5];
	while (t--)
	{
		while (true){

			/**���ڹ�����˵���������üӹ��꣬Ҫת�Ƶ���һ��������**/
			for (int i = 0; i<M; i++){
				//if(�����ĵ�ǰ�ӹ���ɣ���Ҫת�Ƶ��¸������ϼӹ�){	  
				if (job[i].GetCurOps().endTime == CurTime){
					/**��������һ������**/
					if (job[i].GetCurOpsIndex() == OP - 1){
						job[i].moveToNextStage();
						break;
					}

					/**�ҵ���һ���ɼӹ��Ļ���**/
					int m_index;
					int col = i*OP + (job[i].GetCurOpsIndex() + 1);
					for (int row = 0; row<M; row++){
						if (OperateTime[col][row] != 0){
							m_index = row;
							break;
						}
					}
					/**�� jobi�ӵ���һ�������Ļ���������**/
					machine[m_index].InsertBuffer(i + 1);
					job[i].moveToNextStage();
				}
			}

			//if( ���й������ӹ����) 
			if (job[0].GetCurOpsIndex() == OP && job[1].GetCurOpsIndex() == OP && job[2].GetCurOpsIndex() == OP)
				break;

			/**���ڻ�����˵��������ѡ�񹤼�����**/
			for (int j = 0; j<M; j++){
				//if(IsIdle(j)){
				if (machine[j].GetCompleteTime() <= CurTime && !machine[j].IsEmpty()){

					// ���ݱ��룬���м���ѡ������ʵĹ���,������ʼ�ӹ�
					int * jobSequence = Chromos.GetSegment(j);
					int CurBest = machine[j].StartOperate(jobSequence, 3) - 1; //����������ӳ��Ҫ-1

					//��ʼ�ӹ�
					//int ProcessTime = GetTime(CurBest,job[CurBest].GetCurrentOps(),j)
					int ProcessTime = OperateTime[CurBest*OP + job[CurBest].GetCurOpsIndex()][j];  //�õ�����ʱ��
					job[CurBest].SetCurOps(CurTime, ProcessTime);						   //���ù���ļӹ�����
					machine[j].SetCompleteTime(CurTime + ProcessTime);					   //���û�����һ�ε����ʱ��

					//��¼��һ�����ߵ�ʱ��
					AddToTable(CurTime + ProcessTime);
				}
			}

			//ѡ����һ�����ߵ�
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