#include <stdio.h>
#include <stdlib.h>
typedef struct simpleDb{
char ID;
char year;
char C1ID;
char C1G;
char C2ID;
char C2G;
char C3ID;
char C3G;
}SDB;
SDB arr[9];
char Counter=0;
char SDB_AddEntry(char id,char year,char*subject,char*grade)
{
    if(Counter<10){
    arr[Counter].ID=id;
    arr[Counter].year=year;
    arr[Counter].C1ID=*(subject);
    arr[Counter].C1G=*(grade);
    arr[Counter].C2ID=*(subject+1);
    arr[Counter].C2G=*(grade+1);
    arr[Counter].C3ID=*(subject+2);
    arr[Counter].C3G=*(grade+2);
    Counter++;
    return (1);
    }
    else
    {
        return (0);
    }
}

char SDB_isFull(void)
{
    if(Counter == 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char SDB_GetUsedSize(void)
{
    return Counter;

}


void SDB_DeleteEntry(char id)
{
    for(int i=0;i<10;i++)
    {
        if(arr[i].ID==id)
        {
            arr[i].ID=0;
            arr[i].year=0;
            arr[i].C1ID=0;
            arr[i].C1G=0;
            arr[i].C2ID=0;
            arr[i].C2G=0;
            arr[i].C3ID=0;
            arr[i].C3G=0;
            Counter--;
        }
    }

}


void SDB_GetList(char*count,char*list)
{
    *count=Counter;
    for(int i=0;i<Counter;i++)
    {
        *(list+i)=arr[i].ID;
    }
}
char SDB_isExist(char id)
{
    int count=0;
   for(int i=0;i<10;i++)
    {
        if(id==arr[i].ID)
        {
            count++;
        }
    }
    if(count==1)
    {
        return 1;
    }
    else{
        return 0;
    }
}

char SDB_ReadEntry(char id,char*year,char*subject,char*grade)
{
    char check=0;
    check=SDB_isExist(id);
    if(check==1)
    {
        for(int i=0;i<10;i++)
        {
            if(id==arr[i].ID)
            {
                *year=arr[i].year;
                *(subject)=arr[i].C1ID;
                *(grade)=arr[i].C1G;
                *(subject+1)=arr[i].C2ID;
                *(grade+1)=arr[i].C2G;
                *(subject+2)=arr[i].C3ID;
                *(grade+2)=arr[i].C3G;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int x=0;
    char corse[3]={1,2,3};
    char grade [3]={100,90,80};
    SDB_AddEntry(10,15,corse,grade);
    SDB_AddEntry(11,13,corse,grade);
    SDB_DeleteEntry(10);
    printf("%d",arr[1].ID);

    return 0;
}
