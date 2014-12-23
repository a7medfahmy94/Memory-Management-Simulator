/*
 * Partition.h
 *
 *  Created on: Dec 23, 2014
 *      Author: fahmy
 */

#ifndef PARTITION_H_
#define PARTITION_H_

using namespace std;

class Partition{
public:

	Partition(int s,int l,bool b):
		start(s),length(l),status(b){
	}

	Partition():
		start(-1),length(-1),status(0){
	}

	int getStart(){return this->start;}
	int getLength(){return this->length;}
	bool getStatus(){return this->status;}

	void setStart(int i){this->start = i;}
	void setLength(int i){this->length = i;}
	void setStatus(bool b){this->status = b;}

	void increaseLength(int l){this->length+=l;}

	//joins two contiguous partitions into an empty big partition
	Partition join(Partition& b){
		return Partition(min(start,b.start),length+b.length,false);
	}

	Partition allocate(int l){
		if(length - l >= 0){
			int len = length;
			this->status = true;
			this->length = l;
			return Partition(start+l,len,false);;
		}
		return Partition();
	}

	bool friend operator<(const Partition& p1,const Partition& p2){
		return p1.start <= p2.start;
	}

private:
	int start;
	int length;
	bool status;
};


#endif /* PARTITION_H_ */
