#pragma once
#define MAX_MACHINE_SIZE 15
#define MAX_LENGTH 50
class Encode
{
private :
	/** Ù–‘**/
	int MSegment[MAX_MACHINE_SIZE][MAX_LENGTH];
public:
	Encode(int Segment[MAX_MACHINE_SIZE][MAX_LENGTH]);
	int *GetSegment(int m_index);
};

