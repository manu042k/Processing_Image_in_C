/*
 * Author           :    Manoj M
 * Filename         :    DSP.h
 * Functions        :    Read_img, interpImg
 * Global Variables :    NONE
 * Macros           :    Height , Width ,last , last_o

*/

//Defining macros
#define Height 256
#define Width  256
#define last 65536
#define last_o (512*256)



#include<stdio.h>
#include <c6x.h>

//Function to read image pixels
void Read_img(unsigned char * restrict Input_data,char *Input_File)
{
	//File handling
	FILE *Image_Buffer  = fopen(Input_File,"rb");
	 if(Image_Buffer==NULL)
	    {
		 exit(1);
	    }
	fread(Input_data,sizeof(unsigned char),Height*Width,Image_Buffer);
	fclose (Image_Buffer ) ;

}

//Function to interpolate the image
void interpImg(unsigned char *Input_data ,unsigned char * restrict Output_data,char *Output_File )
{
     int i,m;

     FILE *Output_Buffer = fopen(Output_File,"wb");
     m=0;


    //Here the loop computes 6px of 1st half image and 6px of 2nd half of the image
    //there by reducing the cycles count

	#pragma MUST_ITERATE (21845,21845,6);
    for(i=0;i<Height*Width;i+=6)
    {

    	Output_data[i] = Input_data[m];
    	Output_data[i+1] = _avgu4(Input_data[m],Input_data[m+1]+1);
    	Output_data[i+2] = Input_data[m+1];
    	Output_data[i+3] = _avgu4(Input_data[m+1],Input_data[m+1+1]+1);
    	Output_data[i+4] = Input_data[m+2];
    	Output_data[i+5] = _avgu4(Input_data[m+2],Input_data[m+1+2]+1);



    	Output_data[last_o - i] = Input_data[last-m];
    	Output_data[last_o-i-1] = _avgu4(Input_data[last-m],Input_data[last-m-1]+1);
    	Output_data[last_o-i-2] = Input_data[last-m-1];
       	Output_data[last_o-i-3] = _avgu4(Input_data[last-m-1],Input_data[last-m-1-1]+1);
       	Output_data[last_o-i-4] = Input_data[last-m-2];
       	Output_data[last_o-i-5] = _avgu4(Input_data[last-m-2],Input_data[last-m-1-2]+1);

        m=m+3;
    }


    //writing back the data
	fwrite(Output_data,sizeof(unsigned char),2*Height*Width,Output_Buffer);
	fclose (Output_Buffer ) ;

}


