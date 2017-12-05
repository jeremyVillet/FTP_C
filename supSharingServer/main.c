#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


#define WINDOWS // preciser l OS ici avant la compilation pour compiler le code adapté

#ifdef WINDOWS
#include <winsock2.h>
#include <sys/types.h>
#include <windows.h>

typedef int socklen_t; //type servant à stocker la taille d'une structure propre aux sockets

#endif

#ifdef LINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s) // regle le probleme de la fonction portant deux noms différents entre windows et linux

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#endif

#include "main.h"
int main(int argc , char *argv[]) {

    #ifdef WINDOWS
    // pour pouvoir utiliser les sockets sous windows
    WSADATA dataWSA;
    WSAStartup(MAKEWORD(2,2),&dataWSA);
    #endif



    // socket coté server
    SOCKET server_socket;
    SOCKADDR_IN server_sin;
    socklen_t s_size = sizeof(server_sin);

    // socket coté server client
    SOCKET client_socket;
    SOCKADDR_IN client_sin;
    socklen_t c_size = sizeof(client_sin);

    int socket_error;


    // Creation et paramètrage de la socket


    server_socket=socket(AF_INET,SOCK_STREAM,0); // protocole TCP/IPv4 , protocole TCP
    if(server_socket!=INVALID_SOCKET){
        server_sin.sin_addr.s_addr = htonl(INADDR_ANY); // je défini ici l adresse du server
        server_sin.sin_family = AF_INET;
        server_sin.sin_port = htons(1337); // Je spécifie le port qui sera utilisé lors de la connection

        socket_error= bind(server_socket, (SOCKADDR*)&server_sin,s_size); // J'associe les infos a notre socket créé précedemment

        if(socket_error!=SOCKET_ERROR){
            printf("supSharing Server is actually open and it works !\n");

            listen(server_socket,4); // J'etablit la co en mettant la socket en écoute . 4 connections peuvent être mise en attentes
            printf("Please wait we are initialising connection on port 1337\n");

            client_socket = accept(server_socket, (SOCKADDR*)&client_sin, &c_size); //permet la connection client /server
            printf("One client is connecting with the socket %d on %s:%d\n",client_socket,inet_ntoa(client_sin.sin_addr),htons(client_sin.sin_port));

            // On envoye au client le contenu de la string welcome

            int x;
            for(x=0;x<2;x++){
                send(client_socket,welcome[x],100,0);
            }

            // traitement des info envoyé par le client
            while(idCommand!=0){
                if(recv(client_socket,command_rcv,100,0)!=SOCKET_ERROR){
                    idCommand=compare(command_rcv,command); // On recupere sous forme d'id la command taper par le client
                    printf("Message recu : id command =%d\n",idCommand);

                    // En fonction de l id commande on appelle la fonction executant l instruction demandée
                    switch(idCommand){

                        case 1 :
                            printf("Instruction help : \n");
                            command_help(client_socket);
                            break;
                        case 2 :
                            printf("Instruction cd : \n");
                            command_cd(client_socket,pathDirectory);
                            break;
                        case 3 :
                            printf("Instruction put  : \n");
                            command_put(client_socket);
                            break;
                        case 4 :
                            printf("Instruction :ls  \n");
                            command_ls(client_socket,pathDirectory);
                            break;
                        case 5 :
                            printf("Instruction  delete: \n");
                            command_delete(client_socket,pathDirectory);
                            break;
                        case 6 :
                            printf("Instruction :mkdir \n");
                            command_mkdir(client_socket,pathDirectory);
                            break;
                        case 7 :
                            printf("Instruction :get\n");
                            command_get(client_socket,pathDirectory);
                            break;
                        case 8 :
                            printf("Instruction :statut \n");
                            break;
                        default:
                            break;
                    }
                }

                fflush(stdin);
            }
            shutdown(client_socket,2); //On ferme la transmission dans les 2 sens une fois cette dernière effectué
        }
        else{
            perror("listen");
        }
    }else{
        perror("bind");
    }
        //On ferme les sockets client et server

    closesocket(client_socket);
    closesocket(server_socket);
    printf("The sockets are closed , server is closed\n");


    #ifdef WINDOWS
    // Je libére les ressource allouer précedemment par WSAStartup

    WSACleanup();
    #endif

    getchar();
    return EXIT_SUCCESS;


}
// associe un id a la commande recu du client afin de savoir quel instruction executer
int compare(char command_rcv[],char command[2][64]){
    int x, i,letterMatched;

    // return un nombre en fonction de la commande envoyer par le client
    for(i=0;i<9;i++){
        letterMatched=0;
        for (x=0;x<strlen(command[i]);x++){
            if(command_rcv[x]==command[i][x]){
                letterMatched++;
            }
        }
        if (letterMatched==strlen(command[i])){
            return i; // numero en fonction de la commande recu : 0:quit ,1:help
        } // si la commande correspond a une des commandes existante

    }
    return -1; // le client a taper une commande ne retournant rien


}
//instruction help (id 1 ) envoie au client la liste des commande et commant les utiliser

