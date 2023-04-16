The project is to load data through a CSV file and write program that will conduct a variety of queries on that data.

Dataset

The dataset (attached) is a modified CSV file on all International flight departing from US Airports between January and June 2020 reported by the US Department of Transportation (https://data.transportation.gov/Aviation/International_Report_Passengers/xgub-n9bw). Each record holds a route (origin to destination) operated by an airline. This CSV file was modified to keep it simple and relatively smaller. Here is a description of each column:
   • Column1–Month(1–January,2–February,3–March,4–April,5–May,6–June)
   • Column 2 – 3-letter IATA Airport Code for the origin airport (e.g., SAT for San Antonio International Airport)
   • Column 3 – 3-letter IATA Airport Code for the destination airport
   • Column 4 – 2-letter IATA Airline Code for the airline (e.g., AA for American Airlines).
   • Column 5 – The passenger category, in our example, there is only one category.
   • Column 6 – Total number of passengers in that month for that route
Note that there is a header row you must skip. Since this data holds passenger statistics for each route operated by an airline for six months, you should see the airline route repeated six times. For example, you will see the JFK to LHR operated by BA route 6 times, once for each of the six months.

Task 1 – create route-records.h

All data is loaded into an array of RouteRecord’s which will they be queried in main().
   • Create a struct named RouteRecord that will hold information about a route that is operated by one airline. The struct will have the following data members: 
      o Origin airport code
      o Destination airport code
      o Airline code
      o Array of passenger counts. There are six months’ worth of data for each route. (Index 0 will represent January’s passenger count, Index 1 will represent February’s passenger count, etc.).
   • Add the header guards and prototypes for the functions (see Task 2)
   • Include this enum in your header file so you can use as values for determining what type of search you will conduct.
     typedef enum SearchType { ROUTE, ORIGIN, DESTINATION, AIRLINE } SearchType;
     
Task 2 – create route-records.c

Write the following functions:
   • RouteRecord*createRecords(FILE*fileIn)–Thisfunctioncreates the array of RouteRecord’s and initializes it. The function takes in a file pointer. The function will do the following:
      o This function goes through the CSV file and counts the number of total records (not including the header)
      o DynamicallyallocatememoryforanarrayofRouteRecord’sbasedonthe count.
      o EachRouteRecordstructobjecthasanarrayof6integerstoholdthenumber of passengers for six months. Initialize each of these integer values to 0. You do not need to initialize the other data members in the struct.
      o Rewind the file pointer
      o Return the pointer to the array you dynamically allocated.
      
   • intfillRecords(RouteRecord*r,FILE*fileIn)–Thisfunction will process the data in the CSV file. Essentially, the code will go through each record, parse out the record, and enter it into the array. The function will follow these rules:
      o ThefunctionwillcallfindAirlineRoute()toseeiftheexactroutewiththe origin, destination, and airline was already entered in the array. If it was found, then you will update the existing record in your array with the passenger data for that month. Recall there should be six entries (one for each month) for each route operated by an airline. If the route operated by the airline does not already exist in the array, add this new route to the array.
      o ThefunctionreturnstheactualnumberofRouteRecord’susedinthearray. The value returned will be less than the size of the array created since not all records in the original CSV file will be entered into the array.
      
   • intfindAirlineRoute(RouteRecord*r,intlength,const char* origin, const char* destination, const char* airline, int curIdx ) – This RECURSIVE function finds a record in the RouteRecord array with the same origin and destination airport codes and airline. It returns the index number in which these three strings appear in the array. The function will return -1 if it cannot find these three strings in the same struct object.
  
   • voidsearchRecords(RouteRecord*r,intlength,constchar* key1, const char* key2, SearchType st ) – This function searches the RouteRecord array and prints out the results of the search.
      o You will traverse the array and compare specific data members against the keys.
      o TheparameterstdeterminesifthefunctionissearchingbyROUTE,ORIGIN, DESTINATION, AIRLINE.
      o ForORIGIN,DESTINATION,AIRLINE,key1willholdthevalueyouare looking for. For ROUTE, you are searching both the origin and destination and airport, so key1 and key2 will hold those values, respectively, that you will use to compare against the data members. For example, if the search is by the destination: st will be equal to DESTINATION, key1 will have an airport code that the user entered, and you will compare each struct’s destination data member against the airport code.
      o You will print out the airline and the route for each matching value. Then, you will print out the total number of passengers on all matching records, total number of passengers by month for all matching records, as well as average numbers of passengers per month. Note that you must handle any instances where you the search has 0 results.
      
   • voidprintMenu()–Thisfunctionprintsthemenu.Hereisthefunctionbelow.Be sure to add this prototype to the header file.
   
          void printMenu()
          {
               printf( "\n\n######### Airline Route Records
               Database MENU #########\n" );
               printf( "1. Search by Route\n" );
               printf( "2. Search by Origin Airport\n" );
               printf( "3. Search by Destination Airport\n" );
               printf( "4. Search by Airline\n" );
               printf( "5. Quit\n" );
               printf( "Enter your selection: " );
         }
         
TASK 3: Complete the main.c

   • Download the attached main.c
   • Follow the instructions written in the comments in the main() function.
   • The main() is the driver of the program. It calls the functions above to load the data from the CSV file and to run queries that the user asks for.
   • The name of the file will be passed in through command line arguments.
   • The user will enter a numeric value from the menu. You must handle the case in which the user enters invalid values (e.g., strings).
   
Task 4: Create a makefile

Create a makefile to compile and link all the files together. The grader will compile your code using your makefile.
