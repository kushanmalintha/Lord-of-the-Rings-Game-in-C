#include <stdio.h>
#include <stdlib.h>


char **array;
enum boolean {FALSE,TRUE};
typedef enum boolean bool_t;
bool_t t=TRUE;
bool_t f=FALSE;

int teleport_array_size;

// all the distances
int D1,D2,D3,D4,D5;


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


// check the calculated number equal to the given two numbers
int fibonacciCheck(int num1,int num2,int calculatedNum)
{
    int num_f=fibonacci(calculatedNum);
    if(num_f==num1 || num_f==num2){
        return t;
    }else{
        return f;
    }
}


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
    /*for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%c",array[i][j]);
        }printf("\n");
    }printf("\n");*/
}



// function to check, if the next move is in the array or not
int inBounds(int N1, int N2, int H, int W)
{
    return (N1>=0 && N1<H && N2>=0 && N2<W);
}


// function to check, if the next move is according to given conditions 
int canMove(char currentCell, char nextCell)
{
    int asciDiff=nextCell-currentCell;
    return (asciDiff<=2 && asciDiff>=0) || (asciDiff>=-3 && asciDiff<0);
}


// function to create a numbered array according to the positions that can access if no teleportation doors
void numberArray1(int H, int W, int S1, int S2, int E1, int E2)
{
    int number_array[H][W];

    // asign all the elements in number_array to -1
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            number_array[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue[H*W][2];

    // front: row value of the queue, back: row value of the queue that store the last elements
    int front=0;
    int back=0;
    //  make an array to store the directions that the present state can move
    int directions[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

    // initiate the starting position to zero in number_array
    number_array[S1][S2]=0;

    queue[back][0]=S1;
    queue[back][1]=S2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue[front][0];
        int presentY=queue[front][1];
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
                queue[back][0]=newX;
                queue[back][1]=newY;

                // the new state of the number_array asign to the increment number
                number_array[newX][newY]=Number+1;
                back++;
            }
        }
    }


    // check whether if there are  possible paths or not
    if(number_array[E1][E2]==-1){
        printf("There is no possible path from %c to %c\n",array[S1][S2],array[E1][E2]);
    }
    if(number_array[E1][E2]!=-1){
        printf("The minimum distance from %c to %c is %d\n",array[S1][S2],array[E1][E2],number_array[E1][E2]);
    }

    /*for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%d\t",number_array[i][j]);
         }printf("\n");
    }*/
    //printf("\n");
}


