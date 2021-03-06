#include "fann.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
  const unsigned int num_layers = 2;
  const unsigned int num_input = 1;
  //  const unsigned int num_neurons_hidden = 1;
  const unsigned int num_output = 1;
  const float desired_error = (const float) 0.001;
  const unsigned int max_epochs = 50000;
  const unsigned int epochs_between_reports = 1000;

  //  struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);
  struct fann *ann = fann_create_standard(num_layers, num_input, num_output);
  fann_randomize_weights(ann, 1, -1);
  //  fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
  fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

  fann_train_on_file(ann, argv[1], max_epochs, epochs_between_reports, desired_error);

  fann_destroy(ann);

  return 0;
}
