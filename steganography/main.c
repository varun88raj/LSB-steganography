#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long int binary(char ch)//function to covert character to binary
{
    int d;
    long int sum=0,unit=1;
    while(ch!=0)
    {

        d=ch%2;
        ch = ch/2;
        sum=sum + d*unit;
        unit=unit*10;
    }
        return sum;
}
int power(int x,int y)//function to find powers of 2
{
    int i,p=1;
    for(i=1;i<=y;i++)
    {
        p=p*x;
    }
    return p;
}
char ASCII(long int sum)//function to binary sum to the character
{
    int a=0;
    char ch;
    int d,i,k=0,j=0;
    int str[7]={0};
    while(sum!=0)
    {
            d=sum%10;
            str[k]=d;
            sum=sum/10;
            k++;
    }
    for(i=0;i<7;i++)
    {
            a=a+(str[i])*(power(2,j));
            j++;
    }
    ch=a;
    return ch;
}
char encrypt(char ch,int d)//encrypting function
{
    long int sum;
    if(ch>=0)
    {
        sum=binary(ch);//converting character of image to binary
        if(d==0&&sum%10==1)
        {
            sum=sum-1;//inserting 0 instead of 1
        }
        else if(d==1&&sum%10==0)
        {
            sum=sum+1;//inserting 1 instead of 0
        }
        else if(sum==0&&d==1)
        {
            sum=1;
        }
        else if(sum==1&&d==0)
        {
            sum=0;
        }
        ch=ASCII(sum);//converting modified sum back to character
    }
    else if(ch<0)
    {
        ch=ch-(2*ch);
        sum=binary(ch);
        if(d==0&&sum%10==1&&sum>10)
        {
            sum=sum-1;
        }
        else if(d==1&&sum%10==0&&sum>10)
        {
            sum=sum+1;
        }
        else if(sum==0&&d==1)
        {
            sum=1;
        }
        else if(sum==1&&d==0)
        {
            sum=0;
        }
        ch=ASCII(sum);
        //ch=ch-(2*ch);
        ch=0-ch;
    }
    return ch;
}
int main()
{
    FILE*ptr;
    FILE*ptr_1;
    FILE*ptr_2;
    char ch,dch,b;
    int i,j,k,B,d,q=0,l,x=0;
    long int sum,dsum,y=0;
    int p=0,v=0,count=0;
    char string[100];
    long int string_1[50]={0};
    long int string_2[10][7]={0};
    int str[8]={0};
    printf("\n ENTER ANY WORD (ALPHABETS ONLY STARTING WITH CAPITAL) \n");
    gets(string);
    q=strlen(string);
    ptr_2=fopen("binary.txt","w");
    if(ptr_2==NULL)
    {
        printf("FILE NOT FOUND");
    }
    printf("\nThe corresponding binary file is\n");
    for(j=0;j<strlen(string);j++)
    {
        sum=binary(string[j]);//to covert character of given string to binary
        printf("%li\n",sum);
        k=6;
        while(sum!=0)
        {
            d=sum%10;
            str[k]=d;
            sum=sum/10;
            k--;
        }
        for(i=0;i<7;i++)
        {
            fprintf(ptr_2,"%d",str[i]);//writing every bit of characters to another text file
        }
        printf("\n");
    }
    fclose(ptr_2);
    ptr=fopen("657.jpg","rb+");
    ptr_2=fopen("binary.txt","r");
    ptr_1=fopen("PAINT_1.jpg","wb+");
    if(ptr==NULL)
    {
        printf("FILE NOT FOUND");
    }
    if(ptr_2==NULL)
    {
        printf("FILE NOT FOUND");
    }
    if(ptr_1==NULL)
    {
        printf("FILE NOT FOUND");
    }
    while(!feof(ptr))
    {
        fscanf(ptr,"%c",&ch);//getting every character from the image file
        if(!feof(ptr_2))
        {
                fscanf(ptr_2,"%c",&b);//getting every bit from file (text) 0 and 1
                B=b;
                B=B-48;
                ch=encrypt(ch,B);//sending character of image and bit of text
        }
        fprintf(ptr_1,"%c",ch);
    }
    fclose(ptr);
    fclose(ptr_1);
    fclose(ptr_2);
    printf("\nText has been succesfully encrypted into image\n");
    ptr_1=fopen("PAINT_1.jpg","rb+");
    for(l=0;l<(q*7);l++)
    {
        fscanf(ptr_1,"%c",&dch);
        dsum=binary(dch);
        if(dsum<0)
        {
            dsum=0-dsum;
            dsum=dsum%10;
        }
        else if(dsum==0||dsum==1)
        {
            dsum=dsum;
        }
        else
        {
            dsum=dsum%10;
        }
        string_1[x]=dsum;
        x++;
    }
    fclose(ptr_1);
    for(v=0;v<x/7;v++)
    {
        for(p=0;p<7;p++)
        {
            string_2[v][p]=string_1[count];
            count++;
        }
    }
    printf("\nThe decrypted message is  :  ");
    for(v=0;v<x/7;v++)
    {
        y=0;
        for(p=0;p<7;p++)
        {
            y=y+(string_2[v][p]*power(2,6-p));
        }
        printf("%c",y);
    }
    printf("\n");
}
