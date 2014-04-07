// dictionary.cpp : main project file.

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "sqlite3.h"
using namespace System;

typedef int (*sqlite3_callback)(
	void*,    /* Data provided in the 4th argument of sqlite3_exec() */
	int,      /* The number of columns in row */
	char**,   /* An array of strings representing fields in the row */
	char**    /* An array of strings representing column names */
);

static char mainPrompt[20] = "<Dictionary> ";
#define WORDLENGTH 50

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int searchWord(char word[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   char *sql;
   int rc;
   const char* data = "Callback function called";

   rc = sqlite3_open("dictionary.sqlite3", &db);
   if( rc ){
      printf("Can't open database: %s\n", sqlite3_errmsg(db));
	  printf("%s","error");
   }else{
      printf("Opened database successfully\n");
   }
   /* Create SQL statement */
   sql = strcat(strcat("SELECT * from wordsgrep_word where name = '",word),"'");

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      printf("%d",rc);
      printf("SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      printf("Operation done successfully\n");
   }
   sqlite3_close(db);
   getch();
   return 0;
}

void quit() // write error message and quit
{
    printf("memory exhausted\n");
    exit(1);
}

int getWord()
{
    int max = WORDLENGTH;
    char* word = (char*)malloc(max); // allocate buffer
    if (word == 0) quit();

    char prompt[]= "1) Press Tab for autocompleting words\n Press CTRL-C for finish execution\n\n";
	printf("%s",prompt);
	printf("%s",mainPrompt);

    while (true) { // skip leading whitespace
        int c = getchar();
        if (c == EOF) break; // end of file
        if (!isspace(c)) {
             ungetc(c, stdin);
             break;
        }
    }

    int i = 0;
    while (true) {
        int c = getchar();
        if (isspace(c) || c == EOF) // at end, add terminating zero
            name[i] = 0;
            break;
        }
        name[i] = c;
        if (i==max-1) { // buffer full
            max = max+max;
            name = (char*)realloc(name,max); // get a new and larger buffer
            if (name == 0) quit();
        }
        i++;
    }

    printf("The filename is %s\n", name);
    free(filename); // release memory
    return 0;
}

int main(int argc, char* argv[]){
	char word[50];
	int wordlen = 0;
	printf("%s",prompt);
	while(c=getchar()){
		char prompt[]= "1) Press Tab for autocompleting words\n Press CTRL-C for finish execution";
		printf("%s",prompt);
	}
}
