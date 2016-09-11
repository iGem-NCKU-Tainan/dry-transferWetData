#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define lineLen 1024
#define timeLen 16
#define maxDataHeight 24
#define maxDataWidth 32

struct OUT {
	int time;
	char data[maxDataHeight][maxDataWidth][16];
} output[100000];

int getTime(char *);
void setData(int,int,char *);
int dataHeight = 0, dataWidth = 0;

int main(){
	/* input data and process */
	FILE *pFile;
	char input[32];

	/* progress input */
	printf("Input filename (default: `DATA2.csv`): ");
	fgets(input,32,stdin);
	if(strlen(input)==1) strcpy(input,"DATA2.csv");
	else input[strlen(input)-1]='\0';
	pFile = fopen(input,"r");
	if(pFile == NULL) {
		printf("Please put the input csv file to the same folder.\n");
		exit(0);
	}

	char s[lineLen], time[timeLen];
	int num;
	while(fgets(s,lineLen,pFile)!=0) {
		if(s[0]=='K' && s[1]=='i') {
			sscanf(s,"%*s %*s %d %s",&num,time);
			output[num-1].time = getTime(time);
		}
		else if(s[0]>='A' && s[0]<='Z') {
			setData(num-1,s[0]-'A',s);
			if(s[0]-'A'>dataHeight) dataHeight = s[0]-'A';
        }
	}
	fclose(pFile);
	++dataHeight;

	/* progress output */
	printf("Output filename (default: `transferDATA2.csv`): ");
	fgets(input,32,stdin);
	if(strlen(input)==1) strcpy(input,"transferDATA2.csv");
	else input[strlen(input)-1]='\0';
	pFile = fopen(input,"w");
	if(pFile == NULL) {
		printf("Cannot create the file...\n");
		exit(0);
	}

	/* output data */
	int i, j, k;
	 // time row
	fprintf(pFile,"time");
	for(i=0; i<num; ++i) fprintf(pFile, ",%d", output[i].time);
	fprintf(pFile,"\n");
	 // data row
	for(i=0; i<dataHeight; ++i)
		for(j=0; j<dataWidth; ++j) {
			fprintf(pFile,"%c%d", i+'A', j+1);
			for(k=0; k<num; ++k)
				fprintf(pFile, ",%s", output[k].data[i][j]);
			fprintf(pFile, "\n");
		}
	fclose(pFile);

	printf("Done!\n");
	return 0;
}

void setData(int n, int ar, char *s){
	char *pch;
	int width = 0;
	pch = strtok(s,",\n\r");
	pch = strtok(NULL,",\n\r");
	while(pch!=NULL) {
		strcpy(output[n].data[ar][width++],pch);
		pch = strtok(NULL,",\n\r");
	}
	if(!dataWidth) dataWidth = width;
}

int getTime(char *time){
	char newTime[timeLen];
	int len = strlen(time);
	int hour=0, minute=0, isHour=0, i;
	for(i=1; i<len; ++i){
		if(time[i]==':'){
			if(isHour==0) isHour = 1;
			else break;
		}
		else if(isHour==0)
			hour = hour*10 + time[i]-'0';
		else
			minute = minute*10 + time[i]-'0';
	}
	return hour*60+minute;
}

