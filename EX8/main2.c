#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define COUNTER_FILE "counter.bin"
#define MAX_LOTTO_NUM 7
#define MAX_LOTTO_NUMSET 5

void init_file(void);
int get_counter(void);
void set_counter(int counter);
void do_lotto_main(int counter);
void print_lottofile(int num_set, int counter, char lotto_file[]);
void print_lotto_row(FILE* tmpfp, int n);
int num_in_numset(int num, int numset[], int len);

void init_file() {
    int write_array[1] = {0};
    FILE* fp = fopen(COUNTER_FILE, "r");

    if (fp == NULL) {
        FILE* tmpfp = fopen(COUNTER_FILE, "wb+"); 
        if (tmpfp != NULL) {
            fwrite(write_array, sizeof(int), 1, tmpfp); 
            fclose(tmpfp);
        }
    } else {
        fclose(fp);
    }
}

int get_counter() {
    int read_array[1];
    FILE* tmpfp = fopen(COUNTER_FILE, "rb");
    if (tmpfp == NULL) { 
        return 0; 
    }
    fread(read_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
    return read_array[0];
}

int num_in_numset(int num, int numset[], int len) {
    int ret = 0;
    for (int i = 0; i < len; i++) {
        if (num == numset[i]) {
            ret = 1; 
            break;
        }
    }
    return ret;
}

void print_lotto_row(FILE* tmpfp, int n) {
    int numset[MAX_LOTTO_NUM];

    fprintf(tmpfp, "[%d]: ", n); 

    for (int i = 0; i < MAX_LOTTO_NUM - 1; ) {
        int num = (rand() % 69) + 1;
        if (num_in_numset(num, numset, i)) {
            continue;
        } else {
            numset[i] = num;
            i++;
        }
    }

    for (int i = 0; i < 1; ) {
        int num = (rand() % 10) + 1;
        if (num_in_numset(num, numset, MAX_LOTTO_NUM - 1)) {
            continue;
        } else {
            numset[MAX_LOTTO_NUM - 1] = num;
            i++;
        }
    }

    for (int i = 0; i < MAX_LOTTO_NUM - 1; ++i) {
        for (int j = 0; j < i; ++j) {
            if (numset[j] > numset[i]) {
                int temp = numset[j];
                numset[j] = numset[i];
                numset[i] = temp;
            }
        }
    }

    for (int i = 0; i < MAX_LOTTO_NUM; i++) {
        fprintf(tmpfp, "%02d ", numset[i]); 
    }
    fprintf(tmpfp, "\n");
}

void print_lottofile(int num_set, int counter, char lotto_file[]) {
    time_t curtime;
    time(&curtime);
    srand(time(0)); 

    FILE* tmpfp = fopen(lotto_file, "w+"); 
    if (tmpfp == NULL) return; 

    fprintf(tmpfp, "lotto649 ==========\n");
    fprintf(tmpfp, "========+ No.%05d +========\n", counter); 
    char *time_str = ctime(&curtime);
    time_str[strlen(time_str) - 1] = '\0'; 
    fprintf(tmpfp, "=%s=\n", time_str);

    for (int i = 0; i < MAX_LOTTO_NUMSET; i++) {
        if (i < num_set) {
            print_lotto_row(tmpfp, i + 1);
        } else {
            fprintf(tmpfp, "[%d]: ----\n", i + 1);
        }
    }
    fprintf(tmpfp, "csie@CGU =========\n");
    fclose(tmpfp);
}

void do_lotto_main(int counter) {
    char lotto_file[32];
    int num_set = 0;

    snprintf(lotto_file, 32, "lotto[%05d].txt", counter); 

    printf("歡迎光臨長庚樂透採購買機台\n");
    printf("請問您要買幾組樂透彩:");
    scanf("%d", &num_set);

    if (num_set > MAX_LOTTO_NUMSET) {
        num_set = MAX_LOTTO_NUMSET;
        printf("輸入組數超過上限，自動設定為 %d 組。\n", MAX_LOTTO_NUMSET);
    }

    print_lottofile(num_set, counter, lotto_file);
    printf("已為您購買的 %d 組樂透組合輸出至 %s\n", num_set, lotto_file);
}

void set_counter(int counter) {
    int write_array[1];
    write_array[0] = counter;
    FILE* tmpfp = fopen(COUNTER_FILE, "wb"); 
    if (tmpfp == NULL) return; 
    
    fwrite(write_array, sizeof(int), 1, tmpfp);
    fclose(tmpfp);
}

int main() {
    int counter;

    init_file();                    
    counter = get_counter();        
    printf("目前計數: %d\n", counter);

    do_lotto_main(++counter);       
    
    set_counter(counter);           

    return 0;
}
