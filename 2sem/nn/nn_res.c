#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define EXP 2.71828182845904523536028747
#define LEARNING_RATE 0.01
#define ENER 0.000

double sigmoid(double x){
	return 1. / (1. + pow(EXP, -1. * x));
	// return 1. / (1. + exp(-x));
}

double sigmoid_dx(double x){
	return x * (1 - x);
}

struct neron_net{
	unsigned long long size; //количество коэффициентов
	unsigned long long size_ansvers;
	unsigned long long lenght; //количество слоев
	unsigned long long * struc;
	char base_name[50];
	struct neron_data * data;
};

struct neron_data{
	double * weights;
	double * ansvers;
	double * errors;
	double * dweights;
};

struct neron_net * neron_net_init(unsigned long long lenght, unsigned long long * struc, char * base_name){
	struct neron_net * nn = (struct neron_net *)malloc(sizeof(struct neron_net));
	strcpy(nn->base_name, base_name);
	nn->struc = struc;
	nn->lenght = lenght;
	nn->size = 0;
	nn->size_ansvers = 0;
	for (int i = 0; i < lenght - 1; ++i){
		nn->size += struc[i] * struc[i+1];
	}
	for (int i = 0; i < lenght; ++i){
		nn->size_ansvers += struc[i];
	}
	nn->data = (struct neron_data *)malloc(sizeof(struct neron_data));
	nn->data->weights = (double *)calloc(nn->size, sizeof(double));
	nn->data->dweights = (double *)calloc(nn->size, sizeof(double));
	nn->data->ansvers = (double *)calloc(nn->size_ansvers, sizeof(double));
	nn->data->errors = (double *)calloc(nn->size_ansvers, sizeof(double));
	FILE * f = fopen(base_name, "r");
	for (int i = 0; i < nn->size; ++i){
		fscanf(f, "%lf", &(nn->data->weights[i]));
	}
	fclose(f);
	return nn;
}

void neron_start(struct neron_net * nn, double * input_data){
	for (int i = 0; i < nn->struc[0]; ++i){
		nn->data->ansvers[i] = input_data[i];
	}
	unsigned long long was_weights = 0;
	unsigned long long was_ansvers = 0;
	unsigned long long was_ansvers2 = nn->struc[0];
	double sum = 0;
	for (int i = 1; i < nn->lenght; ++i){
		for (int j = 0; j < nn->struc[i]; ++j){
			sum = 0;
			for (int k = 0; k < nn->struc[i-1]; ++k){
				sum += nn->data->weights[k + (j * nn->struc[i-1]) + was_weights] * nn->data->ansvers[k + was_ansvers];
				// printf("sum = %lf weights i = %d ansvers otkyda i = %d\n", sum, k + (j * nn->struc[i-1]) + was_weights, k + was_ansvers);
			}
			nn->data->ansvers[j + was_ansvers2] = sigmoid(sum);
			// printf("ansvers kuda i = %d\n", j + was_ansvers2);
		}
		was_weights += nn->struc[i - 1] * nn->struc[i];
		was_ansvers += nn->struc[i - 1];
		was_ansvers2 += nn->struc[i]; 
	}
}

