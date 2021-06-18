#ifndef EMDINTENTRECOGNIZER_H
#define EMDINTENTRECOGNIZER_H

/*************************************************************************************************
 * < Embedded Intented Recognizer >
 *
 * A class to handle the text similarity and recognize intents
 *
 *
 * This program uses cosine similarity along with term frequency and inverse document frequency
 * (TF-IDF) to measure the similary between given sentence and the reference sentence
 *
 * The reference senteces are used for the finding the sentence statistics, 
 * and can be found in the data folder
 *
 *************************************************************************************************/


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
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace std;

class EmdIntentRecognizer 
{

    public:

        // Member variables
        std::vector<std::vector<double>> m_vfvDataMat;
        std::vector<std::string> m_vecVocabList;
        std::vector<std::string> m_vecReferenceData;
        std::map< std::string, std::vector<std::string> > m_mapReferenceData;
        std::vector<double> mIDF;

        // Creates a vocabulary list by taking the reference sentences as input
        void vCreateVocabList(vector<vector<string>> vfvData);

        // Converts the list of words to a vector
        std::vector<double> vecBagOfWords2Vec(std::vector<std::string> & vecInput);

        // Converts the reference sentences to a matrix of vectors
        std::vector<std::vector<double>> vfvVector2Mat(vector<vector<string>> vfvDataStr);

        // Calculates the cosine similarity between 2 vectors
        double dGetCosineSimilarity(std::vector<double> &vecData1, std::vector<double> &vecData2);

        // Calculates the Inverse Document Frequency 
        void vGenIDF(std::vector<std::vector<double>> data);

        // Calculates the term frequency
        vector<double> vecGetTf(vector<double> data);

        // Multiplies term frequency with the inverse document frequency
        std::vector<double> vecIdfMutiplier(std::vector<double> vecData);

        // Converts all the sentences in the reference to a tokenized list of words
        std::vector<std::vector<string>> vecParseReferenceData();

        // Returns the count of the term used in the vector
        vector<double> vecGetTermCount(vector<vector<double>> data);

    public:

        // Parameterized Contructor
        EmdIntentRecognizer(std::string strFileName);

        // Converts a sentece to a list of words
        std::vector<std::string> vecParseText(std::string & strInput);

        // Returns the intent of the sentence found after usign TF-IDF with cosine similarity
        std::string strGetIntent(std::string strInput);

        // Calculates the similarity between 2 sentences
        double dGetSimilarity(std::string strInp, std::string strReference);

        // Builds the overall object to use the TF-IDF method
        void vBuild();


};

#endif
