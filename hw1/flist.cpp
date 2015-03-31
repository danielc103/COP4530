/*
    flist.cpp
    01/12/14
    Chris Lacher

    general test harness for fsu::List

    Copyright 2014, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <cctype>  // tolower()
#include <cmath>   // log2() called in some versions of List
#include <list.h>
#include <compare.h>
#include <xstring.h>
#include <xstring.cpp> // avoid separate build
#include <ansicodes.h> // color response in batch mode

// choose one from group A 

// =====================
// ===== group A =======
// =====================

// A1: makes lists of char
typedef char  ElementType;
const char ofc = '\0';
const char* vT = "char";
const char code0 = 'c';
// end A1 */

/* // A2: makes lists of CHAR
#include <CHAR.h>
typedef CHAR  ElementType;
const char ofc = '\0';
const char* vT = "char";
const char code0 = 'c';
// end A2 */

/* // A3: makes lists of String
#include <xstring.h>
#include <xstring.cpp> // in lieu of makefile
typedef fsu::String  ElementType;
const char ofc = ' ';
const char* vT = "String";
const char code0 = 's';
// end A3 */

/* // A4: makes lists of long
typedef long ElementType;
const char ofc = ' ';
const char* vT = "int";
const char code0 = 'i';
// end A4 */

typedef fsu::List < ElementType >       ContainerType;
typedef fsu::GreaterThan< ElementType > PredicateType;

void Preamble();
void DisplayContainerType(const char code0, const char code1 = '1');
void DisplayMenu();
void DisplayPrompt();

template < class C >
void CopyTest( C x )
{
  std::cout << "CopyTest:\n";
  std::cout << "Copied object size: " << x.Size() << '\n'
            << "              dump: ";
  x.Dump(std::cout, ofc);
  std::cout << '\n';
}

template < class C >
void AssignTest(const C& x)
{
  C x1;
  x1 = x;
  std::cout << "AssignTest:\n";
  std::cout << "Original object size: " << x.Size() << '\n'
            << "                dump: ";
  x.Dump(std::cout, ofc);
  std::cout << "Assignee object size: " << x1.Size() << '\n'
            << "                dump: ";
  x1.Dump(std::cout, ofc);
  std::cout << '\n';
}

template < class C >
void StructureTest(const C& x)
{
  x.CheckLinks();
}

void SkipDoc (std::istream& is)
{
  char ch = is.peek();
  while (ch == '#')
  {
    do ch = is.get();
    while (ch != '\n');
    ch = is.peek();
  }
}

