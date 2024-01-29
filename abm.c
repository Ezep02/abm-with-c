#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//variables prototypes
void menu();
void create_new_file(char file[], char mode[]);
void add_new_client(char file[], char mode_add[]);
void existing_client_list(char file[], char mode[]);
void full_list(char file[], char mode[]);
void consult_client_by_id(char file[], char mode[]);
void modify_client_by_id(char file[], char mode[]);
void remove_client_by_id(char file[], char mode[]);

//client register
struct{
    int id;
    char name[30]; 
    int age;
    char status[40]; //Active / deleted / not used
} t_client;




int main(){

    //file
    char file[10] = "abm.dat";

    //modes 
    char mode_rb[10] = "rb";
    char mode_add[10] = "r+b";


    int option;

    //main menu
    menu();
    scanf("%d", &option);

    while (option != 0){

        switch (option)
        {
        case 1:
            system("cls");
            create_new_file(file, mode_rb);
            break;
        
        case 2: 
            system("cls");
            add_new_client(file, mode_add);
            break;

        case 3: 
            system("cls");
            existing_client_list(file, mode_rb);
            break;
        case 4: 
            system("cls");
            full_list(file, mode_rb);
            break;
        case 5: 
            system("cls");
            consult_client_by_id(file, mode_rb);
            break;
        case 6: 
            system("cls");
            modify_client_by_id(file, mode_add);
            break;
        case 7:
            system("cls");
            remove_client_by_id(file, mode_add);
            break;
        default:
            system("cls");
            printf("opcion invalida \n");
            break;
        }
        
        system("pause");
        menu();
        scanf("%d", &option);
    }
    return 0;
}

//main menu options
void menu(){
    printf("1.Create a new file.\n");
    printf("2.Add a new client.\n");
    printf("3.Existing clients list.\n");
    printf("4.Clients full list.\n");
    printf("5.Consult client by id.\n");
    printf("6.Modify a client.\n");
    printf("7.Remove Client.\n");
    printf("0 (Exit) \n");
    printf("Option: ");
}

//modify menu
void modify_menu(){
    
    printf("1.Name.\n");
    printf("2.Age.\n");
    printf("0 (Exit).\n");
    printf("Option: ");

}

//create a new file #
void create_new_file(char file[], char mode[]){
    FILE *fp;
    fp = fopen(file, mode);

    //si no existe, se crea
    if(fp == NULL){
        char mode_wb[10] = "wb";
        fp = fopen(file, mode_wb);
        printf("File successfully created...\n");
        fclose(fp);
    } else {
        fclose(fp);
        printf("File already created...\n");
    }
}

//Add a new client #
void add_new_client(char file[], char mode_add[]){
    
    FILE *fp;
    fp = fopen(file, mode_add);

    if(fp == NULL){
        printf("You must create a new file first..\n");
        return;
    }

    //register

    printf("ID: ");
    scanf("%d", &t_client.id);
    fflush(stdin);

    printf("Name: ");
    fgets(t_client.name, 30, stdin);
    strtok(t_client.name,"\n");
       
    printf("Age: ");
    scanf("%d", &t_client.age);

    strcpy(t_client.status, "ACTIVE");

    fseek(fp, sizeof(t_client)*t_client.id, SEEK_SET);
    fwrite(&t_client, sizeof(t_client), 1, fp);
    fclose(fp);

}  

//Existing clients list #
void existing_client_list(char file[], char mode[]){

    FILE *fp;
    fp = fopen(file, mode);
    
    if(fp == NULL){
        printf("You must create a new file first\n");
        return;
    }

    // Lee registros hasta que alcance el final del archivo
    while (fread(&t_client, sizeof(t_client), 1, fp) == 1) {
        // Haz lo que necesites con los datos del registro
        
        int active = strcmp(t_client.status, "ACTIVE");

        if(active == 0){
            printf("ID: %d\tCLIENT: %s\tAGE: %d\tSTATUS:\t %s\n",t_client.id ,t_client.name,t_client.age, t_client.status);
        }
    }

    fclose(fp);
} 

