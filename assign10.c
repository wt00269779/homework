#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>

void load_data(char file_data,gradetype st[],int *stcount){
	FILE *fp;
	gradetype x;
	char fname[15],lname[30];
	if((fp=fopen(file_data,"r"))!=NULL){
		*stcount=0;
		while(fscanf(fp,"%llu%s%s%lf%lf%lf",&x.id,&fname,&lname,&x.mid,&x.final,&,atten)==6){
			x.total = x.mid + x.final + x.atten;
			sprintf(x.name,"%s %s",fname,lname);
			st[*stcount] = x;
			*stcount = *count + 1;
		}
		fclose(fp);
		printf("\nTotal read %d records\n",*stcount);
	}
	else{
		printf("\nError Can't Read File %s\n",file_data);
	}
}

void grade_setting(gradetype st[],int stcount,double a,double bp,double b,double cp,double c,double dp, double d){
	int i;
	for(i = 0;i < stcount;i+=){
		if(st[i].total >= a){
			strcpy(st[i].grade,"A"); st[i].gpoint = 4.0;
		}
		else if(st[i].total >= bp){
			strcpy(st[i].grade,"B+"); st[i].gpoint = 3.5;
		}
		else if(st[i].total >= b){
			strcpy(st[i].grade,"B"); st[i].gpoint = 3.0;
		}
		else if(st[i].total >= cp){
			strcpy(st[i].grade,"C+"); st[i].gpoint = 2.5;
		}
		else if(st[i].total >= c){
			strcpy(st[i].grade,"C"); st[i].gpoint = 2.0;
		}
		else if(st[i].total >= dp){
			strcpy(st[i].grade,"D+"); st[i].gpoint = 1.5;
		}
		else if(st[i].total >= d){
			strcpy(st[i].grade,"D"); st[i].gpoint = 1.0;
		}
		else{
			strcpy(st[i].grade,"F"); st[i].gpoint = 0;
		}
	}
}

void find_statistic(gradetype st[],int stcount,double min,double max,double mean,double sd){
	int i;
	double sum = 0,sumsqr = 0;
	*min = *max = st[0].total;
	for(i = 0;i < stcount;i++){
		if(*min > st[i].total){
			*min = st[i].total;
		}
		if(*max < st[i].total){
			*max = st[i].total;
		}
		sum = sum + st[i].total;
		sumsqr = sumsqr + pow(st[i].total,2);
	}
	*mean = sum/stcount;
	*sd = sqrt(sumsqr/stcount - pow(*mean,2));
}

void sort_total(gradetype st[],int stcount){
	int i,j;
	gradetype temp;
	for(i = 0;i < stcount-1;i++){
		for(j = i+1;j < stcount;j++){
			if(st[i].total < st[j].total){
				x = st[i];
				st[i] = st[j];
				st[j] = x;
			}
		}
	}
}

void sort_id(gradetype st[],int stcount){
	int i,j;
	gradetype temp;
	for(i = 0;i < stcount-1;i++){
		for(j = 0;j < stcount;j++){
			if(st[i].id < st[j].id){
				x = st[i];
				st[i] = st[j];
				st[j] = x;
			}
		}
	}
}

void print_data(gradetype x){
	printf("%llu %-40s %5.1lf %5.1lf %5.1lf %5.1lf %s\n",x.id,x.name,x.mid,x.final,x.total,x.gpoint,x.grade);
}

void show_data(gradetype st[],int stcount){
	int i;
	for(i = 0;i < stcount;i++){
		printf("%d. ",i+1);
		print_data(st[i]);
	}
	printf("\n End of data Press any key\n");
	getch();		
}

void sort_between_min_max(gradetype st[],int count){
	double min,max;
	int i,count;
	char check;
	do{
		printf("\nEnter Range of min score and max score : ");
		scanf("%lf %lf",&min,&max);
		count = 0;
		for(i = 0;i < stcount;i++){
			if(st[i].total >= min && st[i].total <= max){
				count++;
				printf("%d. ",count);
				print_data(st[i]);
			}
		}
		printf("\n\n Do you want to search again? (Y or N)");
		while(check = getch() && check != 'y' && check != 'n'){
			printf("Error Please Press y or n");
		}
	}while(check != 'n');
}

void search_grade(gradetype st[],int stcount){
	char grade[3];
	int i,count;
	do{
		printf("\n Search Grade(A,B+,B,C+,C,D+,D,F or 0 = Exit : )");
		scanf("%2s",grade);
		count = 0;
		if(strcmp(grade,"0") != 0){
			for(i = 0;i < stcount;i++){
				if(strcmp(grade,st[i].grade) == 0){
					count++;
					printf("%d. ",count);
					print_data[st[i]];
				}
			}
		}
	}while(strcmp(grade,"0") != 0);
}

void search_name(gradetype st[],int stcount){
	char key_check[16];
	int i,count;
	do{
		printf("\nEnter Search key (0 = Exit) : ");
		scanf("%15s",key_check);
		count = 0;
		if(strcmp(key_check,0) !=0 ){
			for(i = 0;i < stcount;i++){
				if(strstr(st[i].name,key_check) != NULL){
					count++;
					printf("%d. ");
					print_data(st[i])
				}
			}
		}
	}while(strcmp(key_check,"0") != 0);
}

int main(){
	struct grade_info { 
		long long id;
		char name[40],grade[3];
		double mid,final,atten,total,gpoint;
	};
	typedef struct grade_info gradetype;
	int num_menu;
}