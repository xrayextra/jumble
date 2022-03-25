#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE1 "5LetterWords.txt"
#define FILE2 "6letterwords.txt"

#define MAXLEN 10

void ProcessWords( FILE *fptr5, char letters[] );

/*
 * Does the daily Jumble for 5 or 6 letter words.  Requires letters in command line.
 */
int main( int argc, char *argv[] )
{
  FILE *fptr5 = fopen( FILE1, "r");
  FILE *fptr6 = fopen( FILE2, "r");
  
  if( !fptr5 )
  {
    fprintf( stderr, "ERROR: could not open %s, exiting...\n", FILE1);
    exit( EXIT_FAILURE );
  }
  if( !fptr6 )
  {
    fprintf( stderr, "ERROR: could not open %s, exiting...\n", FILE2);
    exit( EXIT_FAILURE );
  }
  if( (argc != 2) || ((strlen(argv[1]) < 5) || (strlen(argv[1]) > 6)) )
  {
    fprintf( stdout, "Usage: ./jumble letters\nWhere \"letters\" is a list of letters either five or six characters long.\n" );
    fprintf( stdout, "argc = %d, argv[1] = %s\n", argc, argv[1] );
    exit( EXIT_FAILURE );
  }
  if( strlen(argv[1]) == 5 )
    ProcessWords( fptr5, argv[1] );
  else if( strlen( argv[1] ) == 6 )
    ProcessWords( fptr6, argv[1] );

  fclose( fptr5 );
  fclose( fptr6 );

  return EXIT_SUCCESS;
}

/* Reads words from a file and compares to the set of letters
 * to see if it can find a word from the given letters.
 */
void ProcessWords( FILE *fptr, char letters[] )
{
  char tempstr[MAXLEN];  // temporary string to hold letters
  char lr[MAXLEN];       // letter remaining
  char *cptr;            // character pointer
  char word[MAXLEN];     // first word
  int i;                 // index variables
  int found=1;           // found marker
  
  while( fscanf( fptr, "%s", word ) != EOF )
  {
    found=1;
    strcpy( lr, letters );
    for( i=0; i<strlen( word ) && found; i++ )
    {
      cptr = strchr( lr, word[i] );
      if( cptr )
      {
          *cptr++ = '\0';
          strcpy( tempstr, cptr );
          strcat( lr, tempstr );
      } // end if
      else // word has letters not in the list of letters so reset letters and set found to false
      {
        found=0;
      }
    } // end for;
    if( found )
    {
      fprintf( stdout, "Word found: %s\n", word );
    } //end if
  } //end while
  return;
} // end ProcessWords
