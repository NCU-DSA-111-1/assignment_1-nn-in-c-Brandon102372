#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "genann.h"
#include "DataManagement.h"
#define SPLIT_PERCENTAGE 0.25
#define HIDDEN_LAYER_NUMBER 2
#define OUTPUT_DIMENTION 1
#define RESULT_NUMBER 5

int dataset_size=0;
int input_dim=0;
int output_dim=0;
int BITS_NUMBER=0;
int DATA_POOL_NUMBER=0;
int epoch=0;
DataSet *data_pool=NULL;
DataSet *test=NULL;
DataSet *train=NULL;
char *input_string = NULL;
double *input_bits=NULL;

int main(int argc, char *argv[])
{
	/*Input parameters*/
    printf("Input the number of bits:");
    scanf("%d",&BITS_NUMBER);
	printf("Input training epoch: ");
	scanf("%d",&epoch);
	
	DATA_POOL_NUMBER=pow(2,BITS_NUMBER);
	int test_len = (int)DATA_POOL_NUMBER*SPLIT_PERCENTAGE;
	int train_len = DATA_POOL_NUMBER-(int)DATA_POOL_NUMBER*SPLIT_PERCENTAGE;
    /* This will make the neural network initialize differently each run. */
    srand(time(NULL));
    
    
	/* Generate input and expected out data for the XOR function in random order. */	
	data_pool=generate_bits_and_label(BITS_NUMBER,1,DATA_POOL_NUMBER);
	/* Split generated data into test data and train data, 20% of data is test data*/
	train_test_spilt(DATA_POOL_NUMBER, data_pool, &train, train_len, &test, test_len, SPLIT_PERCENTAGE);
	
    int i,j; //index_counter

	/*Contruct a neural network*/
    genann *ann = genann_init(BITS_NUMBER, HIDDEN_LAYER_NUMBER, BITS_NUMBER, OUTPUT_DIMENTION);
	
	/*Create a csv file to record learning process*/
	FILE *fpt;
	fpt = fopen("learning_accuracy.csv", "w+");
	fprintf(fpt,"epoch,train_accuracy,test_accuracy,total_accuracy,%d\n",BITS_NUMBER);
	
    /* Train labeled data points many times. */
    printf("epoch     train_accuracy     test_accuracy     total_accuracy\n");
    for (i = 0; i < epoch; i++) {
    	double ans=0;
    	/*Train neural network with train datas and labels*/
    	for(j = 0; j<train_len; j++){
    		genann_train(ann, train[j].value, train[j].label , 3);
		}
		
		/*Count the number of correct output in training set and testing set*/
		double test_accuracy=0, train_accuracy=0, total_accuracy=0;
		for(j = 0;j<train_len;j++){
			ans=round(*genann_run(ann, train[j].value));
			if(ans==train[j].label[0]) train_accuracy+=1;
		}
		for(j = 0; j<test_len; j++){
			ans=round(*genann_run(ann, test[j].value));
			if(ans==test[j].label[0]) test_accuracy+=1;
		}

		/*Compute accuracy*/
		total_accuracy=(test_accuracy+train_accuracy)/DATA_POOL_NUMBER;
		train_accuracy=train_accuracy/train_len;
		test_accuracy=test_accuracy/test_len;
		
		/*Write data to csv file*/
		fprintf(fpt,"%d,%lf,%lf,%lf\n",i,train_accuracy,test_accuracy,total_accuracy);
		
		printf("\r%d/%d(%.1f%%)",i,epoch,(double)i/epoch*100);
		if(i%((int)(epoch/RESULT_NUMBER))==0){
			printf("\r%5d     %14f     %13f     %14f\n",i,train_accuracy,test_accuracy,total_accuracy);
		}
    }
	fclose(fpt);
	
    /* Run the network and see what it predicts. */
	input_string=(char*)malloc(BITS_NUMBER*sizeof(char));
	input_bits=(double*)malloc(BITS_NUMBER*sizeof(double));
	while(1){
		printf("\nEnter bit stream to test: ");
		scanf("%s",input_string);
		if(input_string[0]=='2') break;
		for(i=0;i<BITS_NUMBER;i++){
			input_bits[i]=(int)input_string[i]-'0';
		}
		printf("result: %f\n",round(*genann_run(ann, input_bits)));
	}
	
	/*clear memory*/
	free(input_string);
	free(input_bits);
    genann_free(ann);
    freeDataSet(data_pool,DATA_POOL_NUMBER);
    freeDataSet(train,train_len);
    freeDataSet(test,test_len);
	system("pause");
    return 0;
}
