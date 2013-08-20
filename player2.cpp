#include<stdio.h>

bool checked[5000];

struct element_P{
	double player[6][23];
	double dealer[6][23];
	double player_win[6];
	double dealer_win[6];
	element_P(){
		for(int i=0;i<6;i++){
			for(int j=0;j<23;j++){
				player[i][j] = 0.0;
				dealer[i][j] = 0.0;
			}
		}
		for(int i=0;i<6;i++){
			player_win[i] = 0.0;
			dealer_win[i] = 0.0;
		}
	}
};

void divide_count(element_P ** main_matrix , int ** count){
	for(int i=0;i<50;++i){
		for(int j=0; j<12 ; ++j){
			for(int p=0;p<6;++p){
				for(int q=0;q<23;++q){
					main_matrix[i][j].player[p][q] /= (double)count[i][j];
					main_matrix[i][j].dealer[p][q] /= (double)count[i][j];
				}
			}
		}
	}
}

double sum_array(double * arr, int length){
	double sum = 0.0;
	for(int i=0; i<length; ++i){
		sum += arr[i];
	}
	return sum;
}

void write_Probabilities(double* player , double* dealer, double* player_win, double* dealer_win){
	double dealer_arr_sum = sum_array(dealer,23);
	for(int i=0; i<23; ++i){
		dealer[i] /= dealer_arr_sum;
	}
	
	double pwin=0.0 , dwin=0.0;
	for(int i=4; i<=16; ++i){
		pwin += (player[i] * dealer[22]);
		dwin += (player[i] * (dealer[17] + dealer[18] + dealer[19] + dealer[20] + dealer[21]) );
	}
	for(int i=17; i<=21; ++i){
		double dealer_sum1 = 0.0 , dealer_sum2 = 0.0;
		for(int j=17; j < i; ++j){
			dealer_sum1 += dealer[j];
		}
		for(int j=21; j > i; --j){
			dealer_sum2 += dealer[j];
		}
		pwin += (player[i] * (dealer_sum1 + dealer[22]));
		dwin += (player[i] * dealer_sum2);
	}
	dwin += player[22];
	//dwin = 1.0 - pwin;
	*player_win = pwin;
	*dealer_win = dwin;
}


bool hash_check(int i, int j, int k){
	if( checked[ ((100*j) + (i+k)) ] )
		return true;
	else
		return false;
}

bool player_sum_in(int t){
	if(t >= 4 && t <= 20)
		return true;
	else if(t >= 23 && t <= 31)
		return true;
	else if(t == 42)
		return true;
	else
		return false;
}




int sum_left(int * left){
	int sum = 0;
	for(int i=0; i<12; i++){
		sum += left[i];
	}
	return sum;
}

int optimal_score(int t, int player_ace){
	int output = t;
	while(player_ace >= 0){
		if(t <= 21){
			output = t;
			break;
		}
		else{
			output = t;
		}
		t -= 10;
		player_ace--;
	}
	return output;
}

int cardSum(int * player_card){
	int dummy[2] = {player_card[0] , player_card[1]};
	
	if(player_card[0] == 11)
		dummy[0] = 21;
	if(player_card[1] == 11)
		dummy[1] = 21;
	
	return (dummy[0] + dummy[1]);
}

