//
//  Codec.c
//  
//
//  Created by Benjamin Fernandez on 16/12/2017.
//

#include "Codec.h"


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




unsigned long long fileSelection(unsigned char *filename, FILE* file){
    
    
    int i;
    unsigned long long size;
    
    filename = NULL;
    fileSize = 0;
    
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
        
        for (j = (i*9)+5; j < ((i*9)+8)+5; y++){
            
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




