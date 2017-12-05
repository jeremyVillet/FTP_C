//
// Created by jerem on 03/06/2017.
//

#ifndef SUPSHARINGSERVER_MAIN_H
#define SUPSHARINGSERVER_MAIN_H

#endif //SUPSHARINGSERVER_MAIN_H


char server[]="server:# ";
char welcome[2][100]={{"Welcome to SupSharing"},{"You can use help to list commands"}};
char command_rcv[100]="";

int idCommand=-1;

char command[9][64]={{"quit"},{"help"},{"cd:"},{"put:"},{"ls"},{"delete:"},{"mkdir:"},{"get:"},{"status"}};

char pathDirectory[200];
int compare(char commandToSend[],char command[][64]);
int sizeOfFileGet;
char fileClientToGet[100];
void  command_help(SOCKET client_socket);
void command_cd(SOCKET client_socket,char pathDirectory[]);
void command_put(SOCKET client_socket);
void command_ls(SOCKET client_socket,char pathDirectory[]);
void command_delete(SOCKET client_socket,char pathDirectory[]);

void command_mkdir(SOCKET client_socket,char pathDirectory[]);
void command_get(SOCKET client_socket,char pathDirectory[]);

