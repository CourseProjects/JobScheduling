#pragma once
#define N 5
typedef struct OPS{
int startTime;
int endTime;
}ops;
	
class Job
{
/**����**/
private:
	ops operation[N];  	//�ܵĹ���
	int CurOps;			//��ǰ�ӹ��Ĺ���
	int name;			//����
/**����**/
public:
	Job(){};
	Job(int name);
	void SetCurOps(int startPoint,int ProcessTime);//����ǰ����	
	int  GetCurOpsIndex();
	ops GetCurOps();
	void moveToNextStage();
};

