#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool matrixValid(const AvailabilityMatrix& avail, const size_t maxShifts,
    DailySchedule& sched,
		unsigned int row, unsigned int num);
bool solveSchedule(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
	  unsigned int row, unsigned int col);
unsigned int countOccurrences(DailySchedule& sched, unsigned int num);
// Add your implementation of schedule() and other helper functions here
unsigned int countOccurrences(DailySchedule& sched, unsigned int num){
	unsigned int count= 0;
	//look through sched and count occurences of worker id
	for(unsigned int i=0; i<sched.size(); i++){
		for(unsigned int j=0; j<sched[i].size();j++){
			if(sched[i][j]==num){
				count++;
			}
		}
	}
	return count;
}

bool matrixValid(const AvailabilityMatrix& avail, const size_t maxShifts,
    DailySchedule& sched,
		unsigned int row, unsigned int num)
		{
			//if worker is available on this day
			if(avail[row][num]==1){
				//check that they're not already working this day
				bool inRow = false;
				for(unsigned int i=0; i<sched[row].size(); i++){
					if(sched[row][i]==num){
						inRow = true;
					}
				}
				if(!inRow){
					//check that they have not reached maxShifts
					unsigned int count = countOccurrences(sched, num);
					if(count<maxShifts){
						return true;
					}
				}
			}
			return false;
		}

bool solveSchedule(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
		unsigned int row, unsigned int col)
		{
			//if we are at the bottom right corner, return true
			if(row==sched.size()-1 && col==dailyNeed){
				return true;
			}
			//increase row if we are at the end of the previous row
			if(col==dailyNeed){
				row++;
				col=0;
			}
			//loop through worker ids
			for(unsigned int i=0; i<avail[0].size(); i++){
				if(matrixValid(avail, maxShifts, sched, row, i)){
					//assign position to worker id and solve on next column 
					sched[row][col] = i;
					if(solveSchedule(avail, dailyNeed, maxShifts, sched, row, col+1)){
						return true;
					}
				}
				//remove assumption 
				sched[row][col] = INVALID_ID;
			}
			return false; 
		}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
		//fill schedule with invalid worker ids
		for(unsigned int i=0; i<avail.size(); i++){
			vector<unsigned int> inner(dailyNeed, INVALID_ID);
			sched.push_back(inner);
		}
		return solveSchedule(avail, dailyNeed, maxShifts, sched, 0, 0); 
}

