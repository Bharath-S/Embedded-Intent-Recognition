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

    private:

        std::vector<std::vector<double>> dataMat;
        std::vector<std::string> vocabList;
        std::vector<std::string> m_vecReferenceData;
        std::map< std::string, std::vector<std::string> > m_mapReferenceData;
        std::vector<double> mIDF;

        std::vector<std::string> textParse(std::string & bigString);
        void createVocabList(vector<vector<string>> rawDataSet);
        std::vector<double> bagOfWords2VecMN(std::vector<std::string> & inputSet);
        auto vec2mat(vector<vector<string>> rawDataSet);
        double cosine_similarity(std::vector<double> &v1, std::vector<double> &v2);
        vector<double> get_term_count(vector<vector<double>> data);
        void vGenIDF(std::vector<std::vector<double>> data);
        vector<double> get_tf(vector<double> data);
        std::vector<double> vecIdfMutiplier(std::vector<double> vecData);
        std::vector<std::vector<string>> vecParseReferenceData();
        double dGetSimilarity(std::string strInp, std::string strReference);


    public:

        EmdIntentRecognizer(std::string strFileName);
        std::string strGetIntent(std::string strInput);
        void vBuild();

};

#endif
