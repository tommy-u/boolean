#include "fann.h"
#include <stdio.h>
//somewhere with fann installed, compile with
//gcc gen_perceptron.c -Wall -lfann -o percep

int main(int argc, char* argv[])
{
  struct fann *ann = fann_create_standard(2, 3,1);
  fann_set_activation_function_output(ann, FANN_THRESHOLD);
  int out[8], i, j, count = 0, fn_counter[256];
  //zero the counts
  for(i=0;i<256;i++)
    fn_counter[i] = 0;
  //Switch binary or bipolar representation
  //fann_type arr[8][3] = { {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1}, {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1} };
  fann_type arr[8][3] = { {-1,-1,-1}, {-1,-1,1}, {-1,1,-1}, {-1,1,1}, {1,-1,-1}, {1,-1,1}, {1,1,-1}, {1,1,1} };
  int num_reps =10000000; 
  for(i=0;i<num_reps;i++)
    {
      //point to random direction in weight space
      fann_randomize_weights(ann, -10, 10);
      //hold threshold constant
      //      ann->weights[3] = -1;
      //collect each bit of output vector for this solution region
      for(j=0;j<8;j++)
	out[j] = *fann_run(ann, arr[j]);
      //  for(j=0;j<8;j++)
      //	printf("out[%d]=%d\n",j,out[j]);
      
      //Determine which function we're looking at
      int fn_number = 0;
      for(j=0;j<8;j++)
	if(out[j]==1)
	  fn_number+= powf(2,j);
      //for prob
            fn_counter[fn_number]++;
      //for exist
      //      fn_counter[fn_number]=1;

      //printf("fn_number = %d\n",fn_number);
     
    }

  
  for(i=0;i<256;i++)
    //for prob
    printf("chance f%d: %f \n",i, fn_counter[i] / (float) num_reps );
  //printf("exist f%d: %d \n",i, fn_counter[i] );
  fann_destroy(ann);
  return 0;
}
