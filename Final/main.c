/*
 * Author           :    Manoj M
 * Filename         :    main.c
 * Functions        :    main
 * Global Variables :    NONE
 * Macros           :    Height , Width

*/

//header file
#include "image.h"

//main
void main()
{


	//to store pixels
	unsigned char Input_data[Height ][Width];

	//function calls
	Read_img(Input_data,"Image1_256x256.raw");
	Write_img(Input_data,"copy1.raw");
    mean_filter(Input_data,"mean1.raw");
    median_filter(Input_data,"median1.raw");

}