void command_help(SOCKET client_socket){
    char listCommand[10][60]={{"list of commands:"},{"- help list all available commands"},{"- cd:PATH_DIRECTORY change the current directory"},{"- get:PATH_FILE download a file"},{"- ls list files and directories"},{"- delete:NAME_DIRECTORY/FILE delete a file or a directory "},{"- mkdir:NAME_DIRECTORY create a directory "},{"- put:PATH_FILE send a file "},{"- status list numbers of connected users "},{"- quit logout the client"}};
    int i;
    for(i=0;i<10;i++){
        send(client_socket,listCommand[i],60,0);
    }
}
//instruction cd (id 2 ) : ouvrir un répértoire

void command_cd(SOCKET client_socket, char pathDirectory[]){
    int i;
    // On extrait le chemin du dossier de la commande recu
    for(i=3;i<strlen(command_rcv);i++){
        pathDirectory[i-3]=command_rcv[i];
    }
    pathDirectory[strlen(command_rcv)-3]='\0';


    //On teste l ouverture du fichier demander

    DIR* directory=NULL;
    directory=opendir(pathDirectory) ;
    if(directory==NULL){
        char answerforClient[40]="Directory can't be open, bad path :";
        send(client_socket,answerforClient,40,0);
    }else{
        char answerforClient[240]="Directory open";
        send(client_socket, answerforClient,40,0);
    }
    closedir(directory);
}
//instruction get (id 3 ) :recuperation fichier de la part client
void command_put(SOCKET client_socket){
    if (recv( client_socket,(char *)&sizeOfFileGet, sizeof(int),0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
        printf("%s Taille du fichier a recevoir %i\n", server, sizeOfFileGet);
    }
    if (recv( client_socket,fileClientToGet, 100,0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
        printf("%s Nom du fichier a recevoir %s\n", server, fileClientToGet);
        char pathFileClientToGet[100]="";
        strcat(pathFileClientToGet,pathDirectory);
        strcat(pathFileClientToGet,"\\");
        strcat(pathFileClientToGet,fileClientToGet);
        FILE* file=NULL;
        file = fopen(pathFileClientToGet, "wb");
        if (file!=NULL){
            printf("Loading file : ");
            int numberCaraSent=0;
            int percentage=0,counter=0;
            char buffer[1000]="";
            while (numberCaraSent<sizeOfFileGet){
                recv(client_socket,buffer, 1000,0);
                percentage=(10*numberCaraSent/sizeOfFileGet);

                if (percentage-1 == counter){
                    printf("##");
                    counter+=1;
                }
                fwrite(buffer,1000,1,file);
                numberCaraSent+=1000;
            }
            printf("\n");
            fclose(file);
        }
    }
}
//instruction ls (id 4 ) : lister un repertoire

void command_ls(SOCKET client_socket,char pathDirectory[]){

    DIR* directory=opendir(pathDirectory);
    char answerforClient[2000]="";

    struct dirent* nameFile=NULL;

    while((nameFile=readdir(directory))!=NULL){
        // printf("nom fichier : %s\n",nameFile->d_name);
        strcat(answerforClient,nameFile->d_name);
        strcat(answerforClient,"\n");
        }

    if(directory==NULL) { // si la command ls est executé sans avoir ouvert de dossier , on met un message d'erreur dans la reponse pour le client
        strcat(answerforClient,"no folder open !");
    }
    printf("test :%s\n", answerforClient);
    send(client_socket, answerforClient, 2000, 0);

    closedir(directory);

}
//instruction delete (id 5): supprimer un dossier ou un fichier

void command_delete(SOCKET client_socket,char pathDirectory[]) {
    int i;
    char nameFolderToDelete[100];
    char answerToClient[200]="";
    // On extrait le nom du fichier a supprimer
    for(i=7;i<strlen(command_rcv);i++){
        nameFolderToDelete[i-7]=command_rcv[i];
    }
    nameFolderToDelete[strlen(command_rcv)-7]='\0';
    char pathObjectToRemove[200]="";
    strcat(pathObjectToRemove,pathDirectory);
    strcat(pathObjectToRemove,"\\");
    strcat(pathObjectToRemove,nameFolderToDelete);

    
    //Si le client veut supprimer un dossier , on le vide de ses fichiers avant de le supprimer (son chemin est réélement supprimer sur windows qu'apres avoir fermé le client)
    struct dirent* nameFile=NULL;
    DIR* directory=NULL;
    directory=opendir(pathObjectToRemove);
    if(directory!=NULL){
        while((nameFile=readdir(directory))!=NULL){
            char pathFileInFolder[200]="";
            strcpy(pathFileInFolder,pathObjectToRemove);
            strcat(pathFileInFolder,"\\");
            strcat(pathFileInFolder,nameFile->d_name);
            remove (pathFileInFolder);
        }
        rmdir(pathObjectToRemove);
        strcat(answerToClient,"Folder has been deleted with success");
    }else{ // cas ou on désire supprimer un fichier uniquememnt
        remove (pathObjectToRemove);
        strcat(answerToClient,"File has been deleted with success");
    }
    send(client_socket, answerToClient, 200, 0);

    closedir(directory);


}


//instruction mdkir (id 6): Creer un dossier

void command_mkdir(SOCKET client_socket,char pathDirectory[]){
    int i;
    char nameNewFolder[100];
    // On extrait le chemin du dossier de la commande recu
    for(i=6;i<strlen(command_rcv);i++){
        nameNewFolder[i-6]=command_rcv[i];
    }
    nameNewFolder[strlen(command_rcv)-6]='\0';

    DIR* directory=opendir(pathDirectory);
    char answerforClient[100]="";
    if (directory!=NULL){
        char pathNewDirectory[300]="";
        strcat( pathNewDirectory,pathDirectory);
        strcat( pathNewDirectory,"\\");
        strcat( pathNewDirectory,nameNewFolder);

#ifdef WINDOWS
        CreateDirectory(pathNewDirectory,NULL);
#endif
#ifdef LINUX
        mkdir(pathNewDirectory, 0775);
#endif
        DIR* newDirectory=NULL;
        newDirectory=opendir(pathNewDirectory);

        if(newDirectory==NULL){
            strcat(answerforClient,"Error on the new name folder , check the syntaxe ! ");
        }else{
            strcat(answerforClient,"New directory create with success !");
        }
    }else{
        strcat(answerforClient,"You haven't opened folder yet ! Please use the command cd before !");
    }
    send(client_socket, answerforClient, 100, 0);
    closedir(directory);

}

//instruction put (id 7): Envoyer un fichier au client

void command_get(SOCKET client_socket,char pathDirectory[]){
    int i;
    char fileToSend[100]="";
    // On extrait le nom du fichier a envoyer de la commande recu
    for(i=4;i<strlen(command_rcv);i++){
        fileToSend[i-4]=command_rcv[i];
    }
    fileToSend[strlen(command_rcv)-4]='\0';


    char pathFileToSend[200]="";
    strcat(pathFileToSend,pathDirectory);
    strcat(pathFileToSend,"\\");
    strcat(pathFileToSend,fileToSend);

    printf("chemin fichier a envoyer: %s\n",pathFileToSend);
    FILE* file=fopen(pathFileToSend,"rb"); // mode lecture en binaire
    if(file!=NULL){
        fseek(file,0,SEEK_END);
        int sizeOfFile=ftell(file);
        printf("%d octets\n",sizeOfFile);
        send(client_socket,(char *)&sizeOfFile, sizeof(int),0);
        send(client_socket,fileToSend, 100,0);

        int numberCaraSent=0;
        char buffer[1000]="";
        rewind(file);
        while (numberCaraSent<sizeOfFile){
            fread(buffer,1000,1,file);
            send(client_socket,buffer, 1000,0);
            numberCaraSent+=1000;

        }

        fclose(file);
    }else{
        printf("file doesn t exist !\n");
    }
}