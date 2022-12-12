#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double expression(double x);
void method_chord(double x_prev, double x_curr, double e, int N, char flag_results_each_iteration);
void method_halving(double x_prev, double x_curr, double e, int N, char flag_results_each_iteration);
void result_iteration(int n_count, double x);
void exceeding_the_specified_iterations();

int main() {
    int choice_solution, n;
    double a, b, e = 0.000001;
    char flag_results_each_iteration;


    do{
        printf("Methods: "
               "\n 1 - Method hord"
               "\n 2 - Method of halving");
        printf("\nChoose a method of solution(1-2): "); scanf("%d", &choice_solution);
    }while(choice_solution != 1 && choice_solution != 2);

    do{
        printf("\nEnter interval: ");
        printf("\n a = "); scanf("%lf", &a);
        printf("\n b = "); scanf("%lf", &b);
    }while((expression(b) * expression(a)) > 0);
    printf("\nEnter number of iterations: "); scanf("%d", &n);

    do{
        printf("\nDisplay results on each iteration?(y/n): "); scanf(" %c", &flag_results_each_iteration);
    }while(flag_results_each_iteration != 'y' && flag_results_each_iteration != 'n');

    clock_t tic = clock();

    switch(choice_solution) {
        case 1:{method_chord(a, b, e, n, flag_results_each_iteration); break;}
        case 2:{method_halving(a, b, e, n, flag_results_each_iteration); break;}
    }
    clock_t toc = clock();

    printf("\nThe program was spent on: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}


double expression(double x){
    double y;
    y = pow(x,3)+(3*(pow(x,2)))-3;
    return y;
}

void result_iteration(int n, double x){
    printf ("\nNumber of iterations: %u"
            "\n Current X: %.3lf"
            "\n Current f(x)= %g", n, x, expression(x));

}

void exceeding_the_specified_iterations(){
    printf("\nThe specified number of iterations has been exceeded"
           "\n 1 - Continue with the same number of iterations"
           "\n 2 - Continue until the roots are found equation"
           "\n 3 - Exit the program and get intermediate calculation result"
           "\n Choose one of the options: ");
}

void method_chord(double a, double b, double e, int N, char flag_results_each_iteration){
    double c;
    int n = 1, choose, flag_counter = 0;
    int counter_max = N;
    do{
        if(flag_results_each_iteration == 'y'){result_iteration(n, c);}
        if(n>counter_max && flag_counter==0  ){
            result_iteration(n, c);
            do{
                exceeding_the_specified_iterations();
                scanf("%d", &choose);
            }while(choose!=1 && choose!=2 && choose!=3);
            if(choose == 1){counter_max = counter_max*2;}
            else if(choose == 2){flag_counter = 1;}
            else if(choose == 3){break;}
        }
        c=(expression(b)*a-expression(a)*b)/(expression(b)-expression(a));
        if((expression(a)*expression(c)) > 0) a=c;
        else b=c;
        n++;
    }while (fabs(expression(b)-expression(a))>e);
    printf("\nX = %.3lf f(X)= %g", c, expression(c));
}

void method_halving(double x_prev, double x_curr, double e, int N, char flag_results_each_iteration){
    double x;
    int n = 1, choose, flag_counter = 0;
    int counter_max = N;
    do{
        if(flag_results_each_iteration == 'y'){result_iteration(n, x);}
        if(n>counter_max && flag_counter==0  ){
            result_iteration(n, x);
            do{
                exceeding_the_specified_iterations();
                scanf("%d", &choose);
            }while(choose!=1 && choose!=2 && choose!=3);
            if(choose == 1){counter_max = counter_max*2;}
            else if(choose == 2){flag_counter = 1;}
            else if(choose == 3){break;}
        }
        x=(x_prev+x_curr)/2;
        if((expression(x_prev)*expression(x))>0) {x_prev=x;}
        else {x_curr=x;}
        n++;
    }while((x_curr-x_prev)/2 > e);
    printf("\nX = %.3lf f(X)= %g", x, expression(x));
}
