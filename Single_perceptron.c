/*Project: "Single perceptron backpropogation algorithm"
  Created by: Dušan Radivojeviæ, 12.2019.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*Lr is Learning rate.Usual range is from 0.1 (fast) to 0.00001 (slow) learnig rate.
  If output is throwing wrong value this coeficient should be decrease.*/
#define Lr 1

/*Cost is a diference between average error of all learning examples and expected results.
 Less number causes beter precision but more iteration.*/
#define Cost 0.000001

/*sigmoid function compresses all values in 0 to 1 range.
  It is also known as activation function.*/
double sigmoid(double x){
	return 1/(1+exp(-x));
}

/*Out function is meant for checking obtained coefficients at the end of learning.
  It requires input values X1 and X2, coeficients b,w1,w2 and return output result
  according to the function of the neural cell.*/
int Out(int X1,int X2,double b,double w1,double w2){
	double res=X1*w1+X2*w2+b;
	if(sigmoid(res)>=0.5)return 1;
	else return 0;
}

/*main function is meant for larning process, recording the learning flow,
  measuring learning time, and for checking obtained values.*/
int main(int argc, char *argv[]) {
	printf("I am a learning neural cell.\n\nMy look is:\n\n");
	printf("\tX1\tb\n");
	printf("\t  \\w1\n");
	printf("\t  \t( )=a\n");
	printf("\t  /w2\n");
	printf("\tX2\n");	
	printf("\nMy formula: a=sigmoid(X1*w1+X2*w2+b)\n");
	printf("Please wait... ");
	double b,w1,w2,a,a1,C,Average;                   
	double ab=0,aw1=0,aw2=0;
	int red=1,pr=1,r,X1,X2;
	
	/*Array vect[] is learning output set of values.Default values are
	for OR logic gate, for AND would be {0,0,0,1}.
	It is also posible to use NOR,NAND,NOTX1, and NOTX2*/
	int vect[4]={0,1,1,1};
	
	/*Initial values of coeficients are randomly selected*/
	srand(time(0));
	b=(double)((rand()%6000)-3000)/1000.0;
	w1=(double)((rand()%6000)-3000)/1000.0;
	w2=(double)((rand()%6000)-3000)/1000.0;

	/*Values from all iteration (Learning process) will be storage to
	txt file, making it possible to analyze later.*/
	FILE* file_ptr = fopen("Iteration values.txt", "w");
	fprintf (file_ptr, "No\tb\t\tw1\t\tw2\t\taverage error\n");

	/*Before first iteration clock is started.*/
	clock_t start = clock();
	
	/*Iteration loop for finding optimal coefficients with backpropagation metod*/
	while(pr==1){
	r=0;
	Average=0;
	for(X1=0;X1<2;X1++){
		for(X2=0;X2<2;X2++){
				a=X1*w1+X2*w2+b;
				a1=sigmoid(a);
				C=a1-vect[r];
				Average+=C;
				ab+=Lr*C;
				aw1+=Lr*C*X1*a1;
				aw2+=Lr*C*X2*a1;
				r++;
	    }
	}
	b-=ab/4;
	w1-=aw1/4;
	w2-=aw2/4;
	Average/=4;
	ab=0;
	aw1=0;
	aw2=0;
	if(fabs(Average)<Cost){
		pr=0;
		}
		
	/*For each passage through the loop record values to txt file*/	
	fprintf (file_ptr, "%d\t%.8lf\t%.8lf\t%.8lf\t%.8lf\n",red,b,w1,w2,Average);
	red++;
	}

	/*Stop the clock and calculate spent time*/
	clock_t stop = clock();
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	
	/*Print the values to terminal and close the txt file*/
	printf("Thank you!\n");
	printf("\nLearning is complete for: %.3lfsec\nNumber of iterations: %d",elapsed/1000.0,red-1);
	printf("\nCalculated coefficients are:");
	printf("\nb=%.3lf\tw1=%.3lf\tw2=%.3lf",b,w1,w2);
	printf("\nDetaild informations about iterations are in \"Iteration values.txt\"\n");
	printf("\nCheck if output is the same like vect[%d,%d,%d,%d]",vect[0],vect[1],vect[2],vect[3]);
	printf("\n0|0 => %d",Out(0,0,b,w1,w2));
	printf("\n0|1 => %d",Out(0,1,b,w1,w2));
	printf("\n1|0 => %d",Out(1,0,b,w1,w2));
	printf("\n1|1 => %d\n\n",Out(1,1,b,w1,w2));
	fprintf (file_ptr, "b\t\tw1\t\tw2\t\tminimum\t\ttime[ms]\n");
	fprintf (file_ptr, "%lf\t%lf\t%lf\t%.6lf\t%.1f\n",b,w1,w2,Average,elapsed);
	fclose(file_ptr);
	system("pause");
	return 0;
}
