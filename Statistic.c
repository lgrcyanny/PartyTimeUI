#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Data Struct Date */
typedef struct dateStruct
{
	int day;
	int startTime;
	int lastTime;
} Date;

int hostHour;

int week[7];
int hour[24];
Date date[100];


void input() {
	/* Simulate user input */
	int i;

	for (i = 0; i < 7; ++i) {
		/* Initial the week statistic*/
		week[i] = 0;
	}

	for (i = 0; i < 24; ++i) {
		/* Initial the hour statistic*/
		hour[i] = 0;
	}

	for (i = 0; i < 100; ++i) {
		/* 100 random date data */
		date[i].day = rand() % (6 + 1);
		week[date[i].day]++;
		date[i].startTime = rand() % (18 + 1 - 6) + 6;
		date[i].lastTime = rand() % (24 + 1);
		if(date[i].lastTime + date[i].startTime > 24)
			date[i].lastTime = 24 - date[i].startTime;
	}

	/* input the host hour*/
	printf("input host hour: ");
	scanf("%d", &hostHour);
	return;
}

void statistic() {
	int i, j, bestDay, bestHour;
	int *hourSegment = (int*)malloc((24 - hostHour + 1) * sizeof(int));
	
	for (i = 0, bestDay = 0; i < 7; ++i) {
		/* find the best day */
		// printf("%d\n", week[i]);
		if(week[bestDay] < week[i])
			bestDay = i;
	}

	for(i = 0; i < 24; i++) {
		/* count the chosen hour in the best day */
		if(date[i].day == bestDay) {
			for(j = 0; j < date[i].lastTime; j++)
				if(i + j >= 24)
					continue;
				else
					hour[i + j] += 1;
		}
	}

	for(i = 0, bestHour = 0; i < 24 - hostHour + 1; i++) {
		/* find the bestHour */
		hourSegment[i] = 0;
		for(j = 0; j < hostHour; j++) {
			hourSegment[i] += hour[i + j];
		}
		if(hourSegment[bestHour] < hourSegment[i])
			bestHour = i;
	}

	printf("The best day is %d\n", bestDay);
	printf("The best start hour is %d, lasting %d hours\n",bestHour, hostHour);
}

int main(int argc, char const *argv[])
{
	input();
	statistic();	
	return 0;
}