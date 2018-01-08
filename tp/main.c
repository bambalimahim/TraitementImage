#include <stdio.h>
#include <stdlib.h>
#include "pixmap_io.h"

int max5(int nb1, int nb2, int nb3, int nb4, int nb5, int nb6, int nb7, int nb8, int nb9){
	return (nb1|nb2|nb3|nb4|nb5|nb6|nb7|nb8|nb9);
}

int min5(int nb1, int nb2, int nb3, int nb4, int nb5, int nb6, int nb7, int nb8, int nb9){
	return (nb1&nb2&nb3&nb4&nb5&nb6&nb7&nb8&nb9);
}

unsigned char* dilatation(int** image, int width, int height){
  unsigned char *data = (unsigned char *)malloc(width*height);
  int l = 0, i, j;
  for (i = 1; i <= width; ++i)
  {
    for (j = 1; j <= height; ++j)
    {
      data[l] = (max5(image[i][j], image[i][j-1], image[i][j+1], image[i+1][j+1],
        image[i+1][j], image[i+1][j-1], image[i-1][j-1], image[i-1][j], image[i-1][j+1]) == 1)?255:0;l ++;
    }
  }
  return data;
}

unsigned char* erosion(int** image, int width, int height){
  unsigned char *data = (unsigned char *)malloc(width*height);
  int l = 0, i, j;
  for (i = 1; i <= width; ++i)
  {
    for (j = 1; j <= height; ++j)
    {
      data[l] = (min5(image[i][j], image[i][j-1], image[i][j+1], image[i+1][j+1],
        image[i+1][j], image[i+1][j-1], image[i-1][j-1], image[i-1][j], image[i-1][j+1]) == 1)?255:0;l ++;
    }
  }
  return data;
}

void menu(){
  printf("*****************************************************\n");
  printf("**************** 1: Dilatation **********************\n");
  printf("**************** 2: Erosion *************************\n");
  printf("**************** 3: Ouverture ***********************\n");
  printf("**************** 4: Fermeture ***********************\n");
  printf("*****************************************************\n");
}


int main(int argc, char **argv)
{
  unsigned char *data;

  int width, height, i, j = 0, l = 0;
  unsigned char *sortie = (unsigned char *)malloc(width*height);
  if( (argc > 1) && ((data = load_pixmap(argv[1], &width, &height)) != NULL) )
  	printf("Chargement image reussi\n");
  else{
    printf("error de chargement de l'image\n");
    exit(-1);
  }

  //store_pixmap("clone.pgm", data, width, height);
  
  int** image;
  image = (int**)malloc((width+2)*sizeof(int**));
  for (i = 0; i < width+2; ++i)
  {
    image[i] = (int*)malloc((height+2)*sizeof(int*));
  }
  
  for (i = 0; i < width+2; ++i)
  {
  	image[i][0] = 0;
  	image[i][height+1] = 0;
  }
  for (i = 0; i < height+2; ++i)
  {
  	image[0][i] = 0;
  	image[width+1][i] = 0;
  }
  for (i = 1; i <= width; ++i)
  {
  		for (j = 1; j <= height; ++j)
  			{
  				image[i][j] = (data[l] == 255)?1:0;
  				l ++;
  			}	
  }
  
  menu();
  int choix;
  depart:
  printf("Donner votre choix = ");
  scanf("%d", &choix);
  if (choix < 1 || choix > 4)
  {
    printf("Le choix n'est valide\n");
    goto depart;
  }
  switch(choix){
    case 1:
      sortie = dilatation(image, width, height);
    break;
    case 2:
      sortie = erosion(image, width, height);
    break;
    case 3:
      l = 0;
      sortie = erosion(image, width, height);
      for (i = 1; i <= width; ++i)
      {
        for (j = 1; j <= height; ++j)
          {
            image[i][j] = (sortie[l] == 255)?1:0;
            l ++;
          } 
      }
      sortie = dilatation(image, width, height);
    break;
    case 4:
      l = 0;
      sortie = dilatation(image, width, height);
      for (i = 1; i <= width; ++i)
      {
        for (j = 1; j <= height; ++j)
          {
            image[i][j] = (sortie[l] == 255)?1:0;
            l ++;
          } 
      }
      sortie = erosion(image, width, height);
    break;
  }
  store_pixmap("sortie.pgm", sortie, width, height);
 
  
 
  //store_pixmap("erosion.pgm", data2, width, height);
}