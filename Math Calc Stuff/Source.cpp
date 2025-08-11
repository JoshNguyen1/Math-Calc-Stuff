#include <iostream>
#include <random>
using namespace std;


double randomNum() { //random number generator between 0 and 1.
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	return dis(gen);
}


int main() { //Gacha summon simulator
	/*
	Need 70 shards in order to summon the unit.

	5 shards with probability 2.649, guaranteed in 65 summons (pity resets once summoned)

	2 shards with probability 7.285%, guaranteed in 16 summons (pity resets once summoned)

	1 shard with probability 23.841%, guaranteed in 6 summons (pity resets once summoned)

	.23841

	.31126

	.33775
	*/

	double shard_5_probability = 0.02649;
	double shard_2_probability = 0.07285;
	double shard_1_probability = 0.23841;

	double zero_shard = 1 - (shard_5_probability + shard_2_probability + shard_1_probability);
	double one_shard = zero_shard + shard_1_probability;
	double two_shard = one_shard + shard_2_probability;
	double five_shard = two_shard + shard_5_probability;

	int one_pity = 0;
	int two_pity = 0;
	int five_pity = 0;



	
	double rand_temp = 0;

	int num_trials = 1000;
	int total_summons_after_all_trials = 0;
	int number_below_52_summons = 0;

	for (int i = 0; i < num_trials; i++) {

		int summon_counter = 0;
		int shards = 0;

		while (shards < 70) {
			rand_temp = randomNum();
			summon_counter++;

			one_pity++;
			two_pity++;
			five_pity++;

			if ((rand_temp > two_shard && rand_temp < five_shard) || five_pity >= 65) { //pity limit of 65 reached?
				shards += 5;
				five_pity = 0;
			}
			else if ((rand_temp > one_shard && rand_temp < two_shard) || two_pity >= 16) {
				shards += 2;
				two_pity = 0;
			}
			else if ((rand_temp > zero_shard && rand_temp < one_shard) || one_pity >= 6) {
				shards += 1;
				one_pity = 0;
			}

		}
		//cout << summon_counter << "\n";
		total_summons_after_all_trials += summon_counter;
		if (summon_counter <= 52) {
			number_below_52_summons++;
		}
	}
	
	cout << "Average summons to get unit after " << num_trials << " trials: " 
		<< static_cast<double>(total_summons_after_all_trials) / num_trials;

	cout << "\n Chance of getting in less than 53 summons: " << static_cast<double>(number_below_52_summons) / num_trials;
	return 0;
}
