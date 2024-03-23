#include <bits/stdc++.h>

using namespace std;

////----------------------------------Process Class----------------------------------
class Process{
    public: 
        char name;
        int arrival_time;
        int service_time;
};

//----------------------------------Global Variables----------------------------------
const string ALGORITHMS[8] = {"FCFS", "SJN-", "SRTN", "HRRN", "RRvQ", "AGNG"};
int ALGORITHM = 0;
vector<Process> PROCESSES;
vector<string> TIMELINE;
vector<int> FINISH_TIME;
vector<float> TURNAROUND_TIME;
vector<float> NORM_TURN_TIME;
vector<int> PRIORITY;

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

int getTurnaroundTime(int idx){
    return TURNAROUND_TIME[idx];
}

void setTurnaroundTime(int idx, int arrival_time, int finish_time){
    TURNAROUND_TIME[idx] =  finish_time - arrival_time;
}

float getNormalizedTurnaroundTime(int idx){
    return NORM_TURN_TIME[idx];
}

void setNormalizedTurnaroundTime(int idx, int service_time){
    NORM_TURN_TIME[idx] = (float)TURNAROUND_TIME[idx]/(float)service_time;
}

string getAlgorithm(){
    return ALGORITHMS[ALGORITHM];
}

int getPriorityLevel(int process_idx){
    return PRIORITY[process_idx];
}

void setPriorityLevel(int process_idx, int priority){
    PRIORITY[process_idx] = priority;
}

