//
//  main.c
//  
//
//  Created by Benjamin Fernandez on 17/12/2017.
//






#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void menu(){
    printf("\n1/ Encrypt a file");
    printf("\n2/ Decrypt a file");
    printf("\n3/ Quitter");
}



void emptyBuffer(){
    fflush(stdin);
    fflush(stdout);
}




unsigned long long fileSelection(unsigned char * filename, FILE* file){
    
    
    int i;
    unsigned long long size;
    
    filename = NULL;
    size = 0;
    
    for (i = 0; i < 255; i++) {
        filename[i] = 0;
    }
    
    
    // Demande le nom du fichier tant que le fichier n'existe pas.
    
    while (file == NULL) {
        
        printf("\nEnter a filename: ");
        fgets(filename, 255, stdin);
        
        for (i = 0; i < 255; i++) {
            if (filename[i] == '\n') {
                filename[i] = 0;
                break;
            }
        }
        
        file = fopen(filename, "r");
        
        if (file == NULL) {
            printf("File does not exist.\n");
        }
        
    }
    
    
    fclose(file);
    
    
    emptyBuffer();
    
    
    
    
    
    
}





unsigned short checkMatrixFile (FILE * matrixFile){
    
    unsigned char matrix [41];
    
    unsigned short i;
    unsigned short j;
    unsigned short result = 1;
    
    fseek(matrixFile,0,SEEK_SET);
    fread(matrix,sizeof(char),41,matrixFile);
    
    // Vérification du début et de la fin du fichier contenant les caractères G4C=[]
    
    if (matrix[0] != 'G'
        || matrix[1] != '4'
        || matrix[2] != 'C'
        || matrix[3] != '='
        || matrix[4] != '['
        || matrix[40] != ']'){
        result = 0;
    }
    
    
    // Vérification de la matrice
    for (i = 0; i < 4; i ++){
        
        for (j = (i*9)+5; j < ((i*9)+8)+5; j++){
            
            if ( matrix[j] != '0' && matrix[j] != '1'){
                result = 0;
            }
        }
    }
    return result;
}





void stockMatrix (FILE * matrixFile, unsigned char matrix[][8]){
    
    unsigned char key [41];
    
    unsigned short i;
    unsigned short j;
    unsigned short k;
    
    fseek(matrixFile,0,SEEK_SET);
    fread(key,1,41,matrixFile);
    
    for (i = 0; i < 4; i ++){
        k = 0;
        for (j = (i*9)+5; j < ((i*9)+8)+5; j++){
            matrix[i][k] = key[j];
            k++;
        }
    }
}





unsigned short makeNewFilename(unsigned char *filename, unsigned char *encryptedDecryptedFilename, unsigned short mode){
    
    unsigned short i;
    unsigned short result = 0;
    
    
    if(*filename != NULL){
        for (i = 0; i < 255; i++) {
            encryptedDecryptedFilename[i] = '\0';
        }
        
        
        for (i = 0; i < 255; i++) {
            encryptedDecryptedFilename[i] = filename[i];
        }
        
        
        switch (mode) {
            case 1:
                encryptedDecryptedFilename[strlen(encryptedDecryptedFilename)] = 'c';
                break;
                
            case 2:
                encryptedDecryptedFilename[strlen(encryptedDecryptedFilename)] = 'd';
                break;
            default:
                break;
        }
        
        if ( encryptedDecryptedFilename[strlen(encryptedDecryptedFilename)-1] == 'c' || encryptedDecryptedFilename[strlen(encryptedDecryptedFilename)-1] == 'd' ) {
            result = 1;
        } else {
            result = 0;
        }
        
        
        
    } else {
        result = 0;
    }
    
    
    
    return result;
    
}




















int main(int argc, char **argv){

    
    unsigned short choice;
    unsigned short checkMatrix = 0;
    unsigned short error = 1;
    unsigned short mode = 0;
    unsigned short restart = 1;
    
    
    
    unsigned char *encryptedFilename;
    unsigned char *filename;
    unsigned char matrix[4][8];
    
    int i;
    int j;
    
    unsigned long long size;
    
    FILE* file;
    FILE* matrixFile;
    
    
    
    emptyBuffer();
    
    
    printf("\n\n********************** Encrypt/Decrypt Program **********************");
    
    while (restart) {
        choice = 0;
        mode = 0;
        
        
        // Sélection du menu
        menu();
        
        printf("\n\nYour choice : ");
        scanf("%hu", &choice);
        
        
        
        // ReSélection du menu si erreur
        while(choice < 0 || choice > 3){
            menu();
            
            printf("\n\nWrong value please choose an int from 1 to 3.");
            printf("\n\nYour choice : ");
            scanf("%hu", &choice);
            emptyBuffer();
        }
        
        
        
        // Encrypter un fichier
        if (choice == 1){
            printf("OK 1");
            
            filename = malloc(sizeof(char) * 255);
            
            if (filename == NULL) {
                exit(EXIT_FAILURE);
            }
            
            printf("OK 2");
            encryptedFilename = malloc(sizeof(char) * 255);
            
            if (encryptedFilename == NULL) {
                exit(EXIT_FAILURE);
            }
            
            mode = 1;
            
            for (i = 0; i < 255; i ++){
                filename[i] = 0;
            }
            
            printf("OK 3");
            size = fileSelection (filename,file);
            matrixFile = fopen("key.txt", "r");
            
            printf("OK 4");
            // Vérification du contenu du fichier matrice
            checkMatrix = checkMatrixFile(matrixFile);
            
            printf("OK 4");
            if (checkMatrix == 0) {
                printf("\n\nThe matrix format is not a good one");
                printf("\nThe program is going to stop...");
                exit(EXIT_FAILURE);
            }
            
            printf("OK 5");
            fclose(matrixFile);
            
            error = makeNewFilename(filename,encryptedFilename, mode);
            
            printf("OK 6");
            if (error == 0) {
                printf("\n\nThe filename is not valid");
                printf("\nThe program is going to stop...");
                exit(EXIT_FAILURE);
            }
            
            
            // on affiche le tableau qu'on vient de remplir.
            printf("Here is your G4 matrix:\n\n");
            
            for (i = 0; i < 4; i ++){
                for (j = 0; j < 8; j ++){
                    printf("%c ", matrix[i][j]);
                }
                printf("\n");
            }
            printf("Encrypting...\n\n");
            
         
            
            
            free(filename);
            free(encryptedFilename);
            
            
        } else if (choice == 2){
            mode = 2;
        }
        
        
        
        
        
        
        
    }
    
    
    
    return 0;
}
