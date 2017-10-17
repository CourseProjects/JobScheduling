#pragma once
#define N 5
typedef struct OPS{
int startTime;
int endTime;
}ops;
	
class Job
{
/**属性**/
private:
	ops operation[N];  	//总的工序
	int CurOps;			//当前加工的工序
	int name;			//名字
/**方法**/
public:
	Job(){};
	Job(int name);
	void SetCurOps(int startPoint,int ProcessTime);//处理当前工件	
	int  GetCurOpsIndex();
	ops GetCurOps();
	void moveToNextStage();
};

