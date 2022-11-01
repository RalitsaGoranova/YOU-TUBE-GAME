#include <stdio.h>

#include <stdlib.h>

#include <conio.h>

#include <string.h>



typedef struct Words{

        char word[10];

    }Word;



     Word badWords[] =

    {

        "shit",

        "fuck",

        "ass",

        "pussy",

        "bitch"

    };

typedef struct comments{

    char commentUser[15];

    char commentText[50];

    char commentUploadDate[12];

    char commentLikes[4];

}Comment;

typedef struct Video {

    char videoLink[20];

    char videoName[20];

    char videoRating[2];

    char videoUploadDate[12];

    char videoLikes[8];

    char videoDislikes[8];

    Comment videoComments[5];

    struct Video *next;

}Video;

/* Add a new video to linked list */

Video *AddNewVideo(Video *head){

    char temp;

    Video *current =NULL;

        printf("Adding a video...\n");

        current = (Video *)malloc(sizeof(Video));

        printf("Link:");

        scanf("%s", current->videoLink);

        printf("Name:");

        scanf("%c",&temp);

        fgets(current->videoName,100,stdin);

        printf("Rating[1-5]:");

        scanf("%s", current->videoRating);

        printf("Upload Date(DD.MM.YYYY):");

        scanf("%s", current->videoUploadDate);

        printf("Likes:");

        scanf("%s", current->videoLikes);

        printf("Dislikes:");

        scanf("%s", current->videoDislikes);

if(atof(current->videoLikes)/atof(current->videoDislikes) < 0.5)

        {

            printf("Error: Like/Dislike ratio too Low!");

            return head;



        }



        int counter = 0;

        char q[1];

        printf("Add comment[Y/N]?\n");

        scanf("%s",q);

        while(strcmp(q,"Y") == 0)

        {

            printf("user:");

            scanf("%s", current->videoComments[counter].commentUser);

            printf("text:");

            scanf("%c",&temp);

            fgets(current->videoComments[counter].commentText,100,stdin);

            printf("date:");

            scanf("%s", current->videoComments[counter].commentUploadDate);

            printf("likes:");

            scanf("%s", current->videoComments[counter].commentLikes);

            if(ProfanityDetector(current->videoComments[counter].commentText) == 0)

            {

                counter++;

            }

            else

            {

                printf("Profanities Detected, Upload Failed!\n");

            }

        printf("Add comment[Y/N]?\n");

        scanf("%s",q);

        }

        current->next= head;

        head = current;



    return head;

}

/* Print all the elements in the linked list */

void printVideos(Video *head){

    Video *current_video = NULL;

    current_video = head;

    int counter = 1;



    while(current_video != NULL)

    {

        printf("Video %d: %s\n",counter++, current_video->videoName);

        current_video = current_video->next;

    }

}

/* Write Data to a Binary File */

void WriteToFile(Video *head){

    FILE *ptr;

    Video *write_videos = NULL;

    int inputs = 0;



    write_videos = head;

    ptr = fopen("Database.bin","wb");

    while(write_videos != NULL)

        {

            inputs = fwrite(&write_videos,sizeof(200),1,ptr);

            printf("Videos Added to the file: %d\n", inputs++);

            write_videos = write_videos->next;

        }

    fclose(ptr);

}

/* Read Data from a Binary File */

void ReadFromFile(Video *head){

    FILE *ptr;

    Video *in_videos = NULL;

    Video *out_videos = NULL;

    int counter = 1;



    ptr = fopen("Database.bin","rb");

    head = NULL;



        while(!feof(ptr))

    {

        in_videos = (Video *)malloc(sizeof(Video));

        fread(&in_videos,sizeof(200),1,ptr);

        in_videos->next = head;

        head = in_videos;

    }



    fclose(ptr);



    out_videos = head;

    while(out_videos != NULL)

    {

        out_videos = out_videos->next;

        printf("%d. %s",counter++, out_videos->videoName);

    }



}

/*Detecting Profanities in string*/

int ProfanityDetector(char checkedString[]){

    char *ptr;

int i;

    for(i = 0; i <= 5; i ++)

    {

        ptr = strstr(checkedString, "shit");

        if(ptr == NULL)

        {

            return 0;

        }

        else

        {

            return 1;

        }

    }

}

int main(){

    Video *head = NULL;

    int num;

    int option;

    char * temp;

    /* Display Menu */

    while(1) {

        printf("\n |=========================================|\n");

        printf("\n |  Linked list operations:                |\n");

        printf("\n |    1. Add                               |\n");

        printf("\n |    2. Print                             |\n");

        printf("\n |    3. Quit                              |\n");

        printf("\n |=========================================|\n");

        printf("\n Choose an option [1-3] : ");

        if (scanf("%d", &option) != 1) {

            printf(" *Error: Invalid input. Press try again.\n");

            scanf("%s", &temp); /*this will clear the input buffer */

            continue;

        }

        switch (option) {

            case 1:        /* Add */

                head = AddNewVideo(head);

                printf("\nPress any key to continue...");

                getch();

                break;

            case 2: /* Print */

                printf("\nList of Current Videos: \n");

                printVideos(head);

                printf("\n\nPress any key to continue...");

                getch();

                break;

            case 3:    /* Exit */

                WriteToFile(head);

                ReadFromFile(head);

                return(0);

                break;

            default:

                printf("Invalid Option. Please Try again.");

                getch();

            } /* End of Switch */

    } /* End of While */

return(0);

}
