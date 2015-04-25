#include "fann.h"
#include <stdio.h>
//braindead program. sorry, I'm tired
int main(int argc, char* argv[])
{
  const unsigned int num_layers = 2;
  const unsigned int num_input = 1;
  const unsigned int num_output = 1;
  struct fann *ann = fann_create_standard(num_layers, num_input, num_output);
  fann_set_activation_function_output(ann, FANN_THRESHOLD);
  fann_type *calc_out;
  fann_type input[2];
  
  
  int out_0, out_1, i;
  int count = 0;
  int fn_counter[4] = {0, 0, 0, 0};
  for(i=0;i<1000000;i++)
    {
      fann_randomize_weights(ann, -1, 1 );
      input[0] = -1;
      calc_out = fann_run(ann, input);  
      out_0 = calc_out[0];
      //      printf("percep(%f) -> %f\n", input[0], calc_out[0]);
      
      input[0] = 1;
      calc_out = fann_run(ann, input);
      out_1 = calc_out[0];
      //      printf("percep(%f) -> %f\n", input[0], calc_out[0]);
  

      count ++;
      if(out_0==0)
	if(out_1==0)
	  fn_counter[0]++;
	else
	  fn_counter[2]++;
      else
	if(out_1==0)
	  fn_counter[1]++;
	else
	  fn_counter[3]++;
      
    }
  
  printf("chance f0: %f \n", fn_counter[0] / (float) count );
  printf("chance f1: %f \n", fn_counter[1] / (float) count );
  printf("chance f2: %f \n", fn_counter[2] / (float) count );
  printf("chance f3: %f \n", fn_counter[3] / (float) count );

  fann_destroy(ann);
  return 0;
}
