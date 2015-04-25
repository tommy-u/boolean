#include "fann.h"
#include <stdio.h>

//somewhere with fann installed, compile with
//gcc gen_perceptron.c -Wall -lfann -o percep

int main(int argc, char* argv[])
{
  struct fann *ann = fann_create_standard(2,1,1);
  fann_set_activation_function_output(ann, FANN_THRESHOLD);
  fann_type false_encoding, true_encoding;
  int out_0, out_1, i, count = 0, fn_counter[4] = {0, 0, 0, 0};

  //Set false_encoding to 0 for binary, -1 for bipolar (with true_encoding set to 1)
  false_encoding= 0;
  true_encoding = 1;
  //Extra credit: 
  //By a symmetry argument (vertical angle thm), f0 and f3 must have the same probability.
  //That in mind and with false_encoding set to 0, the value of true_encoding can be used to select 
  //the probability for a given function region.
  //As true_encoding -> positive infinity, p(f1) = p(f2) -> .25 
  //As true_encoding -> 0 p(f1) = p(f2) -> 0
  //Of course p(f0) = p(f3) will change in response 

  for(i=0;i<1000000;i++)
    {
      fann_randomize_weights(ann, -1, 1);

      out_0 = *fann_run(ann, &false_encoding);
      out_1 = *fann_run(ann, &true_encoding);

      count ++;
      if( out_0 == 0)
	if( out_1 ==0)
	  fn_counter[0]++;
	else
	  fn_counter[2]++;
      else
	if( out_1 ==0)
	  fn_counter[1]++;
	else
	  fn_counter[3]++;
    }
  
  for(i=0;i<4;i++)
    {
      printf("chance f%d: %f \n",i, fn_counter[i] / (float) count );
    }
  
  fann_destroy(ann);
  return 0;
}
