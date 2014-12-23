/*
 * Memory.h
 *
 *  Created on: Dec 23, 2014
 *      Author: fahmy
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#define sz(x) (int)(x.size())
#define pb push_back

#include <vector>
#include <algorithm>
#include "Partition.h"

using namespace std;

class Memory {

public:

	Memory() {
		nextUnallocated = 0;
	}

	int addPartition(int len) {
		if (nextUnallocated + len < size) {
			Partition p(nextUnallocated, len, false);
			partitions.push_back(p);
			nextUnallocated += len;
			return p.getStart();
		} else {
			return -1;
		}
	}

	int allocate(int method,int length){
		int address = -1;
		switch(method){
		case 1:
			address = firstFit(length);
			break;
		case 2:
			address = bestFit(length);
			break;
		case 3:
			address = worstFit(length);
			break;
		default:
			cout << "Not supported method\n";
			return -2;
		}
		return address;
	}
	bool deallocate(int st){
		int siz = sz(partitions);
		for(int i =0 ; i < siz; i++){
			if(partitions[i].getStart() == st){
				if(partitions[i].getStatus()){
					partitions[i].setStatus(false);
					return true;
				}else{
					return false;
				}
			}
		}
		return false;
	}

	void defragmentation(){
		sort(partitions.begin(),partitions.end());
		Partition empty;
		for(int i = 0 ; i < sz(partitions); i++){
			if(!partitions[i].getStatus()){
				if(empty.getStart() == -1){
					empty.setStart(partitions[i].getStart());
				}
				empty.increaseLength(partitions[i].getLength());
				partitions.erase(partitions.begin()+i);
				i--;
			}else if(empty.getStart()!=-1){
				Partition u = empty.join(partitions[i]);
				int l = partitions[i].getLength();
				partitions.erase(partitions.begin()+i);
				empty = u.allocate(l);
				partitions.insert(partitions.begin()+i,u);
			}
		}
		if(empty.getStart() != -1){
			partitions.pb(empty);
		}
	}

	void print(){
		for(int i = 0 ; i < sz(partitions); i++){
			cout << "Partition " << i << ":\n";
			cout << "at: " << partitions[i].getStart();
			cout << ", length:" << partitions[i].getLength();
			cout << ", status:"
			     << (partitions[i].getStatus()?"Occupied":"Free")
					<< "\n===\n";
		}
	}
private:
	int firstFit(int l){
		//loop over all available partitions
		//the first one that's large enough, allocate it
		for(int i = 0 ; i < sz(partitions); i++){

			Partition& current = partitions[i];

			if(current.getStatus())continue;//if it's used

			if(current.getLength() >= l){//large enough
				//the allocate method returns the right empty part
				//of the partition, and cuts the calling partition's length
				//it basically cuts the partition into two separate partitions
				Partition remainingPartition = current.allocate(l);
				if(remainingPartition.getLength() > 0){
					partitions.pb(remainingPartition);
				}
				return partitions[i].getStart();
			}
		}
		return -1;
	}
	int bestFit(int l){
		int min = size;
		int minIdx = -1;
		for(int i = 0 ; i < sz(partitions); i++){
			Partition& current = partitions[i];

			if(current.getStatus())continue;//if it's used

			if(current.getLength() >= l){

				if(current.getLength() < min){
					min = current.getLength();
					minIdx = i;
				}

			}
		}
		int ret = -1;
		if(minIdx != -1){
			ret = partitions[minIdx].getStart();
			Partition remainingPartition = partitions[minIdx].allocate(l);
			if(remainingPartition.getLength() > 0)
				partitions.pb(remainingPartition);
		}
		return ret;
	}
	int worstFit(int l){
		int max = -1;
		int maxIdx = -1;
		for(int i = 0 ; i < sz(partitions); i++){
			Partition current = partitions[i];

			if(current.getStatus())continue;//if it's used

			if(current.getLength() >= l){

				if(partitions[i].getLength() > max){
					max = partitions[i].getLength();
					maxIdx = i;
				}

			}
		}
		int ret = -1;
		if(maxIdx != -1){
			ret = partitions[maxIdx].getStart();
			Partition remainingPartition = partitions[maxIdx].allocate(l);
			if(remainingPartition.getLength() > 0)
				partitions.pb(remainingPartition);
		}
		return ret;
	}

	static const int size = 1000;
	vector<Partition> partitions;
	int nextUnallocated;
};

#endif /* MEMORY_H_ */
