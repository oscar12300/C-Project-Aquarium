#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
struct fish{
    int id;
    char name[20];
    float size;
    int mood;
    int hungry;
    float life;
    char color[50];
    int feed_times;
    int hunger_decrease_count;
    int interact_count;
    int status;
};
/*主選單(1.開始新的養魚、2.讀取現有的檔案繼續養魚、3.顯示目前所有資料、4.結束遊戲並存檔)*/
void welcome(void);
/*宣告魚的所有狀態*/
void fish_status(struct fish *no);
/*列印魚的所有狀態(包含圖像)*/
void print_status(struct fish *no);
/*列印動作選單(1.餵食、2.互動、3.返回主選單)*/
void print_do_list (void);
/*執行動作指令(1.餵食、2.互動、3.返回主選單)*/
void act(int *main_n,int *food_count, struct fish *no);
/*動作1 餵食(體型/生命每餵食兩次+0.5、若四回合沒餵食則飢餓度-1)*/
void feed_fish (int *feed_n, int *food_count, struct fish *no, int *main_n);
/*動作2 互動(每互動一次心情+1，若三回合沒互動將使心情-1)*/
void interact_fish(int *interact_n, struct fish *no,int *main_n,int *s_check, int *food_count);
/*魚的體型增加、生命增加計算及列印*/
void fish_size_check (struct fish *no, int *feed_n );
/*魚的生命值計算、死亡判斷*/
void life_check1 (struct fish *no);
/*每隻魚的心情起始值為隨機決定*/
int random_mood(void);

int main(){
    srand(time(0));
    FILE *fp1,*fp2;
    struct fish no[5];
    int main_n, feed_n;
    int i, j, food_count = 5;
    char NAME[5][4], COLOR[5][4];
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            NAME[i][j] = ' ';
            COLOR[i][j] = ' ';
        }
    }
    int ID[5]={0},MOOD[5]={0},HUNGRY[5]={0},FEED_TIME[5]={0},
        H_COUNT[5]={0},INTER_COUTN[5]={0},STATUS[5]={0};
    float SIZE[5],LIFE[5];
    /*起始畫面*/
    while(1){
        welcome();
        scanf(" %d",&main_n);
        switch (main_n){
            case 1: fish_status(no); print_status(no); break;
            case 2: fp2 = fopen("status.txt","r");
                    for(i=0;i<5;i++){
                        fscanf(fp2,"%d %d %d %d %d %d %d %f %f",&ID[i],&MOOD[i],&HUNGRY[i],&FEED_TIME[i],
                           &H_COUNT[i],&INTER_COUTN[i],&STATUS[i],&SIZE[i],&LIFE[i]);
                    }
                    strcpy((no+0)->name,"孔雀魚");
                    strcpy((no+0)->color,"\033[47;30m白金色\033[0m");
                    strcpy((no+1)->name,"草金魚");
                    strcpy((no+1)->color,"\033[41;37m紅\033[47;30m白\033[41;37m相\033[47;30m間\033[0m");
                    strcpy((no+2)->name,"垃圾魚");
                    strcpy((no+2)->color,"\033[40;37m黑色\033[0m");
                    strcpy((no+3)->name,"火翅金鑽");
                    strcpy((no+3)->color,"\033[41;37m紅\033[40;37m黑\033[41;37m相\033[40;37m間\033[0m");
                    strcpy((no+4)->name,"紅蓮燈");
                    strcpy((no+4)->color,"\033[41;37m紅\033[44;37m藍\033[41;37m相\033[44;37m間\033[0m");
                    for(i=0;i<5;i++){
                        (no+i)->id = ID[i];
                        (no+i)->mood = MOOD[i];
                        (no+i)->hungry = HUNGRY[i];
                        (no+i)->feed_times = FEED_TIME[i];
                        (no+i)->hunger_decrease_count = H_COUNT[i];
                        (no+i)->interact_count = INTER_COUTN[i];
                        (no+i)->status = STATUS[i];
                        (no+i)->size = SIZE[i];
                        (no+i)->life = LIFE[i];
                    }
                    fclose(fp2);
                    print_status(no);
                    main_n = 1;
                    break;
            case 3: print_status(no); break;
            case 4: fp1 = fopen("pet.txt","w+");
                    fp2 = fopen("status.txt","w+");
                    fprintf(fp1,"\n目前擁有以下這些魚： \n");
                    for(i=0;i<5;i++){
                        if((no+i)->status == 1){
                            fprintf(fp1,"魚編號: %d\n", (no+i)->id);
                            fprintf(fp1,"名稱: %s\n", (no+i)->name);
                            fprintf(fp1,"顏色: %s\n", (no+i)->color);
                            fprintf(fp1,"體型: %.1f\n", (no+i)->size);
                            fprintf(fp1,"心情: %d\n", (no+i)->mood);
                            fprintf(fp1,"飢餓度: %d\n", (no+i)->hungry);
                            fprintf(fp1,"生命值: %.1f\n", (no+i)->life);
                            fprintf(fp1,"---------------------\n");
                            fprintf(fp2,"%d ", (no+i)->id);
                            fprintf(fp2,"%d ", (no+i)->mood);
                            fprintf(fp2,"%d ", (no+i)->hungry);
                            fprintf(fp2,"%d ", (no+i)->feed_times);
                            fprintf(fp2,"%d ", (no+i)->hunger_decrease_count);
                            fprintf(fp2,"%d ", (no+i)->interact_count);
                            fprintf(fp2,"%d ", (no+i)->status);
                            fprintf(fp2,"%.1f ", (no+i)->size);
                            fprintf(fp2,"%.1f ", (no+i)->life);
                        }
                    }
                    fclose(fp1);
                    fclose(fp2);
                    printf("\n檔案儲存成功\!\n");
                    Sleep(2000);
                    exit(0);
        }
        /*執行動作*/
        while(main_n==1){
            act(&main_n,&food_count,no);
        }
    }
    return 0;
}

