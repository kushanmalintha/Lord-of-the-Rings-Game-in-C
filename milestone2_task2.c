#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


char **array;
enum boolean {FALSE,TRUE};
typedef enum boolean bool_t;
bool_t t=TRUE;
bool_t f=FALSE;


// function to create fibonacci series
/*int fibonacci(int n)
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
}*/


// function to create 2D array
void arrayfunction(char characters[],int H,int W)
{
    // allocate memory for 2D array
    array=(char**)malloc(H*sizeof(char*));
    for(int i=0;i<H;i++){
        array[i]=(char*)malloc(W*sizeof(char));
    }
    
    // asign input characters to the array
    int count=0;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            array[i][j]=characters[count];
            count++;
        }
    }
    // print the array
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%c",array[i][j]);
        }printf("\n");
    }printf("\n");
}



// function to check, if the next move is in the array or not
bool inBounds(int N1, int N2, int H, int W)
{
    return (N1>=0 && N1<H && N2>=0 && N2<W);
}


// function to check, if the next move is according to given conditions 
bool canMove(char currentCell, char nextCell)
{
    int asciDiff=nextCell-currentCell;
    return (asciDiff<=2 && asciDiff>=0) || (asciDiff>=-3 && asciDiff<0);
}


// function to create a numbered array according to the positions that can access
void numberArray(int H, int W, int S1, int S2, int E1, int E2, int TR1, int TC1, int TR2, int TC2)
{
    int number_array[H][W];

    // asign all the elements in number_array to -1 for first minimum distance
    for(int i=0;i<H;i++){
      for(int j=0;j<W;j++){
            number_array[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue1[H*W][2];

    // front: row value of the queue1, back: row value of the queue1 that store the last elements
    int front=0;
    int back=0;
    //  make an array to store the directions that the present state can move
    int directions[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

    // initiate the starting position to zero in number_array
    number_array[S1][S2]=0;

    queue1[back][0]=S1;
    queue1[back][1]=S2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue1[front][0];
        int presentY=queue1[front][1];
        front++;

        // equal Number to value of the present value in number_array
        int Number=number_array[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==E1 && presentY==E2){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array[newX][newY]==-1){
                queue1[back][0]=newX;
                queue1[back][1]=newY;

                // the new state of the number_array asign to the increment number
                number_array[newX][newY]=Number+1;
                back++;
            }
        }
    }

    // check whether if there are  possible paths or not
    if(number_array[E1][E2]==-1){
        //printf("There is no possible path from %c to %c\n",array[S1][S2],array[E1][E2]);
        printf("%d\n",-1);
    }
    if(number_array[E1][E2]!=-1){
        //printf("The minimum distance from %c to %c is %d\n",array[S1][S2],array[E1][E2],number_array[E1][E2]);
        printf("%d\n",number_array[E1][E2]);
    }

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%d\t",number_array[i][j]);
         }printf("\n");
    }
    printf("\n");

    // asign all the elements in number_array to -1 for second minimum distance
    for(int i=0;i<H;i++){
      for(int j=0;j<W;j++){
            number_array[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue2[H*W][2];

    // front: row value of the queue2, back: row value of the queue2 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array
    number_array[S1][S2]=0;

    queue2[back][0]=S1;
    queue2[back][1]=S2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue2[front][0];
        int presentY=queue2[front][1];
        front++;

        // equal Number to value of the present value in number_array
        int Number=number_array[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==TR1 && presentY==TC1){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array[newX][newY]==-1){
                queue2[back][0]=newX;
                queue2[back][1]=newY;

                // the new state of the number_array asign to the increment number
                number_array[newX][newY]=Number+1;
                back++;
            }
        }
    }
    // check whether if there are  possible paths or not
    if(number_array[TR1][TC1]==-1){
        //printf("There is no possible path from %c to %c\n",array[S1][S2],array[E1][E2]);
        printf("%d\n",-1);
    }
    if(number_array[TR1][TC1]!=-1){
        //printf("The minimum distance from %c to %c is %d\n",array[S1][S2],array[E1][E2],number_array[E1][E2]);
        printf("%d\n",number_array[TR1][TC1]);
    }

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%d\t",number_array[i][j]);
         }printf("\n");
    }
    printf("\n");

    // asign all the elements in number_array to -1 for third minimum distance
    for(int i=0;i<H;i++){
      for(int j=0;j<W;j++){
            number_array[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue3[H*W][2];

    // front: row value of the queue3, back: row value of the queue3 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array
    number_array[S1][S2]=0;

    queue3[back][0]=S1;
    queue3[back][1]=S2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue3[front][0];
        int presentY=queue3[front][1];
        front++;

        // equal Number to value of the present value in number_array
        int Number=number_array[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==TR2 && presentY==TC2){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array[newX][newY]==-1){
                queue3[back][0]=newX;
                queue3[back][1]=newY;

                // the new state of the number_array asign to the increment number
                number_array[newX][newY]=Number+1;
                back++;
            }
        }
    }
    // check whether if there are  possible paths or not
    if(number_array[TR2][TC2]==-1){
        //printf("There is no possible path from %c to %c\n",array[S1][S2],array[E1][E2]);
        printf("%d\n",-1);
    }
    if(number_array[TR2][TC2]!=-1){
        //printf("The minimum distance from %c to %c is %d\n",array[S1][S2],array[E1][E2],number_array[E1][E2]);
        printf("%d\n",number_array[TR2][TC2]);
    }

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%d\t",number_array[i][j]);
         }printf("\n");
    }
    printf("\n");

    // asign all the elements in number_array to -1 for fourth minimum distance
    for(int i=0;i<H;i++){
      for(int j=0;j<W;j++){
            number_array[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue4[H*W][2];

    // front: row value of the queue4, back: row value of the queue4 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array
    number_array[TR1][TC1]=0;

    queue4[back][0]=TR1;
    queue4[back][1]=TC1;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue4[front][0];
        int presentY=queue4[front][1];
        front++;

        // equal Number to value of the present value in number_array
        int Number=number_array[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==E1 && presentY==E2){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array[newX][newY]==-1){
                queue4[back][0]=newX;
                queue4[back][1]=newY;

                // the new state of the number_array asign to the increment number
                number_array[newX][newY]=Number+1;
                back++;
            }
        }
    }
    // check whether if there are  possible paths or not
    if(number_array[E1][E2]==-1){
        //printf("There is no possible path from %c to %c\n",array[S1][S2],array[E1][E2]);
        printf("%d\n",-1);
    }
    if(number_array[E1][E2]!=-1){
        //printf("The minimum distance from %c to %c is %d\n",array[S1][S2],array[E1][E2],number_array[E1][E2]);
        printf("%d\n",number_array[E1][E2]);
    }

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%d\t",number_array[i][j]);
         }printf("\n");
    }
    printf("\n");

    // asign all the elements in number_array to -1 for fifth minimum distance
    for(int i=0;i<H;i++){
      for(int j=0;j<W;j++){
            number_array[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue5[H*W][2];

    // front: row value of the queue5, back: row value of the queue5 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array
    number_array[TR2][TC2]=0;

    queue5[back][0]=TR2;
    queue5[back][1]=TC2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue5[front][0];
        int presentY=queue5[front][1];
        front++;

        // equal Number to value of the present value in number_array
        int Number=number_array[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==E1 && presentY==E2){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array[newX][newY]==-1){
                queue5[back][0]=newX;
                queue5[back][1]=newY;

                // the new state of the number_array asign to the increment number
                number_array[newX][newY]=Number+1;
                back++;
            }
        }
    }
    // check whether if there are  possible paths or not
    if(number_array[E1][E2]==-1){
        //printf("There is no possible path from %c to %c\n",array[S1][S2],array[E1][E2]);
        printf("%d\n",-1);
    }
    if(number_array[E1][E2]!=-1){
        //printf("The minimum distance from %c to %c is %d\n",array[S1][S2],array[E1][E2],number_array[E1][E2]);
        printf("%d\n",number_array[E1][E2]);
    }

    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%d\t",number_array[i][j]);
         }printf("\n");
    }
    printf("\n");
}


int main()
{
    // H: hight of the character array, W: width of the character array
    int H,W;
    // S1,S2: starting position, E1,E2: end position
    int S1,S2,E1,E2;
    // take the inputs from the user
    scanf("%d %d",&H,&W);
    scanf("%d %d",&S1,&S2);
    scanf("%d %d",&E1,&E2);
    char characters[H*W+1];
    scanf("%s",characters);


    int TR1,TC1,TR2,TC2;
    scanf("%d %d",&TR1,&TC1);
    scanf("%d %d",&TR2,&TC2);


    /*int x;
    x=fibonacciCheck();
    if(x==t){
        printf("TRUE");
    }else{
        printf("FALSE");
    }*/


    // call the functions
    arrayfunction(characters,H,W);
    numberArray(H,W,S1,S2,E1,E2,TR1,TC1,TR2,TC2);


    return 0;
}