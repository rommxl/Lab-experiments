#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//TO add
// Soft coded bias
// automatic backprop and updation using connected network fucntion
// Create array to store all neurons and such in one accessible memory location to automate whole process

void print_neurons(float* arr,int num,char* c){
    printf("%s\n",c);
    for(int i = 0; i < num ; i++){
        printf("%f ",arr[i]);
    }
    printf("\n\n");
}

void print_weights(float** arr,int row, int col){
    printf("Weights are :\n");
    for(int i = 0; i < row ; i++){
        for(int j = 0; j < col; j++){
            printf("%f ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_bias(float* bias,int neuron_cnt,char* c){
    printf("%s\n",c);
    for(int i = 0; i < neuron_cnt; i++){
        printf("%f ",bias[i]);
    }
    printf("\n\n");
}

float* allocate_neuron(float* arr,int size,char* desc){
    printf("Allocating %d %s\n",size,desc);
    arr = (float*)malloc(size * sizeof(float));
    return arr;
}

float** fill_weights(float** weights,int i,int j,char* desc){
    weights = (float**)malloc(i * sizeof(float*));
    for(int x = 0; x<j ; x++){
        weights[x] = (float*)malloc(j * sizeof(float));
    }
    printf("Weights from %s\n",desc);
    for(int a = 0; a < i; a++){
        for(int b = 0; b < j; b++){
            printf("Enter weight for neuron %d to neuron %d: ",a+1,b+1);
            scanf("%f",&weights[a][b]);
        }
    }
    printf("\n");
    return weights;
}

float activation_function(float x){
    float ans = (float)(1/(1+exp(-x)));
    return ans;
}

float diff_activation_function(float x){
    float ans = activation_function(x)*(1-activation_function(x));
    return ans;
}

void feedforward(float* layer1,float* layer2,float* layer2_in,int layer1_size,int layer2_size, float* bias, float** weights){
    printf("Feeding forward\n");
    for(int i = 0 ; i < layer2_size; i++){
        float zin = bias[i];
        for(int j = 0; j < layer1_size; j++){
            zin += layer1[j]*weights[j][i];
        }
        layer2[i] = activation_function(zin);
        layer2_in[i] = zin;
        printf("Finished one neuron to neuron\n\n");
    }
}

void backpropagate_final(float*y, float* yin,int neuron_count,float* error_sigma,float target){
    printf("Back-propagating from final to hidden layer\n");
    for(int i = 0; i < neuron_count; i ++){
        error_sigma[i] = (target - y[i]) * diff_activation_function(yin[i]);
    }
    printf("\n\n");
}

void backpropagate_hidden(float* hidden_layer_error_sigma,float* output_layer_error_sigma,float* hidden_layer_input,float** weight,int hidden_neurons,int output_neurons){
    printf("Back-propagating from hidden to it's input layer\n");
    for(int i = 0 ;i < output_neurons;i++){
        for(int j = 0; j < hidden_neurons; j++){                        // As error sigma was not initilaized, this will not work for nets with  
            hidden_layer_error_sigma[j] = output_layer_error_sigma[i] * weight[j][i];      //more than one output neuron
        }
    }

    for(int i = 0; i<hidden_neurons; i++){
        hidden_layer_error_sigma[i] = hidden_layer_error_sigma[i] * diff_activation_function(hidden_layer_input[i]);
    }
    printf("\n\n");
}

void update_weights(float** weight,float* input,int row,int col,float* error_sigma,float learning_rate,float* bias){
    printf("Update weight\n");
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            weight[j][i] = weight[j][i] + (learning_rate * error_sigma[i] * input[j]);
        }
        bias[i] = bias[i] + (error_sigma[i] * learning_rate);
    }
    printf("\n\n");
}

void main()
{
    float* x;       //input
    float** v;      //input to hidden weights
    float* z;       //hidden
    float* zin;       //hidden
    float** w;      //hidden to output 
    float* y;       //output 
    float* yin;       //output
    float* output_error;    //backpropagating error from output neuron(s)
    float* hidden_error;    //backpropagating error from hidden neuron(s)
    float bias_hidden[] = {0.3,0.5};  //biases
    float bias_output[] = {-0.2};
    int n,p,m;      // neuron numbers
    float learning_rate,target;     //learning rate and target
    printf("Enter number of input neurons: ");
    scanf("%d",&n);
    printf("Enter number of hidden layer neurons: ");
    scanf("%d",&p);
    printf("Enter number of output neurons: ");
    scanf("%d",&m);
    printf("Enter learning rate: ");
    scanf("%f",&learning_rate);
    printf("Enter target: ");
    scanf("%f",&target);
    printf("\n");
    x = allocate_neuron(x,n,"input layer neurons");
    zin = allocate_neuron(zin,p,"hidden layer neurons inputs");
    z = allocate_neuron(z,p,"hidden layer neurons");
    yin = allocate_neuron(yin,m,"output layer neurons inputs");
    y = allocate_neuron(y,m,"output layer neurons");

    hidden_error = allocate_neuron(hidden_error,p,"error propagation for hidden layer");
    output_error = allocate_neuron(output_error,m,"error propagation for output layer");

    for(int i = 0; i < n; i++){
        printf("Enter input neuron %d: ",i+1);
        scanf("%f",&x[i]);
    }

    print_neurons(x,n,"Input neurons");

    v = fill_weights(v,n,p,"input layer to hidden layer");
    w = fill_weights(w,p,m,"hidden layer to output layer");

    feedforward(x,z,zin,n,p,bias_hidden,v);
    print_neurons(z,p,"Hidden neurons");

    feedforward(z,y,yin,p,m,bias_output,w);
    print_neurons(y,m,"Output neurons");


    backpropagate_final(y,yin,m,output_error,target);
    backpropagate_hidden(hidden_error,output_error,zin,v,p,m);
    update_weights(w,z,p,m,output_error,learning_rate,bias_output);
    update_weights(v,x,n,p,hidden_error,learning_rate,bias_hidden);

    printf("V ");
    print_weights(v,n,p);
    print_bias(bias_hidden,p,"Hidden layer bias");
    printf("W: ");
    print_weights(w,p,m);    
    print_bias(bias_output,m,"Output layer bias");
}

//2 2 1 0.25 1 0 1 0.6 -0.3 -0.1 0.4 0.4 0.1