// function to create a numbered array according to the positions that can access for two teleportation doors
void numberArray2(int H, int W, int S1, int S2, int E1, int E2,int teleport_row_no[],int teleport_column_no[])
{
    int number_array_1[H][W];

    ///////// distance from start---------->end
    // asign all the elements in number_array_1 to -1
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            number_array_1[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue_1[H*W][2];

    // front: row value of the queue_1, back: row value of the queue_1 that store the last elements
    int front=0;
    int back=0;
    //  make an array to store the directions that the present state can move
    int directions[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

    // initiate the starting position to zero in number_array_1
    number_array_1[S1][S2]=0;

    queue_1[back][0]=S1;
    queue_1[back][1]=S2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue_1[front][0];
        int presentY=queue_1[front][1];
        front++;

        // equal Number to value of the present value in number_array_1
        int Number=number_array_1[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==E1 && presentY==E2){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array_1[newX][newY]==-1){
                queue_1[back][0]=newX;
                queue_1[back][1]=newY;

                // the new state of the number_array_1 asign to the increment number
                number_array_1[newX][newY]=Number+1;
                back++;
            }
        }
    }


    // check whether if there are  possible paths or not
    if(number_array_1[E1][E2]==-1){
        D1=-1;
    }
    if(number_array_1[E1][E2]!=-1){
        D1=number_array_1[E1][E2];
    }

    /*for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%d\t",number_array_1[i][j]);
         }printf("\n");
    }*/
    //printf("\n");


    ///////// distance from start---------->door1
    // asign all the elements in number_array_2 to -1
    int number_array_2[H][W];
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            number_array_2[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue_2[H*W][2];

    // front: row value of the queue_2, back: row value of the queue_2 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array_2
    number_array_2[S1][S2]=0;

    queue_2[back][0]=S1;
    queue_2[back][1]=S2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue_2[front][0];
        int presentY=queue_2[front][1];
        front++;

        // equal Number to value of the present value in number_array_2
        int Number=number_array_2[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==teleport_row_no[0] && presentY==teleport_column_no[0]){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array_2[newX][newY]==-1){
                queue_2[back][0]=newX;
                queue_2[back][1]=newY;

                // the new state of the number_array_2 asign to the increment number
                number_array_2[newX][newY]=Number+1;
                back++;
            }
        }
    }


    // check whether if there are  possible paths or not
    if(number_array_2[teleport_row_no[0]][teleport_column_no[0]]==-1){
        D2=-1;
    }
    if(number_array_2[teleport_row_no[0]][teleport_column_no[0]]!=-1){
        D2=number_array_2[teleport_row_no[0]][teleport_column_no[0]];
    }


    ///////// distance from start---------->door2
    // asign all the elements in number_array_3 to -1
    int number_array_3[H][W];
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            number_array_3[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue_3[H*W][2];

    // front: row value of the queue_3, back: row value of the queue_3 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array_3
    number_array_3[S1][S2]=0;

    queue_3[back][0]=S1;
    queue_3[back][1]=S2;
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue_3[front][0];
        int presentY=queue_3[front][1];
        front++;

        // equal Number to value of the present value in number_array_3
        int Number=number_array_3[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==teleport_row_no[1] && presentY==teleport_column_no[1]){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array_3[newX][newY]==-1){
                queue_3[back][0]=newX;
                queue_3[back][1]=newY;

                // the new state of the number_array_3 asign to the increment number
                number_array_3[newX][newY]=Number+1;
                back++;
            }
        }
    }


    // check whether if there are  possible paths or not
    if(number_array_3[teleport_row_no[1]][teleport_column_no[1]]==-1){
        D3=-1;
    }
    if(number_array_3[teleport_row_no[1]][teleport_column_no[1]]!=-1){
        D3=number_array_3[teleport_row_no[1]][teleport_column_no[1]];
    }


    ///////// distance from door1---------->end
    // asign all the elements in number_array_4 to -1
    int number_array_4[H][W];
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            number_array_4[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue_4[H*W][2];

    // front: row value of the queue_4, back: row value of the queue_4 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array_4
    number_array_4[teleport_row_no[0]][teleport_column_no[0]]=0;

    queue_4[back][0]=teleport_row_no[0];
    queue_4[back][1]=teleport_column_no[0];
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue_4[front][0];
        int presentY=queue_4[front][1];
        front++;

        // equal Number to value of the present value in number_array_4
        int Number=number_array_4[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==E1 && presentY==E2){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array_4[newX][newY]==-1){
                queue_4[back][0]=newX;
                queue_4[back][1]=newY;

                // the new state of the number_array_4 asign to the increment number
                number_array_4[newX][newY]=Number+1;
                back++;
            }
        }
    }


    // check whether if there are  possible paths or not
    if(number_array_4[E1][E2]==-1){
        D4=-1;
    }
    if(number_array_4[E1][E2]!=-1){
        D4=number_array_4[E1][E2];
    }


    ///////// distance from door2---------->end
    // asign all the elements in number_array_5 to -1
    int number_array_5[H][W];
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            number_array_5[i][j]=-1;
        }
    }

    // make an array to store the coordinates of the  state that can move    
    int queue_5[H*W][2];

    // front: row value of the queue_5, back: row value of the queue_5 that store the last elements
    front=0;
    back=0;

    // initiate the starting position to zero in number_array_5
    number_array_5[teleport_row_no[1]][teleport_column_no[1]]=0;

    queue_5[back][0]=teleport_row_no[1];
    queue_5[back][1]=teleport_column_no[1];
    back=1;

    // loop to check smallest path for the given destination
    while(front!=back){
        int presentX=queue_5[front][0];
        int presentY=queue_5[front][1];
        front++;

        // equal Number to value of the present value in number_array_5
        int Number=number_array_5[presentX][presentY];

        // check whether present state reach to the destination
        if(presentX==E1 && presentY==E2){
            break;
        }

        // loop to check the present state can move which direction
        for(int i=0;i<4;i++){
            int newX=presentX+directions[i][0];
            int newY=presentY+directions[i][1];

            // check whether the next move is within the bound or according to the given conditions
            if(inBounds(newX,newY,H,W) && canMove(array[presentX][presentY],array[newX][newY]) && number_array_5[newX][newY]==-1){
                queue_5[back][0]=newX;
                queue_5[back][1]=newY;

                // the new state of the number_array_5 asign to the increment number
                number_array_5[newX][newY]=Number+1;
                back++;
            }
        }
    }


    // check whether if there are  possible paths or not
    if(number_array_5[E1][E2]==-1){
        D5=-1;
    }
    if(number_array_5[E1][E2]!=-1){
        D5=number_array_5[E1][E2];
    }

    printf("D1=%d  D2=%d  D3=%d  D4=%d  D5=%d\n",D1,D2,D3,D4,D5);

}


