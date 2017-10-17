#include "Machine.h"

Machine::Machine(int name)
{
	this->CompleteTime=0;
	this->name=name;
	this->CurPoint=0;
}

void Machine::InsertBuffer(int job){
	//JobBuffer.add(job)
	this->JobBuffer[this->CurPoint]= job;
	CurPoint++;
}
int * Machine::GetCurrentJobs(){
	//return JobBuffer[size];
	return this->JobBuffer;  //(注意这传的是指针)
}

/***
int GetRuleSequence(){
	int[] RuleSequence;
	int[] fitness;
	if (this->rule == "lpt"){
		for (i = 1...JobBuffer){}
			fitness = GetProcessTime(i);
			sort(fitness, GetRuleSequence);
		}
	}
	if (Rule1){
		c1*ProcessingTIMe + c2*WaitTIme + c3*RemainTime + 4 + 5;
	}

	return RuleSequence[];
}
**/

int Machine::StartOperate(int* JobSequence,int len){
	

	//遍历序列
	for(int i=0;i<len;i++){
		for(int j=0;j<this->CurPoint;j++)
		//当前优先级位置的工件是否在缓冲区中
		if( JobSequence[i]== this->JobBuffer[j]){
			int job_index =this->JobBuffer[j];
			//从缓冲区中删去工件
			for(int p=j+1;p<this->CurPoint;p++){
				this->JobBuffer[p-1]= this->JobBuffer[p];
			}
			this->CurPoint--;
			
			//返回工件索引
			return job_index;
		}
	}
}
void Machine::SetCompleteTime(int nextTime){
	this->CompleteTime = nextTime;
}

int Machine::GetCompleteTime(){
	return this->CompleteTime;
}

bool Machine::IsEmpty(){
	return this->CurPoint==0?true:false;
}