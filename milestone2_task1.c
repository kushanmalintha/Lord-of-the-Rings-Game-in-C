#include <stdio.h>


enum boolean {FALSE,TRUE};
typedef enum boolean bool_t;
bool_t t=TRUE;
bool_t f=FALSE;


// function to create fibonacci series
int fibonacci(int n)
{
    if(n==0){
        return 0;
    }else if(n==1){
        return 1;
    }else{
        return fibonacci(n-1)+fibonacci(n-2);
    }
}


// function to take three int and return true false
int fibonacciCheck()
{
    int num1,num2,num3,num_f;
    scanf("%d %d %d",&num1,&num2,&num3);
    num_f=fibonacci(num1);
    if(num_f==num2 || num_f==num3){
        return t;
    }else{
        return f;
    }
}


int main()
{
    int x;
    x=fibonacciCheck();
    if(x==t){
        printf("TRUE");
    }else{
        printf("FALSE");
    }
    return 0;
}