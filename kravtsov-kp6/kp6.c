#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 100
#define MAX_LINE_LEN 1000 
#define MAX_GRADES 4 

struct Person{
    char surname[20];
    char initials[20];
    char gender;
    int group;
    int av;
};

int main() {
    struct Person array[N];
    int maxAv = -1;
    int count = 0;
    
    char filename[] = "students.csv"; 
    FILE* file = fopen(filename, "r"); 
    if (file == NULL) { 
        printf("Ошибка открытия файла\n");
        return 1;
    }
    
    char line[MAX_LINE_LEN]; 

    while (fgets(line, MAX_LINE_LEN, file)) { 
        char* token = strtok(line, ","); 
        char* initials = strtok(NULL, ","); 
        char* gender = strtok(NULL, ",");
        char* studentGroupStr = strtok(NULL, ",");
        int studentGroup = atoi(studentGroupStr); 
        
        float sum = 0.0; 

        for (int i = 0; i < MAX_GRADES; i++) { 
            char* gradeStr = strtok(NULL, ",");
            if (gradeStr != NULL) {
                int grade = atoi(gradeStr);
                sum += grade;
            }
            else 
                break;
        }

        int av = round(sum / MAX_GRADES);
        maxAv = (av > maxAv) ? av : maxAv;   

        if (strcmp(gender, "Ж") == 0) { 
            // printf("%d ", studentGroup);
            array[count].av = av;
            array[count].group = studentGroup;
            ++count;
        }
    }

    int groups[1000];
    for(int i = 0; i < 1000; ++i) {
        groups[i] = 0;
    }

    for(int i = 0; i < count; ++i) {
        if (array[i].av == maxAv) {
            groups[array[i].group] += 1;
        }
    }

    int max = 0;
    int answ = 0;

    for(int i = 0; i < 1000; ++i) {
        if (max < groups[i]) {
            max = groups[i];
            answ = i;
        }
    }

    printf("%d\n", answ);
    
    fclose(file); 
    
    return 0;
}

