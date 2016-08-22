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

char filename[16][16] = { 
	"0_尿.csv", "01_糖尿.csv", "02_糖尿.csv", "05_糖尿.csv", "1_糖尿.csv",
	"2_糖尿.csv", "5_糖尿.csv", "15_糖尿.csv", "0_水.csv", "01_糖水.csv",
	"02_糖水.csv", "05_糖水.csv", "1_糖水.csv", "2_糖水.csv", "5_糖水.csv",
	"15_糖水.csv" };

int main(){
	/* input data and process */
	FILE *pFile;
	char input[32];

	/* progress input */
	printf("Is the input filename `data.csv`? \nIf yes press enter; if not input your filename here: "); 
	fgets(input,32,stdin);
	if(strlen(input)==1) strcpy(input,"data.csv");
	else input[strlen(input)]='\0';
	pFile = fopen("data.csv","r");
	char s[lineLen], time[timeLen];
	int num;
	if(pFile == NULL) printf("Please put the input file `data.csv` to the same folder.\n");
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
	for(int i=0; i<dataHeight; ++i) {
		FILE *pLeft, *pRight;
		pLeft = fopen(filename[i],"w");
		pRight = fopen(filename[i+dataHeight/2],"w");
		if(pFile!=NULL && pRight!=NULL)
			for(int j=0; j<num; ++j) {
				fprintf(pLeft, "%d", output[j].time);
				fprintf(pRight, "%d", output[j+dataHeight/2].time);
				for(int k=0; k<dataWidth; ++k) { 
					fprintf(pLeft, ",%s", output[j].data[i][k]);
					fprintf(pRight, ",%s", output[j+dataHeight/2].data[i][k]);
				}
				fprintf(pLeft, "\n");
				fprintf(pRight, "\n");
			}
		fclose(pLeft);
		fclose(pRight);
	}
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
	int hour=0, minute=0, isHour=0;
	for(int i=1; i<len; ++i){
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

