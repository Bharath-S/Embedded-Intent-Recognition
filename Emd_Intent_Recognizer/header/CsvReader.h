#ifndef CSVREADER_H
#define CSVREADER_H

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

        CsvReader(std::string sFile);
        std::map< std::string, std::vector<std::string> > mapGetReference();
        std::vector<std::string> vecGetStrings();

};

#endif
