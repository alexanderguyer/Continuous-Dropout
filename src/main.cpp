#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "mnist_iterator.h"
#include "matrix_nn.h"
#include "softmax.h"
#include "relu.h"
#include "cross_entropy.h"
#include "mse.h"
#include "gaussianesque_distribution.h"

using std::ostringstream;
using std::cout;
using std::ofstream;
using std::setprecision;
using std::fixed;
using std::flush;

void iterate(double alpha, double beta, int upper_bound, double training_rate, int epochs = 10) {
	int num_layers = 3;
	int num_nodes[] = {28*28, 150, 10};
	relu r;
	softmax s;
	activation_function *functions[] = {&r, &s};
	cross_entropy m;
	// Create probability distribution and pass it into the matrix constructor
	gaussianesque g(alpha, beta);
	gaussianesque_distribution dropout_dist(&g, upper_bound);
	matrix_nn nn(num_layers, num_nodes, functions, &m, training_rate, &dropout_dist);
	mnist_iterator itr;

	int num_sets = 60000;
	int read_size = 1000;
	int batch_size = 50;
	int num_reads = (num_sets / read_size) * read_size < num_sets ? (num_sets / read_size) + 1 : (num_sets / read_size);

	for (int epoch = 0; epoch < epochs; epoch++) {
		if (epoch > 0) {
			cout << ", " << flush;
		}
		cout << epoch << ": " << flush;
		for(int i = 0; i < num_reads; i++){
			int remaining = num_sets - i * read_size;
			int specific_read_size = read_size < remaining ? read_size : remaining;

			double **batch = itr.get_inputs(i * read_size, specific_read_size, mnist_iterator::TYPE_TRAIN);
			double **desired_outputs = itr.get_desired_outputs(i * read_size, specific_read_size, mnist_iterator::TYPE_TRAIN);

			int num_batches = (specific_read_size / batch_size) * batch_size < specific_read_size ? (specific_read_size / batch_size) + 1 : (specific_read_size / batch_size);
			for(int j = 0; j < num_batches; j++){
				remaining = specific_read_size - j * batch_size;
				double specific_batch_size = batch_size < remaining ? batch_size : remaining;
				nn.train(batch + j * batch_size, desired_outputs + j * batch_size, specific_batch_size, 1);
			}
			for(int j = 0; j < specific_read_size; j++){
				delete [] batch[j];
				delete [] desired_outputs[j];
			}
			delete [] batch;
			delete [] desired_outputs;
		}

		
	}

	num_sets = 10000;
	read_size = 1000;
	batch_size = 50;
	num_reads = (num_sets / read_size) * read_size < num_sets ? (num_sets / read_size) + 1 : (num_sets / read_size);

	int num_correct = 0;

	for(int i = 0; i < num_reads; i++){
		int remaining = num_sets - i * read_size;
		int specific_read_size = read_size < remaining ? read_size : remaining;
		double **batch = itr.get_inputs(i * read_size, specific_read_size, mnist_iterator::TYPE_TEST);
		double **desired_outputs = itr.get_desired_outputs(i * read_size, specific_read_size, mnist_iterator::TYPE_TEST);

		int num_batches = (specific_read_size / batch_size) * batch_size < specific_read_size ? (specific_read_size / batch_size) + 1 : (specific_read_size / batch_size);
		for(int j = 0; j < num_batches; j++){
			remaining = specific_read_size - j * batch_size;
			double specific_batch_size = batch_size < remaining ? batch_size : remaining;
			nn.calc_outputs(batch + j * batch_size, specific_batch_size);
			for(int k = 0; k < specific_batch_size; k++){
				int highest_predicted_index = 0, highest_actual_index = 0;
				double highest_predicted = nn.get_output(k, 0), highest_actual = (desired_outputs + j * batch_size)[k][0];
				for(int l = 1; l < 10; l++){
					double output = nn.get_output(k, l);
					if(output > highest_predicted){
						highest_predicted_index = l;
						highest_predicted = output;
					}
					double desired_output = (desired_outputs + j * batch_size)[k][l];
					if(desired_output > highest_actual){
						highest_actual_index = l;
						highest_actual = desired_output;
					}
				}

				if(highest_predicted_index == highest_actual_index) {
					num_correct++;
				}
			}
		}

		for(int j = 0; j < specific_read_size; j++){
			delete [] batch[j];
			delete [] desired_outputs[j];
		}
		delete [] batch;
		delete [] desired_outputs;
	}

	ostringstream out_file_name;
	out_file_name << fixed;
	out_file_name << setprecision(1);
	out_file_name << "data/result-a" << alpha << "-b" << beta << "-ub" << upper_bound << "-tr";
	out_file_name << setprecision(5);
	out_file_name << training_rate << ".txt";

	ofstream out_file(out_file_name.str());
	double percent_correct = (double) num_correct / 10000.0;
	out_file << std::setprecision(5);
	out_file << percent_correct << "\n";

	cout << setprecision(5) << percent_correct << " => " << out_file_name.str() << "\n";
}

int main(){
	for (int alpha_itr = 0; alpha_itr < 6; alpha_itr++) {
		for (int beta_itr = 0; beta_itr < 6; beta_itr++) {
			for (int upper_bound_itr = 0; upper_bound_itr < 3; upper_bound_itr++) {
				for (int training_rate_itr = 0; training_rate_itr < 3; training_rate_itr++) {
					double alpha = alpha_itr + 2;
					double beta = beta_itr + 1;
					int upper_bound = ceil((upper_bound_itr + 1) * beta);
					double training_rate = 0.00025 * pow(10, training_rate_itr);
					iterate(alpha, beta, upper_bound, training_rate);
				}
			}
		}
	}

	return 0;
}
