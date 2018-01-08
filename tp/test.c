#include<stdio.h>
#include<stdlib.h>
#include"fct.h"

int max5(int nb1, int nb2, int nb3, int nb4, int nb5, int nb6, int nb7, int nb8, int nb9){
  return (nb1|nb2|nb3|nb4|nb5|nb6|nb7|nb8|nb9);
}

int main(int argc, char **argv){

       int *image;
       char nom[20],p[20];
       char nomOut[20];
    int nbc,nbl,max, i, j, l;
       FILE *ff;
       image=(int*)malloc(nbc*nbl*sizeof(*image));
       


       ff=fopen(argv[1],"r");
       if(ff==NULL){
                    printf("nulll");
                  }
       fscanf(ff,"%s\n%d %d\n%d",p,&nbl,&nbc,&max);

   int sortie[nbl+2][nbc+2];
   Lire(argv[1],image,nbl,nbc,max);
    for (i = 0; i < width+2; ++i)
    {
      sortie[i][0] = 0;
      sortie[i][height+1] = 0;
    }
    for (i = 0; i < height+2; ++i)
    {
      sortie[0][i] = 0;
      sortie[width+1][i] = 0;
    }


int *data1 = (unsigned char *)malloc(width*height);
unsigned char *data2 = (unsigned char *)malloc(width*height);
  for (i = 1; i <= nbl; ++i)
  {
      for (j = 1; j <= nbc; ++j)
        {
          sortie[i][j] = (image[l] == 255)?1:0;
          l ++;
        } 
  }

// dilatation
  l = 0;
  for (i = 1; i <= nbl; ++i)
  {
    for (j = 1; j <= nbc; ++j)
    {
      data1[l] = (max5(sortie[i][j], sortie[i][j-1], sortie[i][j+1], sortie[i+1][j+1],
        sortie[i+1][j], sortie[i+1][j-1], sortie[i-1][j-1], sortie[i-1][j], sortie[i-1][j+1]) == 1)?255:0;l ++;
    }
  }


                                      //



       printf("donnnez nomOut \n");
       scanf("%s",nomOut);

       Save("dilatation.pgm",data1,nbl,nbc,max);


system("PAUSE");
return 0;
}