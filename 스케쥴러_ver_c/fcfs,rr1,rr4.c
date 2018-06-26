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
// a�� �� ���ٿ�.
// b�� �� ������ .. �� ������� ����Ѵ�. 
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
	tail = (tail + 1) % size; // ��ĭ�� ������.
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
	//�����͸� �����Ѵ�.
	return temp;
}

void Fcfs_scheduling() 
//���������� ������� ȭ�鿡 ������Ѵ�. 
{
	
	int i = 0;
	int j = 0;
	int temp = 0;
	int p = 0;
	int r = 0;
	int loop = 0;
		printf("--FCFS �����층--\n"); 
	

	for(j = 1; j < 21; j++)
	//Ÿ�̸� 20�� ����.
	{
		for(r = 0; r < 5; r++)
		{
			if(arrive[r] <= j-1)
			//�����ð��� ���� ƽ�̶� ������.
			{
				for(p = j; p < j+ service[r]; p++)
				{
				map[r][p] = '*';
				}
				//���� �Ѵ�.

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
			printf("--RR �����층--\n"); 
			for(p = 0; p < 5; p++)
			{
				temp_service[p] = service[p];
			}
		}
	if(time > 20) return ;
	for(r = 0 ;r < 5 ; r++)
	//�ѹ� ƽ�� �������� �����ð��� �˻��մϴ�.
	{
		if(arrive[r] == 0 && time == 0)
		{
			pushQ(r);
			//��ġ�ϴ� ���μ��� ��ȣ�� ť�� �ְ�
		}
		
		if((arrive[r]-1 == time) && time > 0)
		{
			pushQ(r);
		}
	}
	
	temp = popQ();
	
	//���� ƽ���� ť�� ����ִ� ���� ���մϴ�.
	if(temp != -999)
	{map[temp][time+1] = print[0];}
	// ���� �ð��� ť���� ���� ���� ���� �մϴ�. 
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
			printf("--RR �����층 q=4 --\n"); 
			for(p = 0; p < 5; p++)
			{
				temp_service[p] = service[p];
			}
		}
	if(time > 20) return ;

	if(q < 1 && temp_service[current] > 0)
		pushQ(current);

	for(r = 0 ;r < 5 ; r++)
	//�ѹ� ƽ�� �������� �����ð��� �˻��մϴ�.
	{
		if(arrive[r] == 0 && time == 0)
		{
			pushQ(r);
			//��ġ�ϴ� ���μ��� ��ȣ�� ť�� �ְ�
		}
		
		if((arrive[r]-1 == time) && time > 0)
		{
			pushQ(r);
		}
	}

		if(time == 0) current = popQ();
		// �ð��� 0�� ��� ������ �����ؼ� ������.
		else if(time > 0 && temp_service[current] < 1)
			{
				current = popQ();
				q = quanturm;
			}
		// �ð��� 0 �̻��̰�, ���� ���μ��� ���� �ð��� ������ ���
		else if(q < 1 && temp_service[current] > 0)			
		{
			q = quanturm;
			current = popQ();
		}
		//Ÿ�� ���� �ð��� ������ ��� ������ ���� �ð��� ���������
		else; // ���� ���μ����� ����.
		

		if(current != -999)
		{
			map[current][time+1] = print[0];
		}
		// ���� �ð��� ť���� ���� ���� ���� �մϴ�. 
		else return;
		
		temp_service[current] -= 1;
		
		

	Round_robin_2(time + 1,quanturm, q - 1, current);
	//�ð��� 1�� Ÿ�����ҵ� 1�ʾ� �پ���.

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
	//Ÿ�̸�
	{
		for(j = 0; j < 5; j++)
		// �����ð� ��ȸ.
		{
			if(arrive[j] <= i)
		//������ ���μ����� �ִٸ�.
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
		//�� �տ� a~e ���ڰ� ��.
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