void neron_learn(struct neron_net * nn, double * data_for_learn, double * data_result){
	neron_start(nn, data_for_learn);
	double learning_rate = LEARNING_RATE;
	double weights_delta = 0;
	unsigned long long was_weights = 0;
	unsigned long long was_ansvers = 0;
	unsigned long long was_errors = 0;
	unsigned long long was_errors2 = 0;
	unsigned long long was_errors3 = 0;
	double error_sum = 0;
	for (int i = nn->lenght - 1; i > 0; --i){
		for (int j = 0; j < nn->struc[i] ; ++j){
			if(i == nn->lenght - 1){
				nn->data->errors[nn->size_ansvers - 1 - j] = data_result[nn->struc[i] - 1 - j] - nn->data->ansvers[nn->size_ansvers - 1 - j];
				nn->data->errors[nn->size_ansvers - 1 - j] *= sigmoid_dx(nn->data->ansvers[nn->size_ansvers - 1 - j]);
				// printf("----for i = %d error = %lf\n", nn->size_ansvers - 1 - j, nn->data->errors[nn->size_ansvers - 1 - j]);
			} else{
				nn->data->errors[nn->size_ansvers - 1 - j - was_errors] = 0;
				for (int k = 0; k < nn->struc[i+1]; ++k){
					nn->data->errors[nn->size_ansvers - 1 - j - was_errors] += nn->data->weights[nn->size - 1 - j - (k * nn->struc[i]) - was_weights] * nn->data->errors[nn->size_ansvers - 1 - k - was_errors3];
					// printf("wi = %d wi = %lf eri = %d\n", nn->size - 1 - j - (k * nn->struc[i]) - was_weights, nn->data->weights[nn->size - 1 - j - (k * nn->struc[i]) - was_weights], nn->size_ansvers - 1 - k - was_errors2);
					// printf("++err = %lf m1 = %lf m2 = %lf wer1 = %d wer2 = %d wer3 = %d\n", nn->data->errors[nn->size_ansvers - 1 - j - was_errors],nn->data->weights[nn->size - 1 - j - (k * nn->struc[i]) - was_weights],nn->data->errors[nn->size_ansvers - 1 - k - was_errors2], was_errors, was_errors2, was_errors3);
				}
				nn->data->errors[nn->size_ansvers - 1 - j - was_errors] *= sigmoid_dx(nn->data->ansvers[nn->size_ansvers - 1 - j - was_errors]);
				// printf("for i = %d error = %lf\n", nn->size_ansvers - 1 - j - was_errors, nn->data->errors[nn->size_ansvers - 1 - j - was_errors]);
			}
		}

		if(i < nn->lenght - 1){
			was_weights += nn->struc[i + 1] * nn->struc[i];	
		}
		was_errors += nn->struc[i];
		for (int q = 0; q < nn->struc[i] * nn->struc[i-1]; ++q){
			nn->data->dweights[nn->size - 1 - q - was_weights] = (nn->data->dweights[nn->size - 1 - q - was_weights] * ENER) + nn->data->ansvers[nn->size_ansvers - 1 - was_errors - (q % nn->struc[i-1])] * nn->data->errors[nn->size_ansvers - 1 - was_errors2 - (q / nn->struc[i - 1])] * learning_rate;
			nn->data->weights[nn->size - 1 - q - was_weights] += nn->data->dweights[nn->size - 1 - q - was_weights];
			// printf("wi = %d  ansi = %d  eri = %d\n", nn->size - 1 - q - was_weights, nn->size_ansvers - 1 - was_errors - (q % nn->struc[i-1]), nn->size_ansvers - 1 - was_errors + nn->struc[i] - (q / nn->struc[i - 1]));	
		}
		
		if(i != nn->lenght - 1){
			was_errors2 += nn->struc[i - 1];	
		}
		if(i != nn->lenght - 1){
			was_errors3 += nn->struc[i + 1];	
		}
		

	}
}

void init_file(char * str, int size, double value){
	FILE * t = fopen(str, "r");
	if(t != NULL){
		fclose(t);
		return;
	}
	printf("\nfile maked\n");
	srand(time(NULL));
	double n = 0;
	FILE * f = fopen(str, "w");
	for (int i = 0; i < size; ++i){
		n = (rand() % 1000) / 1000.;
		fprintf(f, "%lf ", n);
	}
	fclose(f);
}

void save_file(char * str, struct neron_net * nn){
	FILE * f = fopen(str, "w");
	for (int i = 0; i < nn->size; ++i){
		fprintf(f, "%lf ", nn->data->weights[i]);
	}
	fclose(f);
}

double * getdata(char * str){
	FILE * f = fopen(str, "r");
	if(f == NULL){
		printf("ERROR READ\n");
		exit(-1);
	}
	double * mas = malloc(30*25*sizeof(double));
	for (int i = 0; i < 30*25; ++i){
		fscanf(f,"%lf",&(mas[i]));
		// printf("%lf ",mas[i]);
	}
	fclose(f);
	// printf("\n=============================\n");
	return mas;
}

int get_ansver(struct neron_net * nn, char * str){
	double * data = getdata(str);
	neron_start(nn, data);
	double max = 0;
	int maxi = 0;
	for (int i = 0; i < 9; ++i){
		if(nn->data->ansvers[nn->size_ansvers - 9 + i] > max){
			max = nn->data->ansvers[nn->size_ansvers - 9 + i];
			maxi = i + 1;
		}
	}
	return maxi;
}

int main(int argc, char ** argv){
	init_file(argv[1], 10000, 0.39);
	unsigned long long struc_net[3] = {25*30, 25*30, 9};
	struct neron_net * nn = neron_net_init(3, struc_net, argv[1]);
	
	printf("\n%d%d%d%d%d%d\n", get_ansver(nn, argv[2]), get_ansver(nn, argv[3]), get_ansver(nn, argv[4]), get_ansver(nn, argv[5]), get_ansver(nn, argv[6]), get_ansver(nn, argv[7]));

	// printf("\nansvers :\n");
	// for (int i = 0; i < nn->size_ansvers; ++i){
	// 	printf("%lf ", nn->data->ansvers[i]);
	// }
	// printf("\nweights :\n");
	// for (int i = 0; i < nn->size; ++i){
	// 	printf("%lf ", nn->data->weights[i]);
	// }
	// printf("\nerrors :\n");
	// for (int i = 0; i < nn->size_ansvers; ++i){
	// 	printf("%lf ", nn->data->errors[i]);
	// }
	return 0;
}