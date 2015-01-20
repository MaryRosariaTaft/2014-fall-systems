#include <stdio.h>
#include <stdlib.h>

int multiples();
int sum_sq();

int main(){

  printf("\n");

  printf("Problems from https://projecteuler.net/problems \n\n");

  printf("(1) Multiples of 3 and 5 \n");
  printf("Solution: %d \n\n",multiples());

  printf("(6) Sum Square Difference \n");
  printf("Solution: %d \n\n",sum_sq());

  return 0;

}

//find the sum of all the multiples of 3 or 5 below 1000
int multiples(){
  int i;
  int sum=0;
  for(i=0;i<1000;i++){
    if(i%3==0||i%5==0){
      sum+=i;
    }
  }
  return sum;
}

//find the difference between the sum of the squares of the first 100 natural numbers and the square of the sum of the first 100 natural numbers
int sum_sq(){
  int i;

  int sum=0;
  for(i=0;i<=100;i++){
    sum+=i*i;
  }

  int sq=0;
  for(i=0;i<=100;i++){
    sq+=i;
  }
  sq=sq*sq;

  return sq-sum;

}
