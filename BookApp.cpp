#include "Book.h"
#include <iostream>
#include <vector>
#include <fstream>
/***** Complete this file. *****/

using namespace std;

// Status codes.
enum class StatusCode {OK, DUPLICATE, NOT_FOUND, INVALID_COMMAND};

/**
 * Find the book in the catalog with the given ISBN.
 * Use a binary search.
 * @param isbn the ISBN.
 * @param catalog the vector of book records.
 * @return the vector index of the book if found, else return -1.
 */
int find(const string isbn, const vector<Book>& catalog);

const string INPUT_FILE_NAME = "commands.in";

/**
 * The main. Open the command input file and loop to process commands.
 */
int main()
{
    // Open the input file.
    ifstream input;
    input.open(INPUT_FILE_NAME);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FILE_NAME << endl;
        return -1;
    }

    vector<Book> catalog;  // book catalog

    char command;
    input >> command;  // read the first command

    /**
     * Loop to read commands until the end of file.
     */
    while (!input.fail())
    {
       cout << endl << command << " ";

       if(command == '+'){
          input >> ws;
          Book book1;
          int index, result;
          input >> book1;
          if (catalog.size() == 0)
          {
             catalog.insert(catalog.begin(), book1);
             cout << "Inserted at index 0: "<< book1 << endl;
          }
          else
          {
             //find existed book index or the index should be inserted at
             string search_isbn = book1.get_isbn();

            if(search_isbn.compare(catalog[0].get_isbn()) == 0)
            {
                cout << "Inserted at index 0: " << book1 << endl;
                cout << "*** Duplicate ISDN ***" << endl;
            }
            else
            {
                result = find(search_isbn, catalog);
                if (result <= 0) //book not exist, insert the book
                {
                   index = -result;
                   catalog.insert(catalog.begin() + index, book1);
                   cout << "Inserted at index " << index << ": "<< book1 << endl;
                }
                else //book exist, not insert
                {
                   index = result;
                   cout << "Inserted at index " << index << ": "<< book1 << endl;
                   cout << "*** Duplicate ISDN ***" << endl;
                }
            }
          }
       }
       else if(command == '-'){
          //remove the book from catalog
	  input >> ws;
	  string search_isbn = "";
	  getline (input, search_isbn);
          if(search_isbn.compare(catalog[0].get_isbn()) == 0)
          {
              cout << "Removed " << catalog[0] << endl;
              catalog.erase(catalog.begin());
          }
          else
          {
              int result = find(search_isbn, catalog);
              if (result <= 0) //book not exist, error
              {
                 Book book1(search_isbn, "", "", "", "none", Book::Category::NONE);
                	 cout << "Removed " << book1 << endl;
                 cout << "*** Book not found ***"<< endl;
              }
              else //book exist, remove
              {
                 int index = result;
                 cout << "Removed " << catalog[index] << endl;
                 catalog.erase(catalog.begin() + index);
              }
          }
       }
       else if(command == '?'){
          //search and print the required book
          string search = "";
          getline (input, search);
//          list all books in catalog
          if (search.compare("") == 0 )
          {
	     cout << "All books in the catalog:" << endl;
	     for (int i = 0; i < catalog.size() ;i++ )
	     {
		cout << catalog[i] << endl;
	     }
          }
          else
//           search with requirement
          {
        	  	  int pos = search.find("=");
        	  	  string search_str = search.substr(pos + 1);
        	  	  if(pos == 5)
        	  	  {
        	  		cout << "Book with ISBN " << search_str << ":" << endl;
        	  	          if(search_str.compare(catalog[0].get_isbn()) == 0)
        	  	          {
        	  	              cout << catalog[0] << endl;
        	  	          }
        	  	          else
        	  	          {
        	  	              int result = find(search_str, catalog);
        	  	              if (result > 0) //book exist, print book
        	  	              {
        	  	                 int index = result;
        	  	                 cout << catalog[index] << endl;
        	  	              }
        	  	          }
        	  	  }
        	  	  else if (pos == 7)
        	  	  {
        	  		cout << "Books by author " << search_str << ":"<< endl;
			     for (int i = 0; i < catalog.size() ;i++ )
			     {
				if (search_str.compare(catalog[i].get_author()) == 0) cout << catalog[i] << endl;
			     }
        	  	  }
        	  	  else if(pos == 9)
        	  	  {
        	  		cout << "Books in category " << search_str << ":"<< endl;
   			     for (int i = 0; i < catalog.size() ;i++ )
   			     {
   				if (search_str.compare(catalog[i].get_category()) == 0) cout << catalog[i] << endl;
   			     }
        	  	  }
        	  	  else  cout << "*** Invalid command ***" << pos << endl;
          }
       }
       else
       {
	       cout << "*** Invalid command ***" << endl;
	       char next;
	       while(input.get(next))
	       {
	           if (next == '\n')
	           {    break;
	           }
	       }
       }
       input >> command;
     }

    return 0;
}

int find(const string isbn, const vector<Book>& catalog)
{
  string search = isbn.substr(4);
  int value = stoi (search);
  if (value < 0) value = -value;
  int low = 0;
   int high = catalog.size() - 1;

    while (low <= high) {
       int mid = (low + high)/2;
       Book mid_book = catalog[mid];
       string mid_isbn = mid_book.get_isbn();
       string mid_search = mid_isbn.substr(4);
       int mid_value = stoi (mid_search);
       if (mid_value < 0) mid_value = -mid_value;

       if (value == mid_value) {
            return mid;
       }
       else if (value < mid_value) {
          high = mid-1;
       }
       else {
         low = mid+1;
       }
    }
    return -low;
}