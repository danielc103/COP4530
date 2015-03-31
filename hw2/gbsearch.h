/*
    gbsearch.h
    01/01/12
    Chris Lacher

    Generic binary search algorithms for random access iterators

    02/01/14: removed const from P&

    Iterative implementations:
      runtime  = Theta(log n)
      runspace = +Theta(1) 

    These algorithms take parameters of type I, T, and optionally a third
    parameter of type P. 

    about I
    =======

    I is a random access iterator type; this means that the bracket operator

      T& operator [] (unsigned int);

    is defined and the usual "pointer" arithmetic operations are defined:

      I&    operator += (long n);
      I&    operator -= (long n);
      I     operator +  (long n) const;
      long  operator -  (const I& I2) const;

    Examples include: ordinary array iterators (pointers);
                      TVector<T>::Iterator;
                      TDeQueue<T>::Iterator;

    about T
    =======

    T is the value type of the iterator I

    about P 
    =======

    P is a predicate class used for order; an object cmp of class P
    has the function evaluation operator overloaded with the prototype

      bool operator () (const T&, const T&);

    Note that P must be used to order the elements so that P can work
    as a search condition: "a < b" iff "true = P(a,b)".

    g_lower_bound() and g_upper_bound() implement binary search for random
    access iterators.  It is assumed that the elements of iteration are in
    nondecreasing order (using operator < or an optional predicate object).

    g_lower_bound returns an iterator to the first location containing the
    search value if found, and the location where it would be otherwise. 
    g_upper_bound returns an iterator to the first location whose element is
    greater than the search value if such exists or the end iterator
    otherwise. I.e. (assuming L = lower bound and U = upper bound):

    if t is in the collection: t == *L, t < *U, and L and U point to the
    first elements in the range with these properties; thus,
    L and U mark the range of t in the collection;

    if t is not in the collection: L == U, and these iterators point to the
    location where t could be inserted and maintain nondecreasing order.

    bool binary_search() uses the same algorithm, returning true iff found.

    All these versions of binary search run in logorithmic time
    and require only a constant amount of additional run space.

    Copyright 2012, R.C. Lacher
*/

#ifndef _GBSEARCH_H
#define _GBSEARCH_H

#include <compare.h>

namespace fsu
{

  template <class I, typename T, class P>
  I g_lower_bound (I low, I hih, const T& val, P& cmp)
  // pre:    I is a random access iterator (operator [] and "pointer" arithmetic)
  //         I has ValueType T
  //         low + n = hih for some n >= 0
  //         low[0] ... low[n-1] are in non-decreasing order using cmp
  // post:   no state is changed
  // return: itr = lower bound location in range, that is:
  //         itr = low + i, where low[i-1] < val <= low[i] or
  //         itr = hih if no such i exists
  {
    I mid;
    while (low != hih)
    {
      mid =  low + ((hih - low) >> 1);    // low <= mid < hih
      if (cmp(*mid , val))                // *mid < val
	low = ++mid;                        // *mid <= val
      else                                // val <= *mid
	hih = mid;                          // val <= *hih
    }  
    return low;
  }

  /* here is an equivalent integer version of the code
  {
    unsigned long   max  = hih - low;  // 1 + largest valid index
    unsigned long   lo(0), hi(max), mi;

    while (lo < hi)
    {
      mi =  (lo + hi) / 2;            
      if (LessThan(low[mi] , val))    
        lo = mi + 1;                  
      else                            
        hi = mi;                      
    }
    return low + lo;
  }
  */

  template <class I, typename T, class P>
  I g_upper_bound (I low, I hih, const T& val, P& cmp)
  // pre:    I is a random access iterator (operator [] and "pointer" arithmetic)
  //         I has ValueType T
  //         low + n = hih for some n >= 0
  //         low[0] ... low[n-1] are in non-decreasing order using cmp
  // post:   no state is changed
  // return: itr =  low + i, where low[i-1] <= val < low[i]; or
  //         itr = hih if no such i exists
  {
    I mid;
    while (low != hih)
    {
      mid =  low + ((hih - low) >> 1);    // low <= mid < hih
      if (cmp(val, *mid))                 // val < low[mid]
	hih = mid;                          // val < low[hih]
      else                                // low[mid] <= val
	low = ++mid;                        // low[low - 1] <= val
    }
    return low;
  }

  template <class I, typename T, class P>
  bool g_binary_search (I low, I hih, const T& val, P& cmp)
  // pre:    I is a random access iterator (operator [] and "pointer" arithmetic)
  //         I has ValueType T
  //         low + n = hih for some n >= 0
  //         low[0] ... low[n-1] are in non-decreasing order using cmp
  // post:   no state is changed
  // return: true if found, false if not found
  {
    I lb = fsu::g_lower_bound(low, hih, val, cmp);
    if (lb != hih)
    {
      if (val == *lb)
      {
	return 1;
      }
    }
    return 0;
  }

  template <class I, typename T>
  I g_lower_bound (I low, I hih, const T& val)
  {
    fsu::LessThan<T> cmp;
    return fsu::g_lower_bound(low, hih, val, cmp);
  }

  template <class I, typename T>
  I g_upper_bound (I low, I hih, const T& val)
  {
    fsu::LessThan<T> cmp;
    return fsu::g_upper_bound(low, hih, val, cmp);
  }

  template <class I, typename T>
  bool g_binary_search (I low, I hih, const T& val)
  {
    fsu::LessThan<T> cmp;
    return fsu::g_binary_search(low, hih, val, cmp);
  }

  /* Proof (g_lower_bound)
   -----

  Before entering loop, define beg = low, top = hih - 1

  loop invariants:
                      beg[0..low-1] are < val
                      beg[hih..top] are >= val
                      0 <= low <= mid <= hih <= top

  Proof of Termination: (hih - low) collides with 0

  Return Value: after loop terminates, the following are true:
                low == hih 
                0 <= low <= top
                beg[low] == beg + low is where val SHOULD be, i.e.:
                  val <= beg[0]                    if low == 0
                  beg[low - 1] < val <= beg[low]   if 0 < low < top
                  beg[top - 1] < val               if low == top
  */

} // namespace fsu

#endif
