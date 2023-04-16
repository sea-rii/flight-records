#include "route-records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RouteRecord* createRecords( FILE* fileIn)
{
   int count = 0;
   char buffer[80];
   if (fgets(buffer, 80, fileIn) == NULL)
   {
      printf("Error: file is empty! \n");
   }
  
   while (fgets(buffer, 80, fileIn) != NULL)
   {
      count++;
   }

   RouteRecord* r = (RouteRecord*)malloc(sizeof(RouteRecord) * count);
   int i;
   int j;

   for (i=0; i<count; ++i)
   {
      for (j=0; j<6; ++j)
      {
         r[i].passenger[j] = 0;
      }
   }

   rewind(fileIn);
   return r;

}

int fillRecords(RouteRecord* r, FILE* fileIn)
{
   int size = -1;
   int month;
   char origin[3];
   char dest[3];
   char airline[2];
   char type[20];
   int total;

   char buffer[80];

   if (fgets(buffer, 80, fileIn) == NULL)
   {
      printf("Error: file is empty!\n");
   }
   while (fgets(buffer, 80, fileIn) != NULL)
   {
      sscanf(buffer, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, origin, dest, airline, type, &total);
      if (findAirlineRoute(r, size, origin, dest, airline, 0) == -1)
      {
          // create a new entry
          size++;
          strcpy(r[size].origin, origin);
          strcpy(r[size].dest, dest);
          strcpy(r[size].airline, airline);
          r[size].passenger[month] = total;
      }
      else 
      {
        // update
          r[findAirlineRoute(r, size, origin, dest, airline, 0)].passenger[month] += total;
      }
   }
   return (size+1);
}

int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* dest, const char* airline, int curIdx)
{
   if (curIdx > length)
   {
      return -1;
   }
   else 
   {
      if ((strcmp(origin, r[curIdx].origin) == 0) && (strcmp(dest, r[curIdx].dest) == 0) && (strcmp(airline, r[curIdx].airline) == 0))
      {
          return curIdx;
      }
      else
      {
          findAirlineRoute(r, length, origin, dest, airline, curIdx+1);
      }
   }
}

void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st)
{
   int i;
   int matched = 0;
   int passengers[6] = {0, 0, 0, 0, 0, 0};
   int j;
   if (st == ORIGIN)
   {
     printf("Searching by origin...\n");
     for (i=0; i <length; ++i)
     {
        if (strcmp(key1, r[i].origin) == 0)
        {
           matched++;
           printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].dest);
           for (j=0; j<6; ++j)
           {
               passengers[j] += r[i].passenger[j];
           }
        }
     }
     printf("%d matches were found.\n", matched);
   }

   if (st == DESTINATION)
   {
      printf("Searching by destination...\n");
      for (i=0; i<length; ++i)
      {
         if (strcmp(key1, r[i].dest) == 0)
         {
           matched++;
           printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].dest);
           for (j=0; j < 6; ++j)
           {
              passengers[j] += r[i].passenger[j];
           }
         }
      }
      printf("%d matches were found.\n", matched);
   }
  
   if (st == AIRLINE)
   {
     printf("Searching by airline...\n");
     for (i=0; i < length; ++i)
     {
        if (strcmp(key1, r[i].airline) == 0)
        {
          matched++;
          printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].dest);
          for (j=0; j <6; ++j)
          {
             passengers[j] += r[i].passenger[j];
          }
        }
     }
     printf("%d matches were found.\n", matched);
   }

  if (st == ROUTE)
  {
    printf("Searching by route...\n");
    for (i=0; i < length; ++i)
    {
       if ((strcmp(key1, r[i].origin) == 0) && (strcmp(key2, r[i].dest) == 0))
       {
         matched++;
         printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].dest);
         for (j=0; j < 6; ++j)
         {
            passengers[j] += r[i].passenger[j];
         }
       }
    }
    printf("%d matches were found.\n", matched);
  }

  printf("total = %d\n", passengers[0]+passengers[1]+passengers[2]+passengers[3]+passengers[4]+passengers[5]);
  for (i=0; i < 6; ++i)
  {
    printf("month %d = %d\n", i+1, passengers[i]);
  }
  
}

void printMenu()
{
   printf("\n\n######### Airline Route Records Database MENU #########\n");
   printf("1. Search by Route\n");
   printf("2. Search by Origin Airport\n");
   printf("3. Search by Destination Airport\n");
   printf("4. Search by Airline\n");
   printf("5. Quit\n");
   printf("Enter your selection: ");
}




