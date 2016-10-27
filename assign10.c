#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

struct grade_info { 
		long long id;
		char name[40],grade[3];
		double mid,final,atten,total,gpoint;
};
typedef struct grade_info gradetype;
gradetype st[100],x;

struct score_mid{
	double min,max,mean,sd;
};
typedef struct score_mid s_mid;

struct score_final{
	double min,max,mean,sd;
};
typedef struct score_final s_final;

struct score_atten{
	double min,max,mean,sd;
};
typedef struct score_atten s_atten;


int load_data_student(char file_data[],gradetype st[],int *stcount,s_mid *mid,s_final *final,s_atten *atten){
	FILE *fp;
	gradetype x;
	mid[0].min = 100; mid[0].max = 0; mid[0].mean = 0; mid[0].sd = 0;
	final[0].min = 100; final[0].max = 0; final[0].mean = 0; final[0].sd = 0;
	atten[0].min = 100; atten[0].max = 0; atten[0].mean = 0; atten[0].sd = 0;
	char fname[15],lname[30];
	if((fp = fopen(file_data,"r"))!=NULL){
		*stcount=0;
		while(fscanf(fp,"%llu,%s%[^,],%lf,%lf,%lf",&x.id,&fname,&lname,&x.mid,&x.final,&x.atten)==6){
			x.total = x.mid + x.final + x.atten;
			sprintf(x.name,"%s %s",fname,lname);
			st[*stcount] = x;
			*stcount = *stcount + 1;
		}
		fclose(fp);
		return 1;
	}
	else{
		return 0;
	}
}

void statistic(gradetype st[],int stcount,s_mid *mid,s_final *final,s_atten *atten){
	int i;
	mid[0].mean = final[0].mean = atten[0].mean = mid[0].sd = final[0].sd = atten[0].sd = 0;
	for(i=0;i<stcount;i++){
		if(mid[0].min > st[i].mid){
			mid[0].min = st[i].mid;
		}
		if(final[0].min > st[i].final){
			final[0].min = st[i].final;
		}
		if(atten[0].min > st[i].atten){
			atten[0].min = st[i].atten;
		}
		if(mid[0].max < st[i].mid){
			mid[0].max = st[i].mid;
		}
		if(final[0].max < st[i].final){
			final[0].max = st[i].final;
		}
		if(atten[0].max < st[i].atten){
			atten[0].max = st[i].atten;
		}
		mid[0].mean += st[i].mid;
		final[0].mean += st[i].final;
		atten[0].mean += st[i].atten;
		mid[0].sd += pow(st[i].mid,2);
		final[0].sd += pow(st[i].final,2);
		atten[0].sd += pow(st[i].atten,2);
	}		
	mid[0].mean = mid[0].mean/ stcount;
	final[0].mean = final[0].mean/ stcount;
	atten[0].mean = atten[0].mean / stcount;
	mid[0].sd = sqrt(mid[0].sd/ stcount - pow(mid[0].mean,2));
	final[0].sd = sqrt(final[0].sd/ stcount - pow(final[0].mean,2));
	atten[0].sd = sqrt(atten[0].sd/ stcount - pow(atten[0].mean,2));
}

struct Grade{
	int A,Bp,B,Cp,C,Dp,D,F;
	double GPA;
};
typedef struct Grade Ggrade;

void Grade_setting(gradetype st[],int dl ,int stcount, double a, double bp,double b, double cp, double c, double dp, double d,Ggrade gr[]){
	int i;
	for(i = 0;i < stcount;i++){
		if(st[i].total >= a){
			strcpy(st[i].grade,"A"); st[i].gpoint = 4.0;
			gr[0].A += 1 - dl;
		}
		else if(st[i].total >= bp){
			strcpy(st[i].grade,"B+"); st[i].gpoint = 3.5;
			gr[0].Bp += 1 - dl;
		}
		else if(st[i].total >= b){
			strcpy(st[i].grade,"B"); st[i].gpoint = 3.0;
			gr[0].B += 1 - dl;
		}
		else if(st[i].total >= cp){
			strcpy(st[i].grade,"C+"); st[i].gpoint = 2.5;
			gr[0].Cp += 1 - dl;
		}
		else if(st[i].total >= c){
			strcpy(st[i].grade,"C"); st[i].gpoint = 2.0;
			gr[0].C += 1 - dl;
		}
		else if(st[i].total >= dp){
			strcpy(st[i].grade,"D+"); st[i].gpoint = 1.5;
			gr[0].Dp += 1 - dl;
		}
		else if(st[i].total >= d){
			strcpy(st[i].grade,"D"); st[i].gpoint = 1.0;
			gr[0].D += 1 - dl;
		}
		else if(st[i].total >= 0){
			strcpy(st[i].grade,"F"); st[i].gpoint = 0;
			gr[0].F += 1 - dl;
		}
		gr[0].GPA = gr[0].A*4 + gr[0].Bp*3.5 + gr[0].B*3 + gr[0].Cp*2.5 + gr[0].C*2 + gr[0].Dp*1.5 + gr[0].D;	
	}
}

