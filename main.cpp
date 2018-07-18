//(323) Project#3 - HeapSort by Xiaomin Chen
//Bsed on ID implementation of Partial Order Binary Trees/Priority Queue

#include<iostream>
#include<fstream>
using namespace std;

class HeapSort{
	private:
		int fatherIndex;
		int leftKidIndex;
		int rightKidIndex;
		int minKidIndex;
		int numInt;
		int *heapAry;	
		
	public:
		HeapSort(int n){
			heapAry = new int[n]();															//dynamically allocates size for an array
			numInt = n;																		//stores the number of integers in the input file
		}
		void buildHeap(ifstream& inFile, ofstream& outFile1){								//building a heap from the input file
			int num, kidIndex;
			inFile.seekg(0, inFile.beg);													//rereads from the beginning of the text file
			while(!inFile.eof()){															//while it is not the end of file
				inFile>>num;																//store the integer
				if(num < 0){																//checks if input data is positive
					cerr<<"Only positive integers. "<<endl;									//if not, output an error message
					break;																	//breaks the while loop and stops building the loop
				}
				if(isDuplicate(num)){														//if new data already exist in array
					continue;																//continue to next data
				}
				insertOneDataItem(num);														//insert the integer into the end of array
				kidIndex = heapAry[0];														//new data's index: heapAry[0] is saved as kidIndex
				bubbleUp(kidIndex);															//bubble up the new integer if possible
				printHeap(outFile1);														//prints current heap after the data has fallen into the right place
			}//continues to next integer
		}
		void deleteHeap(ofstream& outFile2, ofstream& outFile1){
			int data;																		//stores the deleted root data
			while(!isHeapEmpty()){															//while heap is not
				data = getRoot();															//store the root data before deletion
				outFile2<<data<<endl;														//print data to output file #2
				deleteRoot();																//delete the root and replace with last data item
				fatherIndex = 1;															//index of new data is 1, the root
				bubbleDown(fatherIndex);													//bubble down the new root to store it in the right place
				printHeap(outFile1);														//prints current heap after the data has fallen into the right place
			}//continues to delete integer
			delete [] heapAry;
		}
		void insertOneDataItem(int data){													//insert new data at the end of the array
			int newIdx = heapAry[0] + 1;													//index of new data is previous last index + 1
			if(!isHeapFull()){																//if heap is not full
				heapAry[newIdx] = data;														//store new data under the next spot
			}
			++heapAry[0];																	//last index is incremented by one
		}
		int getRoot(){																		//returns the root data
			return heapAry[1];																//root data is always store under index 1
		}
		void deleteRoot(){																	//delete the root data and replaced by the last data item
			int last = heapAry[0];															//find the index of last data
			swap(1, last);																	//swap root and last item
			heapAry[last] = 0;																//last data becomes zero
			--heapAry[0];																	//last index (# of item) is decremented
		}
		void bubbleUp(int kidIndex){														//bubble up newly inserted data
			if(isRoot(kidIndex)){															//checks if new data is a root
				return;																		//if so, do nothing
			}
			else{																			//if not
				fatherIndex = kidIndex/2;													//father's index is calculated
				if(heapAry[kidIndex] < heapAry[fatherIndex]){								//compare the data of kid and father
					swap(kidIndex, fatherIndex);											//swap place if new data is less than father's data
					bubbleUp(fatherIndex);													//continue to bubble up if possible, using recursion
				}
			}
		}
		void bubbleDown(int currentIdx){													//bubble down the new root
			leftKidIndex = (currentIdx*2);													//find left children 
			rightKidIndex = (currentIdx*2) + 1;												//find right children
			
			if(isLeaf(currentIdx)){															//if the new root is already a leaf
				return;																		//do nothing
			}
			else{
				if(kidExist(leftKidIndex) && kidExist(rightKidIndex)){						//if both children exists
					minKidIndex = findMinKidIndex(leftKidIndex, rightKidIndex);				//compares the data of left and right children
				}																			//or else at least one children exists, 
				else if(kidExist(leftKidIndex)){											//check if it has a left children
					minKidIndex = leftKidIndex;
				}
				else																		//else it has a right children
					minKidIndex = rightKidIndex;
				
				if(heapAry[minKidIndex] < heapAry[currentIdx]){								//compare the current data and smaller of the two children
					swap(minKidIndex, currentIdx);											//swap place if children has a smaller value
					bubbleDown(minKidIndex);												//continue to bubble down if possible, using recursion
				}
			}
		}
		bool isLeaf(int idx){																//checks if current data is a leaf using the index	
			if(!kidExist(leftKidIndex) && !kidExist(rightKidIndex)){						//if both of the so-called children's index is out of bound, then they dont exist
				return true;																//which makes current data a leaf
			}
			else																			//else if one children exists
				return false;																//the data is not a leaf
		}
		bool isRoot(int idx){																//checks if current data is a root by using it's index value
			if(idx == 1){																	//if index is 1
				return true;																//must be the root
			}
			else 
				return false;
		}
		int findMinKidIndex(int leftIdx, int rightIdx){										//finds which children has a smaller value stored
			if(heapAry[leftIdx] < heapAry[rightIdx]){										//compares the two data using their index value
				return leftIdx;																//return left children's index if data is smaller
			}
			else
				return rightIdx;
		}
		bool isHeapEmpty(){																	//checks if the heap is empty
			if(heapAry[0] == 0){															//if index of last data stored is 0
				return true;																//then the heap is empty
			}
			else
				return false;
		}
		bool isHeapFull(){																	//checks if the heap is full
			if(heapAry[0] == numInt){														//if the last index is equal to the number of integers found
				return true;																//then the heap is full
			}
			else
				return false;
		}
		void printHeap(ofstream& out1){														//prints the first ten items into the output file for debugging purposes
			out1 << "Current Heap:\t";														//current heap items
			if(heapAry[0] >= 10){															//if heap have ten or more items
				for(int i=1; i<11; i++){													//only print the first ten
					out1<<heapAry[i]<<"\t";									
				}
	
			}
			else{																			//else the heap doesnt even have at least ten items
				for(int i=1; i<=heapAry[0]; i++){											//only print what the heap have
					out1<<heapAry[i]<<"\t";
				}	
			}
			out1<<endl;
			
		}
		void swap(int x, int y){															//swap the data in the two array indexes
			int tempValue;																
			tempValue = heapAry[x];
			heapAry[x] = heapAry[y];
			heapAry[y] = tempValue;
		}
		bool isDuplicate(int d){															//check if new data value already exist in heap
			for(int i=1; i<=heapAry[0]; i++){
				if(d == heapAry[i])															//if so, it is a duplicate
					return true;
			}	
			return false;																	//else, not
		}
		bool kidExist(int index){															//check if the children index is in range to see if it exist
			if(index <= heapAry[0])
				return true;
			else
				return false;
		}
};