int main( int argc, char* argv[] )
{
  bool BATCH = 0;
  if (argc > 1) BATCH = 1;

  // used to load data from a file
  fsu::String   datafile;
  std::ifstream dataistream;
  std::ofstream dataostream;

  // set up for command file / batch mode
  std::istream* isptr = &std::cin;
  std::ifstream ifs;
  if (BATCH)
  {
    ifs.open(argv[1]);
    if (ifs.fail())
    {
      std::cout << " ** Error: cannot open file " << argv[1] << '\n';
      return 0;
    }
    isptr = &ifs;
  }
  if (!BATCH) Preamble();
  if (!BATCH) DisplayMenu();
  ContainerType x1, x2, x3;
  ContainerType::Iterator i0, i1, i2, i3;
  ContainerType::ConstIterator ci;
  PredicateType pred;
  ElementType  Tval;
  char option;
  if (BATCH) SkipDoc(*isptr);
  do
  {
    DisplayPrompt();
    *isptr >> option;
    if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
    switch (option)
    {
      case '1': 
        *isptr >> option;
        if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
        switch (option)
        {
          case '1':   // void PushFront (T)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x1.PushFront(" 
		      << Tval
		      << ")\n";
	    x1.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x1.PushBack(" 
		      << Tval
		      << ")\n";
	    x1.PushBack(Tval);
            break;
        
          case '3':   // void Insert (t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x1.Insert(" 
		      << Tval
		      << ")\n";
	    i1 = x1.Insert(Tval);
            break;
        
          case 'i':   // Insert (i,t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x1.Insert(i1," 
		      << Tval
		      << ")\n";
	    i1 = x1.Insert(i1,Tval);
            break;

          case '4':   // void PopFront()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (x1.Empty())
            {  
              std::cout << "unable to pop: x1 is empty\n";
              break;
            }
            Tval = x1.Front();
            x1.PopFront();
            std::cout << Tval << " popped from front of x1\n";
            i1 = x1.Begin();
            break;
        
          case '5':   // void PopBack()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (x1.Empty())
            {  
              std::cout <<  "unable to pop: x1 is empty\n";
              break;
            }
            Tval = x1.Back();
            x1.PopBack();
            std::cout << Tval << " popped from back of x1\n";
            i1 = x1.rBegin();
            break;
        
          case '6':   // void Remove(t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            std::cout << x1.Remove(Tval) << " copies of " << Tval 
		      << " removed from x1\n";
            break;

          case 'r':   // void Remove(i)
            if (BATCH) std::cout << '\n';
            if (i1.Valid())
            {
	      std::cout << "  " << *i1 << " =  *i1\n";
              std::cout << "  i1 = x1.Remove(i1)\n";
	      i1 = x1.Remove(i1);
	      std::cout << "  " << *i1 << " =  *i1\n";
            }
	    else
	      std::cout << "  Unable to remove: i1 is invalid\n";
            break;

          case 'a':
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
	    if (x1.Empty())
	      std::cout << "x1 is empty: no front element\n";
            else
              std::cout << x1.Front() << " = x1.Front()\n";
            i1 = x1.Begin();
            std::cout << "  i1 = x1.Begin()\n";
            break;

          case 'z':
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
	    if (x1.Empty())
	      std::cout << "x1 is empty: no back element\n";
            else
              std::cout << x1.Back() << " = x1.Back()\n";
            i1 = x1.rBegin();
            std::cout << "  i1 = x1.rBegin()\n";
            break;

          case 'c':   // void Clear ()
            if (BATCH) std::cout << '\n';
            x1.Clear();
            i1 = x1.Begin();
            break;

          case '*': case '?':  // *i, i.Valid
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (i1.Valid())
              std::cout << "*i1 == " << *i1 << '\n';
            else
              std::cout << "i1 == NULL\n";
            break;
        
          case '^':   // *i = t
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            if (i1.Valid())
            {
              *i1 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update: iterator invalid\n";
            break;
        
          case 'R':   // void Reverse()
            if (BATCH) std::cout << '\n';
	    x1.Reverse();
            std::cout << "  x1.Reverse();\n";
	    break;

          case 'M': case 'm':  // Merge(list)
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
	    switch(option)
	    {
	      case '1':
		x1.Merge(x1);
		std::cout << "  x1.Merge(x1);\n";
		break;
	      case '2':
		x1.Merge(x2);
		std::cout << "  x1.Merge(x2);\n";
		break;
	      case '3':
		x1.Merge(x3);
		std::cout << "  x1.Merge(x3);\n";
		break;
	    }
	    break;

          case 'e':   // bool Empty()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            std::cout << "x1 is";
            if (!x1.Empty())
              std::cout << " NOT";
            std::cout << " empty\n";
            break;

	  case 'd':  case 'D': // Display
            if (BATCH) std::cout << '\n';
            DisplayContainerType(code0);
            std::cout << "  x1.Display(std::cout): ";
            x1.Display(std::cout,ofc);
            std::cout << '\n';
            break;
          
	  case 't':  case 'T': // traverse
            if (BATCH) std::cout << '\n';
            std::cout << "   Traverse x1: ";
            for (i0 = x1.Begin(); i0 != x1.End(); ++i0)
            {
              std::cout << ofc << *i0;
            }
            std::cout << '\n';
            std::cout << "  rTraverse x1: ";
            for (i0 = x1.rBegin(); i0 != x1.rEnd(); --i0)
            {
              std::cout << ofc << *i0;
            }
            std::cout << '\n';
            break;
          
          case 's': case 'S':  // unsigned int Size()
            if (BATCH) std::cout << '\n';
            std::cout << "  " << x1.Size() << " = x1.Size();\n";
	    break;

          case '<':   // void Sort()
            if (BATCH) std::cout << '\n';
	    x1.Sort();
            std::cout << "  x1.Sort();\n";
	    break;

          case '>':   // void Sort(p)
            if (BATCH) std::cout << '\n';
	    x1.Sort(pred);
            std::cout << "  x1.Sort(>);\n";
	    break;

          case '=':
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            switch(option)
            {
              case '1': 
		if (BATCH) std::cout << '\n';
		x1 = x1;
		i1 = x1.Begin();
		std::cout << "x1 = x1; i1 = x1.Begin();\n";
		break;
	      case '2':
		if (BATCH) std::cout << '\n'; 
		x1 = x2;
		i1 = x1.Begin();
		std::cout << "x1 = x2; i1 = x1.Begin();\n";
		break;
	      case '3':
		if (BATCH) std::cout << '\n';
		x1 = x3;
		i1 = x1.Begin();
		std::cout << "x1 = x3; i1 = x1.Begin();\n";
		break;
	      case '=':
	        *isptr >> option;
                if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
		std::cout << "  ";
		switch(option)
                {
                  case '1':
                    if (x1 == x1)
                      std::cout << "x1 == x1\n";
                    else
                      std::cout << "x1 != x1\n";
                    break;
                  case '2':
                    if (x1 == x2)
                      std::cout << "x1 == x2\n";
                    else
                      std::cout << "x1 != x2\n";
                    break;
                  case '3':
                    if (x1 == x3)
                      std::cout << "x1 == x3\n";
                    else
                      std::cout << "x1 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            switch(option)
            {
              case '1':
                if (x1 != x1)
                  std::cout << "x1 != x1\n";
                else
                  std::cout << "x1 == x1\n";
                break;
              case '2':
                if (x1 != x2)
                  std::cout << "x1 != x2\n";
                else
                  std::cout << "x1 == x2\n";
                break;
              case '3':
                if (x1 != x3)
                  std::cout << "x1 != x3\n";
                else
                  std::cout << "x1 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            switch(option)
            {
              case '+':
		if (BATCH) std::cout << '\n'; 
		++i1;
		std::cout << "  ++i1;";
		if (i1.Valid())
		  std::cout << "  " << *i1 << " = *i1;\n";
		else 
		  std::cout << "  false = i1.Valid();\n";
		break;
              case '=':
		*isptr >> option;
                if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
                switch(option)
		{
                  case '1':
		    x1 += x1;
                    std::cout << "  x1 += x1;\n";
                  break;
                  case '2':
		    x1 += x2;
                    std::cout << "  x1 += x2;\n";
                  break;
                  case '3':
		    x1 += x3;
                    std::cout << "  x1 += x3;\n";
                  break;
		}
		break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }  
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
            --i1;
	    std::cout << "  --i1;";
	    if (i1.Valid())
	      std::cout << "  " << *i1 << " = *i1;\n";
	    else 
	      std::cout << "  false = i1.Valid();\n";
	    break;

          case 'l': case 'L': // load file
            *isptr >> datafile;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << ' ' << datafile << ANSI_COLOR_RESET << '\n'; 
            dataistream.open(datafile.Cstr());
            if ( dataistream.fail() )
            {
              std::cout << " ** unable to open file " << datafile << '\n';
              dataistream.clear();
            }
            else
            {
              while (dataistream >> Tval)
                x1.PushBack(Tval);
              dataistream.clear();
              dataistream.close();
              std::cout << " Loaded data from file " << datafile << " at back of x1\n";
            }
            break;

          case 'w': case 'W': // write file
            *isptr >> datafile;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << ' ' << datafile << ANSI_COLOR_RESET << '\n'; 
            dataostream.open(datafile.Cstr());
            if ( dataostream.fail() )
            {
              std::cout << " ** unable to open file " << datafile << '\n';
              dataostream.clear();
            }
            else
            {
              for (ci = x1.Begin(); ci != x1.End(); ++ci)
                dataostream << *ci << '\n';
              dataostream.close();
              std::cout << " Written x1 data to file " << datafile << '\n';
            }
            break;

          default:
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
            do 
	    {
	      isptr->get(option);
	      if (BATCH)
              {
                std::cout << ANSI_COLOR_BOLD_RED;
                std::cout.put(option);
                std::cout << ANSI_COLOR_RESET;
              }
	    } 
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '1'
        break;

      case '2': 
        *isptr >> option;
        if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
        switch (option)
        {
          case '1':   // void PushFront (T)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x2.PushFront(" 
		      << Tval
		      << ")\n";
	    x2.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x2.PushBack(" 
		      << Tval
		      << ")\n";
	    x2.PushBack(Tval);
            break;
        
          case '3':   // void Insert (t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x2.Insert(" 
		      << Tval
		      << ")\n";
	    i2 = x2.Insert(Tval);
            break;
        
          case 'i':   // Insert (i,t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x2.Insert(i2," 
		      << Tval
		      << ")\n";
	    i2 = x2.Insert(i2,Tval);
            break;

          case '4':   // void PopFront()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (x2.Empty())
            {  
              std::cout << "unable to pop: x2 is empty\n";
              break;
            }
            Tval = x2.Front();
            x2.PopFront();
            std::cout << Tval << " popped from front of x2\n";
            i2 = x2.Begin();
            break;
        
          case '5':   // void PopBack()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (x2.Empty())
            {  
              std::cout <<  "unable to pop: x2 is empty\n";
              break;
            }
            Tval = x2.Back();
            x2.PopBack();
            std::cout << Tval << " popped from back of x2\n";
            i2 = x2.rBegin();
            break;
        
          case '6':   // void Remove(t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            std::cout << x2.Remove(Tval) << " copies of " << Tval 
		      << " removed from x2\n";
            break;

          case 'r':   // void Remove(i)
            if (BATCH) std::cout << '\n';
            if (i2.Valid())
            {
	      std::cout << "  " << *i2 << " =  *i2\n";
              std::cout << "  i2 = x2.Remove(i2)\n";
	      i2 = x2.Remove(i2);
	      std::cout << "  " << *i2 << " =  *i2\n";
            }
	    else
	      std::cout << "  Unable to remove: i2 is invalid\n";
            break;

          case 'a':
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
	    if (x2.Empty())
	      std::cout << "x2 is empty: no front element\n";
            else
              std::cout << x2.Front() << " = x2.Front()\n";
            i2 = x2.Begin();
            std::cout << "  i2 = x2.Begin()\n";
            break;

          case 'z':
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
	    if (x2.Empty())
	      std::cout << "x2 is empty: no back element\n";
            else
              std::cout << x2.Back() << " = x2.Back()\n";
            i2 = x2.rBegin();
            std::cout << "  i2 = x2.rBegin()\n";
            break;

          case 'c':   // void Clear ()
            if (BATCH) std::cout << '\n';
            x2.Clear();
            i2 = x2.Begin();
            break;

          case '*': case '?':  // *i, i.Valid
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (i2.Valid())
              std::cout << "*i2 == " << *i2 << '\n';
            else
              std::cout << "i2 == NULL\n";
            break;
        
          case '^':   // *i = t
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            if (i2.Valid())
            {
              *i2 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update: iterator invalid\n";
            break;
        
          case 'R':   // void Reverse()
            if (BATCH) std::cout << '\n';
	    x2.Reverse();
            std::cout << "  x2.Reverse();\n";
	    break;

          case 'M': case 'm':  // Merge(list)
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
	    switch(option)
	    {
	      case '1':
		x2.Merge(x1);
		std::cout << "  x2.Merge(x1);\n";
		break;
	      case '2':
		x2.Merge(x2);
		std::cout << "  x2.Merge(x2);\n";
		break;
	      case '3':
		x2.Merge(x3);
		std::cout << "  x2.Merge(x3);\n";
		break;
	    }
	    break;

          case 'e':   // bool Empty()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            std::cout << "x2 is";
            if (!x2.Empty())
              std::cout << " NOT";
            std::cout << " empty\n";
            break;

	  case 'd':  case 'D': // Display
            if (BATCH) std::cout << '\n';
            DisplayContainerType(code0);
            std::cout << "  x2.Display(std::cout): ";
            x2.Display(std::cout,ofc);
            std::cout << '\n';
            break;
          
	  case 't':  case 'T': // traverse
            if (BATCH) std::cout << '\n';
            std::cout << "   Traverse x2: ";
            for (i0 = x2.Begin(); i0 != x2.End(); ++i0)
            {
              std::cout << ofc << *i0;
            }
            std::cout << '\n';
            std::cout << "  rTraverse x2: ";
            for (i0 = x2.rBegin(); i0 != x2.rEnd(); --i0)
            {
              std::cout << ofc << *i0;
            }
            std::cout << '\n';
            break;
          
          case 's': case 'S':  // unsigned int Size()
            if (BATCH) std::cout << '\n';
            std::cout << "  " << x2.Size() << " = x2.Size();\n";
	    break;

          case '<':   // void Sort()
            if (BATCH) std::cout << '\n';
	    x2.Sort();
            std::cout << "  x2.Sort();\n";
	    break;

          case '>':   // void Sort(p)
            if (BATCH) std::cout << '\n';
	    x2.Sort(pred);
            std::cout << "  x2.Sort(>);\n";
	    break;

          case '=':
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            switch(option)
            {
              case '1': 
		if (BATCH) std::cout << '\n';
		x2 = x1;
		i2 = x1.Begin();
		std::cout << "x2 = x1; i2 = x2.Begin();\n";
		break;
	      case '2':
		if (BATCH) std::cout << '\n'; 
		x2 = x2;
		i2 = x2.Begin();
		std::cout << "x2 = x2; i2 = x2.Begin();\n";
		break;
	      case '3':
		if (BATCH) std::cout << '\n';
		x2 = x3;
		i2 = x2.Begin();
		std::cout << "x2 = x3; i2 = x2.Begin();\n";
		break;
	      case '=':
	        *isptr >> option;
                if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
		std::cout << "  ";
		switch(option)
                {
                  case '1':
                    if (x2 == x1)
                      std::cout << "x2 == x1\n";
                    else
                      std::cout << "x2 != x1\n";
                    break;
                  case '2':
                    if (x2 == x2)
                      std::cout << "x2 == x2\n";
                    else
                      std::cout << "x2 != x2\n";
                    break;
                  case '3':
                    if (x2 == x3)
                      std::cout << "x2 == x3\n";
                    else
                      std::cout << "x2 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            switch(option)
            {
              case '1':
                if (x2 != x1)
                  std::cout << "x2 != x1\n";
                else
                  std::cout << "x2 == x1\n";
                break;
              case '2':
                if (x2 != x2)
                  std::cout << "x2 != x2\n";
                else
                  std::cout << "x2 == x2\n";
                break;
              case '3':
                if (x2 != x3)
                  std::cout << "x2 != x3\n";
                else
                  std::cout << "x2 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            switch(option)
            {
              case '+':
		if (BATCH) std::cout << '\n'; 
		++i2;
		std::cout << "  ++i2;";
		if (i2.Valid())
		  std::cout << "  " << *i2 << " = *i2;\n";
		else 
		  std::cout << "  false = i2.Valid();\n";
		break;
              case '=':
		*isptr >> option;
                if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
                switch(option)
		{
                  case '1':
		    x2 += x1;
                    std::cout << "  x2 += x1;\n";
                  break;
                  case '2':
		    x2 += x2;
                    std::cout << "  x2 += x2;\n";
                  break;
                  case '3':
		    x2 += x3;
                    std::cout << "  x2 += x3;\n";
                  break;
		}
		break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }  
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
            --i2;
	    std::cout << "  --i2;";
	    if (i2.Valid())
	      std::cout << "  " << *i2 << " = *i2;\n";
	    else 
	      std::cout << "  false = i2.Valid();\n";
	    break;

          case 'l': case 'L': // load file
            *isptr >> datafile;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << ' ' << datafile << ANSI_COLOR_RESET << '\n'; 
            dataistream.open(datafile.Cstr());
            if ( dataistream.fail() )
            {
              std::cout << " ** unable to open file " << datafile << '\n';
              dataistream.clear();
            }
            else
            {
              while (dataistream >> Tval)
                x2.PushBack(Tval);
              dataistream.clear();
              dataistream.close();
              std::cout << " Loaded data from file " << datafile << " at back of x2\n";
            }
            break;

          case 'w': case 'W': // write file
            *isptr >> datafile;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << ' ' << datafile << ANSI_COLOR_RESET << '\n'; 
            dataostream.open(datafile.Cstr());
            if ( dataostream.fail() )
            {
              std::cout << " ** unable to open file " << datafile << '\n';
              dataostream.clear();
            }
            else
            {
              for (ci = x2.Begin(); ci != x2.End(); ++ci)
                dataostream << *ci << '\n';
              dataostream.close();
              std::cout << " Written x2 data to file " << datafile << '\n';
            }
            break;

          default:
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
            do 
	    {
	      isptr->get(option);
	      if (BATCH)
              {
                std::cout << ANSI_COLOR_BOLD_RED;
                std::cout.put(option);
                std::cout << ANSI_COLOR_RESET;
              }
	    } 
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '2'
        break;

      case '3': 
        *isptr >> option;
        if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
        switch (option)
        {
          case '1':   // void PushFront (T)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x3.PushFront(" 
		      << Tval
		      << ")\n";
	    x3.PushFront(Tval);
            break;
        
          case '2':   // void PushBack (T)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x3.PushBack(" 
		      << Tval
		      << ")\n";
	    x3.PushBack(Tval);
            break;
        
          case '3':   // void Insert (t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x3.Insert(" 
		      << Tval
		      << ")\n";
	    i3 = x3.Insert(Tval);
            break;
        
          case 'i':   // Insert (i,t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  x3.Insert(i3," 
		      << Tval
		      << ")\n";
	    i3 = x3.Insert(i3,Tval);
            break;

          case '4':   // void PopFront()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (x3.Empty())
            {  
              std::cout << "unable to pop: x3 is empty\n";
              break;
            }
            Tval = x3.Front();
            x3.PopFront();
            std::cout << Tval << " popped from front of x3\n";
            i3 = x3.Begin();
            break;
        
          case '5':   // void PopBack()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (x3.Empty())
            {  
              std::cout <<  "unable to pop: x3 is empty\n";
              break;
            }
            Tval = x3.Back();
            x3.PopBack();
            std::cout << Tval << " popped from back of x3\n";
            i3 = x3.rBegin();
            break;
        
          case '6':   // void Remove(t)
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            std::cout << x3.Remove(Tval) << " copies of " << Tval 
		      << " removed from x3\n";
            break;

          case 'r':   // void Remove(i)
            if (BATCH) std::cout << '\n';
            if (i3.Valid())
            {
	      std::cout << "  " << *i3 << " =  *i3\n";
              std::cout << "  i3 = x3.Remove(i3)\n";
	      i3 = x3.Remove(i3);
	      std::cout << "  " << *i3 << " =  *i3\n";
            }
	    else
	      std::cout << "  Unable to remove: i3 is invalid\n";
            break;

          case 'a':
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
	    if (x3.Empty())
	      std::cout << "x3 is empty: no front element\n";
            else
              std::cout << x3.Front() << " = x3.Front()\n";
            i3 = x3.Begin();
            std::cout << "  i3 = x3.Begin()\n";
            break;

          case 'z':
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
	    if (x3.Empty())
	      std::cout << "x3 is empty: no back element\n";
            else
              std::cout << x3.Back() << " = x3.Back()\n";
            i3 = x3.rBegin();
            std::cout << "  i3 = x3.rBegin()\n";
            break;

          case 'c':   // void Clear ()
            if (BATCH) std::cout << '\n';
            x3.Clear();
            i3 = x3.Begin();
            break;

          case '*': case '?':  // *i, i.Valid
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            if (i3.Valid())
              std::cout << "*i3 == " << *i3 << '\n';
            else
              std::cout << "i3 == NULL\n";
            break;
        
          case '^':   // *i = t
            *isptr >> Tval;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << Tval << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            if (i3.Valid())
            {
              *i3 = Tval;
              std::cout << "Update completed\n";
            }
            else
              std::cout << "Cannot update: iterator invalid\n";
            break;
        
          case 'R':   // void Reverse()
            if (BATCH) std::cout << '\n';
	    x3.Reverse();
            std::cout << "  x3.Reverse();\n";
	    break;

          case 'M': case 'm':  // Merge(list)
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
	    switch(option)
	    {
	      case '1':
		x3.Merge(x1);
		std::cout << "  x3.Merge(x1);\n";
		break;
	      case '2':
		x3.Merge(x2);
		std::cout << "  x3.Merge(x2);\n";
		break;
	      case '3':
		x3.Merge(x3);
		std::cout << "  x3.Merge(x3);\n";
		break;
	    }
	    break;

          case 'e':   // bool Empty()
            if (BATCH) std::cout << '\n';
            std::cout << "  ";
            std::cout << "x3 is";
            if (!x3.Empty())
              std::cout << " NOT";
            std::cout << " empty\n";
            break;

	  case 'd':  case 'D': // Display
            if (BATCH) std::cout << '\n';
            DisplayContainerType(code0);
            std::cout << "  x3.Display(std::cout): ";
            x3.Display(std::cout,ofc);
            std::cout << '\n';
            break;
          
	  case 't':  case 'T': // traverse
            if (BATCH) std::cout << '\n';
            std::cout << "   Traverse x3: ";
            for (i0 = x3.Begin(); i0 != x3.End(); ++i0)
            {
              std::cout << ofc << *i0;
            }
            std::cout << '\n';
            std::cout << "  rTraverse x3: ";
            for (i0 = x3.rBegin(); i0 != x3.rEnd(); --i0)
            {
              std::cout << ofc << *i0;
            }
            std::cout << '\n';
            break;
          
          case 's': case 'S':  // unsigned int Size()
            if (BATCH) std::cout << '\n';
            std::cout << "  " << x3.Size() << " = x3.Size();\n";
	    break;

          case '<':   // void Sort()
            if (BATCH) std::cout << '\n';
	    x3.Sort();
            std::cout << "  x3.Sort();\n";
	    break;

          case '>':   // void Sort(p)
            if (BATCH) std::cout << '\n';
	    x3.Sort(pred);
            std::cout << "  x3.Sort(>);\n";
	    break;

          case '=':
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            switch(option)
            {
              case '1': 
		if (BATCH) std::cout << '\n';
		x3 = x1;
		i3 = x3.Begin();
		std::cout << "x3 = x1; i3 = x3.Begin();\n";
		break;
	      case '2':
		if (BATCH) std::cout << '\n'; 
		x3 = x2;
		i3 = x3.Begin();
		std::cout << "x3 = x2; i3 = x3.Begin();\n";
		break;
	      case '3':
		if (BATCH) std::cout << '\n';
		x3 = x3;
		i3 = x3.Begin();
		std::cout << "x3 = x3; i3 = x3.Begin();\n";
		break;
	      case '=':
	        *isptr >> option;
                if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
		std::cout << "  ";
		switch(option)
                {
                  case '1':
                    if (x3 == x1)
                      std::cout << "x3 == x1\n";
                    else
                      std::cout << "x3 != x1\n";
                    break;
                  case '2':
                    if (x3 == x2)
                      std::cout << "x3 == x2\n";
                    else
                      std::cout << "x3 != x2\n";
                    break;
                  case '3':
                    if (x3 == x3)
                      std::cout << "x3 == x3\n";
                    else
                      std::cout << "x3 != x3\n";
                    break;
                }
                break;
            }
            break;

          case '!':
            *isptr >> option;  // assumed to be '='
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n';
            std::cout << "  ";
            switch(option)
            {
              case '1':
                if (x3 != x1)
                  std::cout << "x3 != x1\n";
                else
                  std::cout << "x3 == x1\n";
                break;
              case '2':
                if (x3 != x2)
                  std::cout << "x3 != x2\n";
                else
                  std::cout << "x3 == x2\n";
                break;
              case '3':
                if (x3 != x3)
                  std::cout << "x3 != x3\n";
                else
                  std::cout << "x3 == x3\n";
                break;
            }
            break;

          case '+':   // ++(), +=()
            *isptr >> option;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET;
            switch(option)
            {
              case '+':
		if (BATCH) std::cout << '\n'; 
		++i3;
		std::cout << "  ++i3;";
		if (i3.Valid())
		  std::cout << "  " << *i3 << " = *i3;\n";
		else 
		  std::cout << "  false = i3.Valid();\n";
		break;
              case '=':
		*isptr >> option;
                if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
                switch(option)
		{
                  case '1':
		    x3 += x1;
                    std::cout << "  x3 += x1;\n";
                  break;
                  case '2':
		    x3 += x2;
                    std::cout << "  x3 += x2;\n";
                  break;
                  case '3':
		    x3 += x3;
                    std::cout << "  x3 += x3;\n";
                  break;
		}
		break;
              default: std::cout << "** Unknown command -- try again\n";
              break;
            }  
            break;
        
          case '-':   // --
            *isptr >> option;  // assumed to be '-'
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
            --i3;
	    std::cout << "  --i3;";
	    if (i3.Valid())
	      std::cout << "  " << *i3 << " = *i3;\n";
	    else 
	      std::cout << "  false = i3.Valid();\n";
	    break;

          case 'l': case 'L': // load file
            *isptr >> datafile;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << ' ' << datafile << ANSI_COLOR_RESET << '\n'; 
            dataistream.open(datafile.Cstr());
            if ( dataistream.fail() )
            {
              std::cout << " ** unable to open file " << datafile << '\n';
              dataistream.clear();
            }
            else
            {
              while (dataistream >> Tval)
                x3.PushBack(Tval);
              dataistream.clear();
              dataistream.close();
              std::cout << " Loaded data from file " << datafile << " at back of x3\n";
            }
            break;

          case 'w': case 'W': // write file
            *isptr >> datafile;
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << ' ' << datafile << ANSI_COLOR_RESET << '\n'; 
            dataostream.open(datafile.Cstr());
            if ( dataostream.fail() )
            {
              std::cout << " ** unable to open file " << datafile << '\n';
              dataostream.clear();
            }
            else
            {
              for (ci = x3.Begin(); ci != x3.End(); ++ci)
                dataostream << *ci << '\n';
              dataostream.close();
              std::cout << " Written x3 data to file " << datafile << '\n';
            }
            break;

          default:
            if (BATCH) std::cout << ANSI_COLOR_BOLD_RED << option << ANSI_COLOR_RESET << '\n'; 
            do 
	    {
	      isptr->get(option);
	      if (BATCH)
              {
                std::cout << ANSI_COLOR_BOLD_RED;
                std::cout.put(option);
                std::cout << ANSI_COLOR_RESET;
              }
	    } 
            while (option != '\n');
            std::cout << " ** Unrecognized command -- please try again\n";

        }  // end case '3'
        break;

      case '=':
	if (BATCH) std::cout << '\n'; 
        x3 = x2 = x1;
	i1 = x1.Begin();
	i2 = x2.Begin();
	i3 = x3.Begin();
	CopyTest(x3);
	AssignTest(x3);
        StructureTest(x3);
	break;

      case 'm': case 'M':
	if (BATCH) std::cout << '\n'; 
        DisplayMenu();
	break;

      case 'x': case 'X':  // switch to interactive mode or quit
	if (BATCH)
	{
	  std::cout << '\n';
	  ifs.close();
	  BATCH = 0;
	  isptr = &std::cin;
	}
	else
	{
	  option = 'q';
	}
	break;

      case 'q': case 'Q':
	if (BATCH) std::cout << '\n'; 
	option = 'q';
        break;
          
      default:
        do 
        {
          isptr->get(option);
          if (BATCH)
          {
            std::cout << ANSI_COLOR_BOLD_RED;
            std::cout.put(option);
            std::cout << ANSI_COLOR_RESET;
          }
        } 
	while (option != '\n');
        std::cout << "** Unrecognized command -- please try again.\n";
    }
  }
  while (option != 'q');
  if (BATCH) ifs.close();
  std::cout << "\nHave a nice day." << std::endl;
  return EXIT_SUCCESS;
}

void DisplayPrompt()
{
  std::cout << "Enter [command][arguments] ('m' for menu, 'q' to quit): ";
}

void DisplayMenu()
{
  std::cout 
       << '\n'
       << "  PushFront  (Tval)  .....  1      PopFront   ()  .........  4\n"
       << "  PushBack   (Tval)  .....  2      PopBack    ()  .........  5\n"
       << "  Insert     (Tval)  .....  3      Remove     (Tval)  .....  6\n"
       << "  Insert     (I,Tval)  ...  i      Remove     (I)  ........  r\n"
       << "  Front      ()  .........  a      Back       ()  .........  z\n"
       << "  Empty      ()  .........  e      Size       ()  .........  s\n"
       << "  I.Valid    ()  .........  ?      Clear      ()  .........  c\n"
       << "  *I         .............  *      *I = Tval  .............  ^\n"
       << "  I = X.Begin()  .........  a      I = X.rBegin()  ........  z\n"
       << "  ++I  ...................  ++     --I  ...................  --\n"
       << "  Sort  ..................  <      Sort(>)  ...............  >\n"
       << "  Reverse  ...............  R      Merge (list)  ..........  M\n"
       << "  Display  ...............  D      Traverse  ..............  T\n"
       << "  Load data from file  ...  L      Write list to file  ....  W\n\n"
       << "   Switch to interactive mode  ......  X\n"
       << "   operators  = , += , ==, !=  ......  [list][op][list]\n\n"
       << "   Enter '=' alone  .................  x3 = x2 = x1;\n"
       << "                     ................  CopyTest(x3);\n"
       << "                      ...............  AssignTest(x3);\n"
       << "                       ..............  StructureTest(x3);\n"
       << "                        .............  i1 = x1.Begin();\n"
       << "                         ............  i2 = x2.Begin();\n"
       << "                          ...........  i3 = x3.Begin();\n"
       << std::endl;
}

void Preamble()
{
  std::cout << "\n   This test uses three Container objects: x1, x2, x3\n" 
	    << "   and three associated Iterator objects: i1, i2, i3\n"
            << "   The test accesses the list API through a menu of commands (below).\n" 
            << "   For most, designate the list (1, 2 or 3), followed by the command,\n"
	    << "   followed by the argument if needed.\n"
	    << "   Some example entries and their meaning for the API:\n\n"
	    << "      Entry     Action\n"
	    << "      -----     ------\n"
	    << "      11z       x1.PushFront(z)\n"
	    << "      32q       x3.PushBack(q)\n"
	    << "      2a        i2 = x2.Begin()  \n"
	    << "      2++       ++i2\n"
	    << "      2ig       x2.Insert(i2,g)\n"
	    << "      1<        x1.Sort()\n"
	    << "      1>        x1.Sort(pred)\n"
	    << "      3=2       x3 = x2\n"
	    << "      =         x3 = x2 = x1; init i1, i2, i3; CopyTest(x3); AssignTest(x3);\n\n";
}

void DisplayContainerType(const char code0, const char code1)
{
  switch(code0)
  {
    case 'c':
      switch(code1)
      {
        case '1':
          std::cout << "List < char >";
          break;
        default:
          std::cerr << " [bad code1 passed to DisplayPrompt()]";
      }
      break;
    case 's':
      switch(code1)
      {
        case '1':
          std::cout << "List < String >";
          break;
        default:
          std::cerr << " [bad code1 passed to DisplayPrompt()]";
      }
      break;
    case 'i':
      switch(code1)
      {
        case '1':
          std::cout << "List < int >";
          break;
        default:
          std::cerr << " [bad code1 passed to DisplayPrompt()]";
      }
      break;
    default:
      std::cerr << " [bad code[0] passed to DisplayPrompt()]";
  }
}

