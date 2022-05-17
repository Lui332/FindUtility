/*
 * NAME: Luis Armando Garza
 * DATE: 05/01/22
 * COURSE: CS 4352 Operating Systems
 * DESCRIPTION: Search through a directory and list all file paths within it
 *              that satisfy the criteria given (where-to-look, name, mmin, and inum)
 * 
 *              action criteria can delete a specified file or directory
 * 
 * INPUT EXAMPLES: ./a.out -w testdir 
 *                 ./a.out -w .
 *                 ./a.out -w testdir -m -5
 *                 ./a.out -w testdir -n exampleFile -m +10
 *                 ./a.out -i 12394131
 *                 ./a.out -n exampleFile 
 *                 ./a.out -w testdir -a delete
 *                 ./a.out -i 12394131 -a delete
 *                 ./a.out -w testdir -n exampleFile -m +10 -a delete
 * OUTPUT: Prints all file paths within directory provided that satisfy criteria, or 
 *         displays all files that have been successfully deleted due to criteria given
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
char * full_path;

//read_dir() FUNCTION

void read_dir(char* sub_dir, char* name, char* mmin, char* inum, char* action) {
    DIR *sub_dp=opendir(sub_dir);     //open directory
    struct dirent * sub_dirp;         //defines a file system independent directory entry
    struct stat buf;                  // define a file status structure
    time_t seconds;                   //time struct
    
    if(sub_dp!=NULL) {                               //if directory opened successfully
        while((sub_dirp=readdir(sub_dp))!=NULL) {         //while there are files to read
            char * temp =sub_dirp->d_name;                //set current file name
            char temp1[]=".";                             //set current directory
            char temp2[]="..";                            //set parent directory

            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0) {        //if file is not current dir or parent dir
                char temp3[]="/";
                char *temp_sub=temp3;
                temp_sub=strcat(temp_sub,temp);
                char * temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);                      //create variable for complete file path
                DIR * subsubdp=opendir(temp_full_path);               //attempt to open as sub-directory
                if(subsubdp!=NULL) {                                  //if directory opened successfully
                    closedir(subsubdp);

                    // DETERMINE IF DIRECTORY PASSES CRITERIA TO BE PRINTED

                    if (strcmp(name, "EMPTY") != 0) {                              //if name of dir needs to be checked
                        if (strcmp(name, sub_dirp->d_name) != 0) {                 //check if names match
                            read_dir(temp_full_path, name, mmin, inum, action);        // if no match, continue into sub-dir
                            continue;
                        }
                    }
                    
                    if (stat(temp_full_path, &buf) == 0) {

                        if (strcmp(mmin, "EMPTY") != 0) {                                        //if mmin of dir needs to be checked
                            seconds = time (NULL);
                            int desired_minute_range = atoi(mmin);                               //convert mmin to int
                            long last_modified_minutes = (seconds - (int)buf.st_mtime) / 60;     //file last modified time in mins

                            if (mmin[0] != '-' && mmin[0] != '+' && desired_minute_range != last_modified_minutes) {   //if times do not match
                                read_dir(temp_full_path, name, mmin, inum, action);                                        //continue into sub-dir
                                continue;
                            }
                            else if (mmin[0] == '-' &&  last_modified_minutes > (desired_minute_range * -1)) {      //if time is not less than
                                read_dir(temp_full_path, name, mmin, inum, action);                                     //continue into sub-dir
                                continue;
                            }
                            else if (mmin[0] == '+' && desired_minute_range > last_modified_minutes) {       //if time is not nore than
                                read_dir(temp_full_path, name, mmin, inum, action);                              //continue into sub-dir
                                continue;
                            }

                        }

                        if (strcmp(inum , "EMPTY") != 0) {                              //check if inum of dir needs to be checked
                            if (buf.st_ino != strtol(inum, NULL, 10)) {                 //if inums do not match
                                read_dir(temp_full_path, name, mmin, inum, action);         //continue into sub-dir     
                                continue;
                            }
                        }
                    }

                    if (strcmp(action, "EMPTY") != 0) {                        //if action entered, check if delete
                        if (strcmp(action, "delete") == 0) {
                            if (remove(temp_full_path) == 0) {                 //delete directory
                                printf("DELETED:  %s\n", temp_full_path);      //successful deletion, continue to next file in current dir
                                continue;
                            } else
                                printf("NOT DELETED:  %s\n", temp_full_path);  //dir could not be deleted
                        } else {
                            printf("INVALID ACTION\n");                        //action could not be handled
                            break;
                        }
                    }

                    printf("%s\n", temp_full_path);                       //directory passed all the criteria, print complete path to directory
                    read_dir(temp_full_path, name, mmin, inum, action);   //continue into sub-dir

                } else {    //else file could not be opened as directory

                    // DETERMINE IF FILE PASSES CRITERIA TO BE PRINTED

                    if (strcmp(name, "EMPTY") != 0) {                //if name of file needs to be checked
                        if (strcmp(name, sub_dirp->d_name) != 0)     //check if names match
                            continue;                                     //if no match, continue into next file
                    }
                    
                    if (stat(temp_full_path, &buf) == 0) {

                        if (strcmp(mmin, "EMPTY") != 0) {                                      //if mmin of file needs to be checked
                            seconds = time (NULL);
                            int desired_minute_range = atoi(mmin);                             //convert mmin to int
                            long last_modified_minutes = (seconds - (int)buf.st_mtime) / 60;   //file last modified time in mins

                            if (mmin[0] != '-' && mmin[0] != '+' && desired_minute_range != last_modified_minutes)   //if times do not match
                                continue;                                                                                //continue into next file
                            else if (mmin[0] == '-' &&  last_modified_minutes > (desired_minute_range * -1))         //if time is not less than
                                continue;
                            else if (mmin[0] == '+' && desired_minute_range > last_modified_minutes)                 //if time is not nore than
                                continue;

                        }

                        if (strcmp(inum , "EMPTY") != 0) {               //check if inum of file needs to be checked
                            if (buf.st_ino != strtol(inum, NULL, 10))    //if inums do not match
                                continue;                                     //continue into next file
                        }
                    }

                    if (strcmp(action, "EMPTY") != 0) {                        //if action entered, check if delete
                        if (strcmp(action, "delete") == 0) {
                            if (remove(temp_full_path) == 0) {                 //delete directory
                                printf("DELETED:  %s\n", temp_full_path);      //successful deletion, continue to next file in current dir
                                continue;
                            } else
                                printf("NOT DELETED:  %s\n", temp_full_path);  //dir could not be deleted
                        } else {
                            printf("INVALID ACTION\n");                        //action could not be handled
                            break;
                        }
                    }
        
                    printf("%s\n", temp_full_path);     //file passed all the criteria, print complete path to file
                }
            }
        }

        closedir(sub_dp);      //closed opened directory

    } else {
        printf("cannot open directory\n");      //directory provided could not be opened
        exit(2);
    }

}

//main() FUNCTION

int main(int argc, char **argv) {
    int w;
    char *where = ".", *name = "EMPTY", *mmin = "EMPTY", *inum = "EMPTY", *action = "EMPTY";   //set default criteria

    if(argc <2) {                                               //if less than two command line argruments
        read_dir(where, "EMPTY", "EMPTY", "EMPTY", "EMPTY");        //read current dir and exit
        exit(0);
    } else {

        while (1) {
            char c;
            c = getopt(argc, argv, "w:n:m:i:a:");	/* A colon (‘:’) to
                                * indicate that it
                                * takes a required
                                * argument, e.g, -w
                                * testdir */
            if (c == -1) {
                /* We have finished processing all the arguments. */
                break;
            }
            switch (c) {
            case 'w':               //where criteria
                w = 1;
                where = optarg;
                break;
            case 'n':               //name criteria
                name = optarg;
                break;
            case 'm':               //mmin criteria
                mmin = optarg;
                break;
            case 'i':               //inum criteria
                inum = optarg;
                break;
            case 'a':               //action criteria
                action = optarg;
                break;
            case '?':               //unknown criteria
            default:
                printf("An invalid option detected.\n");
            }
	    }
    }
    
    read_dir(where, name, mmin, inum, action);     //read directory using criteria given

    exit(0);
}
