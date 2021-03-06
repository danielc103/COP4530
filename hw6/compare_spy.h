/*

compare_spy.h
2/21/14
Daniel C Carroll

Define and implement the predicate classes

*/


#ifndef _COMPARE_SPY_H
#define _COMPARE_SPY_H

namespace fsu
{

  template <typename T>
  class LessThanSpy;

  
  template <typename T>
class LessThanSpy
  {
  public:

    bool operator () (const T& t1, const T& t2) 
    { 
      lessCounter_++;
      return (t1 < t2);
      
    }
    void Reset ()
    {
      lessCounter_ = 0;
    }

    size_t Count () const
    {
      return lessCounter_;
    }
    LessThanSpy (): lessCounter_(0)
    {}

    //private variables
private:

  size_t lessCounter_;

  };

  template <typename T>
  bool operator == (const LessThanSpy<T>& , const LessThanSpy<T>&)
  {
    return 1;
  }

  template <typename T>
  bool operator != (const LessThanSpy<T>& , const LessThanSpy<T>& )
  {
    return 0;
  }


}//end namespace fsu

#endif
