/*
 * NAME: Luis Armando Garza
 * DATE: 05/01/22
 * COURSE: CS 4352 Operating Systems
 * DESCRIPTION: Search through a directory and list all file paths within it
 * 
 * INPUT EXAMPLES: ./a.out testdir
 *                 ./a.out          (current directory)
 *                 ./a.out .
 *                 ./a.out testdir/dir1 
 * OUTPUT: Prints all file paths within directory provided
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
char * full_path;

//read_dir() FUNCTION

void read_dir(char* sub_dir) {
    DIR *sub_dp=opendir(sub_dir);       //open directory
    struct dirent * sub_dirp;           //defines a file system independent directory entry
    
    if(sub_dp!=NULL) {                                //if directory opened successfully
        while((sub_dirp=readdir(sub_dp))!=NULL) {        //while there are files to read
            char * temp =sub_dirp->d_name;               //set current file name     
            char temp1[]=".";                            //set current directory
            char temp2[]="..";                           //set parent directory

            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0) {         //if file is not current dir or parent dir
                char temp3[]="/";
                char *temp_sub=temp3;
                temp_sub=strcat(temp_sub,temp);
                char * temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);                        //create variable for complete file path
                printf("%s\n", temp_full_path);                         //print complete file path
                DIR * subsubdp=opendir(temp_full_path);                 //attempt to open as sub-directory
                if(subsubdp!=NULL) {                                    //if directory opened successfully
                    closedir(subsubdp);                                     //closed opened directory
                    read_dir(temp_full_path);                               //recurcively loop into the sub-directory
                }
            }
        }
        closedir(sub_dp);     //closed opened directory

    } else {
        printf("cannot open directory\n");       //directory provided could not be opened
        exit(2);
    }

}

//main() FUNCTION

int main(int argc, char **argv) {
    char * dir;         //directory
    if(argc < 2) {      //if there are less than 2 command line arguemnts, set directory to currrent directory
        dir=".";            

    } else {            //directory was provided by the user
        dir=argv[1];	
    }

    read_dir(dir);      //read directory
    exit(0);
}


