/*
Daniel C Carroll
ccarroll
dcc12b

wordbench.h

*/

#ifndef _WORDBENCH_H
#define _WORDBENCH_H

#include <xstring.h>
#include <vector.h>
#include <list.h>
#include <pair.h>
#include <ovector.h> 
#include <iostream>
#include <fstream>
#include <olist.h>

class WordBench;



class WordBench
{
public:

  //API
  bool ReadText      (const fsu::String& infile);
  bool WriteReport   (const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const;
  void ShowSummary   () const;
  void ClearData     ();

  WordBench          ();
  ~WordBench         ();

private:

  //the internal class terminology:
  typedef fsu::Pair       < fsu::String, unsigned long >  EntryType;
  typedef fsu::LessThan   < EntryType >                   PredicateType;

  //choose one associative container class for SetType:

  // typedef fsu::UOList       < EntryType, PredicateType >   SetType;
  //typedef fsu::MOList       < EntryType, PredicateType >   SetType;
    typedef fsu::UOVector       < EntryType, PredicateType >   SetType;
  //typedef fsu::MOVector     < EntryType, PredicateType >   SetType;
  //typedef fsu::RBLIT        < EntryType, PredicateType >   SetType;

  //Class variables:
  SetType                      wordset_;
  fsu::List  < fsu::String >   infiles_;

};

#endif
