//
// Created by jerem on 04/06/2017.
//

#ifndef SUPSHARINGCLIENT_MAIN_H_H
#define SUPSHARINGCLIENT_MAIN_H_H

#endif //SUPSHARINGCLIENT_MAIN_H_H

char server[]="server:# ",guest[]="guest:$ ";
int idCommand=1;
char welcome[2][64]={{""},{""}};
char listCommand[10][60]={{""},{""}};

char command[9][64]={{"quit"},{"help"},{"cd:"},{"put:"},{"ls"},{"delete:"},{"mkdir:"},{"get:"},{"status"}};
char commandToSend[64]="";

char answerfromServer[200];

int sizeOfFile;
char fileToGet[100];

void cleanBuffer();
int scanfHomeMade(char *str, int size);

int compare(char commandToSend[],char command[2][64]);
void command_get(SOCKET client_socket);
void command_put(SOCKET client_socket);