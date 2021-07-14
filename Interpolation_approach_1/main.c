/*
 * Author           :    Manoj M
 * Filename         :    DSP.h
 * Functions        :    main
 * Global Variables :    NONE
*/


#include "DSP.h"

//here the main function take the location of file and performs interpolation
void main()
{
	//to find cycles
	volatile unsigned int start, end, cycles;
	TSCL = 0;
	//File locations
	char Input_File[]  = "C:\\Users\\MANU042k\\Desktop\\Path_partner\\ccs_demo\\test\\Image1_256x256.raw";
	char Output_File[]  = "C:\\Users\\MANU042k\\Desktop\\Path_partner\\ccs_demo\\test\\Output_512x256.raw";

	//array to store the data
	unsigned char Input_data[Height * Width];
	unsigned char Output_data[2* Height * Width];

	start = _itoll(TSCH, TSCL);
	//function call
	Read_img(Input_data,Input_File);
	interpImg(Input_data,Output_data,Output_File );

	end = _itoll(TSCH, TSCL);
	cycles = end-start;

	printf("Cycles: %d\n", cycles);

}

