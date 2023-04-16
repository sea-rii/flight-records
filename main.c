#include "route-records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
   FILE* f = NULL;
   if (argc < 2)
   {
     printf("ERROR: Missing file name and end the program\n");
     return 1;
   }
 
   f =fopen(argv[1], "r");
   if (f == NULL)
   {
      printf("Error: could not open the file! \n");
      return 2;
   }   

   RouteRecord* r = createRecords(f);
   int size = fillRecords(r, f);
   printf("number of unique routes = %d\n", size);

   fclose(f);

   char ch;
   char key1[8];
   char key2[8];
   do {
      printMenu();
      scanf("%c", &ch);
      if ((ch != '1') && (ch != '2') && (ch != '3') && (ch != '4') && (ch != '5'))
      {           
         printf("Error: invalid values\n");
      }
      else 
      {
         if (ch == '1')
         {
           printf("Enter origin: ");
           scanf("%[^\n]", key1);
           printf("Enter destination: \n");
           scanf("%[^\n]", key2);
           searchRecords(r, size, key1, "dummy", ORIGIN);
         }

        if (ch == '2')
        {
          printf("Enter origin: \n");
          scanf("%[^\n]", key1);
          searchRecords(r, size, key1, "dummy", ORIGIN);
        }

        if (ch == '3')
        {
          printf("Enter destination: \n");
          scanf("%[^\n]", key1);
          searchRecords(r, size, key1, "dummy", DESTINATION);
        }
     
        if (ch == '4')
        {
          printf("Enter airlie: \n");
          scanf("%[^\n]", key1);
          searchRecords(r, size, key1, "dummy", AIRLINE);
        }
     }

   }while(ch != 5);

   return 0;
}

