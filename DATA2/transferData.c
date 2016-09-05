#include <stdio.h>
#include <string.h>
#define dataWidth 12
#define dataHeight 8
#define lineLen 1024
#define timeLen 16

struct OUT {
	int time;
	char data[dataHeight][dataWidth][16];
} output[100000];

int getTime(char *);
void setData(int,int,char *);

int main(){
	/* input data and process */
	FILE *pFile;
	char input[32];

	/* progress input */
	printf("Is the input filename `DATA2.csv`? \nIf yes press enter; if not input your filename here: ");
	fgets(input,32,stdin);
	if(strlen(input)==1) strcpy(input,"DATA2.csv");
	else input[strlen(input)]='\0';

	pFile = fopen(input,"r");
	char s[lineLen], time[timeLen];
	int num;
	if(pFile == NULL) printf("Please put the input csv file to the same folder.\n");
	while(fgets(s,lineLen,pFile)!=0) {
		if(s[0]=='K') {
			sscanf(s,"%*s %*s %d %s",&num,time);
			output[num-1].time = getTime(time);
		}
		else if(s[0]>='A' && s[0]<='H')
			setData(num-1,s[0]-'A',s);
	}
	fclose(pFile);
	/* output data */
	int i, j, k;
	char filename[32] = "transferDATA2.csv";
	pFile = fopen(filename, "w");
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
	return 0;
}

void setData(int n, int ar, char *s){
	char *pch;
	int width = 0;
	pch = strtok(s,",");
	do {
		pch = strtok(NULL,",");
		strcpy(output[n].data[ar][width++],pch);
	} while(pch!=NULL && width<12);
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