//----------------------------------Utility Functions----------------------------------
void fillWatitingTime(){
    //Fill waiting time for each process
    for(int i = 0; i<getCount(); i++){
        Process process = getProcess(i);
        int arrival = process.arrival_time;
        int finish = getFinishTime(i);
        string timeline = getTimeline(i);
        //If the process wasn't getting executed (but it has arrived) from arrival to finish time it means it's in waiting state.
        for(int j = arrival+1; j<=finish; j++){
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

float meanTurnaroundTime(){
    float mean = 0;
    for(int i = 0; i<getCount(); i++){
        mean += getTurnaroundTime(i);
    }
    return mean/(float)getCount();
}

float meanNormalizedTurnaroundTime(){
    float mean = 0;
    for(int i = 0; i<getCount(); i++){
        mean += getNormalizedTurnaroundTime(i);
    }
    return mean/(float)getCount();
}

void printArr(vector<int>& arr){
    for(int i = 0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
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

//----------------------------------Comparators----------------------------------
bool sortByArrivalTime(const Process& a, const Process& b){
    return a.arrival_time < b.arrival_time;
}

class SortByServiceTimeSJN{
    public:
        bool operator()(pair<Process, int> p1, pair<Process, int> p2){
            //If service time is different, sort on the basis of lesser service time.
            if(p1.first.service_time != p2.first.service_time) return p1.first.service_time > p2.first.service_time;
            //Else sort on the basis of lesser arrival time to reduce waiting time.
            else return p1.first.arrival_time > p2.first.arrival_time;
        }
};

class SortByServiceTimeSRTN{
    public:
        bool operator()(tuple<Process, int, int> t1, tuple<Process, int, int> t2){
            if(get<2>(t1) != get<2>(t2)) return get<2>(t1) > get<2>(t2);
            else return get<0>(t1).arrival_time > get<0>(t2).arrival_time;
        }
};

class SortByResponseRatio{
    public:
        bool operator()(tuple<Process, int, int> t1, tuple<Process, int, int> t2){
            float response_ratio_t1 = (float)(get<2>(t1) + get<0>(t1).service_time)/(float)get<0>(t1).service_time;
            float response_ratio_t2 = (float)(get<2>(t2) + get<0>(t2).service_time)/(float)get<0>(t2).service_time;
            return response_ratio_t1 < response_ratio_t2;
        }
};

//----------------------------------Algorithms----------------------------------
void aging(int Quantum){

}

void roundRobinVaryingQuantum(int Quantum){
    int time = 0, executed = 0;
    queue<pair<int, int>> q;
    vector<bool> inserted(getCount());
    while(executed<getCount()){
        for(int i = 0; i<getCount(); i++){
            Process curr = getProcess(i);
            //If current process' arrival time is less than or equal to time and not already inserted in q, insert it.
            if(curr.arrival_time<=time && !inserted[i]){
                q.push({i, curr.service_time});
                inserted[i] = true;
            }
        }

        if(q.empty()){
            time++;
            for(int j = 0; j<getCount(); j++){
                TIMELINE[j] += "| ";
            }
            continue;
        }

        int process_idx = q.front().first;
        int burst_time = q.front().second;
        q.pop();

        //If process didn't got executed in the current time quantum
        if(burst_time>Quantum){
            for(int i = 0; i<getCount(); i++){
                for(int k = time; k<time+Quantum; k++){
                    if(i==process_idx) TIMELINE[i] += "|*";
                    else TIMELINE[i] += "| ";
                }
            }
            time += Quantum;
        }
        //If process got executed
        else{
            for(int i = 0; i<getCount(); i++){
                for(int k = time; k<time+burst_time; k++){
                    if(i==process_idx) TIMELINE[i] += "|*";
                    else TIMELINE[i] += "| ";
                }
            }
            Process process = getProcess(process_idx);
            time += burst_time;
            setFinishTime(process_idx, time);
            setTurnaroundTime(process_idx, process.arrival_time, time);
            setNormalizedTurnaroundTime(process_idx, process.service_time);
            executed++;
        }
        
        //Since time passed, processes maybe available for execution so add them.
        for(int i = 0; i<getCount(); i++){
            Process curr = getProcess(i);
            //If current process' arrival time is less than or equal to time and not already inserted in q, insert it.
            if(curr.arrival_time<=time && !inserted[i]){
                q.push({i, curr.service_time});
                inserted[i] = true;
            }
        }

        //Push the current process if burst_time was more than Quantum that is, it didn't got executed. 
        if(burst_time>Quantum) q.push({process_idx, burst_time-Quantum});
    }

    fillWatitingTime();
}

void highestResponseRatioNext(){
    int time = 0, executed = 0;
    vector<bool> inserted(getCount());
    priority_queue<tuple<Process, int, int>, vector<tuple<Process, int, int>>, SortByResponseRatio> pq;
    while(executed<getCount()){
        for(int i = 0; i<getCount(); i++){
            Process curr = getProcess(i);
            //If current process' arrival time is less than or equal to time and not already inserted in pq, insert it.
            if(curr.arrival_time<=time && !inserted[i]){
                pq.push(make_tuple(curr, i, time-curr.arrival_time));
                inserted[i] = true;
            }
        }

        if(pq.empty()){
            time++;
            for(int j = 0; j<getCount(); j++){
                TIMELINE[j] += "| ";
            }
            continue;
        }

        Process process = get<0>(pq.top());
        int process_idx = get<1>(pq.top());
        int waiting_time = get<2>(pq.top());
        pq.pop();

        for(int i = 0; i<getCount(); i++){
            for(int k = time; k<time+process.service_time; k++){
                if(i==process_idx) TIMELINE[i] += "|*";
                else TIMELINE[i] += "| ";
            }
        }

        time += process.service_time;
        //Add waiting time for processes
        setFinishTime(process_idx, time);
        setTurnaroundTime(process_idx, process.arrival_time, time);
        setNormalizedTurnaroundTime(process_idx, process.service_time);
        executed++;

        //Increase the waiting time for all the processes in the queue. 
        vector<tuple<Process, int, int>> temp;
        while(!pq.empty()){
            auto curr = pq.top();
            pq.pop();
            get<2>(curr) = get<2>(curr) + process.service_time;
            temp.push_back(curr);
        }
        for(int i = 0; i<temp.size(); i++) pq.push(temp[i]);
    }

    fillWatitingTime();
}

void shortestRemainingTimeNext(){
    int time = 0, executed = 0;
    vector<bool> inserted(getCount());
    priority_queue<tuple<Process, int, int>, vector<tuple<Process, int, int>>, SortByServiceTimeSRTN> pq; 
    while(executed<getCount()){
        for(int i = 0; i<getCount(); i++){
            Process curr = getProcess(i);
            //If current process' arrival time is less than or equal to time and not already inserted in pq, insert it.
            if(curr.arrival_time<=time && !inserted[i]){
                pq.push(make_tuple(curr, i, curr.service_time));
                inserted[i] = true;
            }
        }

        if(pq.empty()){
            time++;
            for(int j = 0; j<getCount(); j++){
                TIMELINE[j] += "| ";
            }
            continue;
        }

        Process process = get<0>(pq.top());
        int process_idx = get<1>(pq.top());
        int service_time = get<2>(pq.top());
        pq.pop();

        ////Execute process for 1 unit time
        service_time -= 1;
        time += 1;
        for(int i = 0; i<getCount(); i++){
            if(i==process_idx) TIMELINE[i] += "|*";
            else TIMELINE[i] += "| ";
        }

        //If burst time is left, add the process again to pq.
        if(service_time>0) pq.push({process, process_idx, service_time});
        else{
            //Else the process has been executed
            setFinishTime(process_idx, time);
            setTurnaroundTime(process_idx, process.arrival_time, time);
            setNormalizedTurnaroundTime(process_idx, process.service_time);
            executed++;
        }
    }
    
    fillWatitingTime();
}

void shortestJobNext(){
    int time = 0, executed = 0;
    vector<bool> inserted(getCount());
    priority_queue<pair<Process, int>, vector<pair<Process, int>>, SortByServiceTimeSJN> pq; 
    while(executed<getCount()){
        for(int i = 0; i<getCount(); i++){
            Process curr = getProcess(i);
            //If current process' arrival time is less than or equal to time and not already inserted in pq, insert it.
            if(curr.arrival_time<=time && !inserted[i]){
                pq.push({curr, i});
                inserted[i] = true;
            }
        }

        //If pq is empty implies no process has arrived yet, increment time.
        if(pq.empty()){
            time++;
            for(int j = 0; j<getCount(); j++){
                TIMELINE[j] += "| ";
            }
            continue;
        }

        //Execution
        Process process = pq.top().first;
        int process_idx = pq.top().second;
        pq.pop();

        for(int j = 0; j<getCount(); j++){
            for(int k = time; k<time+process.service_time; k++){
                if(process_idx==j) TIMELINE[j] += "|*";
                else TIMELINE[j] += "| ";
            }
        }

        //After execution service_time amount of time will be passed.
        time += process.service_time;
        setFinishTime(process_idx, time);
        setTurnaroundTime(process_idx, process.arrival_time, time);
        setNormalizedTurnaroundTime(process_idx, process.service_time);
        executed++;
    }

    fillWatitingTime();
}

void firstComeFirstServe(){
    // Sorting the processes on the basis of Arrival Time so that processes arriving earlier should be processed earlier.
    sort(PROCESSES.begin(), PROCESSES.end(), sortByArrivalTime);
    int time = 0;
    for(int i = 0; i<getCount(); i++){
        Process curr = getProcess(i);
        int arrival = curr.arrival_time;

        //If arrival of process is greater than time, it means there are no processes to execute for now, so make the Timeline empty till time equals arrival time.
        if(arrival>time){
            for(int j = 0; j<getCount(); j++){
                for(int k = time; k<arrival; k++){
                    TIMELINE[j] += "| ";
                }
            }
            time = arrival;
        }
        
        //Print "*" for the process getting executed and " " for all the other processes.
        for(int j = 0; j<getCount(); j++){
            for(int k = time; k<time+curr.service_time; k++){
                if(i==j) TIMELINE[j] += "|*";
                else TIMELINE[j] += "| ";
            }
        }

        //Time passed will be equal to service_time of executed process.
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
    cout<<"| Mean|"<<endl;
}

void printFinishTime(){
    cout<<"Finish     ";
    for(int i = 0; i<getCount(); i++){
        int finish = getFinishTime(i);
        printStatsFormat(finish);
    }
    cout<<"|-----|"<<endl;
}

void printTurnaroundTime(){
    cout<<"Turnaround ";
    for(int i = 0; i<getCount(); i++){
        int turnaround = getTurnaroundTime(i);
        printStatsFormat(turnaround);
    }
    float mean = meanTurnaroundTime();
    printf("| %.2f|\n", mean);
}

void printNormalizedTurnaroundTime(){
    cout<<"NormTurn   ";
    for(int i = 0; i<getCount(); i++){
        float normTurn = getNormalizedTurnaroundTime(i);
        printf("| %.2f", normTurn);
    }
    float mean = meanNormalizedTurnaroundTime();
    printf("| %.2f|\n", mean);
}

void printStats(){
    string algorithm = getAlgorithm();
    cout<<algorithm<<endl;
    printProcesses();
    printArrivalTime();
    printServiceTime();
    printFinishTime();
    printTurnaroundTime();
    printNormalizedTurnaroundTime();
}

//----------------------------------Input Handlers----------------------------------
void algorithmHandler(int algorithm, int operation){
    ALGORITHM = algorithm-1;
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
    PRIORITY.resize(getCount());
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
    cout<<"3. Shortest Remaining Time Next"<<endl;
    cout<<"4. Highest Response Ratio Next"<<endl;
    cout<<"5. Round Robin with varying Quantum"<<endl;
    cout<<"6. Aging"<<endl;
    cin>>algorithm;

    switch(algorithm){
        case 1:
            firstComeFirstServe();
            algorithmHandler(1, operation);
            break;
        case 2:
            shortestJobNext();
            algorithmHandler(2, operation);
            break;
        case 3:
            shortestRemainingTimeNext();
            algorithmHandler(3, operation);
            break;
        case 4:
            highestResponseRatioNext();
            algorithmHandler(4, operation);
            break;
        case 5:
            int quantum;
            cout<<"Enter Time Quantum: ";
            cin>>quantum;
            if(quantum<=0) break;
            roundRobinVaryingQuantum(quantum);
            algorithmHandler(5, operation);
            break;
        case 6:
            cout<<"Enter priority of processes in order of input: ";
            for(int i = 0; i<getCount(); i++) cin>>PRIORITY[i];
            int quantum;
            cin>>quantum;
            aging(quantum);
            algorithmHandler(6, operation);
            break;
        default:
            break;
    }

    return 0;
}