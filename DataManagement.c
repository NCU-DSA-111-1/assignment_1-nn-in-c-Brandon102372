#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "DataManagement.h"
#define min(x,y) (((x)<(y))?(x):(y))
#define BINARY_BASE 2


void train_test_spilt(int num,DataSet *data_pool, DataSet **train, int train_num, DataSet **test, int test_num, float split){
    int i=0;//counter
	*train =  &data_pool[0];
	*test = &data_pool[train_num];
}

DataSet *generate_bits_and_label(int bit_num,int label_num,int n_data){
	
	/*Generate all the possible condition of N bits*/
    int data_table_len=(int)pow(2,bit_num);
	int i=0,j=0;//counter
	int *data_table=(int*)malloc(data_table_len*sizeof(int));
	int data_set_num=min(n_data,data_table_len);
	
	DataSet *bits=(DataSet*)malloc(data_set_num*sizeof(DataSet));
	for (i=0;i<data_table_len;i++){
		data_table[i]=i;
	}
	/*Shuffle sequential datas*/
	shuffle(data_table,data_table_len,sizeof(int));
	
	/*Convert decimal number to binary and calculate thier exact XOR result*/
    for (i=0 ; i<data_set_num;i++){
        bits[i].value=(double*)malloc(bit_num * sizeof(double));
        memset(bits[i].value,0,bit_num *sizeof(double));
        
        int dec=data_table[i];
        int counter_1s=0;

        for(j=0;j<bit_num;j++){
            bits[i].value[j] = dec % BINARY_BASE;
            dec /= BINARY_BASE;

            counter_1s+=bits[i].value[j];
        }
        
        bits[i].label=(double*)malloc(label_num * sizeof(double));
        bits[i].label[0]=(double)(counter_1s%BINARY_BASE);
    }
    
    free(data_table);
    return bits;
}

int rand_comparison(const void *a, const void *b)
{
    (void)a; (void)b;
    return rand()% 2 ? +1 : -1;
}

void shuffle(void *base, size_t nmemb, size_t size)
{
    qsort(base, nmemb, size, rand_comparison);
}

void freeDataSet(DataSet* dat,int len){
	int i; //index
	for (i=0;i<len;i++){
		free(dat[i].value);
		free(dat[i].label);
	}
	free(dat);
}

