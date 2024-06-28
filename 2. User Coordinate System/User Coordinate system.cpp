#include<graphics.h>
#include<stdio.h>
#include<dos.h>

int main()
{
    int MaxX,MaxY;
    initwindow(400,400,"First lab");

    MaxX=getmaxx();
    MaxY=getmaxy();

    line(MaxX/2,0,MaxX/2,MaxY);
    line(0,MaxY/2,MaxX,MaxY/2);



    while(!kbhit())
    {
        delay(200);
    }


    return 0;
}
