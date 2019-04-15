#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct data
{
    int number;
    int arrival_time;
    int burst_time;
    int rt;
    int ft;
    int st;
    int waiting_time;
    int tat;
};

int fr = -1, rr = -1;
struct data priorQueue[51];
void LJF(struct data x) {
    int k, j;
    for (k=0;k<=rr;k++)
    {
        if (x.burst_time>priorQueue[k].burst_time)
        {
            for (j=rr+1;j>k;j--)
            {
                priorQueue[j]=priorQueue[j - 1];
            }
            priorQueue[k] = x;
            return;
        }
    }
    priorQueue[k] = x;
}

void SJF(struct data x) {
    int k, j;
    for (k=0;k<=rr;k++)
    {
        if (x.burst_time<priorQueue[k].burst_time)
        {
            for (j =rr+1;j>k;j--)
            {
                priorQueue[j] = priorQueue[j - 1];
            }
            priorQueue[k] = x;
            return;
        }
    }
    priorQueue[k] = x;
}

void Push(struct data x, int y) {
    if(fr==-1&&rr==-1)
    {
        fr++;
        rr++;
        priorQueue[rr] = x;
        return;
    }
    else
    {
    	if(y==1)
        LJF(x);
        else
        SJF(x);
    }
    rr++;
}

void Pop()
{
    int k;
    if(fr==-1&&rr==-1)
    {
        return;
    }
    for (k=0;k<rr;k++)
    {
        priorQueue[k] = priorQueue[k + 1];
    }
    rr--;
    if (rr==-1)
        fr=-1;
}

int Empty()
{
    return ((fr==-1 && rr==-1));
}
struct data pqTop()
{
    return priorQueue[fr];
}

void calculation(struct data p[],int g[],int m,int tt) {

    int k, j;
    float avgWt = 0, avgTrt = 0;
    for (k=0;k<m;k++)
    {
        for (j=tt;j>=0;j--)
        {
            if (g[j]==k+1)
            {
                p[k].ft=j+1;
                break;
            }
        }
    }

    for(k=0;k<m;k++)
    {
        for (j=0;j<tt;j++)
        {
            if (g[j]==k+1)
            {
                p[k].st=j;
                break;
            }
        }
    }
    for (k=0;k<m;k++)
    {
        p[k].waiting_time=p[k].ft-p[k].arrival_time-p[k].burst_time;
        p[k].tat=p[k].waiting_time+p[k].burst_time;
        avgWt+=p[k].waiting_time;
        avgTrt+=p[k].tat;
    }
    avgWt /= m;
    avgTrt /= m;
    printf("\n");
    printf("Average Waiting Time And Average Turn Around Time \n\n");
    printf("%f %f", avgWt, avgTrt);
    printf("\n");

}

void function(struct data p[],int m,int x)
{
    int tt=0,k,j;
    tt += p[0].arrival_time+p[0].burst_time;
    for (k=1;k<m;k++)
    {
        if (tt<p[k].arrival_time)
            tt=p[k].arrival_time;
        tt+=p[k].burst_time;
    }
    int ghart[tt],cpu_state=0;
    for (k=0;k<tt;k++)
        ghart[k] = -1;
    struct data current;
    for (k=0;k<tt;k++)
    {
        for (j=0;j<m;j++)
        {
            if (k==p[j].arrival_time)
            {
                	Push(p[j], x);
            }
        }
        if (cpu_state==0)
        {
            if (!Empty())
            {
                current = pqTop();
                Pop();
                cpu_state = 1;}}
        if (cpu_state==1)
        {
            current.burst_time--;
            ghart[k] = current.number;
            if (current.burst_time==0)
            {
                cpu_state=0;
            }}}

    for ( k=0;k<tt;k++)
        printf("%d ",ghart[k]);
    calculation(p,ghart,m,tt);
}

int main()
{

    int m,k;
    printf("enter number of process");
    scanf("%d", &m);
    struct data p[m];
    for (k=0;k<m;k++)
    {
    	scanf("%d", &p[k].number);
    	printf("enter arrival time for process %d :",k+1);
        scanf("%d",&p[k].arrival_time);
        p[k].burst_time = p[k].arrival_time * 2;
    }

    function(p, m, 1);
    printf("\n");
    function(p, m, 2);
}
