/*
    <2.3.14>
    <Daniel C Carroll>
    <ccarroll>
  
    <>

*/

#include <fstream>
#include <iomanip>
#include <genalg.h>
#include <maze.h>

namespace maze
{

  //------------------------------
  //   class Maze
  //------------------------------

  void Maze::Clear ()
  {
     cellVector_.Clear();
     conQueue_.Clear();
     numrows_ = 0;
     numcols_ = 0;
    
  }

  void Maze::Solve(fsu::List<unsigned long>& solution)
  {
     
    // fsu::Vector<Cell>::Iterator i;
    Cell * N ;
    Cell * F ;
    
    conQueue_.Clear();
    
    for (size_t i = 0; i < cellVector_.Size(); ++i)
    {
      cellVector_[i].UnSetVisited();
      cellVector_[i].SetParent(0);
    }
    //  for(i = cellVector_.Begin(); i != cellVector_.End(); ++i)
    // {
    // i->UnSetVisited();
    // i->SetParent(0);
    // }
    
     
    start_->SetVisited();
    conQueue_.Push(start_);
    
    while(!conQueue_.Empty())
    {
      F = conQueue_.Front();
      if(F == goal_)
      {       
        
        break;
      } 
      
     
      while((N = F->GetNextNeighbor()))
      {
        N->SetVisited();
        N->SetParent(F);
        conQueue_.Push(N);               
      }

      conQueue_.Pop();
     }
      
     
     while (F != 0)
        {
          solution.PushFront(F->GetID());
          F = F->GetParent();
        }
     
    }

    bool Maze::Initialize (const char* filename)
  {

             
   
    std::ifstream ifs;
    

    ifs.open(filename);
    
    if (ifs.fail())
    {
      std::cerr << "Error: Check File";
      return 0;
    }
    
    ifs >> numrows_ >> numcols_;
    
    unsigned long totalCells = numrows_ * numcols_;
    unsigned long counter = 0;
    
    cellVector_.SetSize(totalCells );
    unsigned long row, col;    
    unsigned long walls;    
        
    for (size_t j = 0; j < totalCells; ++j)
      
    {
      
      row = j/numcols_;
      col = j % numcols_;
      cellVector_[j].SetID(counter);
      ifs>>walls;
     
          
          //north
      if ((walls & 0x01) == 0)
      {
        if (j <  numcols_)
        {} //std::cerr << "Error";//repair
        else
          cellVector_[j].AddNeighbor(&cellVector_[j-numcols_]);
        
      }
      
      //east
      if ((walls & 0x02) == 0)
      {
        if (col + 1 == numcols_)
        {} // std::cerr << "Error"; //repair
        else
          cellVector_[j].AddNeighbor(&cellVector_[j+1]);
        
      }
      
      //west
      if((walls & 0x08) == 0)
          {
            if (col == 0)
            {} // std::cerr << "Error"; //repair
            else
              cellVector_[j].AddNeighbor(&cellVector_[j-1]);
            
          }
            
          //south
          if ((walls & 0x04) == 0)
            {
              if (row + 1 == numrows_)
              {} // std::cerr << "Error";//repair
              else
                cellVector_[j].AddNeighbor(&cellVector_[j+numcols_]);
            }
          //  std::cout << "\n " << cellVector_[j].GetID();          
          counter++;

    }
    
     unsigned long start, goal;
     ifs >> start;
     
     ifs >> goal;
     
     
     start_ = &cellVector_[start];
     goal_ = &cellVector_[goal];    
       
     ifs.close();
  
    return 1;
    }
    
  bool Maze::Consistent() const
  {
    
    //fsu::ConstListIterator<Cell *>ci ;
    // Cell * N;
    //std::cout << "anything\n";
    // for (size_t i = 0; i < cellVector_.Size(); ++i)
    // {
    //std::cout << "firstFOR\n";
    //for ()
    //{
    //  std::cout << "second\n";
    //  if ( (*ci)->IsNeighbor(cellVector_[i]) == false)
    //  std::cout << "here";
    // }
    // }
    

    //    for(all cells in cellvector C)
    // {
    //  for(all neighbors of C N)
    //  {
    //    if(c is not neighbor of N)
    //     std::cout << cells C and N don't match
    //  }
    // }
     return 1;
  }

  void Maze::ShowMaze(std::ostream& os) const
  {
    os << " ** ShowMaze not implemented\n";
  }

  // Maze:: implementations below are already done

  Maze::Maze () : numrows_(0), numcols_(0), start_(0), goal_(0), cellVector_(0), conQueue_()
  {}

  Maze::~Maze ()
  {
    Clear();
  }

  //------------------------------
  //   class Cell
  //------------------------------

  Cell& Cell::operator = (const Cell& c) // note: called by Vector::SetSize()
  {
    if (this != &c)
    {
      id_ = c.id_;
      neighborList_ = c.neighborList_;
      visited_ = c.visited_;
      searchParent_ = c.searchParent_;
    }
    return *this;
  }

  void Cell::Clear()
  {
    
    //fsu::ListIterator <Cell *> i = neighborList_.Begin();
    //ile (i !=  neighborList_.End())
    // {
    //  delete [] (*i)->GetNextNeighbor();
    //  delete &(*i);
    //  i++;
    // }
     
  }

  void Cell::AddNeighbor (Cell * N)
  {
        
    neighborList_.PushBack(N);
  }

  Cell* Cell::GetNextNeighbor () const
  {
    fsu::ConstListIterator <Cell *> i ;
    for(i = neighborList_.Begin(); i != neighborList_.End(); ++i)
    {
      if (!(*i)->IsVisited())
        return *i;
    }
      
    return 0;
  } 

  bool Cell::IsNeighbor (const Cell * N) const
  {
    
    fsu::ConstListIterator<Cell *> i;
    

    for (i = neighborList_.Begin(); i != neighborList_.End(); ++i)
    {
      if ((*i) == N)
       return 1;
   }
 
    return 0;
  }

  // Cell:: implementations below are already done

  void Cell::SetID (unsigned long id)
  {
    id_ = id;
  }

  unsigned long Cell::GetID () const
  {
    return id_;
  }

  void Cell::SetParent (Cell * N) 
  {
    searchParent_ = N;
  }

  Cell * Cell::GetParent () const
  {
    return searchParent_;
  }

  void Cell::SetVisited ()
  {
    visited_ = 1;
  }

  void Cell::UnSetVisited ()
  {
    visited_ = 0;
  }

  bool Cell::IsVisited () const
  {
    return visited_;
  }

  // default constructor, required to create vector of cells
  Cell::Cell  () : id_(0), neighborList_(), visited_(0), searchParent_(0)
  {}

  // destructor - calls Cell::Clear()
  Cell::~Cell ()
  {
    Clear();
  }

  // copy constructor - implemented, but sends message when called
  // (we should not be using it)
  Cell::Cell(const Cell& c) : id_(c.id_), neighborList_(c.neighborList_), visited_(c.visited_)
  {
    std::cout << "** ERROR: call to Cell copy constructor\n";
  }

} // namespace
