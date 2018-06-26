#include <stdlib.h>
#include <stdio.h>


typedef int boolean;
#define false 0
#define true 1

int arrive[5] = {0, 2, 4, 6, 8};
char process[5] = {'a','b','c','d','e'};
int service[5] = {3,6,4,5,2}; // �������� 
char print[2] = {'*',' '};
// 5 * 21 ¥�� ��¸��� �����.
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
	(*queue_s).tail = ((*queue_s).tail + 1) % (*queue_s).size; // ��ĭ�� ������.
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
	//�����͸� �����Ѵ�.
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
	
	// �ƹ��͵� �ƴ� ���¿����� ù��° ť�� ���Ĺ���
	if(q == -1) q = queue1.quantum;
	
	if(time == 0 )
		{		
			printf("--MFQ �����층 q=1 --\n"); 
			for(p = 0; p < 5; p++)
			{
				temp_service[p] = service[p];
			}
		}

	if(time > 20) return ;

	if(q < 1 && temp_service[current] > 0)
		//Ÿ�������� ���µ� �ð��� ���������
		{			
			if(isEmpty(&queue1) && isEmpty(&queue2) && isEmpty(&queue3))
			{
				pushQ(&queue1,current); //a�� �ٽõ���.
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

			//���� �ð��� ���Ҵµ� ���� ť�� ���� ��� ó�� ť�� �̵��Ѵ�.
		}
		
		
	for(i=0;i<5 ;i++)
	//�ð����� �����ð� �˻�.
	{
		if(arrive[i] == 0 && time == 0)
		{
			pushQ(&queue1,i);
			//ù��° ������ ���μ����� �ٷ� ť�� ����ִ´�.
		}
		/*if(arrive[i]-1 == time && time > 0)
		{
			pushQ(&queue1,i);
		}*/
		// �״������͵� �ϴ� �����ϸ� ù��° ť�� �ִ´�.
	}

	if(isEmpty(&queue2) && isEmpty(&queue3) && sizeQ(&queue1) == 1 && time == 0)
	{
		current = popQ(&queue1);
		currentQ = &queue1;
	}
	// ������ ť�� ����ְ� ù��° ť�� ���μ����� ����ִ� ����.
	/*else if (time > 0 && sizeQ(&queue1) == 1 && isEmpty(&queue2) && isEmpty(&queue3) && q < 1)
	{
		current = popQ(&queue1);
		currentQ = &queue1;
		q = (*currentQ).quantum;
	}*/
	// �ð��� 0�� �̻��ӿ��� ������ ù��° ť���� �۾��� �ϳ��� ������� ���
	// �״�� ���� ť���� ���μ����� ����ȴ�.
	// ť�� �켱����, �ѹ��� �ϳ��� ť�� ���μ����� ���� �����ϴٴ°�.
	
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
	//�״��� ���ʹ� ť 1�� �켱���� ����ȴ�.
	else if (time > 0 && isEmpty(&queue1) && sizeQ(&queue2) > 0 && q < 1)
	{
		current = popQ(&queue2);
		currentQ = &queue2;
		q = (*currentQ).quantum;
	}
	//�ð��� 0�� �̻��ε� ù��° ť�۾��� ��� ������ ���. 

	else if (time > 0 && isEmpty(&queue1) && isEmpty(&queue2) && sizeQ(&queue3) > 0 && q < 1)
	{
		current = popQ(&queue3);
		currentQ = &queue3;
		q = (*currentQ).quantum;
	}

	else; // Ÿ�� ������ ������ ���� ���� ���μ��� ����.

	
	

	if(current != -999 && q > 0)
		{
			map[current][time+1] = print[0];
			
		}
		// ���� �ð��� ť���� ���� ���� ���� �մϴ�. 
	else return;

		temp_service[current] -= 1;
		

		
		for(i=0;i<5 ;i++)
	//�ð����� �����ð� �˻�.
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
		//�� �տ� a~e ���ڰ� ��.
	}
	

	InitQ(&queue1,100,1,1);
	InitQ(&queue2,100,2,1);
	InitQ(&queue3,100,3,1);
	// ť�� ũ��, ť�� ������ ���� �ʱ�ȭ

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