#include "CsvReader.h"

CsvReader::CsvReader(std::string sFile)
{
    std::ifstream fin(sFile,  std::ifstream::in);
    if (!fin) 
    { 
        std::cout << "Error, could not open file." << std::endl; 
    }
    std::string line;
    std::string delimiter = ",";
    std::string intent, value;
    
    while(std::getline(fin, line))
    {
        std::stringstream ss(line);
        size_t pos = 0;
        std::string token, str;
        pos = line.find(delimiter);
        if(pos == std::string::npos)
        {
            std::cout << "error" << std::endl; 
        }

        token = line.substr(0, pos);
        str = line.substr(pos + delimiter.length(), std::string::npos);
        boost::algorithm::to_lower(str);
        m_mapData[token].push_back(str);
    }

    fin.close();
}

std::map< std::string, std::vector<std::string> > CsvReader::mapGetReference()
{
    return m_mapData;
}

std::vector<std::string>  CsvReader::vecGetStrings()
{
    std::vector<std::string> vReferenceStr;
    for(auto & elem: m_mapData)
    {
        for(auto value: elem.second)
        {
            vReferenceStr.push_back(value);
        }
    }

    return vReferenceStr;
}