int dealerProbability(double * arr, int * left, int t , double prob){
	if(t<17){
		int i=2;
		do{
			if(left[i]){
				if(t+i>21)
					arr[22] += (prob * (double)left[i] / (double)sum_left(left));
				else if(t+i >= 17)
					arr[t+i] += (prob * (double)left[i] / (double)sum_left(left));
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

int hit(double * arr, double * dealer_arr, int dealer_card, int * left, int t , double prob , int* player_ace, int hits){
	//printf("hit(t = %d, hits = %d);\n",t,hits);
	if(hits == 0){
		t = optimal_score(t, *player_ace);
		if(t>21){
			arr[22] += prob;
		}
		else
			arr[t] += prob;
		return dealerProbability(dealer_arr, left, dealer_card , 1.0);
	}
	else{
		for(int j=2;j<12;j++){
			if(left[j]){
				--left[j];
				if(j == 11){
					++(*player_ace);
					int temp_hits = hits - 1;
					hit(arr, dealer_arr, dealer_card, left, t+j , (prob * (double)(left[j]+1) / (double)(sum_left(left)+1) ) , player_ace, temp_hits);
					--(*player_ace);
				}
				else{
					int temp_hits = hits - 1;
					hit(arr, dealer_arr, dealer_card, left, t+j , (prob * (double)(left[j]+1) / (double)(sum_left(left)+1) ) , player_ace, temp_hits);
				}
				++left[j];
			}
		}
	}
	return 1;
}

int stand(double * arr, int t , int* player_ace){
	t = optimal_score(t, *player_ace);
	if(t>21){
		arr[22] += 1;
	}
	else
		arr[t] += 1;
	return 1;
}



int playerProbability(element_P ** arr, int** count, int * left,  int* player_ace){
	int player_card[2] , dealer_card;
	for(int i=2;i<12;i++){
		int counter1 = left[i];
		while(counter1){
			--left[i];
			if(i == 11)
				++(*player_ace);
			player_card[0] = i;
			for(int j=2;j<12;j++){
				int counter2 = left[j];
				while(counter2){
					--left[j];
					dealer_card = j; 
					for(int k=2;k<12;k++){
						int counter3 = left[k];
						while(counter3){
							--left[k];
							if(k == 11)
								++(*player_ace);
							player_card[1] = k;
							int card_sum = cardSum(player_card);
							int actual_card_sum = player_card[0] + player_card[1];
							if(checked[hash_check(i,j,k)])
								;
							else{
								for(int cases = 0; cases<3; ++cases){
									//if(cases > 0){
									hit(arr[card_sum][j].player[cases], arr[card_sum][j].dealer[cases], dealer_card, left, actual_card_sum , 1.0 , player_ace, cases);
									//dealerProbability( arr[card_sum][j].dealer[cases], left, dealer_card , 1.0);
								}
								++count[card_sum][j];
								checked[ ((100*j) + (i+k)) ] = true;
							}
							if(k == 11)
								--(*player_ace);
							++left[k];
							--counter3;
						}
					}
					++left[j];
					--counter2;
				}
			}
			if(i == 11)
				--(*player_ace);
			++left[i];
			--counter1;
		}
	}
	return 0;
}


int main(){
	for(int i=0; i<5000; ++i){
		checked[i] = false;
	}
	element_P ** main_matrix  = new element_P * [50];
	for(int i=0;i<50;++i){
		*(main_matrix + i) = new element_P[12];
	}
	
	int** count = new int*[50];
	for(int i=0;i<50;++i){
		*(count + i) = new int[12];
		//memset( *(count + i) , 0 , 50*sizeof(int) );
	}
	
	for(int i=0;i<50;++i){
		for(int j=0;j<12;++j){
			count[i][j] = 0;
		}
	}
	
	
	

	int * player_ace = new int;
	*player_ace = 0;
	
	
	//double player_arr[10][22] = {0};
	//double arr[7]={0};
	int left[12] = {0,0,4,4,4,4,4,4,4,4,16,4};
	for(int p=2; p<12; ++p)
		left[p] *= 1;
	
	/*
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
	*/
	
	playerProbability(main_matrix,  count,  left,  player_ace);
	
	divide_count(main_matrix , count)	;
	
	for(int i=0;i<50;++i){
		for(int j=0;j<12;++j){
			//element_P node = main_matrix[i][j];
			for(int k=0; k<6; ++k)
				write_Probabilities(main_matrix[i][j].player[k] , main_matrix[i][j].dealer[k], (main_matrix[i][j].player_win+k), (main_matrix[i][j].dealer_win+k) );
		}
	}
	
	for(int i=0;i<50;++i){
		if(player_sum_in(i)){
			for(int j=2;j<12;++j){
				printf("Sum:%d , Dealer Card:%d\n",i,j);
				for(int k=0; k<3; ++k){
					if(k == 0)
						printf("Stand:\tPlayer win = %lf\tDealer win = %lf\n", main_matrix[i][j].player_win[k] , main_matrix[i][j].dealer_win[k] );
					else
						printf("Hit %d:\tPlayer win = %lf\tDealer win = %lf\n",k , main_matrix[i][j].player_win[k] , main_matrix[i][j].dealer_win[k] );
				}
				printf("\n");
			}
		}
		printf("\n");
	}
	printf("\n");
	
	//--------------------------------
	/*
	for(int i=0;i<50;++i){
		for(int j=0;j<12;++j){
			element_P node = main_matrix[i][j];
			printf("Sum:%d , Dealer Card:%d\n",i,j);
			for(int p=0;p<6;++p){
				for(int q=0;q<23;++q){
					if(p == 0){
						printf("Stand:\tTotal = %d\tDealer P = %lf\tPlayer P = %lf\n", q , node.dealer[p][q] , node.player[p][q]);
					}
					else
						printf("Hit %d:\tTotal = %d\tDealer P = %lf\tPlayer P = %lf\n",p , q , node.dealer[p][q] , node.player[p][q]);
				}
				printf("\n");
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
	
	*/
	/*
	printf("Stand:\n");
	for(int i=0;i<50;++i){
		if(player_sum_in(i)){
			for(int j=2;j<12;++j){
				//printf("Sum:%d , Dealer Card:%d\n",i,j);
				for(int k=0; k<6; ++k){
					if(k == 0)
						printf("%d\t%d\t%lf\n", i,j,main_matrix[i][j].player_win[k] );
				}
			}
		}
	}
	printf("\n\n");
	
	
	printf("Hit 1:\n");
	for(int i=0;i<50;++i){
		if(player_sum_in(i)){
			for(int j=2;j<12;++j){
				//printf("Sum:%d , Dealer Card:%d\n",i,j);
				for(int k=0; k<6; ++k){
					if(k == 1)
						printf("%d\t%d\t%lf\n", i,j,main_matrix[i][j].player_win[k] );
				}
			}
		}
	}
	printf("\n\n");
	
	printf("Hit 2:\n");
	for(int i=0;i<50;++i){
		if(player_sum_in(i)){
			for(int j=2;j<12;++j){
				//printf("Sum:%d , Dealer Card:%d\n",i,j);
				for(int k=0; k<6; ++k){
					if(k == 2)
						printf("%d\t%d\t%lf\n", i,j,main_matrix[i][j].player_win[k] );
				}
			}
		}
	}
	printf("\n\n");
	
	*/
	
	
	for(int i=0;i<50;++i){
		delete[] *(main_matrix + i);
	}
	delete[] main_matrix;
	
	for(int i=0;i<50;++i){
		delete[] *(count + i);
	}
	delete[] count;
	delete player_ace;
	
	
	//------------------------------------------------------------------------
	/*
	//element_P * A = new element_P;
	int zero = 112;
	int* ace = &zero;
	int t = 21;
	printf("%d\n",optimal_score(t, * ace));
//A.player[]
	
	int cards[2] = {11 , 10};
	printf("cardSum() = %d\n",cardSum(cards));
	*/
	return 0;
}
