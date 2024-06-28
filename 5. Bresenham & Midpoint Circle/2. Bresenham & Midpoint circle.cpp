#include<iostream>
#include<graphics.h>
#include<dos.h>
using namespace std;

void bresenhumLineDrawing(int x1,int y1,int x2,int y2)
{
    if(x1>x2 ||y1>y2)
    {
        x1=x1+x2;
        x2=x1-x2;
        x1=x1-x2;

        y1=y1+y2;
        y2=y1-y2;
        y1=y1-y2;
    }

    float m=(y2-y1)/((x2+1)-x1);

    if(abs(m)<=1)
    {
        int dx=x2-x1;
        int dy=y2-y1;

        int d=2*dy-dx;
        int inc1=2*dy;
        int inc2=2*(dy-dx);

        while(x1<=x2)
        {
            putpixel(x1,y1,15);
            //delay(100);

            if(d<=0)
                d=d+inc1;
            else
            {

                d=d+inc2;
                y1++;
            }
            x1++;
        }
    }
    else{
        int dy=y2-y1;
        int dx=x2-x1;

        int d=2*dx-dy;
        int inc1=2*dx;
        int inc2=2*(dx-dy);

        while(y1<=y2)
        {
            putpixel(x1,y1,15);
            //delay(100);

            if(d<=0)
            {
                d=d+inc1;
            }
            else
            {

                d=d+inc2;
                x1++;
            }
            y1++;
        }
    }

}

void printCirclePoint(int x,int y,int h,int k)
{
    putpixel(x+h,y+k,15);
    putpixel(-x+h,y+k,15);
    putpixel(x+h,-y+k,15);
    putpixel(-x+h,-y+k,15);

    putpixel(y+h,x+k,15);
    putpixel(-y+h,x+k,15);
    putpixel(y+h,-x+k,15);
    putpixel(-y+h,-x+k,15);
}
void bresenhumCircle(int h,int k,int r)
{
    int x=0;
    int y=r;
    int d=3-2*r;

    while(x<=y)
    {
        printCirclePoint(x,y,h,k);
        delay(100);

        if(d<0)
            d=d+(4*x)+6;
        else
        {
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
}

void midPointCircle(int h,int k,int r)
{

    int x=0;
    int y=r;
    int p=1-r;

    while(x<=y)
    {
        printCirclePoint(x,y,h,k);
        delay(100);

        if(p<0)
            p=p+2*x+3;
        else
        {
            p=p+2*(x-y)+5;
            y--;
        }
        x++;
    }
}


int main()
{

    //initialize boundary lines
    initwindow(600,600,"Test Program");
    int X=getmaxx();
    int Y=getmaxy();
    int xh=X/2;
    int yh=Y/2;

    line(0,0,X,0);
    line(0,Y,X,Y);
    line(0,0,0,Y);
    line(X,0,X,Y);

    //line(X/2,0,X/2,Y);
    //line(0,Y/2,X,Y/2);

    //calling function
    bresenhumLineDrawing(X/2,0,X/2,Y);
    bresenhumLineDrawing(0,Y/2,X,Y/2);

    //bresenhumCircle(X/4,3*Y/4,50);
    midPointCircle(3*X/4,Y/4,50);


    while(!kbhit())
    {
        delay(200);
    }


    return 0;
}
