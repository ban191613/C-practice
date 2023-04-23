// #include <iostream>
// #include <vector>
// #include "linearList.h"
// #include "vectorList.h"
// #include "chainList.h"
// #include "my_matrix.h"
// #include "my_stack.h"
// #include"my_queue.h"
// int main()
// {
//     // linearList<int> *x=new arrayList<int>(100);
//     // vectorList<int> *y=new vectorList<int>(100);
//     // delete x;
//     // delete y;
//     linearList<int> *z=new vectorList<int>(100);
//     delete z;

//     cout << "finish!";

//     return 0;
// }
#include <iostream>
#include <queue>
using std::cout;
using std::queue;
struct task;
struct job;
struct machine;
class eventList;

int timeNow; // 当前时间
int numMachine; //机器数量
int numJobs; // 任务数量
eventList* eList; // 事件表的指针
machine* mArray;     // 机器指针
int largeTime=10000;  //在这个时间内机器都已经完成工作
struct task
{
    int machine;
    int time;
    task(int machine=0,int time=0):machine(machine),time(time)
    {

    }
};
struct job  //工序表
{
    queue<task> taskQ;  //工序表
    int length;         //被调度的工序时间之和
    int arrivalTime;    //到达当前队列的时间
    int id;             //任务的标识符
    job(int id=0):id(id)
    {
        length=0;
        arrivalTime=0;
    }
    void addTask(int machine,int time)
    {
        task thetask(machine,time);
        taskQ.push(thetask);
    }
    int remove_next_task()   //执行完一项工序增加了length 返回的这项工序的时间
    {
        int thetime=taskQ.front().time;
        taskQ.pop();
        length+=thetime;
        return thetime;
    }
};
struct machine
{
    queue<job*> jobQ; //机器的执行队列
    int changetime;   //机器的转换时间
    int totalwait;     //机器的总体延时
    int numtasks;      //机器的处理工序数
    job* activejob;  // 机器当前处理的任务
    machine():totalwait(0),numtasks(0),activejob(NULL)
    {
    }
};
class eventList
{
private:
    int numMachines;  //机器数量
    int *finishTime; //完成时间组数
public:
    eventList(int Numbermachine,int Largetime){
        if (Numbermachine<1)
        {
            cout<<"error!";
        }
        numMachines=Numbermachine;
        finishTime=new int [numMachines+1];
        for (int  i = 1; i < numMachines; i++)
        {
            finishTime[i]=Largetime;
        }
        
    };
    ~eventList()
    {
        delete [] finishTime;
    }
    int nextEventMachine()
    {
        int p=1;
        int t=finishTime[1];
        for (int  i = 2; i <= numMachines; i++)
        {
            if (finishTime[i]<t)
            {
                p=i;
                t=finishTime[i];
            }
            
        }
        return p;
    }
    int nextEventtime(int machine){return finishTime[machine];}
    void setfinishtime(int machine,int time)
    {
        finishTime[machine]=time;
    }
};

void inputData()
{
    
}
void startShop()
{

}
void simulate()
{

}
void outputStatistices()
{

}

int main()
{

    inputData();//获取机器和任务数量
    startShop();//装入初始任务
    simulate();//执行仿真
    outputStatistices();//输出结果
    cout << "finish!";

    return 0;
}
// #include "stack"
// #include "string"
// #include "iostream"
// #include "array"

// using namespace std;

// array<int, 10> arr;
// stack<int> *track;
// int numberofcars;
// int numberoftrack;
// int smallestcar;
// int itstrack;
// bool putin(int c)
// {
//     int besttrck = -1;
//     int bestTop = numberofcars + 1;
//     for (int i = 0; i < numberoftrack; i++)
//     {
//         if (track[i].empty())
//         {
//             besttrck = i;
//         }
//         else
//         {
//             int topcar = track[i].top();
//             if (c < topcar && topcar < bestTop)
//             {
//                 bestTop = topcar;
//                 besttrck = i;
//             }
//         }
//     }
//     if (besttrck == -1)
//     {
//         return false;
//     }
//     cout << "in" << c << endl;
//     track[besttrck].push(c);
//     if (c < smallestcar)
//     {
//         smallestcar = c;
//         itstrack = besttrck;
//     }
//     return true;
// }
// bool railload(int intputOrder[], int theNumberofCars, int theNumberoftracks)
// {
//     numberofcars = theNumberofCars;
//     numberoftrack = theNumberoftracks;
//     track = new stack<int>[numberoftrack];
//     int nextCarToOoutput = 1;
//     smallestcar = numberofcars + 2;
//     for (int i = 0; i < numberofcars; i++)
//     {
//         if (nextCarToOoutput == intputOrder[i])
//         {
//             cout << "out" << intputOrder[i] << endl;
//             cout << i << endl;
//             nextCarToOoutput++;
//             while (smallestcar == nextCarToOoutput)
//             {
//                 cout << "out" << track[itstrack].top() << endl;
//                 track[itstrack].pop();

