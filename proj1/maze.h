/*
    maze.h 

    <1.31.14>
    <Daniel C Carroll>
    <ccarroll>

*/

#ifndef _MAZE_H
#define _MAZE_H

#include <iostream>
#include <list.h>
#include <vector.h>
#include <deque.h>
#include <queue.h>
#include <stack.h>

namespace maze
{

  //------------------------------
  //   class Maze
  //------------------------------

  class Cell;

  class Maze 
  {
  public: 

    bool Initialize    ( const char* filename );
    bool Consistent    () const;
    void Solve         ( fsu::List < unsigned long > & solution );
    void ShowMaze      ( std::ostream& os = std::cout ) const;

         Maze          ();
         ~Maze         ();

  private: // variables
    unsigned long                                   numrows_, numcols_;
    Cell *                                          start_;
    Cell *                                          goal_;
    fsu::Vector < Cell >                            cellVector_;  // cell inventory
    // fsu::Stack  < Cell* , fsu::Vector < Cell* > >   conStack_;    // DFS
    fsu::Queue  < Cell* , fsu::Deque  < Cell* > >   conQueue_;    // BFS

  private: // methods
    void Clear();

    // not intended to be used -- do not implement
    Maze             (const Maze&);  // copy constructor
    Maze& operator = (const Maze&);  // assignment operator

  }  ;  // class Maze

  //------------------------------
  //   class Cell
  //------------------------------

  class Cell
  {
    friend bool Maze::Consistent() const;

  public:
                  Cell             ();
                  ~Cell            ();
                  Cell             (const Cell& c);
    Cell&         operator =       (const Cell& c);

    void          Clear            ();

    void          SetID            (unsigned long id);
    unsigned long GetID            ()                const;
    void          SetParent        (Cell*);
    Cell*         GetParent        ()                const;
    void          SetVisited       ();
    void          UnSetVisited     ();
    bool          IsVisited        ()                const;
  
    void          AddNeighbor      (Cell * N);
    Cell*         GetNextNeighbor  ()                const;
    bool          IsNeighbor       (const Cell * N)  const;

  private:  // variables
    unsigned long        id_;
    fsu::List < Cell* >  neighborList_;
    bool                 visited_;
    Cell *               searchParent_; // needed only for BFS

  } ;  // class Cell

} // namespace

#endif
