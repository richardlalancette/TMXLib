///////////////////////////////////////////////////////////////////////////
//
// TMX Library - Simple C++11 library to parse TMX files
// Copyright (C) 2012 Alexandre Quemy (alexandre.quemy@gmail.com)
//
// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  ue,
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info".
//
// In this respect, the user's attention is drawn to the risks associated
// with loading,  using,  modifying and/or developing or reproducing the
// software by the user in light of its specific status of free software,
// that may mean  that it is complicated to manipulate,  and  that  also
// therefore means  that it is reserved for developers  and  experienced
// professionals having in-depth computer knowledge. Users are therefore
// encouraged to load and test the software's suitability as regards their
// requirements in conditions enabling the security of their systems and/or
// data to be ensured and,  more generally, to use and operate it in the
// same conditions as regards security.
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
//
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <tmx/tmx>

using namespace boost::property_tree;

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
Map::Map(std::string path)
{
    load(path);
}

///////////////////////////////////////////////////////////////////////////
Map::~Map()
{
    for(auto it = std::begin(imagelayers); it < std::end(imagelayers); it++)
        delete *it;
        
    for(auto it = std::begin(layers); it < std::end(layers); it++)
        delete *it;
        
    for(auto it = std::begin(objectgroups); it < std::end(objectgroups); it++)
        delete *it;
}

///////////////////////////////////////////////////////////////////////////
void Map::load(std::string path)
{
    // Opening TMX file
    ptree pt;
    read_xml(path, pt);

    ptree::const_iterator child = pt.begin();
    ptree node = child->second;

    // Parse data
    for (ptree::const_iterator cat = node.begin(); cat != node.end(); ++cat)
    {
        if(cat->first == "<xmlattr>")
        {
            const ptree& node = cat->second;
            for (ptree::const_iterator attr = node.begin(); attr != node.end(); ++attr)
            {
                if(!attr->second.data().empty())
                {
                    if(attr->first == "version")
                        version = attr->second.data();
                    else if(attr->first == "orientation")
                        if(attr->second.data() == "orthogonal")
                            orientation = ORTHOGONAL;
                        else if(attr->second.data() == "isometric")
                            orientation = ISOMETRIC;
                        else
                            throw "Unknow orientation";
                    else if(attr->first == "width")
                        width = std::stoi(attr->second.data());
                    else if(attr->first == "height")
                        height = std::stoi(attr->second.data());
                    else if(attr->first == "tilewidth")
                        tilewidth = std::stoi(attr->second.data());
                    else if(attr->first == "tileheight")
                        tileheight = std::stoi(attr->second.data());
                    else
                        throw std::runtime_error("Unknow attribut in Map");
                }
            }
        }
        else if(cat->first == "properties")
            properties = Properties(cat->second);
        else if(cat->first == "tileset")
            tilesets.push_back(Tileset(cat->second));
        else if(cat->first == "imagelayer")
        {
            imagelayers.push_back(new Imagelayer(cat->second));
            push_back(imagelayers.back());
        }
        else if(cat->first == "layer")
        {
            layers.push_back(new Layer(cat->second));
            push_back(layers.back());
        }
        else if(cat->first == "objectgroup")
        {
            objectgroups.push_back(new Objectgroup(cat->second));
            push_back(objectgroups.back());
        }
        else
            throw std::runtime_error("Unknow subsection in Map");
    }
}

///////////////////////////////////////////////////////////////////////////
std::string Map::getVersion() const
{
    return version;
}     

///////////////////////////////////////////////////////////////////////////
Orientation Map::getOrientation() const
{
    return orientation;
}     
 
///////////////////////////////////////////////////////////////////////////
int Map::getWidth() const
{
    return width;
}     
   
///////////////////////////////////////////////////////////////////////////             
int Map::getHeight() const
{
    return height;
}     
    
///////////////////////////////////////////////////////////////////////////          
int Map::getTilewidth() const
{
    return tilewidth;
}     
   
///////////////////////////////////////////////////////////////////////////        
int Map::getTileheight() const
{
    return tileheight;
}     
    
///////////////////////////////////////////////////////////////////////////       
Tilesets Map::getTilesets() const
{
    return tilesets;
}      

///////////////////////////////////////////////////////////////////////////       
Layers Map::getLayers() const
{
    return layers;
}   

///////////////////////////////////////////////////////////////////////////       
Imagelayers Map::getImagelayers() const
{
    return imagelayers;
}    
    
///////////////////////////////////////////////////////////////////////////       
Objectgroups Map::getObjectgroups() const
{
    return objectgroups;
}     

///////////////////////////////////////////////////////////////////////////
Properties Map::getProperties() const
{
    return properties;
}  

///////////////////////////////////////////////////////////////////////////
void Map::dump() const
{
    std::cout << "#######################################################" << std::endl;
    std::cout << "# Version : " << version << std::endl;
    std::cout << "# Orientation : " << orientation << std::endl;
    std::cout << "# Dimension (w*h) : " << width << "*" << height << std::endl;
    std::cout << "# Tile Dimension (w*h) : " << tilewidth << "*" << tileheight << std::endl;
    std::cout << "# Properties :" << std::endl;
    if(!properties.empty())
        properties.dump();
    for(auto tileset : tilesets)
        tileset.dump();
    for(auto layer : *this)
        layer->dump();

}

} // namespace tmx
