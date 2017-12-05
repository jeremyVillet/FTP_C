#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define WINDOWS // preciser l OS ici avant la compilation pour compiler le code adapté

#ifdef WINDOWS
#include <winsock2.h>

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



    SOCKET client_socket;
    SOCKADDR_IN client_sin;

    client_socket=(socket(AF_INET,SOCK_STREAM,0));// On créé la socket TCP/IPv4

    // On configure la connection grace aux sous varibales de la structure SOCKADDR-IN
    client_sin.sin_addr.s_addr=inet_addr("127.0.0.1");
    client_sin.sin_family=AF_INET;
    client_sin.sin_port=htons(1337);

    if(connect(client_socket,(SOCKADDR*)&client_sin, sizeof(client_sin))!=SOCKET_ERROR){ // On verifie que le client a bien pu se connecter
        printf("Success connection on %s on the port 1337 \n",inet_ntoa(client_sin.sin_addr));

        // client connecté au server

        // On recoit les deux messages d'acceuil du server
        int i;
        for(i=0;i<2;i++){
            if(recv(client_socket,welcome[i],100,0)!=SOCKET_ERROR){ // si la reception s est bien passer on affiche la string concerné
                printf("%s%s\n",server,welcome[i]);
            }
        }


        // On envoie une commande au server

        while(idCommand!=0){
            printf("%s ",guest);
            scanf("%s",commandToSend);

            idCommand=compare(commandToSend,command); // la connection est maintenu tant que l utilisateur ne rentre pas la commande quit


            if( idCommand==-1){ // On envoie la commande au serveur uniquement si cette dernière existe
                printf("%s Command not found, please check the syntaxe \n",server);
            }else
                send(client_socket,commandToSend,100,0);
            switch(idCommand) {
                case 1:// Commande help tapée ,on appelle la fonction affichant la liste des commandes
                    for(i=0;i<10;i++){
                        if(recv(client_socket,listCommand[i],60,0)!=SOCKET_ERROR){ // si la reception s est bien passer on affiche la string concerné
                            printf("%s%s\n",server,listCommand[i]);
                        }
                    }
                    break;
                case 2: // commande cd : on affiche la reponse du serveur
                    if (recv(client_socket, answerfromServer, 40, 0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
                        printf("%s%s\n", server, answerfromServer);
                    }
                    break;
                case 3: // commande put : on affiche la reponse du serveur
                    command_put(client_socket);
                    break;
                case 4:// commande ls : on affiche la reponse du serveur
                    if (recv(client_socket, answerfromServer, 2000, 0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
                        printf("%s List of folders and files : \n%s\n", server, answerfromServer);
                    }
                    break;
                case 5:// commande delete: on affiche la reponse du serveur
                    if (recv(client_socket, answerfromServer, 200, 0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
                        printf("%s%s\n", server, answerfromServer);
                    }
                    break;
                case 6:// commande mkdir : on affiche la reponse du serveur
                    if (recv(client_socket, answerfromServer, 100, 0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
                        printf("%s%s\n", server, answerfromServer);
                    }
                    break;
                case 7:// commande get : on affiche la reponse du serveur
                    command_get(client_socket);
                    break;
                default:
                    break;

            }

            fflush(stdin);
        }

        shutdown(client_socket,2); // on ferme la conection des deux sens

    }else{
        printf("Failed to connect\n");
    }
    closesocket(client_socket);

#ifdef WINDOWS
    // On libére les ressource allouer précedemment par WSAStartup
    WSACleanup();
#endif

    printf("%s Bye , see you soon ;)",server);

    // On vide le buffer ( surtout le buffer clavier ) et on attend que l' utilisateur appuie sur une touche pour fermer le programme
    fflush(stdin);
    getchar();
    return EXIT_SUCCESS;


}
// Analyse des commandes envoyés au server
int compare(char commandToSend[],char command[2][64]){
    int x, i,letterMatched;

    // return un nombre en fonction de la commande envoyer par le client
    for(i=0;i<9;i++){
        letterMatched=0;
        for (x=0;x<strlen(command[i]);x++){
            if(commandToSend[x]==command[i][x]){
                letterMatched++;
            }
        }
        if (letterMatched==strlen(command[i])){
            return i; // numero en fonction de la commande recu : 0:quit ,1:help
        } // si la commande correspond a une des commandes existante

    }
    return -1; // le client a taper une commande ne retournant rien


}



//instruction put (id 3): Envoyer un fichier au server

void command_put(SOCKET client_socket){
    int i;
    char fileToSend[100]="";
    // On extrait le nom du fichier a envoyer de la commande recu
    for(i=4;i<strlen(commandToSend);i++){
        fileToSend[i-4]=commandToSend[i];
    }
    fileToSend[strlen(commandToSend)-4]='\0';


    printf("chemin fichier a envoyer: %s\n",fileToSend);
    FILE* file=fopen(fileToSend,"rb"); // mode lecture en binaire
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

// gestion du reception du fichier lors d'un get (id commande 7)

void command_get(SOCKET client_socket){
    if (recv( client_socket,(char *)&sizeOfFile, sizeof(int),0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
        printf("%s Taille du fichier a recevoir %i\n", server, sizeOfFile);
    }
    if (recv( client_socket,fileToGet, 100,0) != SOCKET_ERROR) { // si la reception s est bien passer on affiche la string concerné
        printf("%s Nom du fichier a recevoir %s\n", server, fileToGet);
        FILE* file=NULL;
        file = fopen(fileToGet, "wb");
        if (file!=NULL){
            printf("Loading file : ");
            int numberCaraSent=0;
            int percentage=0,counter=0;
            char buffer[1000]="";
            while (numberCaraSent<sizeOfFile){
                recv(client_socket,buffer, 1000,0);
                percentage=(10*numberCaraSent/sizeOfFile);

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

