#include<iostream>
#include<graphics.h>
#include<dos.h>
using namespace std;

void findRegionalCode(int numOfLines,int xMin,int xMax,int yMin,int yMax,int lineX1[],int lineY1[],int lineX2[],int lineY2[],int regionCode1[],int regionCode2[])
{
    //finding region code
    for(int i=0;i<numOfLines;i++)
    {
        int x1=lineX1[i];
        int y1=lineY1[i];
        int x2=lineX2[i];
        int y2=lineY2[i];

        if(x1<xMin)
            regionCode1[i]+=1;
        if(x1>xMax)
            regionCode1[i]+=2;
        if(y1>yMax)
            regionCode1[i]+=8;
        if(y1<yMin)
            regionCode1[i]+=4;
        //else
            //regionCode1=0;

        if(x2<xMin)
            regionCode2[i]+=1;
        if(x2>xMax)
            regionCode2[i]+=2;
        if(y2>yMax)
            regionCode2[i]+=8;
        if(y2<yMin)
            regionCode2[i]+=4;
        //else
            //regionCode2[i]=0;

    }
}

void checkingCategory(int numOfLines,int regionCode1[],int regionCode2[],int lineCondition[])
{
    //cheching category
    for(int i=0;i<numOfLines;i++)
    {
        if(regionCode1[i]==0 && regionCode2[i]==0)
        {
            lineCondition[i]=1;//visible
            cout<<"Line "<<i+1<<" is visible\n";
        }
        else if((regionCode1[i] & regionCode2[i])!=0)
        {
            lineCondition[i]=-1;
            cout<<"Line "<<i+1<<" is Invisible\n";
        }
        else
        {
           lineCondition[i]=0;
            cout<<"Line "<<i+1<<" is Clipping candidate\n";
        }
    }
}

int numOfClippingCandidate(int n,int lineCondition[])
{
    int num=0;

    for(int i=0;i<n;i++)
    {
        if(lineCondition[i]==0)
            num++;
    }
    return num;
}
void cohenSutherlandLine()
{
    //initialize the algorithm
    int xMax,yMax;
    int xMin,yMin;
    int numOfLines;
    int linesX1[20],lineY1[20],linesX2[20],lineY2[20]; //lines X & Y
    int regionCode1[20]={0},regionCode2[20]={0};
    int lineCondition[20]={0}; //0=clipping candidate, 1 = visible, -1=not visible

    cout<<"Enter Min Max value of X :";
    cin>>xMin>>xMax;

    cout<<"Enter Min Max value of Y:";
    cin>>yMin>>yMax;

    cout<<"Enter number of lines :";
    cin>>numOfLines;

    cout<<"Enter "<<numOfLines<<"\'s x1 y1 & x2, y2"<<endl;
    for(int i=0;i<numOfLines;i++)
    {
        cin>>linesX1[i]>>lineY1[i]>>linesX2[i]>>lineY2[i];
    }


    findRegionalCode(numOfLines,xMin,xMax,yMin,yMax,linesX1,lineY1,linesX2,lineY2,regionCode1,regionCode2);

    checkingCategory(numOfLines,regionCode1,regionCode2,lineCondition);


    while(numOfClippingCandidate(numOfLines,lineCondition)!=0)
    {
        for(int i=0;i<numOfLines;i++)
        {
            if(lineCondition[i]==0)
            {
                float m=(1.0*lineY2[i]+lineY1[i])/(linesX2[i]-linesX1[i]);

                if((regionCode1[i]&1)!=0)
                {
                    lineY1[i]=lineY1[i]+m*(xMin-linesX1[i]);
                    linesX1[i]=xMin;
                    regionCode1[i]-=1;
                }
                else if((regionCode1[i]&2)!=0)
                {
                    lineY1[i]=lineY1[i]+m*(xMax-linesX1[i]);
                    linesX1[i]=xMax;
                    regionCode1[i]-=2;
                }
                else if((regionCode1[i]&8)!=0)
                {
                    linesX1[i]=linesX1[i]+(yMax-lineY1[i])/m;
                    lineY1[i]=yMax;
                    regionCode1[i]-=8;
                }
                else if((regionCode1[i]&4)!=0)
                {
                    linesX1[i]=linesX1[i]+(yMin-lineY1[i])/m;
                    lineY1[i]=yMin;
                    regionCode1[i]-=4;
                }



                if((regionCode2[i]&1)!=0)
                {
                    lineY2[i]=lineY1[i]+m*(xMin-linesX1[i]);
                    linesX2[i]=xMin;
                    regionCode2[i]-=1;
                }
                else if((regionCode2[i]&2)!=0)
                {
                    lineY2[i]=lineY1[i]+m*(xMax-linesX1[i]);
                    linesX2[i]=xMax;
                    regionCode2[i]-=2;
                }
                else if((regionCode2[i]&8)!=0)
                {
                    linesX2[i]=linesX1[i]+(yMax-lineY1[i])/m;
                    lineY2[i]=yMax;
                    regionCode2[i]-=8;
                }
                else if((regionCode2[i]&4)!=0)
                {
                    linesX2[i]=linesX1[i]+(yMin-lineY1[i])/m;
                    lineY2[i]=yMin;
                    regionCode2[i]-=4;
                }
            }

            checkingCategory(numOfLines,regionCode1,regionCode2,lineCondition);

        }
    }

    cout<<endl<<endl<<"Final line Conditions"<<endl;

    for(int i=0;i<numOfLines;i++)
    {
        if(lineCondition[i]==1)
        cout<<"Line "<<i+1<<" "<<" points: "<<linesX1[i]<<" "<<lineY1[i]<<" & "<<linesX2[i]<<" "<<lineY2[i]<<endl;

    }
}

int main()
{

    cohenSutherlandLine();

    return 0;
}
