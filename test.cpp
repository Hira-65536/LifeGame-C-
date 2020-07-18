#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

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
        //c=a;a=b;b=c;
    }
    return 0;
}

void print_cells(int (&a)[MAP_HEIGHT][MAP_WIDTH],int cnt)
{
    int x=0, y=0;
    int break_flag=0;
    //int cells[MAP_HEIGHT][MAP_WIDTH]={{}};
    while(true)
    {
        system("cls");
        printf("CURSOR MOVE:wasd SET:SPACE NEXT:r \n");
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                if ((x == j) && (y == i))
                    printf("™");
                else
                    printf("%s",a[i][j]?"¡":" ");
                /*if ((x == j) && (y == i))
                    printf("@");
                else
                    printf("%d",lives_counter(a,j,i));*/
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
            int loop_WIDTH = (MAP_WIDTH + _x + x) % MAP_WIDTH;
            int loop_HEIGHT = (MAP_HEIGHT + _y + y) % MAP_HEIGHT;
            count += a[loop_HEIGHT][loop_WIDTH];
        }
    }
    return count;
}

void step_cells(int (&before)[MAP_HEIGHT][MAP_WIDTH], int (&after)[MAP_HEIGHT][MAP_WIDTH])
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
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
