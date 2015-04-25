#include <stdio.h>
#include "floatfann.h"

int main()
{
  fann_type *calc_out;
  fann_type input[2];
  const unsigned int num_input = 2;
  const unsigned int num_output = 1;
  const unsigned int num_layers = 2;
  struct fann *ann = fann_create_standard(num_layers, num_input, num_output);
  fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
  fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

  int i;
  for(i=0; i<4; i++)
    {
      input[0] = 0;
      input[1] = 1;
      calc_out = fann_run(ann, input);
      
      printf("xor test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);
    }
  fann_destroy(ann);
  return 0;
}
