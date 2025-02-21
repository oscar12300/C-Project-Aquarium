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
/*�D���(1.�}�l�s���i���B2.Ū���{�����ɮ��~��i���B3.��ܥثe�Ҧ���ơB4.�����C���æs��)*/
void welcome(void);
/*�ŧi�����Ҧ����A*/
void fish_status(struct fish *no);
/*�C�L�����Ҧ����A(�]�t�Ϲ�)*/
void print_status(struct fish *no);
/*�C�L�ʧ@���(1.�����B2.���ʡB3.��^�D���)*/
void print_do_list (void);
/*����ʧ@���O(1.�����B2.���ʡB3.��^�D���)*/
void act(int *main_n,int *food_count, struct fish *no);
/*�ʧ@1 ����(�髬/�ͩR�C�����⦸+0.5�B�Y�|�^�X�S�����h���j��-1)*/
void feed_fish (int *feed_n, int *food_count, struct fish *no, int *main_n);
/*�ʧ@2 ����(�C���ʤ@���߱�+1�A�Y�T�^�X�S���ʱN�Ϥ߱�-1)*/
void interact_fish(int *interact_n, struct fish *no,int *main_n,int *s_check, int *food_count);
/*�����髬�W�[�B�ͩR�W�[�p��ΦC�L*/
void fish_size_check (struct fish *no, int *feed_n );
/*�����ͩR�ȭp��B���`�P�_*/
void life_check1 (struct fish *no);
/*�C�������߱��_�l�Ȭ��H���M�w*/
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
    /*�_�l�e��*/
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
                    strcpy((no+0)->name,"�ճ���");
                    strcpy((no+0)->color,"\033[47;30m�ժ���\033[0m");
                    strcpy((no+1)->name,"�����");
                    strcpy((no+1)->color,"\033[41;37m��\033[47;30m��\033[41;37m��\033[47;30m��\033[0m");
                    strcpy((no+2)->name,"�U����");
                    strcpy((no+2)->color,"\033[40;37m�¦�\033[0m");
                    strcpy((no+3)->name,"���ͪ��p");
                    strcpy((no+3)->color,"\033[41;37m��\033[40;37m��\033[41;37m��\033[40;37m��\033[0m");
                    strcpy((no+4)->name,"�����O");
                    strcpy((no+4)->color,"\033[41;37m��\033[44;37m��\033[41;37m��\033[44;37m��\033[0m");
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
                    fprintf(fp1,"\n�ثe�֦��H�U�o�ǳ��G \n");
                    for(i=0;i<5;i++){
                        if((no+i)->status == 1){
                            fprintf(fp1,"���s��: %d\n", (no+i)->id);
                            fprintf(fp1,"�W��: %s\n", (no+i)->name);
                            fprintf(fp1,"�C��: %s\n", (no+i)->color);
                            fprintf(fp1,"�髬: %.1f\n", (no+i)->size);
                            fprintf(fp1,"�߱�: %d\n", (no+i)->mood);
                            fprintf(fp1,"���j��: %d\n", (no+i)->hungry);
                            fprintf(fp1,"�ͩR��: %.1f\n", (no+i)->life);
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
                    printf("\n�ɮ��x�s���\\!\n");
                    Sleep(2000);
                    exit(0);
        }
        /*����ʧ@*/
        while(main_n==1){
            act(&main_n,&food_count,no);
        }
    }
    return 0;
}