/*主選單(1.開始新的養魚、2.讀取現有的檔案繼續養魚、3.顯示目前所有資料、4.結束遊戲並存檔)*/
void welcome(void){
    printf("\033[7m 歡迎遊玩開心水族箱 \033[m\n");
    printf("****************************\n");
    printf("*          主選單          *\n");
    printf("****************************\n");
    printf("*                          *\n");
    printf("*      1.開始養魚          *\n");
    printf("*      2.讀取檔案繼續養魚  *\n");
    printf("*      3.檢視目前資料      *\n");
    printf("*      4.結束並存檔        *\n");
    printf("*                          *\n");
    printf("****************************\n");
    printf("輸入數字以執行的動作: ");
}
/*宣告魚的所有狀態*/
void fish_status(struct fish *no){

    /*一號魚*/
    (no+0)->id = 1;
    strcpy((no+0)->name,"孔雀魚");
    strcpy((no+0)->color,"\033[47;30m白金色\033[0m");
    (no+0)->size = 5.0;
    (no+0)->mood = random_mood();
    (no+0)->hungry = 3;
    (no+0)->life = 3.0;
    (no+0)->feed_times = 0;
    (no+0)->hunger_decrease_count = 0;
    (no+0)->interact_count = 0;
    (no+0)->status = 1;
    /*二號魚*/
    (no+1)->id = 2;
    strcpy((no+1)->name,"草金魚");
    strcpy((no+1)->color,"\033[41;37m紅\033[47;30m白\033[41;37m相\033[47;30m間\033[0m");
    (no+1)->size = 6.0;
    (no+1)->mood = random_mood();
    (no+1)->hungry = 3;
    (no+1)->life = 3.0;
    (no+1)->feed_times = 0;
    (no+1)->hunger_decrease_count = 0;
    (no+1)->interact_count = 0;
    (no+1)->status = 1;
    /*三號魚*/
    (no+2)->id = 3;
    strcpy((no+2)->name,"垃圾魚");
    strcpy((no+2)->color,"\033[40;37m黑色\033[0m");
    (no+2)->size = 7.0;
    (no+2)->mood = random_mood();
    (no+2)->hungry = 3;
    (no+2)->life = 3.0;
    (no+2)->feed_times = 0;
    (no+2)->hunger_decrease_count = 0;
    (no+2)->interact_count = 0;
    (no+2)->status = 1;
    /*四號魚*/
    (no+3)->id = 4;
    strcpy((no+3)->name,"火翅金鑽");
    strcpy((no+3)->color,"\033[41;37m紅\033[40;37m黑\033[41;37m相\033[40;37m間\033[0m");
    (no+3)->size = 6.0;
    (no+3)->mood = random_mood();
    (no+3)->hungry = 3;
    (no+3)->life = 3.0;
    (no+3)->feed_times = 0;
    (no+3)->hunger_decrease_count = 0;
    (no+3)->interact_count = 0;
    (no+3)->status = 1;
    /*五號魚*/
    (no+4)->id = 5;
    strcpy((no+4)->name,"紅蓮燈");
    strcpy((no+4)->color,"\033[41;37m紅\033[44;37m藍\033[41;37m相\033[44;37m間\033[0m");
    (no+4)->size = 5.0;
    (no+4)->mood = random_mood();
    (no+4)->hungry = 3;
    (no+4)->feed_times = 0;
    (no+4)->life = 3.0;
    (no+4)->hunger_decrease_count = 0;
    (no+4)->interact_count = 0;
    (no+4)->status = 1;
}
/*列印魚的所有狀態(包含圖像)*/
void print_status(struct fish *no){
   int i;
    printf("\n您目前擁有的魚： \n");
    for(i=0;i<5;i++){
    if((no+i)->status == 1){
        printf("魚編號: %d\n", (no+i)->id);
        printf("名稱: %s", (no+i)->name);
         switch (i){
            case 0: printf("     /¯¯¯¯¯¯¯¯\\  /|\n"); break;
            case 1: printf("     \033[40;37m/¯¯\033[40;31m¯¯\033[40;37m¯¯\033[40;31m¯¯\033[40;37m\\  /\033[40;31m|\033[0m\n"); break;
            case 2: printf("    \033[7m /¯¯¯¯¯¯¯¯\\  /|\033[m\n"); break;
            case 3: printf("  \033[47;30m /¯¯\033[47;31m¯¯\033[47;30m¯¯\033[47;31m¯¯\033[47;30m\\  /\033[47;31m|\033[0m\n"); break;
            case 4: printf("     \033[40;34m/¯¯\033[40;31m¯¯\033[40;34m¯¯\033[40;31m¯¯\\  \033[40;31m/\033[40;34m|\033[0m\n"); break;
        }
        printf("顏色: %s", (no+i)->color);
         switch (i){
            case 0: printf("    / ^        \\/ |\n"); break;
            case 1: printf("  \033[40;31m/ \033[40;37m^        \033[40;37m\\\033[40;37m/ \033[40;31m|\n"); break;
            case 2: printf("      \033[7m/ ^        \\/ |\033[m\n"); break;
            case 3: printf("  \033[47;31m/ \033[47;30m^        \\/ \033[47;31m|\033[0m\n"); break;
            case 4: printf("  \033[40;31m/ \033[40;37m^        \033[40;34m\\/ |\033[0m\n"); break;
        }
        printf("\033[33m體型\033[0m: %.1f", (no+i)->size);
         switch (i){
            case 0: printf("       \\          /\\ |\n"); break;
            case 1: printf("       \033[40;31m\\          \033[40;37m/\\ \033[40;31m|\n"); break;
            case 2: printf("       \033[7m\\          /\\ |\033[m\n"); break;
            case 3: printf("       \033[47;31m\\          \033[47;30m/\\ \033[47;31m|\033[0m\n"); break;
            case 4: printf("       \033[40;31m\\          \033[40;34m/\\ |\033[0m\n"); break;
        }
        printf("\033[35m心情\033[0m: %d", (no+i)->mood);
        switch (i){
            case 0: printf("          \\________/  \\|\n"); break;
            case 1: printf("          \033[40;37m\\__\033[40;31m__\033[40;37m__\033[40;31m__\033[40;37m/  \\\033[40;31m|\033[0m\n"); break;
            case 2: printf("         \033[7m \\________/  \\|\033[m\n"); break;
            case 3: printf("         \033[47;30m \\__\033[47;31m__\033[47;30m__\033[47;31m__\033[47;30m/  \\\033[47;31m|\033[0m\n"); break;
            case 4: printf("          \033[40;34m\\__\033[40;31m__\033[40;34m__\033[40;31m__\033[40;31m/  \\\033[40;34m|\033[0m\n"); break;
        }
        printf("\033[32m飢餓度\033[0m: %d\n", (no+i)->hungry);
        printf("\033[31m生命值\033[0m: %.1f\n", (no+i)->life);
        printf("-----------------------------------\n");
        Sleep(500);
        }
    }
}
/*列印動作選單(1.餵食、2.互動、3.返回主選單)*/
void print_do_list (void){
    printf("\n********************\n");
    printf("*     動作選單     *\n");
    printf("********************\n");
    printf("*                  *\n");
    printf("*    1.餵食        *\n");
    printf("*    2.互動        *\n");
    printf("*    3.返回主選單  *\n");
    printf("*                  *\n");
    printf("********************\n");
    printf("輸入數字以執行的動作: ");
}
/*執行動作指令(1.餵食、2.互動、3.返回主選單)*/
void act(int *main_n,int *food_count, struct fish *no){
    int check = 0;
    int feed_n;
    int interact_n;
    int do_n;
    int *s_check, s_c = 0;
    print_do_list();
    scanf("%d",&do_n);
    if(do_n == 1){
        printf("您目前持有的飼料數: %d\n\n",*food_count);
        if(*food_count > 0){
            printf("請輸入想餵食的對象編號: ");
            while(check != 1){
            scanf("%d",&feed_n);
                if(feed_n>5||feed_n<0){
                    check = 0;
                    printf("請重新輸入編號(1~5): ");
                }
                else{
                    check = 1;
                    feed_fish(&feed_n, food_count, no, main_n);
                }
            }
        }else{
            printf("您目前沒有飼料了!\n");
            printf("(你可以透過和魚互動隨機取得飼料)\n");
            printf("\033[7m\n將您導向至動作選單....\033[m\n");
            *main_n = 1;
            Sleep(500);
        }
    }
    if(do_n == 2){
        check = 0;
        printf("請輸入想互動的對象編號: ");
        while(check != 1){
            scanf("%d",&interact_n);
            if(interact_n>5||interact_n<0){
                check = 0;
                printf("請重新輸入編號(1~5): ");
            }
            else{
                check = 1;
                while(s_c != 1){
                    interact_fish(&interact_n, no, main_n, s_check, food_count);
                    s_c = *s_check;
                }
            }
        }
    }
    if(do_n == 3){
        printf("\n");
        *main_n = 0;
    }
}
/*動作1 餵食(體型/生命每餵食兩次+0.5、若四回合沒餵食則飢餓度-1)*/
void feed_fish (int *feed_n, int *food_count, struct fish *no, int *main_n){
     int i;
     if((no+(*feed_n-1))->hungry > 0 && (no+(*feed_n-1))->hungry < 5){
        switch (*feed_n){
            case 1:
                (no+0)->hunger_decrease_count = 0;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                break;
            case 2:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count = 0;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                break;
            case 3:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count = 0;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                break;
            case 4:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count = 0;
                (no+4)->hunger_decrease_count += 1;
                break;
            case 5:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count = 0;
                break;
        }
    }
    switch (*feed_n){
        case 1: case 2: case 3: case 4: case 5:
            if((no+(*feed_n-1))->hungry==5){
                printf("%d號魚的\033[32m飢餓度\033[0m已達最大值!\n",*feed_n);
                printf("\033[7m將您導向至動作選單....\033[m\n");
                Sleep(500);
                *main_n = 1;
                break;
            }else if((no+(*feed_n-1))->hungry > 0){
                (no+(*feed_n-1))->hungry += 1;
                *food_count-=1;
                printf("%d號魚增加了 1 點\033[32m飢餓度\033[0m !\n",*feed_n);
                printf("%d號魚的\033[32m飢餓度\033[0m現在為: %d !\n\n",*feed_n, (no+(*feed_n-1))->hungry);
                (no+(*feed_n-1))->feed_times += 1;
                fish_size_check(no,feed_n);
                Sleep(500);
                for(i=0;i<5;i++){
                    if((no+i)->hunger_decrease_count != 0 && (no+i)->hunger_decrease_count % 4 == 0){
                        (no+i)->hungry -= 1;
                        printf("(%d號魚的\033[32m飢餓度\033[0m下降 1 點)\n",i+1);
                        printf("(%d號魚的\033[32m飢餓度\033[0m現在為 : %d)\n\n",i+1,(no+i)->hungry);
                        Sleep(500);
                    }
                }
                life_check1(no);
                printf("\033[7m\n返回動作選單....\033[m\n");
                *main_n = 1;
                Sleep(500);
                break;
            }
    }
}
/*動作2 互動(每互動一次心情+1，若三回合沒互動將使心情-1)*/
void interact_fish(int *interact_n, struct fish *no, int *main_n, int *s_check, int *food_count){
    int sleep;
    int food_rand;
    int i;
        sleep = rand() % 5 + 1;
        if(sleep != 1 || (no+(*interact_n-1)) -> mood != 5){
         switch (*interact_n){
            case 1:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                (no+0)->interact_count = 0;
                (no+1)->interact_count += 1;
                (no+2)->interact_count += 1;
                (no+3)->interact_count += 1;
                (no+4)->interact_count += 1;
                break;
            case 2:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                (no+0)->interact_count += 1;
                (no+1)->interact_count = 0;
                (no+2)->interact_count += 1;
                (no+3)->interact_count += 1;
                (no+4)->interact_count += 1;
                break;
            case 3:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                (no+0)->interact_count += 1;
                (no+1)->interact_count += 1;
                (no+2)->interact_count = 0;
                (no+3)->interact_count += 1;
                (no+4)->interact_count += 1;
                break;
            case 4:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                (no+0)->interact_count += 1;
                (no+1)->interact_count += 1;
                (no+2)->interact_count += 1;
                (no+3)->interact_count = 0;
                (no+4)->interact_count += 1;
                break;
            case 5:
                (no+0)->hunger_decrease_count += 1;
                (no+1)->hunger_decrease_count += 1;
                (no+2)->hunger_decrease_count += 1;
                (no+3)->hunger_decrease_count += 1;
                (no+4)->hunger_decrease_count += 1;
                (no+0)->interact_count += 1;
                (no+1)->interact_count += 1;
                (no+2)->interact_count += 1;
                (no+3)->interact_count += 1;
                (no+4)->interact_count = 0;
                break;
            }
        }
        switch(*interact_n){
            case 1: case 2: case 3: case 4: case 5:
                if(sleep == 1 && (no+(*interact_n-1))->mood > 0){
                    printf("%d號魚似乎正在睡覺...\n",*interact_n);
                    Sleep(500);
                    printf("試試看和別隻魚互動，或嘗試喚醒它!\n(再次輸入編號，或輸入0返回動作選單): ");
                    *s_check = 0;
                    *main_n = 1;
                    scanf("%d",interact_n);
                    if(*interact_n == 0){
                        *main_n = 1;
                        *s_check = 1;
                    }
                    break;
                }else if ((no+(*interact_n-1))->mood > 0){
                    if((no+(*interact_n-1)) -> mood == 5){
                        printf("%d號魚的已經是最開心的狀態 !\n",*interact_n);
                        printf("試試看和別隻魚互動吧 !\n(再次輸入編號，或輸入0返回動作選單): ");
                        *s_check = 0;
                        *main_n = 1;
                        scanf("%d",interact_n);
                        if(*interact_n == 0){
                            *main_n = 1;
                            *s_check = 1;
                        }
                        break;
                    }else{
                        (no+(*interact_n-1)) -> mood += 1;
                        printf("\n你盯著%d號魚看，並露出微笑...\n",*interact_n);
                        Sleep(500);
                        printf("%d號魚的\033[35m心情\033[0m增加了1點 !\n",*interact_n);
                        printf("%d號魚的\033[35m心情\033[0m現在為: %d !\n\n",*interact_n, (no+(*interact_n-1))->mood);
                        Sleep(500);
                        for(i=0;i<5;i++){
                            if((no+i)->hunger_decrease_count != 0 && (no+i)->hunger_decrease_count % 4 == 0){
                                if((no+i)->hungry > 0){
                                    (no+i)->hungry -= 1;
                                    if((no+i)->hungry > 0){
                                        printf("(%d號魚的\033[32m飢餓度\033[0m下降了 1 點)\n",i+1);
                                        printf("(%d號魚的\033[32m飢餓度\033[0m現在為 : %d)\n\n",i+1,(no+i)->hungry);
                                        Sleep(700);
                                    }else if ((no+i)->hungry == 0){
                                        printf("(您的%d號魚已經快餓死了!!)\n",i+1);
                                    }
                                }
                            }
                            if((no+i)->interact_count != 0 && (no+i)->interact_count % 3 == 0){
                                if((no+i)->mood > 1){
                                    (no+i)->mood -= 1;
                                    if((no+i)->mood > 1){
                                        printf("(%d號魚的\033[35m心情\033[0m下降了 1 點)\n", i+1);
                                        printf("(%d號魚的\033[35m心情\033[0m現在為 : %d)\n\n",i+1,(no+i)->mood);
                                        Sleep(700);
                                    }else if((no+i)->mood == 1){
                                        printf("(您的%d號魚\033[35m心情\033[0m非常差，\033[35m心情\033[0m現在為1點!!)\n\n",i+1);
                                    }
                                }
                            }
                        }
                        Sleep(500);
                        life_check1(no);
                        *s_check = 1;
                        *main_n = 1;
                        food_rand = rand() % 3 + 1;
                        if(food_rand == 1){
                            *food_count += 1;
                            printf("\n(您獲得了 1 個飼料!)\n");
                            printf("您目前持有的飼料數: %d \n\n", *food_count);
                        }
                        printf("\033[7m\n返回動作選單....\033[m\n");
                        Sleep(500);
                        break;
                    }
                }
                *s_check = 1;
                *main_n = 1;
        }
}
/*魚的體型增加、生命增加計算及列印*/
void fish_size_check (struct fish *no, int *feed_n ){
    if((no+(*feed_n-1))->feed_times % 2 == 0){
        if((no+(*feed_n-1))->size==15){
            printf("您的%d號魚\033[33m體型\033[0m已達最大值!\n",*feed_n);
            Sleep(500);
        }
        else{
            (no+(*feed_n-1))->size += 0.5;
            printf("%d號魚\033[33m體型\033[0m增加了 0.5 cm!\n",*feed_n);
            printf("目前%d號魚的\033[33m體型\033[0m為: %.1f cm\n\n", *feed_n, (no+(*feed_n-1))->size);
            Sleep(500);
        }
        if((no+(*feed_n-1))->life==5){
            printf("您的%d號魚\033[31m生命\033[0m已達最大值!\n",*feed_n);
            Sleep(500);
        }
        else{
            (no+(*feed_n-1))->life += 0.5;
            printf("%d號魚\033[31m生命值\033[0m增加了 0.5 !\n",*feed_n);
            printf("目前%d號魚的\033[31m生命值\033[0m為: %.1f\n\n", *feed_n, (no+(*feed_n-1))->life);
            Sleep(500);
        }
    }

}
/*魚的生命值計算、死亡判斷*/
void life_check1 (struct fish *no){
    int i;
    for(i=0;i<5;i++){
        if((no+i)->hungry==0){
            (no+i)->life -= 1;
            if((no+i)->life>=0){
                printf("由於您太久沒有餵食%d號魚，它的\033[31m生命值\033[0m下降了 1 點 !\n",i+1);
                printf("目前%d號魚的\033[31m生命值\033[0m為: %.1f\n", i+1, (no+i)->life);
                printf("(盡快餵食%d號魚!!)\n\n",i+1);
                Sleep(500);
            }
        }
        if((no+i)->mood==1){
            (no+i)->life -= 1;
            if((no+i)->life>=0){
                printf("由於%d號魚的\033[35m心情\033[0m不佳，\033[31m生命值\033[0m下降了 1 點 !\n",i+1);
                printf("目前%d號魚的\033[31m生命值\033[0m為: %.1f\n", i+1,(no+i)->life);
                printf("(盡快與%d號魚互動吧!!)\n\n",i+1);
                Sleep(500);
            }
        }
        if((no+i)->life==0){
            printf("您的%d號魚很不幸的死亡了.....\n\n",i+1);
            strcpy((no+i)->name,"已死亡");
            strcpy((no+i)->color,"未知");
            (no+i)->size = -1;
            (no+i)->mood = -1;
            (no+i)->hungry = -1;
            (no+i)->feed_times = -1;
            (no+i)->life = -1;
            (no+i)->hunger_decrease_count = -999;
            (no+i)->interact_count = -999;
            (no+i)->status = -1;
        }
    }
}
/*每隻魚的心情起始值為隨機決定*/
int random_mood(void){
    int r_mood = rand() % 3 + 2;
    return r_mood;
}

