#include <bits/stdc++.h>

using namespace std;

class Process{
    public: 
        string name;
        int arrival_time;
        int service_time;
};

/**Global Variables*/
const string ALGORITHMS[1] = {"FCFS"};
vector<Process> PROCESSES;
vector<string> TIMELINE;

void printProcesses(){
    for(int i = 0; i<PROCESSES.size(); i++){
        Process process = PROCESSES[i];
        cout<<process.name<<" "<<process.arrival_time<<" "<<process.service_time<<endl;
    }
}

bool sortByArrivalTime(Process& a, const Process& b){
    return a.arrival_time < b.arrival_time;
}

void firstComeFirstServe(){
    //Sorting the processes on the basis of Arrival Time so that processes arriving earlier should be processed earlier.
    sort(PROCESSES.begin(), PROCESSES.end(), sortByArrivalTime);

}

void printTimeline(){

}

void printStats(){

}

void inputProcesses(){
    cout<<"Provide details about processes."<<endl;
    cout<<"Format: Process_Name Arrival_Time Service_Time"<<endl;
    cout<<"Press 0 to exit."<<endl;
    
    while(1){
        string process_name;
        int arrival_time, service_time;
        cin>>process_name;
        if(process_name=="0") break;

        Process process;
        cin>>arrival_time>>service_time;

        process.name = process_name;
        process.arrival_time = arrival_time;
        process.service_time = service_time;
        PROCESSES.push_back(process);
    }

    TIMELINE.resize(PROCESSES.size());
}

int main(){
    int operation, algorithm;
    
    cout<<"Enter operation to perform: "<<endl;
    cout<<"1. Trace Algorithm"<<endl;
    cout<<"2. Get Stats"<<endl;
    cout<<"3. Exit"<<endl;
    cin>>operation;

    inputProcesses();
    cout<<"Choose an algorithm: "<<endl;
    cout<<"1. FCFS"<<endl;
    cin>>algorithm;

    switch(algorithm){
        case 1:
            firstComeFirstServe();
            if(operation==1) printStats();
            else printTimeline();
    }

    return 0;
}