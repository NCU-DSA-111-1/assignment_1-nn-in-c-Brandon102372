#ifndef DATA_H
#define DATA_H
#include <stdio.h>

//A structure that store the pointer of value and label of a data
//for example: value = 1111, label = 0
typedef struct data{
    double *value;
    double *label;
}DataSet;
         
/*Split training and testing data*/
void train_test_spilt(int num,DataSet *data_pool, DataSet **train, int train_num, DataSet **test, int test_num, float split);
/*Randomly generate N none reapeat datas*/  
DataSet *generate_bits_and_label(int bit_num,int label_num,int data_set_num);
/*Random compare function for sorting*/
int rand_comparison(const void *a, const void *b);
/*Shuffle the datas*/
void shuffle(void *base, size_t nmemb, size_t size);
/*Free memory of DataSet array*/
void freeDataSet(DataSet* dat,int len);

#endif
