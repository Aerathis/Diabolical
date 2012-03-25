#ifndef _MAP_H
#define _MAP_H

#include <iostream>
#include <malloc.h>

// Currently this is only going to make squares, because they're easier to work with and I'm lazy. 
template <class T>
class Map
{
 public:
  Map()
    {
      mapSize = 0;
    }
  Map(int size)
    {
      mapSize = size;
      if (!mapCells = (T*)malloc(sizeof(T)*mapSize*mapSize))
	{
	  
	}
    }

  ~Map()
    {
      std::cout << "Freeing map memory" << std::endl;
      free(mapCells);
    }

  T getLocationAtCoord(int x, int y){}

  void setLocationAtCoord(int x, int y, T value) {}

  int getMapSize()
  {
    return mapSize;
  }
  void setSize(int size)
  {
    mapSize = size;
    if(mapCells = (T*)malloc(sizeof(T)*mapSize*mapSize))
      {
	std::cout << "Allocated Memory for map" << std::endl;
      }
    else
      {
	std::cout << "Failed to allocate memory for map" << std::endl;
      }
  }

 private:
  T* mapCells;
  int mapSize;
};

#endif //MAP_H
