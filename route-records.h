#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H

typedef enum SearchType{ ROUTE, ORIGIN, DESTINATION, AIRLINE} SearchType;

typedef struct RouteRecord
{
  char origin[3];
  char dest[3];
  char airline[2];
  int passenger[6];
}RouteRecord;

#endif
