#include <bits/stdc++.h>

using namespace std;

class Process{
    public: 
        char name;
        int arrival_time;
        int service_time;
};

/**Global Variables*/
const string ALGORITHMS[1] = {"FCFS"};
int ALGORITHM;
vector<Process> PROCESSES;
vector<string> TIMELINE;
vector<int> FINISH_TIME;
vector<int> TURNAROUND_TIME;
vector<int> NORM_TURN_TIME;

void printProcesses(){
    for(int i = 0; i<PROCESSES.size(); i++){
        Process process = PROCESSES[i];
        cout<<process.name<<" "<<process.arrival_time<<" "<<process.service_time<<endl;
    }
}

void printArr(vector<int>& arr){
    for(int i = 0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

Process getProcess(int idx){
    return PROCESSES[idx];
}

int getFinishTime(int idx){
    return FINISH_TIME[idx];
}

int getCount(){
    return PROCESSES.size();
}

string getTimeline(int idx){
    return TIMELINE[idx];
}

void updateTimeline(string newTimeline, int idx){
    TIMELINE[idx] = newTimeline;
}

bool sortByArrivalTime(const Process& a, const Process& b){
    return a.arrival_time < b.arrival_time;
}

void fillWatitingTime(){
    for(int i = 0; i<getCount(); i++){
        Process process = getProcess(i);
        int arrival = process.arrival_time;
        int finish = getFinishTime(i);
        string timeline = getTimeline(i);
        for(int j = arrival+1; j<finish; j++){
            if(timeline[j*2-1]==' ') timeline[j*2-1] = '.';
        }
        updateTimeline(timeline, i);
    }
}

void firstComeFirstServe(){
    // Sorting the processes on the basis of Arrival Time so that processes arriving earlier should be processed earlier.
    sort(PROCESSES.begin(), PROCESSES.end(), sortByArrivalTime);
    int time = -1;
    for(int i = 0; i<getCount(); i++){
        Process curr = getProcess(i);
        if(time==-1){
            time = curr.arrival_time;
        }
        int arrival = curr.arrival_time;
        if(arrival>time){
            for(int j = 0; j<getCount(); j++){
                for(int k = time; k<arrival; k++){
                    TIMELINE[j] += "| ";
                }
            }
            time = arrival;
        }
        
        for(int j = 0; j<getCount(); j++){
            for(int k = time; k<time+curr.service_time; k++){
                if(i==j) TIMELINE[j] += "|*";
                else TIMELINE[j] += "| ";
            }
        }
        time += curr.service_time;
        FINISH_TIME[i] = time;
    }
    fillWatitingTime();
}

void printTimeline(){
    cout<<ALGORITHMS[ALGORITHM]<<"\t";
    
    int totalTime = TIMELINE[0].size()/2;
    for(int i = 0; i<totalTime/10; i++){
        for(int j = 0; j<=9; j++) cout<<j<<" ";
    }
    for(int i = 0; i<=totalTime%10; i++) cout<<i<<" ";
    cout<<endl;

    int dashes = 8 + TIMELINE[0].size();
    for(int i = 0; i<=dashes; i++) cout<<"-";
    cout<<endl;

    for(int i = 0; i<TIMELINE.size(); i++){
        cout<<PROCESSES[i].name<<"\t"<<TIMELINE[i]<<"|"<<endl;
    }

    for(int i = 0; i<=dashes; i++) cout<<"-";
    cout<<endl;
}

void printStats(){

}

void inputProcesses(){
    cout<<"Provide details about processes."<<endl;
    cout<<"Format: Process_Name Arrival_Time Service_Time"<<endl;
    cout<<"Press 0 to exit."<<endl;

    while(1){
        char process_name;
        int arrival_time, service_time;
        cin>>process_name;
        if(process_name=='0') break;

        Process process;
        cin>>arrival_time>>service_time;

        process.name = process_name;
        process.arrival_time = arrival_time;
        process.service_time = service_time;
        PROCESSES.push_back(process);
    }

    TIMELINE.resize(getCount());
    FINISH_TIME.resize(getCount());
    TURNAROUND_TIME.resize(getCount());
    NORM_TURN_TIME.resize(getCount());
}

int main(){
    int operation, algorithm;
    
    cout<<"Enter operation to perform: "<<endl;
    cout<<"1. Trace Algorithm"<<endl;
    cout<<"2. Get Stats"<<endl;
    cin>>operation;

    inputProcesses();
    cout<<"Choose an algorithm: "<<endl;
    cout<<"1. FCFS"<<endl;
    cin>>algorithm;

    switch(algorithm){
        case 1:
            firstComeFirstServe();
            ALGORITHM = 0;
            if(operation==1) printTimeline();
            else printStats();
    }

    return 0;
}