int countData(ifstream& r){
	r.seekg(0, r.beg);																		//rereads from the beginning of the text file
	int c = 0;
	int d;
	while(!r.eof()){
		r >> d;
		c++;
	}
	return c;
}

int main(int argc, char** argv){															//builds a heap out of positive integers where repeated value is omitted
	//decalration of variables
	int count;																				//number of integers in the input file
	ifstream read;																			//to read the input file
    ofstream write1;																		//write into an output file
    ofstream write2;																		//write into an output file
    read.open(argv[1]);																		//opens up the input file
    write1.open(argv[2]);																	//opens up the first output file
    write2.open(argv[3]);																	//opens up the second output file
	
	//check the number of arguments
	if (argc != 4) {																		//error from invalid number of arguments
        cerr << "Error: Number of arguments unsatisfied."<<endl;
        exit(1);
    }
    
    read.seekg(0, std::ios::end);															//first check if file is empty
	if (read.tellg() == 0){
		cerr << "File is empty." << endl;
		exit(1);
	}
	
    count = countData(read);																//reads the input file and count the number of integers
    HeapSort tree(count + 1);																//calls HeapSort constructor to initialize an array of size 'count + 1'
    tree.buildHeap(read, write1);															//builds the heap using the input file and then print to output file #1 after every change (bubbleUp) for debugging purpose	
    tree.deleteHeap(write2, write1);														//print root data to output file #1 after each deletion, also print to output file #1 after every change (bubbleDown) for debugging purpose
    
    read.close();
    write1.close();
    write2.close();
	return 0;
}//output the integers in an ascending order using heapSort




