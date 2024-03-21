#include <bits/stdc++.h>

using namespace std;

/**Global Variables*/
const string ALGORITHMS[1] = {"FCFS"};
vector<tuple<string, int, int>> PROCESSES;
vector<string> TIMELINE;

void printProcesses(){
    for(int i = 0; i<PROCESSES.size(); i++){
        tuple<string, int, int> process = PROCESSES[i];
        cout<<get<0>(process)<<" "<<get<1>(process)<<" "<<get<2>(process)<<endl;
    }
}

void firstComeFirstServe(){
    printProcesses();
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
        tuple<string, int, int> process;
        cin>>arrival_time>>service_time;
        process = make_tuple(process_name, arrival_time, service_time);
        PROCESSES.push_back(process);
    }
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