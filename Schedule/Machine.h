#pragma once

#define MAX_SIZE 5
class Machine
{
	/** Ù–‘**/
private:
	int CompleteTime;
	int  name;
	int  JobBuffer[MAX_SIZE];
	int  CurPoint;
public:
	Machine(){};
	Machine(int name);
	void  InsertBuffer(int job);
	int *GetCurrentJobs();
	bool GetCurState();
	int StartOperate(int * JobSequence,int len);
	void SetCompleteTime(int nextTime);
	int  GetCompleteTime();
	bool IsEmpty();
};

