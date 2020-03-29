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
int Ghant[total_time]={0};
	for( i= 0; i< total_time; i++ )
	{
		Ghant[i]=-1;
	}
        priority_queue < P_d ,vector<Process_Data> ,comPare> pq;
	queue< P_d > rq;
	int cpu_state = 0;
	int quantum = 4 ;
	current.Pid = -2;
	current.P = 999999;
for ( clock = 0; clock< total_time; clock++ )
	{
		for( int j = 0; j< n ; j++ )
		{
			if(clock == input[j].AT)
			{
				pq.push(input[j]);
			}
		}

		if(cpu_state == 0)
		{
			if(!pq.empty())
			{
				current = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4;
			}
			else if(!rq.empty())
			{
				current = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1)
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().P < current.P )
				{
					rq.push(current);
					current = pq.top();
					pq.pop();
					quantum = 4;
				}
			}
			else if(rq_process == 1 && (!pq.empty()))
			{
				rq.push(current);
				current = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}


		}


		if(current.Pid != -2)
			current.RT--;
			quantum--;
		{
			Ghant[clock] = current.Pid;
			if(current.RT == 0)
			{
				cpu_state = 0 ;
				quantum = 4 ;
				current.Pid = -2;
				current.P = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 )
			{
				rq.push(current);
				current.Pid = -2;
				current.P = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;
			}
		}
	}
sort( input.begin(), input.end(), idsort );

	for(int i=0;i<n;i++)
	{
		for(int k=total_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].FT=k+1;
				break;
			}
		}
	}
       for(int i=0;i<n;i++)
	{
		for(int k=0;k<total_time;k++)
		{

			if(Ghant[k]==i+1)
			{
				input[i].ST=k;
				break;
			}
		}
	}
sort( input.begin(), input.end(), Numsort );
	for(int i=0;i<n;i++)
	{
		input[i].Res_T=input[i].ST-input[i].AT;
		input[i].WT=(input[i].FT-input[i].AT)-input[i].BT;

	}

	cout<<endl<<"**************************************************************"<<endl;
	cout<<endl;
	cout<<"Process Id  |  Response_Time  |  Finish_Time  |  Waiting_Time "<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<"       "<< input[i].Pid <<"            "<< input[i].Res_T <<"             "<< input[i].FT <<"               "<< input[i].WT <<endl;
	}
	return 0;
}

