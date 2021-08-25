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
  // /* THIS IS THE METHOD THAT YOU SHOULD WRITE */

  int row, col;
  int new_pos = 0;
  int old_pos = 0;

  if((rows <= 0) || (cols <= 0)) return -1;

  *newrows = (int)rows * 2;
  *newcols = (int)cols * 2;

  *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));

  /*
  for (row=0; row < (*newrows); row++){
    for (col=0; col < (*newcols); col++) {
      printf("========================\n");
      
      if (old_pos == 512)
      {
        old_pos = 0;
      } else if (new_pos%2 == 0 && new_pos != 0 && new_pos != 1)
      {
        old_pos++;
      }
      
      
      // if (new_pos%2 == 0 && new_pos != 0 && new_pos != 1)
      //   old_pos++;

      //(*new)[new_pos] = original[(row * rows / (*newrows))  * cols + col * cols / (*newcols)];
      (*new)[new_pos] = original[old_pos];
        printf("new_pos = %d\n", new_pos);
        printf("old_pos = %d\n", old_pos);
        printf("old_old_pos = %d\n", (row * rows / (*newrows))  * cols + col * cols / (*newcols));
        printf("row = %d\n", row);
        printf("col = %d\n", col);

      // (*new)[new_pos] = original[old_pos];
      new_pos++;

      //printf("old_pos = %d\n", old_pos);

      
      
    }
  }
  */

  for (row = 0; row < rows; row++)
  {
    for (col = 0; col < cols; col++)
    {
      PIXEL *o = original + row * cols + col;
      for (int j = 0; j < 2; j++)
      {
        for (int i = 0; i < 2; i++)
        {
          PIXEL *n = (*new) + (row * 2 + i) * (*newcols) + (col * 2 + j);
          *n = *o;

          printf("value = %d\n", (row * 2 + i) * (*newcols) + (col * 2 + j));

          // (*new)[new_pos] = original[(row * 2 + i) * (*newcols) + (col * 2 + j)];
          // new_pos++;
        }
      }
    }
  }

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

  for (row=0; row < rows; row++){
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col; //changes by 3 bits every time (RGB)
      PIXEL* n = (*new) + row*cols + (cols-1-col); //changes by 3 bits every time (RGB)
      *n = *o;
    }
  }

  return 0;
}

int main()
{
  int rows, cols;
  PIXEL *pix, *npix;

  printf("read from file: example.bmp\n");
  readFile("example.bmp", &rows, &cols, &pix);

  // printf("flip image horizontally\n");
  // flip(pix, rows, cols, &npix);

  // printf("write to file: flipped.bmp\n");
  // writeFile("flipped.bmp", rows, cols, npix);

  printf("resize image\n");
  process(pix, rows, cols, 0, &npix, &rows, &cols);

  printf("write to file: resized.bmp\n");
  writeFile("resized.bmp", rows, cols, npix);

  free(pix);
  free(npix);
  return 0;
}
