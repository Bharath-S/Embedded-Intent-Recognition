#ifndef CSVREADER_H
#define CSVREADER_H

/*********************************************************************************************************
 * < CSV File Reader >
 *
 * A class to read the CSV file containing Intent and the reference sentence in a comma separated string
 *
 * Eg: 
 *
 * Get Weather,What is the weather like today?
 *
 ********************************************************************************************************/

#include<fstream>
#include<string>
#include<map>
#include<iostream>
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>

class CsvReader 
{

    private:

        std::map< std::string, std::vector<std::string> > m_mapData;

    public:

        // Constructor
        CsvReader(std::string sFile);

        // Returns the reference string as map datastructure with key->value pair
        // being Intent->Sentence format
        std::map< std::string, std::vector<std::string> > mapGetReference();

        // Returns all the sentences from the file as a vector of strings
        std::vector<std::string> vecGetStrings();

};

#endif
