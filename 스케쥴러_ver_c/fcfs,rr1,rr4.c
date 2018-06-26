#include <stdlib.h>
#include <stdio.h>

typedef int boolean;
#define false 0
#define true 1

int arrive[5] = {0, 2, 4, 6, 8};
char process[5] = {'a','b','c','d','e'};
int service[5] = {3,6,4,5,2}; // 수정가능 
char print[2] = {'*',' '};
// 5 * 21 짜리 출력맵을 만든다.
char map[5][50] = {' '};
int temp_service[5] = {0};
// a는 맨 윗줄에.
// b는 그 다음줄 .. 이 순서대로 출력한다. 
int *queue;

int size;
int head;
int tail;

void InitQ(int size2)
{
	size = size2;
	queue = (int*)malloc(sizeof(int) *size);
	
	head = 0;
	tail = 0;
}


boolean pushQ(int data)
{
	if((tail+1) % size == head)
	{
		return false;

	}
	queue[tail] = data;
	tail = (tail + 1) % size; // 한칸을 돌린다.
	return true;
}

int popQ()
{
	int temp;
	if(head == tail)
	{
		return -999;
	}
	temp = queue[head];
	head = (head+1) % size;
	//데이터를 삭제한다.
	return temp;
}

void Fcfs_scheduling() 
//먼저도착한 순서대로 화면에 ㅁ출력한다. 
{
	
	int i = 0;
	int j = 0;
	int temp = 0;
	int p = 0;
	int r = 0;
	int loop = 0;
		printf("--FCFS 스케쥴링--\n"); 
	

	for(j = 1; j < 21; j++)
	//타이머 20초 세기.
	{
		for(r = 0; r < 5; r++)
		{
			if(arrive[r] <= j-1)
			//도착시간이 현재 틱이랑 맞으면.
			{
				for(p = j; p < j+ service[r]; p++)
				{
				map[r][p] = '*';
				}
				//서비스 한다.

				j = j + service[r];
			}

		}
	}

}

void Round_robin(int time, int q)
{
	int i = 0;
	int j = 1;
	int temp = 0;
	int p = 0;
	int loop = 0;
	int r = 0;
	boolean t = true;
	
	
	
		if(time == 0 )
		{
			InitQ(100);
			printf("--RR 스케쥴링--\n"); 
			for(p = 0; p < 5; p++)
			{
				temp_service[p] = service[p];
			}
		}
	if(time > 20) return ;
	for(r = 0 ;r < 5 ; r++)
	//한번 틱이 돌떄마다 도착시간을 검사합니다.
	{
		if(arrive[r] == 0 && time == 0)
		{
			pushQ(r);
			//일치하는 프로세스 번호를 큐에 넣고
		}
		
		if((arrive[r]-1 == time) && time > 0)
		{
			pushQ(r);
		}
	}
	
	temp = popQ();
	
	//현재 틱에서 큐에 들어있는 것을 팝합니다.
	if(temp != -999)
	{map[temp][time+1] = print[0];}
	// 현재 시간에 큐에서 꺼낸 것을 서비스 합니다. 
	else return;

	temp_service[temp] -= q;
	if(temp_service[temp] > 0) pushQ(temp);
	Round_robin(time + 1, q);
}	

void Round_robin_2(int time,int quanturm ,int q, int current)
{
	int i = 0;
	int j = 1;
	int temp = 0;
	int p = 0;
	int loop = 0;
	int r = 0;
	boolean t = true;
	if(q == -1) q = quanturm;
	
		if(time == 0 )
		{
			InitQ(100);
			printf("--RR 스케쥴링 q=4 --\n"); 
			for(p = 0; p < 5; p++)
			{
				temp_service[p] = service[p];
			}
		}
	if(time > 20) return ;

	if(q < 1 && temp_service[current] > 0)
		pushQ(current);

	for(r = 0 ;r < 5 ; r++)
	//한번 틱이 돌떄마다 도착시간을 검사합니다.
	{
		if(arrive[r] == 0 && time == 0)
		{
			pushQ(r);
			//일치하는 프로세스 번호를 큐에 넣고
		}
		
		if((arrive[r]-1 == time) && time > 0)
		{
			pushQ(r);
		}
	}

		if(time == 0) current = popQ();
		// 시간이 0일 경우 무조건 팝을해서 꺼낸다.
		else if(time > 0 && temp_service[current] < 1)
			{
				current = popQ();
				q = quanturm;
			}
		// 시간이 0 이상이고, 현재 프로세스 서비스 시간이 끝났을 경우
		else if(q < 1 && temp_service[current] > 0)			
		{
			q = quanturm;
			current = popQ();
		}
		//타임 퀀텀 시간이 끝났을 경우 하지만 서비스 시간이 남앗을경우
		else; // 현재 프로세스를 유지.
		

		if(current != -999)
		{
			map[current][time+1] = print[0];
		}
		// 현재 시간에 큐에서 꺼낸 것을 서비스 합니다. 
		else return;
		
		temp_service[current] -= 1;
		
		

	Round_robin_2(time + 1,quanturm, q - 1, current);
	//시간은 1초 타임퀀텀도 1초씩 줄어든다.

}

/*

void Spn()
{
	int i = 0;
	int j = 0;
	int temp = 0;
	int p = 0;
	int loop = 0;
	int temp_arrive[5] = {0};
	char temp_process[5] = {' '};
	int temp_service[5] = {0};

	for(i = 0; i < 20; i++)
	//타이머
	{
		for(j = 0; j < 5; j++)
		// 도착시간 순회.
		{
			if(arrive[j] <= i)
		//도착한 프로세스가 있다면.
			{

			}

		}
	}
}
*/
int main()
{
	int i,j;
	
	for(i = 0; i < 5; i++)
	{
		map[i][0] = 65 + i;
		//맨 앞에 a~e 문자가 들어감.
	}
	
	//Fcfs_scheduling();
	//Round_robin(0,1);
	Round_robin_2(0,4, -1,-1);
	for(i = 0; i < 5; i++)
	{
		for(j= 0; j < 50; j++)
		{
			printf("%c",map[i][j]);
		}
		printf("\n");
	}

}