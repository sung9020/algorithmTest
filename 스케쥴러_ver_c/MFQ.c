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
struct queue
{
	int *queue;
	int size;
	int head;
	int tail;
	int quantum;
	int order;
	int num;

};

	struct queue queue1;
	struct queue queue2;
	struct queue queue3;


void InitQ(struct queue* queue_s, int size, int order,int quantum)
{
	
	(*queue_s).size = size;
	(*queue_s).queue = (int*)malloc(sizeof(int) *size);
	(*queue_s).head = 0;
	(*queue_s).tail = 0;
	(*queue_s).order = order;
	(*queue_s).quantum = quantum;
}


boolean pushQ(struct queue* queue_s,int data)
{
	if(((*queue_s).tail+1) % (*queue_s).size == (*queue_s).head)
	{
		return false;

	}
	(*queue_s).queue[(*queue_s).tail] = data;
	(*queue_s).tail = ((*queue_s).tail + 1) % (*queue_s).size; // 한칸을 돌린다.
	(*queue_s).num++;
	return true;
}

int popQ(struct queue* queue_s)
{
	int temp;
	if((*queue_s).head == (*queue_s).tail)
	{
		return -999;
	}
	(*queue_s).num--;
	temp = (*queue_s).queue[(*queue_s).head];
	(*queue_s).head = ((*queue_s).head+1) % (*queue_s).size;
	//데이터를 삭제한다.
	return temp;
}

boolean isEmpty(struct queue *queue_s)
{
	if((*queue_s).num == 0) return true;
	else return false; 
}

int sizeQ(struct queue* queue_s)
{
	return (*queue_s).num;
}



void MFQ(int time, int q, int current, struct queue* currentQ)
{
	
	int i,j,p,_order;
	
	// 아무것도 아닌 상태에서는 첫번째 큐가 스탠바이
	if(q == -1) q = queue1.quantum;
	
	if(time == 0 )
		{		
			printf("--MFQ 스케쥴링 q=1 --\n"); 
			for(p = 0; p < 5; p++)
			{
				temp_service[p] = service[p];
			}
		}

	if(time > 20) return ;

	if(q < 1 && temp_service[current] > 0)
		//타임퀀텀이 없는데 시간이 남았을경우
		{			
			if(isEmpty(&queue1) && isEmpty(&queue2) && isEmpty(&queue3))
			{
				pushQ(&queue1,current); //a가 다시들어간다.
			}
			
			else{

			_order = (*currentQ).order;
			if(_order < 3)
				{
					_order++;
					if(queue2.order == _order)
						pushQ(&queue2,current);
					if(queue3.order == _order)
						pushQ(&queue3,current);
				}
			else 
				{
					pushQ(&queue1,current);
				}
			}

			//서비스 시간이 남았는데 남은 큐가 없을 경우 처음 큐로 이동한다.
		}
		
		
	for(i=0;i<5 ;i++)
	//시간마다 도착시간 검사.
	{
		if(arrive[i] == 0 && time == 0)
		{
			pushQ(&queue1,i);
			//첫번째 도착한 프로세스는 바로 큐에 집어넣는다.
		}
		/*if(arrive[i]-1 == time && time > 0)
		{
			pushQ(&queue1,i);
		}*/
		// 그다음부터도 일단 도착하면 첫번째 큐에 넣는다.
	}

	if(isEmpty(&queue2) && isEmpty(&queue3) && sizeQ(&queue1) == 1 && time == 0)
	{
		current = popQ(&queue1);
		currentQ = &queue1;
	}
	// 나머지 큐가 비어있고 첫번째 큐에 프로세스가 들어있는 상태.
	/*else if (time > 0 && sizeQ(&queue1) == 1 && isEmpty(&queue2) && isEmpty(&queue3) && q < 1)
	{
		current = popQ(&queue1);
		currentQ = &queue1;
		q = (*currentQ).quantum;
	}*/
	// 시간이 0초 이상임에도 여전히 첫번째 큐에만 작업이 하나만 들어있을 경우
	// 그대로 현재 큐에서 프로세스가 실행된다.
	// 큐의 우선순위, 한번에 하나의 큐의 프로세스만 실행 가능하다는것.
	
	else if (time > 0 && sizeQ(&queue1) > 0 && isEmpty(&queue2) &&isEmpty(&queue3) && q< 1)
	{
		current = popQ(&queue1);
		currentQ = &queue1;
		q = (*currentQ).quantum;
	}
	else if (time > 0 && sizeQ(&queue1) > 0 && sizeQ(&queue2) > 0 &&isEmpty(&queue3) && q< 1)
	{
		current = popQ(&queue1);
		currentQ = &queue1;
		q = (*currentQ).quantum;
	}
	else if (time > 0 && sizeQ(&queue1) > 0 && sizeQ(&queue2) > 0 && sizeQ(&queue3) > 0 && q< 1)
	{
		current = popQ(&queue1);
		currentQ = &queue1;
		q = (*currentQ).quantum;
	}
	else if (time > 0 && sizeQ(&queue1) > 0 && isEmpty(&queue2) && sizeQ(&queue3) > 0 && q< 1)
	{
		current = popQ(&queue3);
		currentQ = &queue3;
		q = (*currentQ).quantum;
	}
	//그다음 부터는 큐 1이 우선으로 실행된다.
	else if (time > 0 && isEmpty(&queue1) && sizeQ(&queue2) > 0 && q < 1)
	{
		current = popQ(&queue2);
		currentQ = &queue2;
		q = (*currentQ).quantum;
	}
	//시간이 0초 이상인데 첫번째 큐작업이 모두 끝났을 경우. 

	else if (time > 0 && isEmpty(&queue1) && isEmpty(&queue2) && sizeQ(&queue3) > 0 && q < 1)
	{
		current = popQ(&queue3);
		currentQ = &queue3;
		q = (*currentQ).quantum;
	}

	else; // 타임 퀀텀이 남았을 경우는 현재 프로세스 유지.

	
	

	if(current != -999 && q > 0)
		{
			map[current][time+1] = print[0];
			
		}
		// 현재 시간에 큐에서 꺼낸 것을 서비스 합니다. 
	else return;

		temp_service[current] -= 1;
		

		
		for(i=0;i<5 ;i++)
	//시간마다 도착시간 검사.
	{
	if(arrive[i]-1 == time && time > 0)
		{
			pushQ(&queue1,i);
		}
	}
	
		
		
	MFQ(time + 1, q-1, current, currentQ);
}

int main()
{
	int i,j;
	
	for(i = 0; i < 5; i++)
	{
		map[i][0] = 65 + i;
		//맨 앞에 a~e 문자가 들어감.
	}
	

	InitQ(&queue1,100,1,1);
	InitQ(&queue2,100,2,1);
	InitQ(&queue3,100,3,1);
	// 큐의 크기, 큐의 순서와 퀀텀 초기화

	MFQ(0,-1,-1,NULL);

	for(i = 0; i < 5; i++)
	{
		for(j= 0; j < 50; j++)
		{
			printf("%c",map[i][j]);
		}
		printf("\n");
	}

}