//                 smallestcar = numberofcars + 1;
//                 // 输出
//                 for (int j = 0; j < numberoftrack; j++)
//                 {

                    
//                     if (!track[j].empty() and track[j].top() < smallestcar)
//                     {
//                         smallestcar = track[j].top();
//                         itstrack=j;
//                     }
//                 }
//                 nextCarToOoutput++;
//             }
//         }
//         else // 放入stack
//         {
//             if (!putin(intputOrder[i]))
//             {
//                 return false;
//             }
//         }
//     }
//     return true;
// }
// int main()
// {
//     int a[] = {5, 8, 1, 7, 4, 2, 9, 6, 3};
//     cout << railload(a, 9, 3);
//     return 0;
// }
// #include "stack"
// #include "string"
// #include "iostream"
// #include "array"

// using namespace std;

// array<int, 10> arr;
// stack<int> *track;
// int numberofcars;
// int numberoftrack;
// int smallestcar;
// int itstrack;
// bool putin(int c)
// {
//     int besttrck = -1;
//     int bestTop = numberofcars + 1;
//     for (int i = 0; i < numberoftrack; i++)
//     {
//         if (track[i].empty())
//         {
//             besttrck = i;
//         }
//         else
//         {
//             int topcar = track[i].top();
//             if (c < topcar && topcar < bestTop)
//             {
//                 bestTop = topcar;
//                 besttrck = i;
//             }
//         }
//     }
//     if (besttrck == -1)
//     {
//         return false;
//     }
//     cout << "in" << c << endl;
//     track[besttrck].push(c);
//     if (c < smallestcar)
//     {
//         smallestcar = c;
//         itstrack = besttrck;
//     }
//     return true;
// }
// bool railload(int intputOrder[], int theNumberofCars, int theNumberoftracks)
// {
//     numberofcars = theNumberofCars;
//     numberoftrack = theNumberoftracks;
//     track = new stack<int>[numberoftrack];
//     int nextCarToOoutput = 1;
//     smallestcar = numberofcars + 2;
//     for (int i = 0; i < numberofcars; i++)
//     {
//         if (nextCarToOoutput == intputOrder[i])
//         {
//             cout << "out" << intputOrder[i] << endl;
//             cout << i << endl;
//             nextCarToOoutput++;
//             while (smallestcar == nextCarToOoutput)
//             {
//                 cout << "out" << track[itstrack].top() << endl;
//                 track[itstrack].pop();

//                 smallestcar = numberofcars + 1;
//                 // 输出
//                 for (int j = 0; j < numberoftrack; j++)
//                 {

                    
//                     if (!track[j].empty() and track[j].top() < smallestcar)
//                     {
//                         smallestcar = track[j].top();
//                         itstrack=j;
//                     }
//                 }
//                 nextCarToOoutput++;
//             }
//         }
//         else // 放入stack
//         {
//             if (!putin(intputOrder[i]))
//             {
//                 return false;
//             }
//         }
//     }
//     return true;
// }
// int main()
// {
//     int a[] = {5, 8, 1, 7, 4, 2, 9, 6, 3};
//     cout << railload(a, 9, 3);
//     return 0;
// }
// #include "stack"
// #include "string"
// #include "iostream"
// using namespace std;
// void printMatchpairs(string s)
// {
//     int n=s.size();
//     stack<int> st;
//     for (int i = 0; i < n; i++)
//     {
//         if (s.at(i)=='(')
//         {
//             st.push(i);
//         }
//         else if (s.at(i)==')')
//         {
//             try
//             {
//                 cout<<i<<"and"<<st.top();
//                 st.pop();
//             }
//             catch(const std::exception& e)
//             {
//             }

//         }
//     }
//     if(!st.empty())
//     {
//         cout<<"error!";
//     }

// }
// int main()
// {
//     printMatchpairs("() ()( )()");
//     return 0;
// }

// vector
//  vector<int> a(10);
//  a.push_back(1);
//  for (vector<int>::iterator it = a.begin(); it < a.end(); it++)
//  {
//      *it =1;
//      cout << *it << endl;
//  }
//  a.erase(a.begin() + 3);
//  a.clear();
//  a.resize(5);
//  a.reserve(50);
//  for (vector<int>::iterator it = a.begin(); it < a.end(); it++)
//  {
//      cout << *it << endl;
//  }
//  cout << a.max_size() << endl
//       << a.capacity() << a.size();
//