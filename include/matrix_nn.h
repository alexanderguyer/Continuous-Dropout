#ifndef MATRIX_NN_H
#define MATRIX_NN_H

#include <cstddef>
#include "activation_function.h"
#include "loss_function.h"
#include "probability_distribution.h"

class matrix_nn{
	private:
		int num_layers;
		int *num_nodes;
		double ***weights;
		double ***node_inputs;//as backprop requires forward prop, smart caching trades space for better runtime. Vectorized matrices, as there will be a matrix for every input set.
		double ***node_activations;//^
		double ***input_gradients;//Every weight update requires an update of the gradients, but not all of them, so we should cache them and only update those necessary.
		double ***activation_gradients;//^
		double ***rprop_updates;
		char ***rprop_signs;
		bool first_rprop;
		activation_function **activation_functions;
		double **inputs;
		double **desired_activations;
		int num_sets;
		loss_function *m_loss_function;
		double training_rate;
		double ***dropout_coefficients;
		probability_distribution *dropout_dist;

		double **dot(double **, int, int, double **, int, int);
		double **first_inverse_dot(double **, int, int, double **, int, int);
		double **second_inverse_dot(double **, int, int, double **, int, int);
		double **cross(double **, int, int, double **, int, int);
		double **element_wise_activation_function(double **, int, int, activation_function *);
		double **calc_loss_matrix(double **);
		void delete_forward_products();
		void feed_forward();
		void feed_forward_without_dropout();
		void delete_backward_products();
		void update_inputs(double **);
		void delete_inputs();
		void update_desired_activations(double **);
		void delete_desired_activations();
		void update_rprop_updates(double ***);
		void train();
		void train_rprop();
		void delete_rprop_updates();
		void gen_dropout_coefficients();
		void delete_dropout_coefficients();
		void update_num_sets(int);
		void update_sets(double **inputs, double **desired_activations, int num_sets);
	public:
		matrix_nn(int num_layers, int *num_nodes, activation_function **activation_functions, loss_function *m_loss_function, double training_rate, probability_distribution *p);
		~matrix_nn();
		void feed_backward();
		void calc_outputs(double **, int);
		double get_output(int, int);
		void train(double **, double **, int, int);
		void train_rprop(double **, double **, int, double ***, int);
};

#endif
