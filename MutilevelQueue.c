#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
typedef struct{
	int pro_id;
	int burst_time;
	int remaining_time;
	int priority;
	int waiting_time;
	int turnaround_time;
}Process;
Process k[20];
int s=0;
int total_time=0;
void enqueue(Process *q,int *size,Process process){
	q[*size]=process;
	
	(*size)++;
}
Process dequeue(Process *q,int *size){
	int i;
	Process temp=q[0];
	(*size)--;
	for(i=0;i<*size;i++){
		q[i]=q[i+1];
	}
	return temp;
}
void round_robin(Process *q,int *size,int quantem,int a){
	while(a>0 && *size>0){
		if(a>=quantem){
			Process temp=dequeue(q,size);
			if(temp.remaining_time>=quantem){
				a=a-quantem;
				temp.remaining_time=temp.remaining_time-quantem;
				if(temp.remaining_time <= 0){
					
					printf("Process %d is finished successfully\n",temp.pro_id);
					temp.turnaround_time=total_time;
					
				}
				else{
					
					enqueue(q,size,temp);
				}
				total_time=total_time+quantem;
				
			}
			else{
				a=a-temp.remaining_time;
				total_time=total_time+temp.remaining_time;
				temp.remaining_time=0;
				printf("Process %d is finished successfully\n",temp.pro_id);
				temp.turnaround_time=total_time;
			}
			temp.waiting_time=total_time-temp.burst_time;
			k[temp.pro_id]=temp;
		}
		else if(q[0].remaining_time<=a){
			a=a-q[0].remaining_time;
			total_time=total_time+q[0].remaining_time;
			q[0].remaining_time=0;
			
			Process temp=dequeue(q,size);
			printf("Process %d is finished successfully\n",temp.pro_id);
			temp.turnaround_time=total_time;
			temp.waiting_time=total_time-temp.burst_time;
			k[temp.pro_id]=temp;
			
		}
		else{
			q[0].remaining_time=q[0].remaining_time-a;
			total_time=total_time+a;
			printf("Process %d is running for %d second\n",q[0].pro_id,a);
			a=0;
		}
	}
}

void shortest_job_first(Process *q,int *size,int a){
	while(a>0&& *size>0){
		int i=0,shortest_jobid=0;
		for(i=0;i<*size;i++){
			if(q[i].remaining_time<q[shortest_jobid].remaining_time){
				shortest_jobid=i;
			}
		}
		Process temp=dequeue(q+shortest_jobid,size);
		if(temp.remaining_time>=a){
			temp.remaining_time=temp.remaining_time-a;
			total_time=total_time+a;
			a=0;
			if(temp.remaining_time==0){
				printf("Process %d is finished successfully\n",temp.pro_id);
				temp.turnaround_time=total_time;
			}
			else{
				enqueue(q,size,temp);
			}
			temp.waiting_time=total_time-temp.burst_time;
			k[temp.pro_id]=temp;
		}
		else{
			a=a-temp.remaining_time;
			total_time=total_time+temp.remaining_time;
			temp.remaining_time=0;
			printf("Process %d is finished successfully\n",temp.pro_id);
			temp.turnaround_time=total_time;
			temp.waiting_time=total_time-temp.burst_time;
			k[temp.pro_id]=temp;
		}
	}
}

void fifo(Process *q,int *size,int a){
	while(a>0&& *size>0){
		if(q[0].remaining_time>a){
			q[0].remaining_time=q[0].remaining_time-a;
			total_time=total_time+a;
			a=0;
		}
		else{
			a=a-q[0].remaining_time;
			total_time=total_time+q[0].remaining_time;
			q[0].remaining_time=0;
			Process temp=dequeue(q,size);
			printf("Process %d is finished successfully\n",temp.pro_id);
			temp.turnaround_time=total_time;
			temp.waiting_time=total_time-temp.burst_time;
			k[temp.pro_id]=temp;
		}
	}
}



int main(){
	int n, i, quantem;
    int switchtime = 20;
    Process *q0 = malloc(MAX_SIZE * sizeof(Process)); 
    Process *q1 = malloc(MAX_SIZE * sizeof(Process));
    Process *q2 = malloc(MAX_SIZE * sizeof(Process));
    Process *q3 = malloc(MAX_SIZE * sizeof(Process));
    int size_q0 = 0; 
    int size_q1 = 0;
    int size_q2 = 0;
    int size_q3 = 0;
    printf("Enter the total number of processes:");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        Process newprocess;
        newprocess.pro_id = i;
        printf("Enter the burst time of process %d :", newprocess.pro_id);
        scanf("%d", &newprocess.burst_time);
        printf("Enter the priority of the process %d (0 or 1 or 2 or 3):", newprocess.pro_id);
        scanf("%d", &newprocess.priority);
        newprocess.remaining_time = newprocess.burst_time;
        switch (newprocess.priority) {
            case 0:
                enqueue(q0, &size_q0, newprocess);
                break;
            case 1:
                enqueue(q1, &size_q1, newprocess);
                break;
            case 2:
                enqueue(q2, &size_q2, newprocess);
                break;
            case 3:
                enqueue(q3, &size_q3, newprocess);
                break;
        }
    }
	
	printf("Enter the quantem time for round robin algorithm:");
	scanf(" %d",&quantem);
	while(size_q0>0||size_q1>0||size_q2>0||size_q3>0){
		if(size_q0>0){
			round_robin(q0,&size_q0,quantem,switchtime);
		}
		if(size_q1>0){
			shortest_job_first(q1,&size_q1,switchtime);
		}
		if(size_q2>0){
			shortest_job_first(q2,&size_q2,switchtime);
		}
		if(size_q3>0){
			fifo(q3,&size_q3,switchtime);
		}
	}
	printf("\nProcess\tWaitingTime\tTurnaround Time\n");
	for(i=1;i<=n;i++){
		printf("%d\t%d\t\t%d\n",k[i].pro_id,k[i].waiting_time,k[i].turnaround_time);
		
	}
	free(q0);
    free(q1);
    free(q2);
    free(q3);

}










