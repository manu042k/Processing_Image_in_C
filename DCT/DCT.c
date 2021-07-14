/*
 * Author           :    Manoj M
 * Filename         :    DCT
 * Functions        :    main, print
 * Global Variables :    NONE
 * Functionality    :    takes a N*N matrix as input and applies a 2D discrete cosine transform and performs Quantization
 * Macros           :    size , pi ,quality

 * DCT(i,j)= 1/square_root(2*N) * C(i)*C(j) summation x --> N -1 ( summation y --> N-1( pixel(x,y)*cos((2x+1)i*pi/2N)*cos((2y+1)j*pi/2N)))
            where c(x) = 1/square_root(2) for x=0
                       = 1 for x>1
 * Quantization table(i,j) = 1+ ((1+i+j)*quality factor)
 * Quantization = DCT / table

*/

//start of program
#include <stdio.h>
#include <math.h>

//Defining macros
#define size 8
#define pi 3.141592654
#define quality 2

//function to return c(x)
float coff(int d)
{
    if (d == 0)
        return (1/sqrt(2));
    else
        return 1;
}

//main function
void main()
{

    //input pixels
    int input_pixels[size][size] = { {140,144,147,140,140,155,179,175},
                                     {144,152,140,147,140,148,167,179},
                                     {152,155,136,167,163,162,152,172},
                                     {168,145,156,160,152,155,136,160},
                                     {162,148,156,148,140,136,147,162},
                                     {147,167,140,155,155,140,136,162},
                                     {136,156,123,167,162,144,140,147},
                                     {148,155,136,155,152,147,147,136}
                                   };

    //to store DCT
    int output_pixels[size][size];
    //to store quantization table
    int quant[size][size];
    //to store quantization
    int quantization[size][size];
    //loop variables
    int i,j,m,n;
    //variables
    float dct,p,q ,sum=0;

    //printing the pixels
    printf("Input pixels\n");
    print(input_pixels);

    //shifting by 8 bits
     for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {

                input_pixels[i][j] = input_pixels[i][j]-128;

            }
        }

    //performing DCT
     for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                dct = 0.0;

                for (m = 0; m < size; m++)
                {
                    for (n = 0; n < size; n++)
                    {
                        dct = dct + cos(i*pi*(2*m+1)/(2*size)) *
                               cos(j*pi*(2*n+1)/(2*size)) *
                               input_pixels[m][n];
                    }
                }
                    dct = dct * 1/sqrt(2 * size) * coff(i)*coff(j);
                    output_pixels[i][j] = round(dct);
            }
        }


        //getting quantization table
        for ( i = 0 ; i < size ; i++ )
            {
                for ( j = 0 ; j < size ; j++ )
                    {
                        quant[ i ][ j ] = 1 + ( ( 1 + i + j ) * quality );
                    }
            }


        //performing quantization
        for(i=0 ;i<size;i++)
        {
            for(j=0;j<size;j++)
            {
                quantization[i][j]=output_pixels[i][j]/quant[i][j];
            }
        }

        //printing results
        printf("DCT \n");
        print(output_pixels);
        printf("quantization table \n");
        print(quant);
        printf("quantization\n");
        print(quantization);

}
//function to print the matrix
void print(int mat[size][size])
{
    int i ,j ;

    for(i=0;i<size;i++)
        {
                for(j=0;j<size;j++)
                {
                    printf("%d\t",mat[i][j]);
                }
                printf("\n");
        }
}


