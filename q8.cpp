

#include<stdio.h>

struct schedulingg{
	int p_id;//process id
	int a_t;//arrival time
	int b_t;//brust time
	int c_t;//completion time
	int r_bt;
}f[100], s[100], m[100];

int n, fc=0, sc=0, mc=0;
int Quanta;


void rr(){//round robin process
	int t= m[0].a_t, mark=0, cc=0, i, rc;
	while(t!=120 && cc!=mc){
		for(i=0; i<=mark; i++){
			if(m[i].r_bt > Quanta){
				t += Quanta;
				m[i].r_bt -= Quanta;}
			else if(m[i].r_bt <=Quanta && m[i].r_bt !=0){           //  brust time is less than quanta
				t += m[i].r_bt;
				m[i].r_bt =0;
				m[i].c_t = t;
				cc++;}
			else;
		}
		int str = mark+1;
		for(rc= str; rc<mc; rc++){
			if(m[rc].a_t <= t){
				mark++;
			}
		}
	}	
}

void scheduling(){//priority to faculty is given
	int isc=0, ifc= 0, min, flag;
	if( fc!=0  && sc!=0){
		while(isc<sc && ifc<fc){
			if(f[ifc].a_t == s[isc].a_t){                          //priority of faculty is more than students
				m[mc] = f[ifc];                                    //same arrival time of processes
				mc++;
				ifc++;
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else if(f[ifc].a_t < s[isc].a_t){                         //arriavl of faculty is before student
				m[mc]= f[ifc];
				mc++;
				ifc++;
			}
			else if(f[ifc].a_t > s[isc].a_t){                         //arrival of faculty is after student
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else;
		}
		if(mc != (fc+sc)){
			if(fc!=ifc){
				while(ifc!=fc){
					m[mc]= f[ifc];
					mc++;
					ifc++;
				}
			}
			else if(sc!=isc){
				while(isc!=sc){
					m[mc]= s[isc];
					mc++;
					isc++;
				}
			}
		}
	}
	else if(fc==0){
		while(isc!=sc){
			m[mc]= s[isc];
			mc++;
			isc++;
		}
	}
	else if(sc==0){
		while(ifc!=fc){
			m[mc]= f[ifc];
			mc++;
			ifc++;
		}
	}
	else {
		printf("\n THERE ARE NO VALID JOBS \n");//none of the conditions match
	}
}

void display(){                     //diaplay on the console
	int i=0, total=0, sum=0; 
	double avg;
	printf("\nEXECUTION PROCESS.........\n");
	printf("\nQUERY ID NO.\tARRIVAL TIME\tRESOLVING TIME\tCOMPLETION TIME\tTURN AROUND TIME\tWAITING TIME");
	for(i; i<mc; i++){
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",
		m[i].p_id, (m[i].a_t+1000), m[i].b_t, (m[i].c_t+1000), (m[i].c_t-m[i].a_t), ((m[i].c_t-m[i].a_t)- m[i].b_t));
		//printing the details 
		total= m[i].c_t;
		sum+= (m[i].c_t-m[i].a_t);
	}
	avg = sum/mc;
	printf("\n\nTOTAL TIME FOR ALL QUERIES  : %d", total);// total time
	printf("\nAVERAGE TIME FOR QUERY        : %lf", avg);
	printf("\nEXECUTION OF PROCESS COMPLETED...............");
}

void getdata(){        //taking input from user 
	int match, i, arr_t;
	printf("TOTAL NUMBER OF QUERIES :- "); scanf("%d", &n);
	if(n==0) { printf("\n NO QUERIES ARE THERE \n"); }
	else{
		printf("\nENTER THE QUANTA FOR THE PROCESS : "); scanf("%d", &Quanta);
		printf("\nENTER :-\n1-FACULTY \n2-STUDENT \n");
		for(i=0; i<n; i++){
			printf("\nTYPE OF JOB  (1/2): "); scanf("%d", &match);
			if(match==1){                                           //details of faculty process
				printf("QUERY ID NO.  : "); scanf("%d", &f[fc].p_id);
				printf("ARRIVAL TIME  : "); scanf("%d", &arr_t);
				if(arr_t<1000 || arr_t>1200 )
				{
					printf("\nPLEASE ENTER THE CORRECT TIME ");
					getdata();
				}
				else{f[fc].a_t= arr_t-1000;}
				printf("RESOLVING TIME  : "); scanf("%d", &f[fc].b_t);	 f[fc].r_bt= f[fc].b_t; 
				fc++;
			} else{                                                         //details of student process
				printf("QUERY ID NO.   : "); scanf("%d", &s[sc].p_id);
				printf("ARRIVAL TIME   : "); scanf("%d", &arr_t); 
				if(arr_t<1000 || arr_t>1200){
					printf("\nPLEASE ENTER THE CORRECT TIME  \n");
					getdata(); 
				}
				else {s[sc].a_t= arr_t-1000; }
				printf("RESOLVING TIME   : "); scanf("%d", &s[sc].b_t);	 s[sc].r_bt= s[sc].b_t;
				sc++;
			}
		}
	}
}




 main(){
      printf("\nPLEASE FOLLOW THE GIVEN INSTRUCTIONS :-"
			"\n->ENTER TIME AS EXAMPLE FOE 10:30 AM ENTER 1030 . (THE UNIT OF TIME IS IN MINUTES )"
			"\n->ENTER THE ARRIVAL TIME OF QUERY IN ASCENDING ORDER , i.e., AS IN REAL TIME ARRIVAL METHOD \n"
			" \n\n"	);
	getdata();
	scheduling();
	rr();
	display();
}
