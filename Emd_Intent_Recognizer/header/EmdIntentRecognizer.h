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

using namespace std;

class EmdIntentRecognizer 
{

    public:

        // Member variables
        std::vector<std::vector<double>> dataMat;
        std::vector<std::string> vocabList;
        std::vector<std::string> m_vecReferenceData;
        std::map< std::string, std::vector<std::string> > m_mapReferenceData;
        std::vector<double> mIDF;

        // Creates a vocabulary list by taking the reference sentences as input
        void createVocabList(vector<vector<string>> rawDataSet);

        // Converts the list of words to a vector
        std::vector<double> bagOfWords2VecMN(std::vector<std::string> & inputSet);

        // Converts the reference sentences to a matrix of vectors
        auto vec2mat(vector<vector<string>> rawDataSet);

        // Calculates the cosine similarity between 2 vectors
        double cosine_similarity(std::vector<double> &v1, std::vector<double> &v2);

        // Calculates the Inverse Document Frequency 
        void vGenIDF(std::vector<std::vector<double>> data);

        // Calculates the term frequency
        vector<double> get_tf(vector<double> data);

        // Multiplies term frequency with the inverse document frequency
        std::vector<double> vecIdfMutiplier(std::vector<double> vecData);

        // Converts all the sentences in the reference to a tokenized list of words
        std::vector<std::vector<string>> vecParseReferenceData();

        // Returns the count of the term used in the vector
        vector<double> get_term_count(vector<vector<double>> data);

    public:

        // Parameterized Contructor
        EmdIntentRecognizer(std::string strFileName);

        // Converts a sentece to a list of words
        std::vector<std::string> textParse(std::string & bigString);

        // Returns the intent of the sentence found after usign TF-IDF with cosine similarity
        std::string strGetIntent(std::string strInput);

        // Calculates the similarity between 2 sentences
        double dGetSimilarity(std::string strInp, std::string strReference);

        // Builds the overall object to use the TF-IDF method
        void vBuild();


};

#endif
