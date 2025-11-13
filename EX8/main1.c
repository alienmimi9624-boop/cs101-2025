#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char line_buffer[100];
    char timestamp_line[100]; 
    
    int n1, n2, n3;
    char s1[5], s2[5], s3[5]; 

    printf("請輸入中獎號碼三個: ");
    scanf("%d %d %d", &n1, &n2, &n3);

    sprintf(s1, " %02d", n1);
    sprintf(s2, " %02d", n2);
    sprintf(s3, " %02d", n3);

    printf("輸入中獎號碼為: %02d %02d %02d\n", n1, n2, n3);
    printf("以下為中獎彩卷:\n");

    fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        printf("錯誤: 無法開啟 lotto.txt 檔案。\n");
        return 1;
    }

    strcpy(timestamp_line, ""); 

    while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL) {
        
        if (strstr(line_buffer, "lotto649") != NULL || strstr(line_buffer, "csie@CGU") != NULL) {
            continue;
        }

        if (line_buffer[0] == '[') {
            
            if (strstr(line_buffer, s1) != NULL &&
                strstr(line_buffer, s2) != NULL &&
                strstr(line_buffer, s3) != NULL) 
            {
                if (timestamp_line[0] != '\0') {
                    printf("%s", timestamp_line); 
                }
                printf("%s", line_buffer);
            }
        } 
        else if (line_buffer[0] == '=') {
            strcpy(timestamp_line, line_buffer);
        }
    }

    fclose(fp);

    return 0;
}
