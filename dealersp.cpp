#include<stdio.h>

int sum_left(int * left){
	int sum =0;
	for(int i=0; i<12; i++){
		sum += left[i];
	}
	return sum;
}


int dealerProbability(double * arr, int * left, int t , double prob){
	//int output = 0;
	//printf("func(%d);\n",t);
	if(t<17){
		int i=2;
		do{
			if(left[i]){
				if(t+i>21)
					arr[5] += (prob * (double)left[i] / (double)sum_left(left));
				else if(t+i >= 17)
					arr[t+i-17] += (prob * (double)left[i] / (double)sum_left(left));
				else{
					--left[i];
					dealerProbability(arr, left, t+i , (prob * (double)(left[i]+1) / (double)(sum_left(left)+1) ) );
					++left[i];
				}
			}
			++i;
		}
		while(i < 12); 
	}
	return 0;
}

int main(){

	double arr[7]={0};
	int left[12] = {0,0,4,4,4,4,4,4,4,4,16,4};
	for(int p=2; p<12; ++p)
		left[p] *= 1;
	for(int in=2; in<12; ++in){
		for(int du=0;du<7;++du)
			arr[du]=0;
		printf("Dealers card value : %d\n",in);
		left[in]--; //left[8]--;
		dealerProbability(arr, left, in , 1.00);
		left[in]++;
		double sum_of_prob = 0;
		for(int i=0;i<6;i++){
			sum_of_prob += arr[i];
			int j = i+17;
			if(j == 22)
				printf("Busting probability : %f\n",arr[i]);
			else
				printf("%d probability : %f\n",j,arr[i]);
			
		}
		printf("Sum of Probabilities = %f\n\n",sum_of_prob);
		
	}
		double k = (double)left[10] / (double)sum_left(left);
		printf("k = %f",k);
	return 0;
}
