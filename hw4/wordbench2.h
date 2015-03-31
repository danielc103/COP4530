/*
Daniel C Carroll
wordbench2.h
Header file for 2nd wordbench using OAA
*/

#include <xstring.h>
#include <list.h>
#include <oaa.h>

class WordBench
{
public:
  WordBench          ();
  virtual ~WordBench ();
  bool ReadText      (const fsu::String& infile);
  bool WriteReport   (const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const;
  void ShowSummary   () const;
  void ClearData     ();

private:
  typedef fsu::String            KeyType;
  typedef size_t                 DataType;

  size_t count_;
  fsu::OAA < KeyType, DataType > frequency_;
  fsu::List < fsu::String >      infiles_;
  static void Cleanup (fsu::String& s);

};
