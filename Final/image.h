/*
 * Author           :    Manoj M
 * Filename         :    image.h
 * Functions        :    Read_img, Write_img, mean_filter, median_filter, median
 * Global Variables :    NONE
 * Macros           :    Height , Width

*/


#include<stdio.h>
#include <math.h>

//Defining macros

#define Height 256
#define Width 256

//Function to read image pixels
void Read_img(unsigned char Input_data[Height][Width],char Input_File[])
{
	//File handling
    FILE *Image_Buffer  = fopen(Input_File,"rb");

	int i,j;

	//loops over and extracts data
	for(i=0;i<Height;i++)
    {
        for(j=0;j<Width;j++)
        {
            Input_data[i][j] = getc(Image_Buffer);
           // printf("%d\n",Input_data[i][j]);
        }
    }

	//close buffer
	fclose (Image_Buffer ) ;
}

//Function to write image pixels
void Write_img(unsigned char Output_data[Height][Width],char Output_File[])
{
	//File handling
	FILE *Image_Buffer  = fopen(Output_File,"wb");

    int i,j;

    //loops over and put data into file
	for(i=0;i<Height;i++)
    {
        for(j=0;j<Width;j++)
        {
             putc(Output_data[i][j] ,Image_Buffer);

        }
    }
	//close buffer
	fclose (Image_Buffer ) ;
}

//Function to apply mean filter
void mean_filter(unsigned char img_matrix[Height][Width],char Output_File[])
{
    int i ,j,x;

	//To store mean data
    unsigned char mean_matrix [Height][Width];

	//loop to extract boundary pixels
    for(x=0;x<Height;x++)
    {
        mean_matrix[x][0] = img_matrix[x][0];
        mean_matrix[0][x] = img_matrix[0][x];
        mean_matrix[x][255] = img_matrix[x][255];
        mean_matrix[255][x] = img_matrix[255][x];
        //printf("a:%d\t",mean_matrix[i][0]);
    }

	//performing mean filter operation from index (1,1) to (last-1,last-1)
    for(i=1;i<Height-1;i++)
            {
                for(j=1;j<Width-1;j++)
                    {
                    mean_matrix[i][j] =( img_matrix[i-1][j-1]
                                        + img_matrix[i-1][j]
                                        + img_matrix[i-1][j+1]
                                        + img_matrix[i][j-1]
                                        + img_matrix[i][j]
                                        + img_matrix[i][j+1]
                                        + img_matrix[i+1][j-1]
                                        + img_matrix[i+1][j]
                                        + img_matrix[i+1][j+1])/9;
                   // printf("%d\t",mean_matrix[i][j]);
                    }
        }

	//write back to data
    Write_img(mean_matrix,Output_File);
}
//Function to apply median filter
void median_filter(unsigned char img_matrix[Height][Width],char Output_File[])
{
    int i ,j,x;

	//To store median data
    unsigned char median_matrix [Height][Width];

	//loop to extract boundary pixels
	for(x=0;x<Height;x++)
    {
        median_matrix[x][0] = img_matrix[x][0];
        median_matrix[0][x] = img_matrix[0][x];
        median_matrix[x][255] = img_matrix[x][255];
        median_matrix[255][x] = img_matrix[255][x];
        //printf("a:%d\t",mean_matrix[i][0]);
    }

    //performing median filter operation from index (1,1) to (last-1,last-1)
    for(i=1;i<Height-1;i++)
            {
                for(j=1;j<Width-1;j++)
                    {
                       int median_array[9] = {
                                           img_matrix[i-1][j-1],
                                           img_matrix[i-1][j],
                                           img_matrix[i-1][j+1],
                                           img_matrix[i][j-1],
                                           img_matrix[i][j],
                                           img_matrix[i][j+1],
                                           img_matrix[i+1][j-1],
                                           img_matrix[i+1][j],
                                           img_matrix[i+1][j+1]
                                        };

                    //calling median function
                    median_matrix[i][j] = median(median_array);
                    }
        }
	//write back to data
    Write_img(median_matrix,Output_File);
}

//function to sort the array and returns median of it
int median(int array[9] )
{
    int median;
    int i=0 , j=0 , temp=0 ;

    //bubble sort
    for(i=0 ; i<9 ; i++)
    {
        for(j=0 ; j<9-1 ; j++)
        {
            if(array[j]>array[j+1])
            {
                temp        = array[j];
                array[j]    = array[j+1];
                array[j+1]  = temp;
            }
        }
    }

    //getting median
    if(9%2 == 0)
        median = (array[(9-1)/2] + array[9/2])/2;
    else
        median = array[9/2];

    return median;
}

