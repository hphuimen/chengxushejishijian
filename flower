#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>
#define iris1 "Iris-setosa"
#define iris2 "Iris-versicolor"
#define iris3 "Iris-virginica"
#define random_times 1000
#define train_num 120
#define test_num 30
#define k 9
struct Iris {
    double sepal_length, sepal_width, petal_length, petal_width;
    int variety_id;
};
struct Iris iris[150];      
int index[k];
int wrong_judge = 0;
double distance[train_num];

int input();    
void print_iris_data(); // 打印iris[]中的数据已验证input()random_order()是否正常工作
void judge();   // 判断并评估
double cal_distance(int i1, int i2); // 计算距离
void print_accuracy();
void random_order();    // 打乱测试集与训练集的顺序
void select();       //选出k个最小距离
int main() {
    if (input() == 0) return 0;
    random_order();
    print_iris_data();
    judge();
    print_accuracy();
    return 0;
}

int input() {
    char fname[256];
    char name[20];      // name of iris
    printf("input the file name \n");
    scanf("%s", fname);
    FILE* fp = fopen(fname, "r");      // 二进制是吧
    if (fp == NULL) {
        printf("open file error\n");
        return 0;
    }
    for (int i = 0; i < train_num + test_num; i++) {
        fscanf(fp, "%lf,%lf,%lf,%lf,%s", &iris[i].sepal_length, &iris[i].sepal_width, \
            & iris[i].petal_length, &iris[i].petal_width, name);
        if (strcmp(name, iris1) == 0) iris[i].variety_id = 1;
        else if (strcmp(name, iris2) == 0) iris[i].variety_id = 2;
        else if (strcmp(name, iris3) == 0) iris[i].variety_id = 3;
    }
    fclose(fp);
    return 1;
}

void random_order() {
    int random1, random2;
    struct Iris temp;
    srand((unsigned)time(NULL));
    srand((unsigned)time(NULL));
    for (int i = 0; i < random_times; ++i) {
        random1 = rand() % (train_num + test_num);
        random2 = rand() % (train_num + test_num);
        temp = iris[random1];
        iris[random1] = iris[random2];
        iris[random2] = temp;
    }
}

void print_iris_data() {
    for (int i = 0; i < train_num + test_num; ++i) {
        printf("%lf %lf %lf %lf %d\n", iris[i].sepal_length, iris[i].sepal_width, iris[i].petal_length,
            iris[i].petal_width, iris[i].variety_id);
    }
}

void judge() {
    for (int i = train_num; i < train_num + test_num; ++i) {
        for (int j = 0;j < train_num;j++) {
            distance[j] = cal_distance(i,j);
        }
        select();
        int count[4] = { 0, 0, 0, 0 };
        for (int j = 0;j < k;j++)
        {
            if (iris[index[j]].variety_id == 1) count[1]++;
            else if (iris[index[j]].variety_id == 2) count[2]++;
            else if (iris[index[j]].variety_id == 3) count[3]++;
        }
        int x=1;
        if (count[1] > count[2] && count[1] > count[3]) x = 1;
        else if (count[2] > count[1] && count[2] > count[3]) x = 2;
        else if (count[3] > count[1] && count[3] > count[2]) x = 3;
        
        if (x != iris[i].variety_id) wrong_judge++;
    }
}

double cal_distance(int i1, int i2) {
    double x1 = pow((iris[i1].sepal_length - iris[i2].sepal_length), 2.0);
    double x2 = pow((iris[i1].sepal_width - iris[i2].sepal_width), 2.0);
    double x3 = pow((iris[i1].petal_length - iris[i2].petal_length), 2.0);
    double x4 = pow((iris[i1].petal_width - iris[i2].petal_width), 2.0);
    double distance = sqrt(x1 + x2 + x3 + x4);
    return distance;
}

void select()
{
    for (int i = 0;i < k;i++)
    {
        int t = i; 
        for (int j = i + 1;j < train_num;j++)
        {
            if (distance[j] < distance[t]) t = j;
        }
        index[i] = t;
        distance[t] = 10000;
    }
}

void print_accuracy() {
    double accuracy = 100.0 - 100.0 * wrong_judge / test_num;
    printf("\naccuracy : %lf%%\n", accuracy);
    printf("\naccuracy : %lf%% \nwrong judge time(s) : %d \n", accuracy, wrong_judge);
}
