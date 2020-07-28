#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define WIDTH 10
#define HEIGHT 10
#define MAP_WIDTH WIDTH+2
#define MAP_HEIGHT HEIGHT+2

//printf cells
void print_cells(int (&a)[MAP_HEIGHT][MAP_WIDTH],int cnt);

int lives_counter(int (&a)[MAP_HEIGHT][MAP_WIDTH],int _x, int _y);

//compare now step => next step
void step_cells(int (&before)[MAP_HEIGHT][MAP_WIDTH], int (&after)[MAP_HEIGHT][MAP_WIDTH]);


int main()
{
    int cnt=1;

    int cell_a[MAP_HEIGHT][MAP_WIDTH]={{}};
    int cell_b[MAP_HEIGHT][MAP_WIDTH]={{}};


    int (*a)[MAP_HEIGHT][MAP_WIDTH] = &cell_a;
    int (*b)[MAP_HEIGHT][MAP_WIDTH] = &cell_b;
    int (*c)[MAP_HEIGHT][MAP_WIDTH];

    while(true){
        print_cells(*a,cnt);
        cnt++;
        step_cells(*a,*b);
        print_cells(*b,cnt);
        cnt++;
        step_cells(*b,*a);
    }
    return 0;
}

void print_cells(int (&a)[MAP_HEIGHT][MAP_WIDTH],int cnt)
{
    int x=1, y=1;
    int break_flag=0;
    while(true)
    {
        if(x<=0)x=1;
        if(x>=MAP_WIDTH-1) x=MAP_WIDTH-2;
        if(y<=0)y=1;
        if(y>=MAP_HEIGHT-1) y=MAP_HEIGHT-2;
        system("cls");
        printf("CURSOR MOVE:wasd SET:SPACE NEXT:r \n");
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                if(i==0){
                    a[0][j]=a[MAP_HEIGHT-2][j];
                    printf("%s",a[i][j]?"œ":"Z");
                    continue;
                }else if(i==MAP_HEIGHT-1){
                    a[MAP_HEIGHT-1][j]=a[1][j];
                    printf("%s",a[i][j]?"œ":"Z");
                    continue;
                }
                if(j==0){
                    a[i][0]=a[i][MAP_WIDTH-2];
                    printf("%s",a[i][j]?"œ":"Z");
                    continue;
                }else if(j==MAP_WIDTH-1){
                    a[i][MAP_WIDTH-1]=a[i][1];
                    printf("%s",a[i][j]?"œ":"Z");
                    continue;
                }

                if ((x == j) && (y == i))
                    printf("™");
                else
                    printf("%s",a[i][j]?"¡":" ");
                
            }
            printf("\n");
        }
        printf("GENERATION:%d \n",cnt);
        switch (_getch()){
            case 'w': y--;break;
            case 's': y++;break;
            case 'a': x--;break;
            case 'd': x++;break;
            case ' ': a[y][x] ^= 1;break;
            case 'r': break_flag=1;break;
        }

        if(break_flag){
            break;
        }
    }
}

int lives_counter(int (&a)[MAP_HEIGHT][MAP_WIDTH],int _x, int _y){
    int count=0;

    for(int y=-1;y<=1;y++){
        for(int x=-1;x<=1;x++){
            if((x==0)&&(y==0)) continue;

            int loop_WIDTH = _x + x;
            int loop_HEIGHT = _y + y;
            count += a[loop_HEIGHT][loop_WIDTH];
        }
    }
    return count;
}

void step_cells(int (&before)[MAP_HEIGHT][MAP_WIDTH], int (&after)[MAP_HEIGHT][MAP_WIDTH])
{

    for (int y = 1; y < MAP_HEIGHT-1; y++)
        {
            for (int x = 1; x < MAP_WIDTH-1; x++)
            {
            
            int n = lives_counter(before,x,y);
            int dead_or_alive = before[y][x];
            if(before[y][x]){
                if((n <= 1)||(n >= 4))dead_or_alive=0;//dead
            }else{
                if(n==3)dead_or_alive=1;//alive
            }
            after[y][x] = dead_or_alive;
        }
    }
}
