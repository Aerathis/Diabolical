#include <iostream>
#include <vector>

#include "Loader.h"
#include "Model.h"


namespace Loader
{
  namespace 
  {
    template <class ContainerT>
    void tokenize(const std::string& str, ContainerT& tokens,
		  const std::string& delimiters = " ", const bool trimEmpty = false)
    {
      typedef ContainerT Base;
      typedef typename Base::value_type ValueType;
      typedef typename ValueType::size_type SizeType;
      SizeType pos, lastPos = 0;
      while (true)
	{
	  pos = str.find_first_of(delimiters, lastPos);
	  if (pos == std::string::npos)
	    {
	      pos = str.length();
	      
	      if (pos != lastPos || !trimEmpty)
		tokens.push_back(ValueType(str.data()+lastPos,(SizeType)pos-lastPos));
	      break;
	    }
	  else
	    {
	      if (pos != lastPos || !trimEmpty)
		tokens.push_back(ValueType(str.data()+lastPos,(SizeType)pos-lastPos));
	    }
	  lastPos = pos + 1;
	}
    }

    template<class T>
    bool from_string(T& t,
		     const std::string& s,
		     std::ios_base& (*f)(std::ios_base&))
    {
      std::istringstream iss(s);
      return !(iss >> f >> t).fail();
    }
    void vStringtovFloat(std::vector<std::string> in, std::vector<float>* out)
    {
      std::vector<std::string>::iterator it;
      for (it = in.begin(); it != in.end(); ++it)
	{
	  float f;
	  if (from_string<float>(f, *it, std::dec))
	    {
	      out->push_back(f);
	    }
	  else
	    {
	      std::cout << "from_string failed" << std::endl;
	      break;
	    }
	}
    }

    void extractVertices(TiXmlNode* node, Model::geometryData* out)
    {
      std::vector<std::string> vStrings;
      std::vector<std::string> nStrings;
      std::vector<float> vFloats;
      std::vector<float> nFloats;

      TiXmlNode* vArraySource = node->FirstChild()->FirstChild();
      TiXmlNode* vertexArray = vArraySource->FirstChild()->FirstChild();
      TiXmlNode* nArraySource = vArraySource->NextSibling();
      TiXmlNode* normalArray = nArraySource->FirstChild()->FirstChild();
      TiXmlNode* vertices = nArraySource->NextSibling(); // Not sure if needed
      //TiXmlNode* tSource = vertices->NextSibling();
      //TiXmlNode* triangles = tSource->FirstChild()->NextSibling()->NextSibling()->FirstChild();
      TiXmlNode* pSource = vertices->NextSibling();
      TiXmlNode* polys = pSource->FirstChild()->NextSibling()->NextSibling();
      for (TiXmlNode* child = polys; child; child = child->NextSibling())
	{
	  //Each hop through this loop gets one more poly from child->FirstChild()->Value()
	}

      tokenize(vertexArray->Value(), vStrings);
      vStringtovFloat(vStrings, &vFloats);
      tokenize(normalArray->Value(), nStrings);
      vStringtovFloat(nStrings, &nFloats);
      out->rawVertices = vFloats;
      out->rawNormals = nFloats;

    }

    void extractPhysics(TiXmlNode* node, Model::physicsData* out)
    {
      std::string sShape;
      float fMass;

      // node is the physics_model element in the library_physics_models
      TiXmlNode* massNode = node->FirstChild()->FirstChild()->FirstChild()->NextSibling();
      TiXmlNode* mass = massNode->FirstChild();
      TiXmlNode* shapeNode = massNode->NextSibling()->NextSibling();
      TiXmlNode* shape = shapeNode->FirstChild();
      TiXmlNode* radius = shape->FirstChild()->FirstChild();
      
      fMass = from_string<float>(fMass, mass->Value(), std::dec);
      sShape = shape->Value();

      out->shape = sShape;
      out->mass = fMass;
    }

    void extractPhysicsMaterials(TiXmlNode* node)
    {
      // node is the physics_material element in the library_physics_materials
    }

    void processNodeChildren(TiXmlNode* node, Model::geometryData* dData,
			     Model::physicsData* pData)
    {

      TiXmlNode* child = NULL;
      for (child = node->FirstChild(); child; child = child->NextSibling())
	{
	  if(child->Type() == 1)
	    {
	      std::string typeName = "";
	      typeName = child->Parent()->Value();
	      if (typeName == "library_geometries")
		{
		  extractVertices(child, dData);
		}
	      else if (typeName == "library_physics_materials")
		{
		  extractPhysicsMaterials(child);
		}
	      else if (typeName == "library_physics_models")
		{
		  extractPhysics(child, pData);
		}
	    }
	  processNodeChildren(child, dData, pData);
	}
    }
  }
  void loadModel(const char* fileName, Model::modelData* mData)
  {

    Model::geometryData gData;
    Model::physicsData pData;

    TiXmlDocument doc(fileName);
    bool loadOkay = doc.LoadFile();
    if (loadOkay)
      {
	processNodeChildren(doc.FirstChildElement(), &gData, &pData);
	std::cout << "children processed" << std::endl;
	mData->geometry = gData;
	mData->physics = pData;
      }
    else
      {
	std::cout << "Error loading file" << std::endl;
      }
    
  }
  
  Model::modelData* loadPlayer(const char* fileName)
  {
    Model::modelData* data = NULL;
    std::cout << "loadPlayer called" << std::endl;
    
    loadModel(fileName, data);
    std::cout << "loadModel" << std::endl;

    return data;
  }
}
