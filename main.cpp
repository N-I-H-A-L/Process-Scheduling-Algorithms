#include <bits/stdc++.h>

using namespace std;

class Process{
    public: 
        char name;
        int arrival_time;
        int service_time;
};

//----------------------------------Global Variables----------------------------------
const string ALGORITHMS[2] = {"FCFS", "SJF-"};
int ALGORITHM;
vector<Process> PROCESSES;
vector<string> TIMELINE;
vector<int> FINISH_TIME;
vector<float> TURNAROUND_TIME;
vector<int> NORM_TURN_TIME;

//----------------------------------Getter and Setter Functions----------------------------------
Process getProcess(int idx){
    return PROCESSES[idx];
}

int getFinishTime(int idx){
    return FINISH_TIME[idx];
}

void setFinishTime(int idx, int time){
    FINISH_TIME[idx] = time;
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

void setTurnaroundTime(int idx, int arrival_time, int finish_time){
    TURNAROUND_TIME[idx] =  finish_time - arrival_time;
}

void setNormalizedTurnaroundTime(int idx, int service_time){
    NORM_TURN_TIME[idx] = (float)TURNAROUND_TIME[idx]/(float)service_time;
}

string getAlgorithm(){
    return ALGORITHMS[ALGORITHM];
}

//----------------------------------Utility Functions----------------------------------
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

int getDigitCount(int num){
    int digits = 0;
    do{
        num /= 10;
        digits++;
    }while(num>0);
    return digits;
}

void printStatsFormat(int value){
    int digits = getDigitCount(value);
    int leftSpaces, rightSpaces;
    int remainingSpaces = 5-digits;
    if(remainingSpaces%2==0) leftSpaces = rightSpaces = remainingSpaces/2;
    else{
        leftSpaces = remainingSpaces/2;
        rightSpaces = remainingSpaces - leftSpaces;
    }
    cout<<"|";
    for(int i = 0; i<leftSpaces; i++){
        cout<<" ";
    }
    cout<<value;
    for(int i = 0; i<rightSpaces; i++){
        cout<<" ";
    }
}

//----------------------------------Sorting Functions----------------------------------
bool sortByArrivalTime(const Process& a, const Process& b){
    return a.arrival_time < b.arrival_time;
}

bool sortByServiceTime(const Process& a, const Process& b){
    return a.service_time < b.service_time;
}

//----------------------------------Algorithms----------------------------------
void shortestJobNext(){

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
        setFinishTime(i, time);
        setTurnaroundTime(i, curr.arrival_time, time);
        setNormalizedTurnaroundTime(i, curr.service_time);
    }
    fillWatitingTime();
}

//----------------------------------Print Functions----------------------------------
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

void printProcesses(){
    cout<<"Process    ";
    for(int i = 0; i<getCount(); i++){
        cout<<"|  "<<getProcess(i).name<<"  ";
    }
    cout<<"|"<<endl;
}

void printArrivalTime(){
    cout<<"Arrival    ";
    for(int i = 0; i<getCount(); i++){
        int arrival = getProcess(i).arrival_time;
        printStatsFormat(arrival);
    }
    cout<<"|"<<endl;
}

void printServiceTime(){
    cout<<"Service    ";
    for(int i = 0; i<getCount(); i++){
        int service = getProcess(i).service_time;
        printStatsFormat(service);
    }
    cout<<"|"<<endl;
}

void printStats(){
    string algorithm = getAlgorithm();
    cout<<algorithm<<endl;
    printProcesses();
    printArrivalTime();
    printServiceTime();
    // printFinishTime();
    // printTurnaroundTime();
    // printNormTurnTime();
}

void printArr(vector<int>& arr){
    for(int i = 0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

//----------------------------------Input Handlers----------------------------------

void algorithmHandler(int algorithm_idx, int operation){
    ALGORITHM = algorithm_idx;
    if(operation==1) printTimeline();
    else printStats();
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
    cout<<"2. Shortest Job Next"<<endl;
    cin>>algorithm;

    switch(algorithm){
        case 1:
            firstComeFirstServe();
            algorithmHandler(0, operation);
            break;
        case 2:
            shortestJobNext();
            algorithmHandler(1, operation);
            break;
    }

    return 0;
}