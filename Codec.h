//
//  Codec.h
//  
//
//  Created by Benjamin Fernandez on 16/12/2017.
//

#ifndef Codec_h
#define Codec_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void menu();
void emptyBuffer();
unsigned short checkMatrixFile (FILE* matrixFile);
unsigned long long fileSelection(unsigned char *filename, FILE* file);
void stockMatrix (FILE * matrixFile, unsigned char matrix[][8]);
unsigned short makeNewFilename(unsigned char *filename, unsigned char *encryptedDecryptedFilename, unsigned short mode);






#endif /* Codec_h */
