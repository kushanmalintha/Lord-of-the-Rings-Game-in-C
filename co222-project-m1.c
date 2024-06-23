#include <stdio.h>
#include <stdlib.h>


char **array;


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


// function to create a numbered array according to the positions that can access
void numberArray(int H, int W, int S1, int S2, int E1, int E2)
{
    int number_array[H][W];

    // asign all the elements in number_array to -1 for minimum distance
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
        printf("There is no possible path from %c to %c\n",array[S1][S2],array[E1][E2]);
    }
    if(number_array[E1][E2]!=-1){
        printf("The minimum distance from %c to %c is %d\n",array[S1][S2],array[E1][E2],number_array[E1][E2]);
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


    // call the functions
    arrayfunction(characters,H,W);
    numberArray(H,W,S1,S2,E1,E2);

    return 0;
}