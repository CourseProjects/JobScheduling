#include "Job.h"


Job::Job(int index){
	this->CurOps=0;
	this->operation[CurOps].endTime=-1; //�����տ�ʼ��û��ʼ�ӹ�
	this->name=index;
}

void Job::SetCurOps(int startPoint,int ProcessTime){
	this->operation[CurOps].startTime = startPoint;
	this->operation[CurOps].endTime = startPoint+ProcessTime;
}

int Job::GetCurOpsIndex(){
	return this->CurOps;
}
ops Job::GetCurOps(){
	return this->operation[CurOps];
}

void Job::moveToNextStage(){
	(this->CurOps)++;
}