//client full list #
void full_list(char file[], char mode[]){
    FILE *fp;
    fp = fopen(file, mode);

    if(fp == NULL){
       printf("You must create a new file first\n");
       return;
    }

    while (fread(&t_client, sizeof(t_client), 1, fp) == 1) {

        printf("ID: %d\tCLIENT: %s\tAGE: %d\tSTATUS: %s\t\n",t_client.id ,t_client.name,t_client.age,t_client.status);
    }

    fclose(fp);
}

//consult client by number id #
void consult_client_by_id(char file[], char mode[]){
    FILE *fp;
    fp = fopen(file, mode);

    if(fp == NULL){
        printf("You must create a new file first...\n");
        return;
    }

    int option;
    printf("Client ID: ");
    scanf("%d",&option);

    while(fread(&t_client, sizeof(t_client), 1, fp) == 1){

        if(t_client.id == option){
            printf("ID: %d\tCLIENT: %s\tAGE: %d\tSTATUS: %s\n",t_client.id ,t_client.name,t_client.age,t_client.status);
        } 
    } 

    fclose(fp);
}

//modify a client by id #
void modify_client_by_id(char file[], char mode[]){
    FILE *fp;
    fp = fopen(file, mode);

    if(fp == NULL){
        printf("You must create a new file first...\n");
        return;
    }

    int id;
    printf("Client ID: ");
    scanf("%d", &id);
    system("cls");

    while(fread(&t_client, sizeof(t_client), 1, fp) == 1){

        //if id == option, we can change the client info
        if(t_client.id == id){  
            int modify_opt;

            modify_menu(); //show modify option
            scanf("%d", &modify_opt);
            fflush(stdin);
            system("cls");
            while(modify_opt != 0){
                
                switch (modify_opt)
                {
                case 1:
                    fseek(fp, sizeof(t_client)*id, SEEK_SET);
                    fread(&t_client, sizeof(t_client), 1, fp);
                    
                    printf("New Name: ");
                    fgets(t_client.name, 30, stdin);
                    strtok(t_client.name, "\n");
            
                    fseek(fp, sizeof(t_client)*-1, SEEK_CUR);
                    fwrite(&t_client, sizeof(t_client), 1, fp);
                    system("cls");
                    printf("Successfully Changed\n");
                    system("pause");
                    break;
                case 2: 
                    fseek(fp, sizeof(t_client)*id, SEEK_SET);
                    fread(&t_client, sizeof(t_client), 1, fp);

                    printf("New Age: ");
                    scanf("%d", &t_client.age);

                    fseek(fp, sizeof(t_client)*-1, SEEK_CUR);
                    fwrite(&t_client, sizeof(t_client), 1, fp);
                    system("cls");
                    printf("Successfully Changed\n");
                    system("pause");
                    break;

                default:
                    system("cls");
                    printf("Invalid Option\n");
                    system("pause");
                    break;
                }

                system("cls");
                
                modify_menu();
                scanf("%d", &modify_opt);
                fflush(stdin);
                
            }
            
            fclose(fp);
            
        }

    }

    fclose(fp);
}

//remove a client by id
void remove_client_by_id(char file[], char mode[]){

    FILE *fp;
    fp = fopen(file, mode);
    
    if(fp == NULL){
        printf("You must create a new file first...\n");
        return;
    }

    int id;
    printf("ID client to REMOVE: ");
    scanf("%d", &id);

    while (fread(&t_client, sizeof(t_client), 1, fp) == 1){

        if(t_client.id == id){

            fseek(fp, sizeof(t_client)*id, SEEK_SET);
            fread(&t_client, sizeof(t_client), 1, fp);

            strcpy(t_client.status, "DELETED");
            fseek(fp, sizeof(t_client)*-1, SEEK_CUR);
            fwrite(&t_client, sizeof(t_client), 1, fp);
            printf("Client successfully deleted\n");
            fclose(fp);
        }
    }
    fclose(fp);
}