#include "Book.h"
#include <iostream>
using namespace std;

Book::Book():isbn(""), last(""), first(""), title(""), category(Book::Category::NONE){}

Book::Book(string _isbn, string _last, string _first, string _title, string _categoryStr, Category _category):isbn(_isbn), last(_last), first(_first), title(_title), categoryStr(_categoryStr), category(_category){}

ostream& operator << (ostream& out, Book& book)
{
   out << "Book{ISBN=" << book.isbn << ", last=" << book.last << ", first=" << book.first << ", title=" << book.title << ", category=" << book.categoryStr << "}";
   return out;
}

istream& operator >> (istream& in, Book& book)
{
    
    getline (in, book.isbn, ',');
    getline (in, book.last, ',');
    getline (in, book.first, ',');
    getline (in, book.title, ',');
    getline (in, book.categoryStr);

   //  FICTION, HISTORY, TECHNICAL, NONE
    if (book.categoryStr == "fiction") book.category = Book::Category::FICTION;
    else if (book.categoryStr == "history") book.category = Book::Category::HISTORY;
    else if (book.categoryStr == "technical") book.category = Book::Category::TECHNICAL;
    else  book.category = Book::Category::NONE;

   //  Book book1(_isbn, _last, _first, _title, _categoryStr, _category);
    return in;
}

string Book::get_isbn(){return isbn;}

string Book::get_author(){return last;}

string Book::get_category(){return categoryStr;}

Book::~Book(){}