void find_statistic(gradetype st[],int stcount,double *min,double *max,double *mean,double *sd,s_mid mid,s_final final,s_atten atten,Ggrade gr){
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
	statistic(st,stcount,&mid,&final,&atten);
	*mean = sum/stcount;
	*sd = sqrt(sumsqr/stcount - pow(*mean,2));
	gr.GPA = gr.GPA/stcount;
	printf("\n               _______________________________________________\n");
	printf("              |  score  |  mid  |  final  |  atten  |  total  |\n");
	printf("              |_________|_______|_________|_________|_________|\n");
	printf("              |   min   | %4.2lf  |   %2.2lf  |  %2.2lf  |  %2.2lf  |\n",mid.min,final.min,atten.min,*min);
	printf("              |_________|_______|_________|_________|_________|\n");
	printf("              |   max   | %2.2lf |  %2.2lf  |  %2.2lf  |  %2.2lf  |\n",mid.max,final.max,atten.max,*max);
	printf("              |_________|_______|_________|_________|_________|\n");
	printf("              |   mean  | %2.2lf |  %2.2lf  |  %2.2lf  |  %2.2lf  |\n",mid.mean,final.mean,atten.mean,*mean);
	printf("              |_________|_______|_________|_________|_________|\n");
	printf("              |   sd    | %2.2lf  |   %2.2lf  |   %2.2lf  |  %2.2lf  |\n",mid.sd,final.sd,atten.sd,*sd);
	printf("              |_________|_______|_________|_________|_________|\n");
	printf("\n       __________________________________________________________\n");
	printf("      |          |  A  |  B+ |  B  |  C+ |  C  |  D+ |  D  |  F  |\n");
	printf("      |__________|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("      |  count   |  %2d | %2d  |  %2d | %2d  | %2d  | %2d  | %2d  | %2d  |\n",gr.A,gr.Bp,gr.B,gr.Cp,gr.C,gr.Dp,gr.D,gr.F);
	printf("      |__________|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("\n\n       Average total GPA = %.2lf\n",gr.GPA);
	printf("\n End of data Press any key\n");
	getch();
	
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
	printf("%10llu %-32s  %4.1lf   %4.1lf   %4.1lf  %4.1lf %s\n",x.id,x.name,x.mid,x.final,x.total,x.gpoint,x.grade);
}

void show_data(gradetype st[],int stcount){
	int i;
	system("cls");
	printf("===============================================================================\n");
	printf(" NO.      ID              NAME                     MID    FINAL  TOTAL  GRADE\n");
	printf("===============================================================================\n");
	for(i = 0;i < stcount;i++){
		printf(" %d. ",i+1);
		if(i<9){
			printf(" ");
		}
		print_data(st[i]);
	}
	printf("\n===============================================================================\n");
	printf("\n End of data Press any key\n");
	getch();		
}

void sort_between_min_max(gradetype st[],int stcount){
	double min,max;
	int i,count;
	char check;
	do{
		system("cls");
		printf("\nEnter Range of min score and max score : ");
		scanf("%lf %lf",&min,&max);
		count = 0;
		printf("\n");
		printf("===============================================================================\n");
		printf(" NO.      ID              NAME                     MID    FINAL  TOTAL  GRADE\n");
		printf("===============================================================================\n\n");
		for(i = 0;i < stcount;i++){
			if(st[i].total >= min && st[i].total <= max){
				count++;
				printf(" %d. ",count);
				if(count<10){
						printf(" ");
					}
				print_data(st[i]);
			}
		}
		printf("\n===============================================================================");
		printf("\n Do you want to search again?(Y or N)");
		printf("\n===============================================================================\n");
		do{
			check = getch();
		}while(check != 'Y' && check != 'y' && check != 'n' && check != 'N');
		rewind(stdin);
	}while(check == 'y' || check == 'Y');
}

void search_grade(gradetype st[],int stcount){
	char grade[3],ch;
	int i,count;
	do{
		system("cls");
		printf("\n Search Grade(A,B+,B,C+,C,D+,D,F or 0 = Exit : ) ");
			scanf("%2s",grade);
		count = 0;
		printf("\n");
		printf("===============================================================================\n");
		printf(" NO.      ID              NAME                     MID    FINAL  TOTAL  GRADE\n");
		printf("===============================================================================\n\n");
		if(strcmp(grade,"0") != 0){
			for(i = 0;i < stcount;i++){
				if(strcmp(grade,st[i].grade) == 0){
					count++;
					printf(" %d. ",count);
					if(count<10){
						printf(" ");
					}
					print_data(st[i]);
				}
			}
			printf("\n===============================================================================\n");
			printf(" Do you want to search grade again(Y or N)\n");
			printf("===============================================================================\n");
			do{
				ch = getch();
	   		}while(ch != 'Y' && ch != 'y' && ch != 'n' && ch != 'N');
		}
	}while(strcmp(grade,"0") != 0 && ch != 'n' && ch != 'N');
}

void search_name(gradetype st[],int stcount){
	char key_check[16],ch;
	int i,count;
	do{
		system("cls");
		printf("\nEnter Search key (0 = Exit) : ");
		scanf("%15s",key_check);
		strupr(key_check);
		count = 0;
		printf("===============================================================================\n");
		printf(" NO.      ID              NAME                     MID    FINAL  TOTAL  GRADE\n");
		printf("===============================================================================\n\n");
		if(strcmp(key_check,"0") !=0 ){
			for(i = 0;i < stcount;i++){
				if(strstr(st[i].name,key_check) != NULL){
					count++;
					printf("%d. ",count);
					if(count<10){
						printf(" ");
					}
					print_data(st[i]);
				}
			}
			printf("\n===============================================================================\n");
			printf(" Do you want to search grade again(Y or N)\n");
			printf("===============================================================================\n");
			do{
				ch = getch();
			}while(ch != 'Y' && ch != 'y' && ch != 'n' && ch != 'N');
		}
	}while(strcmp(key_check,"0") != 0 && ch != 'n' && ch != 'N');
}

int getint(int min,int max){
	int num;
	while( scanf("%d",&num) != 1 ||  num < min || num > max ){
		printf("Error Please input number between %d - %d : ",min,max);
		rewind(stdin);
	}
	return num;
}

void isored_data(gradetype st[],int *stcount,Ggrade *gr,double c_grade[]){
	int menu,index,i;
	char fname[15],lname[20],ch;
	gradetype x;
	do{
		system("cls");
		printf("    ========================================================================\n\n");
		printf("\n                        1.Insert data student\n\n");
		printf("                        2.Edit data student\n\n");
		printf("                        0.Exit\n\n");
		printf("    ========================================================================\n\n");
		printf(" Input menu : ");
		menu = getint(0,2);
		if(menu == 1){
			system("cls");
			printf("\n data studen No. %d",*stcount+1);
			printf("\n\n   -> input sudent ID : ");
			scanf("%llu",&x.id);
			printf("\n\n   -> input name and surename : ");
			scanf("%s %s",fname,lname);
			strupr(fname);
			strupr(lname);
			sprintf(x.name,"%s %s",fname,lname);
			printf("\n\n   -> input score midterm ,final and atten : ");
			scanf("%lf %lf %lf",&x.mid,&x.final,&x.atten);
			x.total = x.mid + x.final + x.atten;
			Grade_setting(&x,1,1,c_grade[0],c_grade[1],c_grade[2],c_grade[3],c_grade[4],c_grade[5],c_grade[6],&gr[0]);
			printf("\n===========================================================================");
			printf("\n    ID              NAME                      MID   FINAL  TOTAL  GRADE\n");
			printf("===========================================================================\n\n");
			print_data(x);
			printf("\n===========================================================================\n\n");
			printf("                          comfirm(Y) or cancel(N)");
			do{
				ch = getch();
			}while(ch != 'Y' && ch != 'y' && ch != 'n' && ch != 'N');
			if(ch == 'y' || ch == 'Y'){
				Grade_setting(&x,0,1,c_grade[0],c_grade[1],c_grade[2],c_grade[3],c_grade[4],c_grade[5],c_grade[6],&gr[0]);
				st[*stcount] = x;
				*stcount = *stcount + 1;
			}
		}
		if(menu == 2){
			system("cls");
			int ch_x=0,index2;
			printf("Search from student ID : ");
			scanf("%llu",&x.id);
			for(i=0;i<*stcount;i++){
				if(x.id == st[i].id){
					x = st[i];
					ch_x = 1;
					index = i;
				}
			}
			if(ch_x == 1){
				printf("\n===========================================================================");
				printf("\n    ID              NAME                      MID   FINAL  TOTAL  GRADE\n");
				printf("===========================================================================\n\n");
				print_data(x);
				printf("\n===========================================================================\n\n\n");
				printf(" input score mid,final atten for edit : ");
				scanf("%lf %lf %lf",&x.mid,&x.final,&x.atten);
				x.total = x.mid + x.final + x.atten;
				Grade_setting(&x,0,1,c_grade[0],c_grade[1],c_grade[2],c_grade[3],c_grade[4],c_grade[5],c_grade[6],gr);
				printf("\n===========================================================================");
				printf("\n    ID              NAME                      MID   FINAL  TOTAL  GRADE\n");
				printf("===========================================================================\n\n");
				print_data(x);
				printf("\n===========================================================================\n\n\n");
				printf("Comfirm(Y) or Cancel(N)");
				do{
					ch = getch();
				}while(ch != 'Y' && ch != 'y' && ch != 'n' && ch != 'N');
				if(ch == 'y' || ch == 'Y'){
					st[index] = x;
					gr[0].GPA = gr[0].A = gr[0].B = gr[0].Bp = gr[0].Cp = gr[0].C = gr[0].Dp = gr[0].D = gr[0].F = 0;
					Grade_setting(st,0,*stcount,c_grade[0],c_grade[1],c_grade[2],c_grade[3],c_grade[4],c_grade[5],c_grade[6],gr);
				}
			}
			else{
				printf("\n\n               Sorry not data for student ID : %llu !!!!\n\n",x.id);
				getch();
			}
		}
		rewind(stdin);
	}while(menu != 0);
}

void delete_data(gradetype st[],int *stcount,Ggrade *gr,double c_grade[]){
	int index,ch_x = 0,i,ch_n;
	char ch;
	gradetype x;
	do{	
		ch_n = ch_x = x.id = 0 ;
		system("cls");
		printf(" Input student ID for delete (0 => Exit) : ");
		scanf("%llu",&x.id);
		for(i=0; i < *stcount; i++){
			if(x.id == st[i].id){
				x = st[i];
				index = i;
				ch_x = 1;
			}	
		}
		if(ch_x == 1){
			printf("\n===========================================================================");
			printf("\n    ID              NAME                      MID   FINAL  TOTAL  GRADE\n");
			printf("===========================================================================\n\n");
			print_data(x);
			printf("\n===========================================================================\n\n\n");
			printf("                 Comfirm for delete(Y) or Cancel(N)\n");
			do{
				ch = getch();
				ch_n = 1;
			}while(ch != 'Y' && ch != 'y' && ch != 'n' && ch != 'N');
			if(ch == 'Y' || ch == 'y'){
				Grade_setting(&st[index],2,1,c_grade[0],c_grade[1],c_grade[2],c_grade[3],c_grade[4],c_grade[5],c_grade[6],gr);
				for(i = index;i < *stcount - 1;i++){
					st[i] = st[i + 1];
				}
				*stcount = *stcount - 1;
			}
		}
		else if(x.id != 0){
			printf("\n\n               Sorry not data for student ID : %llu !!!!\n\n",x.id);
			getch();
		}
	}while(x.id != 0 || ch_n == 1);
}

void record_data(char file_name[],gradetype st[],int stcount){
	FILE *fp;
	int sucess = 0,i;
	system("cls");
	fp = fopen(file_name,"w");
	if(fp != NULL){
		for(i = 0;i < stcount;i++){
			fprintf(fp,"%llu,%s,%g,%g,%g\n",st[i].id,st[i].name,st[i].mid,st[i].final,st[i].atten);
			sucess++;
		}
		fclose(fp);
		printf("Total %d record write to file %s",sucess,file_name);
	}
	else{
		printf("Error can't write data to file %s\n",file_name);
	}
}

int main(){
	int num_menu,stcount=0;
	char file_name[20] = "SCORE1.CSV";
	char check_m2,ch_m2;
	double min,max,mean,sd;
	double c_grade[7] = {83,78,70,65,50,40,35};
	int sucess;
	typedef struct grade_info gradetype;
	gradetype st[100];
	s_mid mid;
	s_final final;
	s_atten atten;
	Ggrade gr;
	sucess = load_data_student(file_name,st,&stcount,&mid,&final,&atten);
	Grade_setting(st,0,stcount,83,78,70,65,50,40,35,&gr);
	do{
		system("cls");
		printf("                       Program data score of student\n");		
		printf("                            File : %s\n",file_name);
		if(sucess == 1){
			printf("                         Total read %d records\n",stcount);
		}
		else if(sucess == 0){
			printf("                         Error Can't Read File \n");
		}		
		printf("                                 Menu\n\n");
		printf("                 ------------------------------------------\n");
		printf("                      ==>  1.Read data form file?\n");
		printf("                      ==>  2.Setting cut grade\n");
		printf("                      ==>  3.Show statistic\n");
		printf("                      ==>  4.Show data student\n");
		printf("                      ==>  5.Sort data score for show data\n");
		printf("                      ==>  6.Sort data ID for show data\n");
		printf("                      ==>  7.Finding score range\n");
		printf("                      ==>  8.Show grade is set\n");
		printf("                      ==>  9.Finding form name\n");
		printf("                      ==>  10.Edit and Insert data\n");
		printf("                      ==>  11.Delete data from ID\n");
		printf("                      ==>  12.Record data\n");
		printf("                      ==>  0.Exit\n\n");
		printf("                 ------------------------------------------\n\n");
		if(sucess==1){
			printf("                   Input number for menu : ");
			num_menu = getint(0,12);
		}
		else{
			printf("                   Please edit file at menu 1. : ");
			num_menu = getint(0,1);
		}
		
		if(num_menu == 1){
			char ch_name[15];
			system("cls");
			printf("\n\n\n\n\n                   Read data file (0 => Exit) : ");
			scanf("%s",ch_name);
			if((strcmp(ch_name,"0")) != 0){
				strcpy(file_name,ch_name);
				sucess = load_data_student(file_name,st,&stcount,&mid,&final,&atten);
				if(sucess == 1){
					printf("\n\n                               Read data complete!\n\n");
					printf("                               Total read %d records\n",stcount);
					gr.GPA = gr.A = gr.B = gr.Bp = gr.Cp = gr.C = gr.Dp = gr.D = gr.F = 0;
					Grade_setting(st,0,stcount,c_grade[0],c_grade[1],c_grade[2],c_grade[3],c_grade[4],c_grade[5],c_grade[6],&gr);
				}
				else{
					printf("\n\n                               Read data faill !!");
				}
				getch();
			}
		}
		else if(num_menu == 2){
			do{
				do{
					system("cls");
					printf("\n do you want to setting grade?(Y or N)\n\n");
					ch_m2 = check_m2 = getch();
					if(check_m2 == 'y' || check_m2 == 'Y'){
						char grade[8][3] = {"A","B+","B","C+","C","D","F"};
						int i;
						for(i=0;i<7;i++){
							printf(" cut grade when %s >= ",grade[i]);
							scanf("%lf",&c_grade[i]);
						}
						system("cls");
						printf("\n\n\n");
						for(i=0;i<7;i++){
							printf( "                            score >= %.1lf --> %s\n\n",c_grade[i],grade[i]);
						}
						do{
							printf(" Comfirm! (Y or N) ");
							ch_m2 = getch();
							if(ch_m2 == 'Y' || ch_m2 == 'y'){
								gr.GPA = gr.A = gr.B = gr.Bp = gr.Cp = gr.C = gr.Dp = gr.D = gr.F = 0;
								Grade_setting(st,0,stcount,c_grade[0],c_grade[1],c_grade[2],c_grade[3],c_grade[4],c_grade[5],c_grade[6],&gr);
							}
						}while(ch_m2 != 'n'&&ch_m2 != 'N'&&ch_m2 != 'Y'&&ch_m2!= 'y');
					}
				}while(ch_m2 != 'N' && ch_m2 != 'n' );
				
			}while(check_m2 != 'N' && check_m2 != 'n');
		}
		else if(num_menu == 3){
			system("cls");
			find_statistic(st,stcount,&min,&max,&mean,&sd,mid,final,atten,gr);
		}
		else if(num_menu == 4){
			show_data(st,stcount);
		}
		else if(num_menu == 5){
			sort_total(st,stcount);
			show_data(st,stcount);
		}
		else if(num_menu == 6){
			sort_id(st,stcount);
			show_data(st,stcount);
		}
		else if(num_menu == 7){
			sort_between_min_max(st,stcount);
		}
		else if(num_menu == 8){
			search_grade(st,stcount);
		}
		else if(num_menu == 9){
			search_name(st,stcount);
		}
		else if(num_menu == 10){
			isored_data(st,&stcount,&gr,c_grade);
		}
		else if(num_menu == 11){
			delete_data(st,&stcount,&gr,c_grade);
		}
		else if(num_menu == 12){
			record_data(file_name,st,stcount);
			getch();
		}
	}while(num_menu != 0);
}
