#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define cols 10
#define rows 10
#define foods 10

char board[cols * rows];

int isGameOver = 0;
int snakeX = 5;
int snakeY = 5;

#define SNAKE_MAX_LEN 256

struct SnakePart {
    int x, y;
};

struct Snake {
    int length;
    struct SnakePart part[SNAKE_MAX_LEN];
};

struct Snake snake;

struct Food {
    int consumed;
    int x, y;
};

struct Food food[foods];

void fill_board(){
    int x,y;

    for(y=0; y<rows; y++) {

        for(x=0; x<cols; x++) {

            if(x==0 || y==0 || x==cols-1 || y==rows-1) {
                board[y*cols + x] = '#';
            } else {
                board[y*cols + x] = ' ';
            }
        }
    }
}


void print_board(){
    int x,y;

    for(y=0; y<rows; y++) {

        for(x=0; x<cols; x++) {

            putch(board[y*cols + x]);

        }
        putch('\n');
    }
}

void draw_snake() {
    //  board[snakeY*cols + snakeX] = '@';
    int i;

    for(i=snake.length-1; i>=0; i--) {
        board[snake.part[i].y*cols + snake.part[i].x] = '*';
    }
    board[snake.part[0].y*cols + snake.part[0].x] = '@';
}

void move_snake(int deltaX, int deltaY) {
    int i;

    snake.part[0].x += deltaX;
    snake.part[0].y += deltaY;

    for(i=snake.length-1; i>=0; i--){
        snake.part[i] = snake.part[i-1];
    }
}

void game_rules() { 
    int i;
    int all_food_consumed = 1;
    int tail_collision = 0;

    for(i=0; i<foods; i++) {
        if (!food[i].consumed && food[i].x == snake.part[0].x && food[i].y == snake.part[0].y) {
            food[i].consumed = 1;
            snake.length ++;
        }
    }

    for(i=1; i<snake.length; i++) {
        if(snake.part[0].x == snake.part[i].x && snake.part[0].y == snake.part[i].y) {
            tail_collision = 1;
        }
    }

    if (tail_collision || snake.part[0].x == 0 || snake.part[0].x == cols - 1 || snake.part[0].y == 0 || snake.part[0].y == rows - 1){
        isGameOver = 1;
        printf("Defeat");
    }

    for(i=0; i<foods; i++) {
        if (!food[i].consumed){
            all_food_consumed = 0;
        }
    }

    if (all_food_consumed){
        isGameOver = 1;
        printf("Victory");
    }
        
    
}

void read_keyboard() {
    int  ch = getch();

    switch(ch) {
        case 'w': move_snake( 0, -1); break;
        case 's': move_snake( 0,  1); break;
        case 'a': move_snake(-1,  0); break;
        case 'd': move_snake( 1,  0); break;
        case 'c': isGameOver = 1; break;
    }

}

void draw_food() {
    int i;

    for(i=0; i<foods; i++) {
        if(!food[i].consumed) {
            board[food[i].y*cols + food[i].x] = '+';
        }
    }

}

void initialise_food() {
    int i;

    for(i=0; i<foods; i++) {
        food[i].x = 1 + rand() % (cols - 2);
        food[i].y = 1 + rand() % (rows - 2);
        food[i].consumed = 0;
    }

}

void initialise_snake() {
    snake.length = 1;
    snake.part[0].x = 1 + rand() % (cols - 2);
    snake.part[0].y = 1 + rand() % (rows - 2);
}

int main(int argc, char **argv){
    //printf("Hello, World!\n");

    srand(time(0));

    initialise_food();
    initialise_snake();



    while(!isGameOver) {
        fill_board();
        place_food();
        print_board();
        eat_food();
        draw_snake();

        if (!isGameOver) read_keyboard();
    }

    return 0;
}