/*�D���(1.�}�l�s���i���B2.Ū���{�����ɮ��~��i���B3.��ܥثe�Ҧ���ơB4.�����C���æs��)*/
void welcome(void){
    printf("\033[7m �w��C���}�ߤ��ڽc \033[m\n");
    printf("****************************\n");
    printf("*          �D���          *\n");
    printf("****************************\n");
    printf("*                          *\n");
    printf("*      1.�}�l�i��          *\n");
    printf("*      2.Ū���ɮ��~��i��  *\n");
    printf("*      3.�˵��ثe���      *\n");
    printf("*      4.�����æs��        *\n");
    printf("*                          *\n");
    printf("****************************\n");
    printf("��J�Ʀr�H���檺�ʧ@: ");
}
/*�ŧi�����Ҧ����A*/
void fish_status(struct fish *no){

    /*�@����*/
    (no+0)->id = 1;
    strcpy((no+0)->name,"�ճ���");
    strcpy((no+0)->color,"\033[47;30m�ժ���\033[0m");
    (no+0)->size = 5.0;
    (no+0)->mood = random_mood();
    (no+0)->hungry = 3;
    (no+0)->life = 3.0;
    (no+0)->feed_times = 0;
    (no+0)->hunger_decrease_count = 0;
    (no+0)->interact_count = 0;
    (no+0)->status = 1;
    /*�G����*/
    (no+1)->id = 2;
    strcpy((no+1)->name,"�����");
    strcpy((no+1)->color,"\033[41;37m��\033[47;30m��\033[41;37m��\033[47;30m��\033[0m");
    (no+1)->size = 6.0;
    (no+1)->mood = random_mood();
    (no+1)->hungry = 3;
    (no+1)->life = 3.0;
    (no+1)->feed_times = 0;
    (no+1)->hunger_decrease_count = 0;
    (no+1)->interact_count = 0;
    (no+1)->status = 1;
    /*�T����*/
    (no+2)->id = 3;
    strcpy((no+2)->name,"�U����");
    strcpy((no+2)->color,"\033[40;37m�¦�\033[0m");
    (no+2)->size = 7.0;
    (no+2)->mood = random_mood();
    (no+2)->hungry = 3;
    (no+2)->life = 3.0;
    (no+2)->feed_times = 0;
    (no+2)->hunger_decrease_count = 0;
    (no+2)->interact_count = 0;
    (no+2)->status = 1;
    /*�|����*/
    (no+3)->id = 4;
    strcpy((no+3)->name,"���ͪ��p");
    strcpy((no+3)->color,"\033[41;37m��\033[40;37m��\033[41;37m��\033[40;37m��\033[0m");
    (no+3)->size = 6.0;
    (no+3)->mood = random_mood();
    (no+3)->hungry = 3;
    (no+3)->life = 3.0;
    (no+3)->feed_times = 0;
    (no+3)->hunger_decrease_count = 0;
    (no+3)->interact_count = 0;
    (no+3)->status = 1;
    /*������*/
    (no+4)->id = 5;
    strcpy((no+4)->name,"�����O");
    strcpy((no+4)->color,"\033[41;37m��\033[44;37m��\033[41;37m��\033[44;37m��\033[0m");
    (no+4)->size = 5.0;
    (no+4)->mood = random_mood();
    (no+4)->hungry = 3;
    (no+4)->feed_times = 0;
    (no+4)->life = 3.0;
    (no+4)->hunger_decrease_count = 0;
    (no+4)->interact_count = 0;
    (no+4)->status = 1;
}
/*�C�L�����Ҧ����A(�]�t�Ϲ�)*/
void print_status(struct fish *no){
   int i;
    printf("\n�z�ثe�֦������G \n");
    for(i=0;i<5;i++){
    if((no+i)->status == 1){
        printf("���s��: %d\n", (no+i)->id);
        printf("�W��: %s", (no+i)->name);
         switch (i){
            case 0: printf("     /�¡¡¡¡¡¡¡�\\  /|\n"); break;
            case 1: printf("     \033[40;37m/�¡�\033[40;31m�¡�\033[40;37m�¡�\033[40;31m�¡�\033[40;37m\\  /\033[40;31m|\033[0m\n"); break;
            case 2: printf("    \033[7m /�¡¡¡¡¡¡¡�\\  /|\033[m\n"); break;
            case 3: printf("  \033[47;30m /�¡�\033[47;31m�¡�\033[47;30m�¡�\033[47;31m�¡�\033[47;30m\\  /\033[47;31m|\033[0m\n"); break;
            case 4: printf("     \033[40;34m/�¡�\033[40;31m�¡�\033[40;34m�¡�\033[40;31m�¡�\\  \033[40;31m/\033[40;34m|\033[0m\n"); break;
        }
        printf("�C��: %s", (no+i)->color);
         switch (i){
            case 0: printf("    / ^        \\/ |\n"); break;
            case 1: printf("  \033[40;31m/ \033[40;37m^        \033[40;37m\\\033[40;37m/ \033[40;31m|\n"); break;
            case 2: printf("      \033[7m/ ^        \\/ |\033[m\n"); break;
            case 3: printf("  \033[47;31m/ \033[47;30m^        \\/ \033[47;31m|\033[0m\n"); break;
            case 4: printf("  \033[40;31m/ \033[40;37m^        \033[40;34m\\/ |\033[0m\n"); break;
        }
        printf("\033[33m�髬\033[0m: %.1f", (no+i)->size);
         switch (i){
            case 0: printf("       \\          /\\ |\n"); break;
            case 1: printf("       \033[40;31m\\          \033[40;37m/\\ \033[40;31m|\n"); break;
            case 2: printf("       \033[7m\\          /\\ |\033[m\n"); break;
            case 3: printf("       \033[47;31m\\          \033[47;30m/\\ \033[47;31m|\033[0m\n"); break;
            case 4: printf("       \033[40;31m\\          \033[40;34m/\\ |\033[0m\n"); break;
        }
        printf("\033[35m�߱�\033[0m: %d", (no+i)->mood);
        switch (i){
            case 0: printf("          \\________/  \\|\n"); break;
            case 1: printf("          \033[40;37m\\__\033[40;31m__\033[40;37m__\033[40;31m__\033[40;37m/  \\\033[40;31m|\033[0m\n"); break;
            case 2: printf("         \033[7m \\________/  \\|\033[m\n"); break;
            case 3: printf("         \033[47;30m \\__\033[47;31m__\033[47;30m__\033[47;31m__\033[47;30m/  \\\033[47;31m|\033[0m\n"); break;
            case 4: printf("          \033[40;34m\\__\033[40;31m__\033[40;34m__\033[40;31m__\033[40;31m/  \\\033[40;34m|\033[0m\n"); break;
        }
        printf("\033[32m���j��\033[0m: %d\n", (no+i)->hungry);
        printf("\033[31m�ͩR��\033[0m: %.1f\n", (no+i)->life);
        printf("-----------------------------------\n");
        Sleep(500);
        }
    }
}
/*�C�L�ʧ@���(1.�����B2.���ʡB3.��^�D���)*/
void print_do_list (void){
    printf("\n********************\n");
    printf("*     �ʧ@���     *\n");
    printf("********************\n");
    printf("*                  *\n");
    printf("*    1.����        *\n");
    printf("*    2.����        *\n");
    printf("*    3.��^�D���  *\n");
    printf("*                  *\n");
    printf("********************\n");
    printf("��J�Ʀr�H���檺�ʧ@: ");
}
/*����ʧ@���O(1.�����B2.���ʡB3.��^�D���)*/
void act(int *main_n,int *food_count, struct fish *no){
    int check = 0;
    int feed_n;
    int interact_n;
    int do_n;
    int *s_check, s_c = 0;
    print_do_list();
    scanf("%d",&do_n);
    if(do_n == 1){
        printf("�z�ثe�������}�Ƽ�: %d\n\n",*food_count);
        if(*food_count > 0){
            printf("�п�J�Q��������H�s��: ");
            while(check != 1){
            scanf("%d",&feed_n);
                if(feed_n>5||feed_n<0){
                    check = 0;
                    printf("�Э��s��J�s��(1~5): ");
                }
                else{
                    check = 1;
                    feed_fish(&feed_n, food_count, no, main_n);
                }
            }
        }else{
            printf("�z�ثe�S���}�ƤF!\n");
            printf("(�A�i�H�z�L�M�������H�����o�}��)\n");
            printf("\033[7m\n�N�z�ɦV�ܰʧ@���....\033[m\n");
            *main_n = 1;
            Sleep(500);
        }
    }
    if(do_n == 2){
        check = 0;
        printf("�п�J�Q���ʪ���H�s��: ");
        while(check != 1){
            scanf("%d",&interact_n);
            if(interact_n>5||interact_n<0){
                check = 0;
                printf("�Э��s��J�s��(1~5): ");
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
/*�ʧ@1 ����(�髬/�ͩR�C�����⦸+0.5�B�Y�|�^�X�S�����h���j��-1)*/
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
                printf("%d������\033[32m���j��\033[0m�w�F�̤j��!\n",*feed_n);
                printf("\033[7m�N�z�ɦV�ܰʧ@���....\033[m\n");
                Sleep(500);
                *main_n = 1;
                break;
            }else if((no+(*feed_n-1))->hungry > 0){
                (no+(*feed_n-1))->hungry += 1;
                *food_count-=1;
                printf("%d�����W�[�F 1 �I\033[32m���j��\033[0m !\n",*feed_n);
                printf("%d������\033[32m���j��\033[0m�{�b��: %d !\n\n",*feed_n, (no+(*feed_n-1))->hungry);
                (no+(*feed_n-1))->feed_times += 1;
                fish_size_check(no,feed_n);
                Sleep(500);
                for(i=0;i<5;i++){
                    if((no+i)->hunger_decrease_count != 0 && (no+i)->hunger_decrease_count % 4 == 0){
                        (no+i)->hungry -= 1;
                        printf("(%d������\033[32m���j��\033[0m�U�� 1 �I)\n",i+1);
                        printf("(%d������\033[32m���j��\033[0m�{�b�� : %d)\n\n",i+1,(no+i)->hungry);
                        Sleep(500);
                    }
                }
                life_check1(no);
                printf("\033[7m\n��^�ʧ@���....\033[m\n");
                *main_n = 1;
                Sleep(500);
                break;
            }
    }
}
/*�ʧ@2 ����(�C���ʤ@���߱�+1�A�Y�T�^�X�S���ʱN�Ϥ߱�-1)*/
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
                    printf("%d�������G���b��ı...\n",*interact_n);
                    Sleep(500);
                    printf("�ոլݩM�O�������ʡA�ι��ճ����!\n(�A����J�s���A�ο�J0��^�ʧ@���): ");
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
                        printf("%d�������w�g�O�̶}�ߪ����A !\n",*interact_n);
                        printf("�ոլݩM�O�������ʧa !\n(�A����J�s���A�ο�J0��^�ʧ@���): ");
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
                        printf("\n�A�n��%d�����ݡA���S�X�L��...\n",*interact_n);
                        Sleep(500);
                        printf("%d������\033[35m�߱�\033[0m�W�[�F1�I !\n",*interact_n);
                        printf("%d������\033[35m�߱�\033[0m�{�b��: %d !\n\n",*interact_n, (no+(*interact_n-1))->mood);
                        Sleep(500);
                        for(i=0;i<5;i++){
                            if((no+i)->hunger_decrease_count != 0 && (no+i)->hunger_decrease_count % 4 == 0){
                                if((no+i)->hungry > 0){
                                    (no+i)->hungry -= 1;
                                    if((no+i)->hungry > 0){
                                        printf("(%d������\033[32m���j��\033[0m�U���F 1 �I)\n",i+1);
                                        printf("(%d������\033[32m���j��\033[0m�{�b�� : %d)\n\n",i+1,(no+i)->hungry);
                                        Sleep(700);
                                    }else if ((no+i)->hungry == 0){
                                        printf("(�z��%d�����w�g�־j���F!!)\n",i+1);
                                    }
                                }
                            }
                            if((no+i)->interact_count != 0 && (no+i)->interact_count % 3 == 0){
                                if((no+i)->mood > 1){
                                    (no+i)->mood -= 1;
                                    if((no+i)->mood > 1){
                                        printf("(%d������\033[35m�߱�\033[0m�U���F 1 �I)\n", i+1);
                                        printf("(%d������\033[35m�߱�\033[0m�{�b�� : %d)\n\n",i+1,(no+i)->mood);
                                        Sleep(700);
                                    }else if((no+i)->mood == 1){
                                        printf("(�z��%d����\033[35m�߱�\033[0m�D�`�t�A\033[35m�߱�\033[0m�{�b��1�I!!)\n\n",i+1);
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
                            printf("\n(�z��o�F 1 �ӹ}��!)\n");
                            printf("�z�ثe�������}�Ƽ�: %d \n\n", *food_count);
                        }
                        printf("\033[7m\n��^�ʧ@���....\033[m\n");
                        Sleep(500);
                        break;
                    }
                }
                *s_check = 1;
                *main_n = 1;
        }
}
/*�����髬�W�[�B�ͩR�W�[�p��ΦC�L*/
void fish_size_check (struct fish *no, int *feed_n ){
    if((no+(*feed_n-1))->feed_times % 2 == 0){
        if((no+(*feed_n-1))->size==15){
            printf("�z��%d����\033[33m�髬\033[0m�w�F�̤j��!\n",*feed_n);
            Sleep(500);
        }
        else{
            (no+(*feed_n-1))->size += 0.5;
            printf("%d����\033[33m�髬\033[0m�W�[�F 0.5 cm!\n",*feed_n);
            printf("�ثe%d������\033[33m�髬\033[0m��: %.1f cm\n\n", *feed_n, (no+(*feed_n-1))->size);
            Sleep(500);
        }
        if((no+(*feed_n-1))->life==5){
            printf("�z��%d����\033[31m�ͩR\033[0m�w�F�̤j��!\n",*feed_n);
            Sleep(500);
        }
        else{
            (no+(*feed_n-1))->life += 0.5;
            printf("%d����\033[31m�ͩR��\033[0m�W�[�F 0.5 !\n",*feed_n);
            printf("�ثe%d������\033[31m�ͩR��\033[0m��: %.1f\n\n", *feed_n, (no+(*feed_n-1))->life);
            Sleep(500);
        }
    }

}
/*�����ͩR�ȭp��B���`�P�_*/
void life_check1 (struct fish *no){
    int i;
    for(i=0;i<5;i++){
        if((no+i)->hungry==0){
            (no+i)->life -= 1;
            if((no+i)->life>=0){
                printf("�ѩ�z�Ӥ[�S������%d�����A����\033[31m�ͩR��\033[0m�U���F 1 �I !\n",i+1);
                printf("�ثe%d������\033[31m�ͩR��\033[0m��: %.1f\n", i+1, (no+i)->life);
                printf("(�ɧ�����%d����!!)\n\n",i+1);
                Sleep(500);
            }
        }
        if((no+i)->mood==1){
            (no+i)->life -= 1;
            if((no+i)->life>=0){
                printf("�ѩ�%d������\033[35m�߱�\033[0m���ΡA\033[31m�ͩR��\033[0m�U���F 1 �I !\n",i+1);
                printf("�ثe%d������\033[31m�ͩR��\033[0m��: %.1f\n", i+1,(no+i)->life);
                printf("(�ɧֻP%d�������ʧa!!)\n\n",i+1);
                Sleep(500);
            }
        }
        if((no+i)->life==0){
            printf("�z��%d�����ܤ��������`�F.....\n\n",i+1);
            strcpy((no+i)->name,"�w���`");
            strcpy((no+i)->color,"����");
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
/*�C�������߱��_�l�Ȭ��H���M�w*/
int random_mood(void){
    int r_mood = rand() % 3 + 2;
    return r_mood;
}

