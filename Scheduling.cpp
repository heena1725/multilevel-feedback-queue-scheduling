#include <bits/stdc++.h>
using namespace std;

struct Process_Data
{
	int N;
	int Pid;
	int AT;
	int BT;
	int P;
	int FT;
	int RT;
	int WT;
	int ST;
	int Res_T;

};
struct Process_Data current;
typedef struct Process_Data P_d ;

bool idsort(const P_d& x , const P_d& y)
{
	return x.Pid < y.Pid;
}
bool arrivalsort( const P_d& x ,const P_d& y)
{
	if(x.AT < y.AT)
		return true;
	else if(x.AT > y.AT)
		return false;
	if(x.P < y.P)
		return true;
	else if(x.P > y.P)
		return false;
	if(x.Pid < y.Pid)
		return true;

	return false;
}

bool Numsort( const P_d& x ,const P_d& y)
{
	return x.N < y.N;
}

struct comPare
{
	bool operator()(const P_d& x ,const P_d& y)
	{
		if( x.P > y.P )
			return true;
		else if( x.P < y.P )
			return false;
		if( x.Pid > y.Pid )
			return true;

		return false;
	}
};

int main()
{
	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d tmp;
	int pq_process = 0;
	int rq_process = 0;
	int AT;
	int BT;
	int Pid;
	int P;
	int n;
	int clock;
	int total_time = 0;
	cout<<"Enter Number Of Processes : " <<endl;
	cin>>n;
	cout<<endl;
	for( i= 0; i< n; i++ )
	{
		cout<<"********** Process :"<<i+1<<" **********"<<endl;
		cout<<"Enter Process Id : ";
		cin>>Pid;
		cout<<"enter Arrival Time: ";
		cin>>AT;
		cout<<"Enter Burst Time : ";
		cin>>BT;
		cout<<"Enter Priority : ";
		cin>>P;
		cout<<endl;
		tmp.N = i+1;
		tmp.AT = AT;
		tmp.BT = BT;
		tmp.RT = BT;
		tmp.Pid = Pid;
		tmp.P = P;
		input.push_back(tmp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );

    total_time = total_time + input[0].AT;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_time >= input[i].AT )
    	{
    		total_time = total_time +input[i].BT;
    		 cout<<" ";
    	}
    	else
    	{
    		int diff = (input[i].AT- total_time);
    		total_time = total_time + diff + BT;

    	}
    }
}
