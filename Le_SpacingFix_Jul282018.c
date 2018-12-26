/*=====================================================================================================================================
FileName: Le_FormatFix_Jul2218.c
FileType: C Source File
Author : Dung Le
Created On : 7/24/2018 10:00:00 AM
Last Modified On : 7/30/2018 9:00:00 AM
Description : Fix Spacing/Capitalization Errors from a .txt file
Editor: Notepad++ Ver. 7.5.8
Complier: Raspbian 6.3.0
Kernel: Linux raspberrypi 4.9.59-v7+
=====================================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
	
int main()
{
	FILE *input_file;
	long file_size;
	char *buf_src, *buf_dest, *temp_src_ptr, *temp_dest_ptr;
	int i;
	
	buf_src = buf_dest = temp_src_ptr = temp_dest_ptr = NULL;
	
	input_file = fopen("input.txt","r");
	
	if(input_file == NULL){
		printf("Failure to open file\n");
		return 1;
	}	
	
	fseek(input_file, 0, SEEK_END);					//pointer jumps to the end of the file
	file_size = ftell(input_file);					//the position of that pointer is given, therefore giving file size	
	fseek(input_file, 0, SEEK_SET);					//jumps back to start to allow further processing
	
	buf_src = malloc(1.1 * file_size);				//allocates memory to the pointer
	buf_dest = malloc(1.1 * file_size);				//allocates memory for a blank string	
	
	temp_src_ptr = buf_src;
	temp_dest_ptr = buf_dest;
	
	fgets(buf_src, file_size, input_file);			//reads string from input.txt and allocates it to buf_src
	
	printf("File size = %ld bytes\n", file_size);
	printf("\nOriginal Text:\n\n");
	puts(buf_src);	
	
/*Removes extra whitespaces*/
	while (*temp_src_ptr != 0){  
		if (*temp_src_ptr != ' '){
			*temp_dest_ptr = *temp_src_ptr;
			temp_dest_ptr++;
		}	
		if (*temp_src_ptr == ' '){
			if (*(temp_src_ptr - 1) == ' '){
			} else{			
				*temp_dest_ptr = *temp_src_ptr;
				temp_dest_ptr++;
			}	
		}	
		temp_src_ptr++;
	}
	*temp_dest_ptr = 0;
	

	buf_src = buf_dest;								//copies the revised string from buf_dest to buf_src	
/*Resets pointers of both strings to beginning position*/	
	temp_src_ptr = buf_src;												
	temp_dest_ptr = buf_dest;
	
/*Removes spaces before punctuations*/
	while (*temp_src_ptr != 0){
		if(*temp_src_ptr != ' '){
			*temp_dest_ptr++ = *temp_src_ptr++;
		}	
		if (*temp_src_ptr == ' '){
			if (*(temp_src_ptr + 1) == '!' || *(temp_src_ptr + 1) == '@' || *(temp_src_ptr + 1) == '#' || *(temp_src_ptr + 1) == '$' || *(temp_src_ptr + 1) == '%' || *(temp_src_ptr + 1) == '^' || *(temp_src_ptr + 1) == '*' || *(temp_src_ptr + 1) == ';' || *(temp_src_ptr + 1) == ':' || *(temp_src_ptr + 1) == '"' || *(temp_src_ptr + 1) == ',' || *(temp_src_ptr + 1) == '.' || *(temp_src_ptr + 1) == '/' || *(temp_src_ptr + 1) == '?'  || *(temp_src_ptr + 1) == 0x27  || *(temp_src_ptr + 1) == 0x92){
				temp_src_ptr++;	
			}	else{
				*temp_dest_ptr++ = *temp_src_ptr++;
			}	
		}		
	}
	*temp_dest_ptr = 0;
	
	buf_src = buf_dest;								//copies the revised string from buf_dest to buf_src
/*Resets pointers of both strings to beginning position*/	
	temp_src_ptr = buf_src;												
	temp_dest_ptr = buf_dest;

/*Fixes capitalization errors*/
	while (*temp_src_ptr != 0){
		if (*(temp_src_ptr - 2) == '.' || *(temp_src_ptr - 2) == ':' || *(temp_src_ptr - 2) == '?' || *(temp_src_ptr - 2) == '!'){
			*temp_src_ptr = toupper(*temp_src_ptr);
			*temp_dest_ptr++ = *temp_src_ptr++;
		} else{
			*temp_src_ptr = tolower(*temp_src_ptr);
			*temp_dest_ptr++ = *temp_src_ptr++;
		}	
	}	
	*temp_dest_ptr = 0;
	
	buf_src = buf_dest;								//copies the revised string from buf_dest to buf_sr
/*Resets pointers of both strings to beginning position*/	
	temp_src_ptr = buf_src;												
	temp_dest_ptr = buf_dest;

/*Manually setting first two letters to be upper and lower case respectively due to  limitation*/	
	*temp_src_ptr = toupper(*temp_src_ptr);
	*temp_dest_ptr++ = *temp_src_ptr++;
	*temp_src_ptr = tolower(*temp_src_ptr);
	*temp_dest_ptr = *temp_src_ptr;

	printf("\nRevised Text:\n\n");
	puts(buf_dest);									//prints out final revised string
	
	fclose(input_file);
	
	return 0;
}	