#include "Encode.h"


Encode::Encode(int Segment[MAX_MACHINE_SIZE][MAX_LENGTH]){
	//CopyTo(MSegment,Segment)
	for(int i=0;i<MAX_MACHINE_SIZE;i++){
		for(int j=0;j<MAX_LENGTH;j++){
			this->MSegment[i][j] = Segment[i][j];
		}
	}
}
int * Encode::GetSegment(int m_index){
	return this->MSegment[m_index];
}