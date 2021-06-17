#ifndef EMDINTENTRECOGNIZER_H
#define EMDINTENTRECOGNIZER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include "CsvReader.h"

using namespace std;

class EmdIntentRecognizer 
{

    public:

        std::vector<std::vector<double>> dataMat;
        std::vector<std::string> vocabList;
        std::vector<std::string> m_vecReferenceData;
        std::map< std::string, std::vector<std::string> > m_mapReferenceData;
        std::vector<double> mIDF;

        void createVocabList(vector<vector<string>> rawDataSet);
        std::vector<double> bagOfWords2VecMN(std::vector<std::string> & inputSet);
        auto vec2mat(vector<vector<string>> rawDataSet);
        double cosine_similarity(std::vector<double> &v1, std::vector<double> &v2);
        void vGenIDF(std::vector<std::vector<double>> data);
        vector<double> get_tf(vector<double> data);
        std::vector<double> vecIdfMutiplier(std::vector<double> vecData);
        std::vector<std::vector<string>> vecParseReferenceData();
        vector<double> get_term_count(vector<vector<double>> data);
        
    public:

        EmdIntentRecognizer(std::string strFileName);
        std::vector<std::string> textParse(std::string & bigString);
        
        std::string strGetIntent(std::string strInput);
        double dGetSimilarity(std::string strInp, std::string strReference);
        void vBuild();
        

};

#endif
