#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int p;
int burst[10],arrival[10],priority[10];
int process[10];
int around[10],waiting[10],g[10]={0},e[10];
int w,t;
int b[10];
int sg(int checker[],int i)
{
	int j=0;
	for(j=0;j<i;j++)
	{
		if(e[checker[j]]==0)
			break;
	}
	return j;
}
int show()
{	system("cls");
	sleep(3);
 	system("color 80");
	  	printf("\n\n\t\t\t=======================================================================================================================================\n"); 
  	printf("\n\n\t\t\tProcess\t\t|\tBurst Time\t|\tArrival Time\t|Priority\t|\tTurnaround Time\t|\tWaiting Time\t\n\n"); 
  	printf("\t\t\t=======================================================================================================================================\n\n");
	int i=0;
	for(i=0;i<p;i++)
	{
		printf("\t\t\tProcess[%d]\t|\t%d\t\t|\t%d\t\t|\t%d\t|\t%d\t\t|\t%d\t\n\n",process[i],burst[i],arrival[i],priority[i],around[i],waiting[i]); 
			printf("\n\t\t\t=======================================================================================================================================\n");
	}
	
	printf("\n\t\t\tAverage Waiting Time= %f",w*1.0/p); 
  printf("\n\t\t\tAverage Turnaround Time = %f",t*1.0/p);
  	printf("\n\n\t\t\t=======================================================================================================================================\n\n"); 
}
int kg(int c,int b)			
{
	int  i;
	i=-1;
	int j;
	if(b!=-1)
	{
	for(j=0;j<p;j++)
	{
		if(arrival[j]==arrival[b])
		{
			continue;
		}
		else
		{if(arrival[j]==c)
		{
			return j;
		}
		}
		
	}
}
	else
	{
		for(j=0;j<p;j++)
	{
		if(arrival[j]==c)
		{
			return j;
		
		}
	}
	
	}
	return i;
}
void prior()		
{
	int i=0,j=0,k=p-1,max,temp=-1;
	while(j<p)
	{
		max=-1;
		for(i=0;i<p;i++)
		{
			if(max<=priority[i] && g[i]==0)
			{
				max=priority[i];
				b[k]=i;
				temp=i;
			}
		}
		g[temp]=1;
		j++;
		k--;
	}
}
int min(int time)    
{
	int i,j=-1;
	for(i=0;i<p;i++)
	{
		if(arrival[i]==time && g[i] ==0)
		{
			j=i;
			break;
		}
	}
	if(j!=-1)
	{
		g[j]=1;
	}
	return j;

}
int main()

{
	system("color 87");
	printf("\n\n\n\n\n\t\t\t\t==========================================\n\n"); 
	printf("\t\t\t\t\tShrey Gupta\n\t\t\t\t\tRegd No.: 11703591\n\t\t\t\t\tLovely Professional Univesity\n");
	printf("\n\t\t\t\t==========================================\n"); 
	sleep(10);
	system("cls");
	int i=0,j,temp,temp1;
		system("color 07");
		FILE *fp; 
	fp=fopen("time.txt","w");
	N:	printf("Enter no of processes:-");
	scanf("%d",&p);
	putw(p,fp);
	if (p>10)
	{
		system("cls");
		printf("No. of process can't be  more than 10\n");
		sleep(3);   
		system("cls");
		goto N;
	}
	int fk[p];
	int Q[p];
	int Q2=0;
	for(i=0;i<p;i++)
	{
		process[i]=i;
	}
	for(i=0;i<p;i++)
	{
		printf("\t  Process[%d]\n",i);
		printf("\t=================\n");
		printf("enter burst time :",i);
		scanf("%d",&burst[i]);
		fk[i]=burst[i];
		I:	printf("enter arrival time :",i);
		scanf("%d",&arrival[i]);
		if (arrival[i]<0)
		{
			printf("Wrong Entry\n");
			goto I;
		}	
		Z: printf("enter priority :",i);
		scanf("%d",&priority[i]);
		if (priority[i]<0)
		{
			printf("Wrong Entry\n");
			goto Z;
		}
		 printf("\n");
	}
	int timeline=0;
	int remaining = p;
	int check[10];
	int k=0;
	prior();
	int index;

	for(i=0;i<p;i++)
		g[i]=0;
	i=0;
	while(remaining!=0)
	{
		while((k = min(timeline))!=-1)
		{
			check[i]=k;
			i++;
		}
		if(i==0 || sg(check,i)==i)
		{
			timeline++;
			continue;
		}

		int index= INT_MAX;
	for(j=0;j<i;j++)			
		{
			if(e[check[j]]!=1)
				{
			for(k=0;k<p;k++)
			{
				if(check[j]==b[k])
			{
				
					
						if(k<index)			
						{
							index=k;		
							break;
						}
					}
				}
			
			}
		}
		if(index==INT_MAX)
			continue;
		else{
			temp1=b[index];	
		index=temp1;
		temp=fk[index];
		}
	
		for(j=0;j<=temp&&(kg(timeline,index))==-1&& fk[index]>0;j++)   
		{
			fk[index]--;
			timeline++;
		}
		if(fk[index]>0)
		{
				while((k = min(timeline))!=-1)
				{
					check[i]=k;
					i++;
					while(priority[k]>priority[index]&&kg(timeline,k)==-1&&fk[index]!=0)
					{	fk[index]--;
						timeline++;
						if(kg(timeline,-1)!=-1)
							break;
					}
				}
			
				
			if(priority[kg(timeline,-1)]<priority[index]&&kg(timeline,-1)!=-1)	
			{

				Q[Q2]=index;
				Q2++;
				remaining--;
				e[index]=1;
			}
		}
		if(fk[index]==0)
		{
			waiting[index]=timeline-arrival[index]-burst[index];   
			w=w+waiting[index];
			around[index]=timeline-arrival[index];
			t=t+around[index];
			e[index]=1;
			remaining--;
		}	
		
	}
	int timeq=2;
	remaining = Q2;
	i=0;
	int checking    [10]={0};
	while(remaining!=0)
	{
		 if(fk[Q[i]]<=timeq && fk[Q[i]]>0) 
    { 
      timeline+=fk[Q[i]]; 
      fk[Q[i]]=0;  
    } 
    else if(fk[Q[i]]>0)
    { 
      fk[Q[i]]-=timeq; 
      timeline+=timeq; 
    } 
    if(fk[Q[i]]==0&&check[Q[i]]==0) 
    { 							
      remaining--;  
     	waiting[Q[i]]+=timeline-arrival[Q[i]]-burst[Q[i]];   
		w=w+waiting[Q[i]];
		around[Q[i]]+=timeline-arrival[Q[i]];
		t=t+around[Q[i]];
		check[Q[i]]=1; 
    } 
    if(i==Q2-1)
      i=0;  
    else 			
      i++; 
	}
	show();
	getch();
}
