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
#include <sstream>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/regex.hpp>

#include <tmx/tmx>

namespace tmx
{
///////////////////////////////////////////////////////////////////////////
Points parsePoints(const std::string &str)
{
    Points points;                                        
    Point p;
    // Looking for a pair of points
    boost::regex re("(-?\\d*)\\,(-?\\d*)");
    
    boost::match_results<std::string::iterator> matches;  
    std::string buf;           
    std::stringstream ss(str);
    
    while (ss >> buf) 
    {
        if(boost::regex_search(begin(buf), end(buf), matches, re))
        {
            // matches[0] corresponds to the entiere string
            std::istringstream(matches[1]) >> p.first;
            std::istringstream(matches[2]) >> p.second;
            points.insert(p);
        }
    }
    
    return points;
}

///////////////////////////////////////////////////////////////////////////
std::string DecodeBase64(const std::string &str)
{
    return base64_decode(str);
}

///////////////////////////////////////////////////////////////////////////
std::string DecompressGZIP(const std::string &compressedString)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    
    // Push the decompressor and data in the stream
    in.push(boost::iostreams::gzip_decompressor());
    in.push(boost::make_iterator_range(compressedString));
    
    // Copy the result
    std::string decompressed;
    boost::iostreams::copy(in,boost::iostreams::back_inserter(decompressed));

    return decompressed;
}

///////////////////////////////////////////////////////////////////////////
std::string DecompressZLIB(const std::string &compressedString)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    
    // Push the decompressor and data in the stream
    in.push(boost::iostreams::zlib_decompressor());
    in.push(boost::make_iterator_range(compressedString));
    
    // Copy the result
    std::string decompressed;
    boost::iostreams::copy(in,boost::iostreams::back_inserter(decompressed));

    return decompressed;
}
    
} // namespace tmx