// find the minimum distance
void minimum_distance(int S1,int S2,int E1,int E2)
{
    if(D1==-1 && D2==-1 && D3==-1){
        printf("There is no possible path from %c to %c",array[S1][S2],array[E1][E2]);
    }else if(D1==-1 && D2==-1 && D4==-1){
        printf("There is no possible path from %c to %c",array[S1][S2],array[E1][E2]);
    }else if(D1==-1 && D3==-1 && D5==-1){
        printf("There is no possible path from %c to %c",array[S1][S2],array[E1][E2]);
    }else if(D1==-1 && D4==-1 && D5==-1){
        printf("There is no possible path from %c to %c",array[S1][S2],array[E1][E2]);
    }else if(D2==-1 && D3==-1){
        printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D1);
    }else if(D1==-1 && D2==-1){
        printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D3+D4);
    }else if(D1==-1 && D3==-1){
        printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D2+D5);
    }else if(D1==-1 && D4==-1){
        printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D2+D5);
    }else if(D1==-1 && D5==-1){
        printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D3+D4);
    }else if(D1==-1){
        int x,y;
        x=D2+D5;
        y=D3+D4;
        if(x<y){
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],x);
        }else{
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],y);
        }
    }else if(D2==-1 || D5==-1){
        int x;
        x=D3+D4;
        if(x<D1){
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],x);
        }else{
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D1);
        }
    }else if(D3==-1 || D4==-1){
        int x;
        x=D2+D5;
        if(x<D1){
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],x);
        }else{
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D1);
        }
    }else if(D1!=-1 && D2!=-1 && D3!=-1 && D4!=-1 && D5!=-1){
        int x,y;
        x=D2+D5;
        y=D3+D4;
        if(x<=y && x<=D1){
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],x);
        }else if(y<=x && y<=D1){
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],y);
        }else if(D1<=x && D1<=y){
            printf("The minimum distance from %c to %c is %d",array[S1][S2],array[E1][E2],D1);
        }
    }
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


    int num1,num2;
    scanf("%d",&num1);
    scanf("%d",&num2);


    int no_of_doors;
    // input the nomber of doors
    scanf("%d",&no_of_doors);
    int row_no[no_of_doors];
    int column_no[no_of_doors];
    // input the row and column number of doors
    for(int i=0;i<no_of_doors;i++){
        scanf("%d %d",&row_no[i],&column_no[i]);
    }
    int calculatedNum[no_of_doors];
    // add calculated numbers to an array
    for(int i=0;i<no_of_doors;i++){
        calculatedNum[i]=((row_no[i])*W)+column_no[i];
        //printf("%d\n",calculatedNum[i]);
    }


    int *teleport_row_no;
    int *teleport_column_no;
    teleport_array_size=0;
    // calculate the size need for the teleport arrays
    for(int i=0;i<no_of_doors;i++){
        int x;
        x=fibonacciCheck(num1,num2,calculatedNum[i]);
        if(x==t){
            teleport_array_size++;
        }
    }
    //printf("%d\n",teleport_array_size);
    // allocate memory for teleport arrays
    teleport_row_no=(int*)malloc(teleport_array_size*sizeof(int));
    teleport_column_no=(int*)malloc(teleport_array_size*sizeof(int));
    int z=0;
    // add teleportation doors' row and column number  to the array;
    for(int i=0;i<no_of_doors;i++){
        int x;
        x=fibonacciCheck(num1,num2,calculatedNum[i]);
        if(x==t){
            teleport_row_no[z]=row_no[i];
            teleport_column_no[z]=column_no[i];
            z++;
        }
    }

    // print teleportation arrays
    /*for(int i=0;i<z;i++){
        printf("%d ",teleport_row_no[i]);
    }printf("\n");
    for(int i=0;i<z;i++){
        printf("%d ",teleport_column_no[i]);
    }printf("\n");*/


    // call the functions
    arrayfunction(characters,H,W);
    if(teleport_array_size==0 || teleport_array_size==1){
        numberArray1(H,W,S1,S2,E1,E2);
    }else if(teleport_array_size==2){
        numberArray2(H,W,S1,S2,E1,E2,teleport_row_no,teleport_column_no);
        minimum_distance(S1,S2,E1,E2);
    }

    return 0;
}