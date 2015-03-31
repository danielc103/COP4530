/*

gssearch.h
2.20.14
Daniel C Carroll

generic search algorithm

*/


#ifndef _GSSEARCH_H
#define _GSSEARCH_H

#include <compare_spy.h>

namespace seq
{


  template <class I, typename T, class P>
  I g_lower_bound (I beg, I end, const T& val, P& cmp)
  {
    while(beg != end)
    {
      if (!cmp(*beg, val))
          return beg;
      beg++;
    }
    return beg;


  }

  template <class I, typename T, class P>
  I g_upper_bound (I beg, I end, const T& val, P& cmp)
  {
    while (beg != end)
    {
      if(cmp(val, *beg))
         return beg;
         beg++;
    }
      return beg;

  }

  template <class I, typename T>
  I g_lower_bound (I beg, I end, const T& val)
  {
    fsu::LessThanSpy<T> cmp;
    return fsu::g_lower_bound(beg, end, val, cmp);
  }

  template <class I, typename T>
  I g_upper_bound (I beg, I end, const T& val)
  {
    fsu::LessThanSpy<T> cmp;
    return fsu::g_upper_bound(beg, end, val, cmp);
  }

  }

#endif
