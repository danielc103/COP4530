/*

Daniel C Carroll
ccarroll
dcc12b

wordbench.cpp/implentation

*/

#include <wordbench.h>
#include <iostream>
#include <fstream>
#include <iomanip>

bool WordBench::ReadText (const fsu::String& infile)
{

  
  std::ifstream ifs;

  infiles_.PushBack(infile);
  ifs.open(infile.Cstr());

  if (ifs.fail())
  {
    std::cerr << "**Error can't open file " << infile << std::endl;
    return 0;
  }
  
  fsu::String s;
  unsigned long numwords = 0;
  unsigned long count = 0;
  
  while ( ifs >> s)
  {
    
    
    if (s.Size() > 0)
    {
      //clean word
      size_t i = 0, j = 0;
      while (!isalnum(s[i]))
      {
         ++i;
         // break;
      }
             
      for ( ; i < s.Size(); ++i, ++j)
      {

          if (s[i] == '-' && (!isalnum(s.Element(i+1))))
          {       
            // ++i;
            break;
          }
          
          if (s[i] == '.'  && (!isalnum(s.Element(i+1))))
          {          
            // ++i;
            break;
          }
          
          if (s[i] == '\'' && (!isalnum(s.Element(i+1))))
          {
            // ++i;
            break;
          }

                
          if (s[i] == ')' || s[i] == ';' || s[i] == ']' || s[i] == ':' || s[i] == ','
              || s[i] == '}'  || s[i] == '{' || s[i] == '<' || s[i] == '[' || s[i] == '('
              || s[i] == '\"' || s[i] == '>' || s[i] == '!' || s[i] == '='   )
          {
             ++i;
              break;
          }

          s[j] = s[i];
          // ++j;
          
          // if (isalnum(s[i]))
          // {
          // s[j] = s[i];
          // ++j;
          // }
      }
         

      s.SetSize(j,'\0');
                
            
      //make lowercase
      for (size_t i = 0; s.Size() > i ; ++i)
      {       
        s[i] = tolower(s[i]);
      }

      
      // if (s.Size() > 0)
      // {
        EntryType pair(s,1);
        SetType::ConstIterator iter = wordset_.LowerBound(pair);
        
        if (iter != wordset_.End() && (*iter).first_ == s)
        {
          count = (*iter).second_;
          count++;
          pair.second_ = count;        
        }
        
        numwords++;
        wordset_.Insert(iter, pair);
        // }
    }
    
  }
  
    


  long unsigned uniquewords = 0;
  SetType::ConstIterator i;
  
  for ( i = wordset_.Begin(); i != wordset_.End(); ++i)
    uniquewords++;
    
  
  std::cout << "\nNumber of words read:        " << numwords << std::endl;
  std::cout << "Current vocabulary size:     " << uniquewords <<std::endl;
  
  
  ifs.close();
  return 1;
}



bool WordBench::WriteReport (const fsu::String& outfile, unsigned short c1, unsigned short c2) const
{
  std::ofstream ofs;
  ofs.open(outfile.Cstr());
  

  ofs << "Text Analysis for files: ";
  
  
  fsu:: ConstListIterator<fsu::String> ci;
  
  for (ci = infiles_.Begin(); ci != infiles_.End(); ++ci)
  {
    ofs << (*ci) << " ";
  }
  
  ofs << "\n\n";
  
  ofs << std::left << std::setw(c1) << "word"  <<  std::right <<std::setw(c2) 
      << "frequency"  << std::endl;
  ofs << std::left << std::setw(c1) << "----" << std::right << std::setw(c2) 
      << "---------" << std::endl;
  
  SetType::ConstIterator i;
  for ( i = wordset_.Begin(); i != wordset_.End(); ++i)
  {
    ofs << std::left << std::setw(c1) << (*i).first_ << std::right << std::setw(c2)
        << (*i).second_ << std::endl;
  }
  
  size_t uniquewords = 0;
  unsigned long total = 0;
  SetType::ConstIterator si;
  for ( si = wordset_.Begin(); si != wordset_.End(); ++si)
  {   
    uniquewords++;
    total += (*si).second_;
  }

  ofs << "\nNumber of words:  " << total << std::endl;
  ofs << "Vocabulary size:  " << uniquewords << std::endl;
  
  ofs.close();

  size_t uniquewordss = 0;
  unsigned long totals = 0;
  SetType::ConstIterator sis;
  for ( sis = wordset_.Begin(); sis != wordset_.End(); ++sis)
  {
    uniquewordss++;
    totals += (*sis).second_;
  }

  std::cout << "\nNumber of words:  " << totals << std::endl;
  std::cout << "Vocabulary size:  " << uniquewordss<< std::endl;
  std::cout << "Analysis written to file: " << outfile << std::endl;


  return 1;
}


void WordBench::ShowSummary () const
{

  std::cout << "\nCurrent files:             " ;
  
  fsu::ConstListIterator<fsu::String> ci;
  for (ci = infiles_.Begin(); ci != infiles_.End(); ++ci)
  {
    std::cout << (*ci) << " ";
  }
  std::cout << "\n";

  size_t uniquewords = 0;
  unsigned long total = 0;
  SetType::ConstIterator i;
  for ( i = wordset_.Begin(); i != wordset_.End(); ++i)
  {
    ++uniquewords;
     total += (*i).second_;
    
  }

  std::cout << "Current word cout:         " << total << std::endl;
  std::cout << "Current vocabulary size:   " << uniquewords  <<std::endl;

} 


void WordBench::ClearData ()
{

   infiles_.Clear();
   wordset_.Clear();

}


WordBench::WordBench (): wordset_() , infiles_()
{}

WordBench::~WordBench ()
{}
