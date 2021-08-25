#include <stdio.h>
#include <stdlib.h>
#include "bmplib.h"

/*
 * This method enlarges a 24-bit, uncompressed .bmp file that has been
 * read in using readFile(), by doubling the number of rows and
 * columns. Also the image will convert to gray scale if requested.
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 * bw       - convert to gray scale if not zero
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (twice as many)
 * newcols  - the new number of columns (twice as many)
 */
int process(PIXEL* original, int rows, int cols, int bw,
	    PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */
  return 0;
}

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile(). 
 * 
 * THIS IS PROVIDED TO YOU AS AN EXAMPLE FOR YOU TO UNDERSTAND HOW IT
 * WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, int rows, int cols, PIXEL **new) 
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

int main()
{
  int rows, cols;
  PIXEL *pix, *npix;

  printf("read from file: example.bmp\n");
  readFile("example.bmp", &rows, &cols, &pix);

  printf("flip image horizontally\n");
  flip(pix, rows, cols, &npix);

  printf("write to file: flipped.bmp\n");
  writeFile("flipped.bmp", rows, cols, npix);
    
  free(pix);
  free(npix);
  return 0;
}
