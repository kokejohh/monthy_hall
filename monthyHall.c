#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define CLOSE 0
#define OPEN 1
#define REWARD 2
#define CHOOSE 3  
#define CHANGE 4

int isDup(int *, int);
void printDoors(int *, int);

int main()
{
	srand(time(NULL));

	int round, door;
	int switchWin = 0, stayWin = 0, randomWin = 0;
	int switchLose = 0, stayLose = 0, randomLose = 0;

	printf("Enter round: "); scanf("%d", &round);
	printf("Enter door: "); scanf("%d", &door);

	if (round <= 0)
	{
	    fprintf(stderr, "Error round should > 0\n");
	    return -1;
	} else if (door <= 1)
	{
	    fprintf(stderr, "Error door should > 1\n");
	    return -1;
	}

	int doors[door];

	for(int i = 0; i < round; i++)
	{
		int status[door];
		for (int j = 0; j < door; j++) doors[j] = status[j] = 0;

		int reward = rand() % door;
		doors[reward] = status[reward] = REWARD;

		int choose = rand() % door;
		status[choose] = CHOOSE;

		//stay
		if (doors[choose] == REWARD) stayWin++; else stayLose++;

		//open door
		for (int j = 0; j < door - 2; j++)
		{
			int open = rand() % door;
			while (isDup(status, open)) open = rand() % door;
			status[open] = OPEN;
		}
		//switch
		int tmpChoose = choose;
		while (tmpChoose == choose || status[choose] == OPEN) choose = rand() % door;
		status[choose] = CHANGE;
		doors[choose] == REWARD ? switchWin++ : switchLose++;

		//random or open 1
		choose = rand() % door;
		while (status[choose] == OPEN) choose = rand() % door;
		doors[choose] == REWARD ? randomWin++ : randomLose++;

		printDoors(doors, door);
		printDoors(status, door);
		printf("----------\n");
	}

	printf("O is door opened, * is stay the door, ^ is switch the door\n");
	printf("round = %d\n", round);
	printf("stay win = %d, lose = %d, percent = %.2f%%\n", stayWin, stayLose, stayWin * 100.0 / round);
	printf("switch win = %d, lose = %d, percent = %.2f%%\n", switchWin, switchLose, switchWin * 100.0 / round);
	printf("random win = %d, lose = %d, percent = %.2f%%\n", randomWin, randomLose, randomWin * 100.0 / round);
	
	return 0;
}

int isDup(int *arr, int index)
{
	return arr[index] == OPEN || arr[index] == REWARD || arr[index] == CHOOSE;
}

void printDoors(int *arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%c ", arr[i] == CLOSE ? '0' : arr[i] == OPEN ? 'O' :
					arr[i] == REWARD ? '1' : arr[i] == CHOOSE ? '*' :
					arr[i] == CHANGE ? '^' : '-');
	}
	printf("\n");
}
