#include <stdio.h>
#include "drive.h"

int main(void) 
{
  Drive* d = newDrive();
  printf("%s",displayDrive(d));
  for (int i=0; i <16; i++)
  {
    printf("block %d is used: %d\n",i,isUsed(d,i));
    }
}