#ifndef _LOADER_H
#define _LOADER_H

#include <tinyxml.h>

#include "Model.h"

namespace Loader
{
  void loadModel(const char* filename, Model::modelData* mData);
  Model::modelData* loadPlayer(const char* fileName);
}
#endif //LOADER_H
