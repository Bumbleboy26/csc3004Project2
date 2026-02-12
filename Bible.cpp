/* Bible class function definitions
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * NOTE: You may add code to this file, but do not
 * delete any code or delete any comments.
 *
 * STUDENT NAME: Coen Hall
 */

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Default constructor
Bible::Bible()
{ 
   infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, LookupResult& status)
{ 
   // TODO: scan the file to retrieve the line that holds ref ...
     
   // update the status variable
   status = OTHER; // placeholder until retrieval is attempted
	
   // create and return the verse object
   Verse aVerse;   // default verse, to be replaced by a Verse object
	                // that is constructed from a line in the file.

   if(!instream.is_open())
   {
      instream.open(infile.c_str());
      if(!instream.is_open())
      {
         status = OTHER;
         return(aVerse);
      }
   }

   bool foundBook = false;
   bool foundChapter = false;

   instream.clear();
   instream.seekg(0);

   string line;
   while(getline(instream, line))
   {
      Verse v(line);
      Ref r = v.getRef();
      
      if(r.getBook() == ref.getBook())
      {
         foundBook = true;
         
         if(r.getChapter() == ref.getChapter())
         {
            foundChapter = true;
            if(r == ref)
            {
               status = SUCCESS;
               aVerse = v;
               return(aVerse);
            }
         }
      }
   }

   if(!foundBook)
   {
      status = NO_BOOK;
   }
   else if(!foundChapter)
   {
      status = NO_CHAPTER;
   }
   else
   {
      status = NO_VERSE;
   }

   return(aVerse);
}

// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status)
{
   Verse verse;

   if(!instream.is_open())
   {
      instream.open(infile.c_str());
      isOpen = true;
      if(!instream.is_open())
      {
         status = OTHER;
         return verse;
      }
   }

   string line;
   
   if(getline(instream, line))
   {
      status = SUCCESS;
      verse = Verse(line);
   }
   else
   {
      status = OTHER;
   }

   return verse;
}

// REQUIRED: Return an error message string to describe status
string Bible::error(LookupResult status)
{
   if(status == SUCCESS)
   {
      return "Success.";
   }
   else if(status == NO_BOOK)
   {
      return "Book not found.";
   }
   else if(status == NO_CHAPTER)
   {
      return "Chapter not found.";
   }
   else if(status == NO_VERSE)
   {
      return "Verse not found.";
   }
   else if(status == OTHER)
   {
      return "An error has occurred.";
   }
   else
   {
      return "An unknown error has occurred.";
   }
}

void Bible::display()
{
   cout << "Bible file: " << infile << endl;
}
	
// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status)
{
   return ref;
}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status)
{
   return ref;
}
