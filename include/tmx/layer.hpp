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

#ifndef LAYER_HPP
#define LAYER_HPP

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////

#include <vector>

#include <boost/property_tree/ptree.hpp>

#include <tmx/data.hpp>
#include <tmx/properties.hpp>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
/// \brief Map layer containing data
///
///////////////////////////////////////////////////////////////////////////
class Layer
{
public:

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Create an empty Layer object
    ///
    ///////////////////////////////////////////////////////////////////////////
    Layer() = default;
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contructor by parsing
    ///
    /// Create a Layer object according to a Property Tree
    ///
    /// \param pt Property Tree to parse
    ///
    ///////////////////////////////////////////////////////////////////////////
    Layer(const boost::property_tree::ptree &pt);
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the name
    ///
    /// \return Name
    ///
    ///////////////////////////////////////////////////////////////////////////
    std::string getName();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get X
    ///
    /// \return X
    ///
    ///////////////////////////////////////////////////////////////////////////
    int getX();                
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get Y
    ///
    /// \return Y
    ///
    ///////////////////////////////////////////////////////////////////////////
    int getY();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the width
    ///
    /// \return Width
    ///
    ///////////////////////////////////////////////////////////////////////////            
    int getWidth();  
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the height
    ///
    /// \return Height
    ///
    ///////////////////////////////////////////////////////////////////////////         
    int getHeight();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the opacity
    ///
    /// \return Opacity
    ///
    ///////////////////////////////////////////////////////////////////////////          
    float getOpacity();  
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the visibility
    ///
    /// \return Visible
    ///
    ///////////////////////////////////////////////////////////////////////////      
    bool getVisible(); 
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the Data
    ///
    /// \return Data
    ///
    ///////////////////////////////////////////////////////////////////////////        
    Data getData();    
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the properties
    ///
    /// \return Properties
    ///
    ///////////////////////////////////////////////////////////////////////////         
    Properties getProperties();
    
    ///////////////////////////////////////////////////////////////////////////
    /// \brief Print on the standard output the object
    ///
    ///////////////////////////////////////////////////////////////////////////
    void dump();

private:

    ///////////////////////////////////////////////////////////////////////////
    // Member data
    ///////////////////////////////////////////////////////////////////////////
    std::string name;      ///< Name of the layer
    int x = 0;             ///< Abscissa of the layer
    int y = 0;             ///< Ordinata of the layer
    int width = 0;         ///< Width of the layer
    int height = 0;        ///< Height of the layer
    float opacity = 0;     ///< Opacity of the layer
    bool visible = true;   ///< Define visibility of the layer
    Data data;             ///< Data of the layer
    Properties properties; ///< Properties of the layer
    
};
    
using Layers = std::vector<Layer>;

} // namespace tmx

#endif
