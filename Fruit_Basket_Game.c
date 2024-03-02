
    /****************************
     * Fruit in Basket Game CLI *
     *  Auther : Devesh Patil
     * In this Game Base on C++ Language and basics of Graphs & Objest.
     * We can control the Basket by key 
     *          `a` to move left
     *          `d` to move right
     *          `w` to move top
     *          `s` to move bottom
    *****************************/

// Included Libraries
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int basketx = 3, baskety = 16;
int stopgame = 1;
int width=27;

void input(){
    int ch = getch();
    switch (ch){
        case 97: // a
            if (basketx>1)
                basketx= basketx-1;
            break;
        case 65: //A
            if (basketx>1)
                basketx= basketx-1;
            break;

        case 100: //d
            if (basketx<38)
                basketx = basketx+1;
            break;

        case 68: //D
            if (basketx<38)
                basketx = basketx+1;
            break;
        case 119: //w
            if (baskety>10)
                baskety= baskety-1;
            break;
        case 87: // W
            if (baskety>10)
                baskety= baskety-1;
            break;

        case 115: // s
            if (baskety<18)
                baskety = baskety+1;
            break;

        case 83: //S
            if (baskety<18)
                baskety = baskety+1;
            break;

        case 3:
            stopgame=0;
            break;
    }
}

int main(){
    int f=0,i=0,j=0;

    int fruitx = (rand() % (15 - 1 + 1)) + 1;
    int fruity = 1;
    int fruitx1 = (rand() % (19 - 1 + 1)) + 1;
    int fruity1 = 0;
    int fruitx2 = (rand() % (24 - 1 + 1)) + 1;
    int fruity2 = 0;

    int t = 39;

    int score = 0;
    printf("Welcome User !");
    while (stopgame){
        system("cls");
        printf("\033[0;33m Score : %d\n",score);
        for( i=0;i<20;i++){
            if(i==0 || i==19){
                for(j=0;j<width;j++){
                    if(j==0 || j==width-1){
                        printf("\033[0;34m|");  //Color Red
                    }
                    else{
                        printf("\033[0;34m*");  //Color Red
                    }
                }
            }
            else{
                if ( i!=fruity && i !=fruity1 && i!=fruity2 && i!=baskety){
                    for(j=0;j<width;j++){ 
                        if(j==0 || j==width-1){
                            printf("\033[0;34m|");  //Color Red
                        }
                        else{
                            printf(" ");
                        }
                    }
                }
                else if (i==baskety){
                    for(j=0;j<width-1;j++){ 
                        
                        if (j==basketx){
                            printf("W");
                        }
                        
                        if(j==0 || j==width-2){
                            printf("\033[0;34m|");
                        }
                        else{
                            printf(" ");
                        }
                    }
                }
                else{
                    for(j=0;j<width-1;j++){
                        //  check wheater fruit recheas to end of frame
                        if (fruity==19 || fruity1==19 ||fruity2==19){
                            stopgame = 0;
                        }
                        
                        if (j==fruitx && i==fruity || j==fruitx1 && i==fruity1){
                            printf("\033[0;31mO");
                        }
                        else if (j==fruitx2 && i==fruity2){
                            printf("\033[0;35mQ");
                        }

                        if (fruitx==basketx && fruity==baskety){
                            fruitx = (rand() % (39 - 1 + 1)) + 1;
                            score = score+10;
                            fruity = 0;
                        }
                        else if (fruitx1==basketx && fruity1==baskety){
                            fruitx1 = (rand() % (29 - 1 + 1)) + 1;
                            score = score+10;
                            fruity1 = 0;
                        }
                        else if (fruitx2==basketx && fruity2==baskety){
                            fruitx2 = (rand() % (39 - 1 + 1)) + 1;
                            score = score+20;
                            fruity2 = 0;
                        }
                        

                        if(j==0 || j==width-2){
                            printf("\033[0;34m|");
                        }
                        else{
                            printf(" ");
                        }
                    }
                }
            }
            printf("\n");
        }

        fruity++;
        if (fruity>5 || fruity1>5){ 
            fruity1++;
        }
        
        if(fruity1>5 || fruity2>3){ 
            fruity2++;
        }

        if (fruity==4 || fruity1==4){
            t-=1;
        }

        input();
    }
    return 0;
}
