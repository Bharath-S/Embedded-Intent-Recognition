#include "EmdIntentRecognizer.h"

using namespace std;

/**
 * Parameterized Constructor, reads the data from the data file
 * Args: 
 *     strFileName - Path of the data file
 */
EmdIntentRecognizer::EmdIntentRecognizer(std::string strFileName)
{
    CsvReader fReferenceData(strFileName);
    m_mapReferenceData = fReferenceData.mapGetReference();
    m_vecReferenceData = fReferenceData.vecGetStrings();
}


/**
 * Parses the string to a list of words
 * Args: 
 *     strInput - Sentence to be split into words
 * Return: 
 *     A vector of words
 */
std::vector<std::string> EmdIntentRecognizer::vecParseText(std::string & strInput)
{
    std::vector<std::string> vecTok;
    if(!strInput.empty())
    {
        boost::tokenizer<> tok(strInput);
        for(boost::tokenizer<>::iterator itr = tok.begin(); itr != tok.end(); ++ itr)
            vecTok.push_back(*itr);
    }
    return vecTok;
}

/**
 * Creates a vocabulary list by taking the reference sentences as input
 * Args: 
 *     rawDataSet - A vector of strings reads from the data file
 */
void EmdIntentRecognizer::vCreateVocabList(std::vector<std::vector<std::string>> vfvData)
{
    std::set<std::string> setVocabListSet;
    for (std::vector<std::string> vecDocument : vfvData)
    {
        for (std::string strWord : vecDocument)
            setVocabListSet.insert(strWord);
    }
    std::copy(setVocabListSet.begin(), setVocabListSet.end(), std::back_inserter(m_vecVocabList));
}

/**
 * Converts the list of words to a vector 
 * Args: 
 *     inputSet - List of words parsed earlier by the vecParseText
 * Return: 
 *     A vector representing the list of words
 */
std::vector<double> EmdIntentRecognizer::vecBagOfWords2Vec(std::vector<std::string> & vecInput)
{
    std::vector<double> vecReturn(m_vecVocabList.size(), 0);
    for (std::string strWord : vecInput)
    {
        size_t idx = std::find(m_vecVocabList.begin(), m_vecVocabList.end(), strWord) - m_vecVocabList.begin();
        if (idx != m_vecVocabList.size())
            vecReturn.at(idx) += 1;
    }
    return vecReturn;
}

/**
 * Converts the list of strings to a list of vectors
 * Args: 
 *     rawDataSet - List of sentences read from the data file
 * Return: 
 *     A list of vectors
 */
std::vector<std::vector<double>> EmdIntentRecognizer::vfvVector2Mat(std::vector<std::vector<std::string>> vfvDataStr)
{
    vCreateVocabList(vfvDataStr);
    int cnt(0);
    for (auto it = vfvDataStr.begin(); it != vfvDataStr.end(); ++ it)
    {
        cnt ++;
        m_vfvDataMat.push_back(vecBagOfWords2Vec(*it));
    }
    return m_vfvDataMat;
}

/**
 * Calculates the cosine similarity between 2 vectors
 * Args: 
 *     vecData1 - input vector 1
 *     vecData2 - input vector 2
 * Return: 
 *     Similaity value
 */
double EmdIntentRecognizer::dGetCosineSimilarity(std::vector<double> &vecData1, std::vector<double> &vecData2)
{

    assertm(vecData1.size()==vecData2.size(), "Error in dGetCosineSimilarity, Please check the Input and the reference data file");
    
    double d1, d2, d3 = 0;
    unsigned int len = vecData1.size();
    for (unsigned int i = 0; i < len; ++i)
    {
        d1 += (vecData1[i] * vecData2[i]);
        d2 += (vecData1[i] * vecData1[i]);
        d3 += (vecData2[i] * vecData2[i]);
    }
    return d1 / (sqrt(d2) * sqrt(d3));
}

/**
 * Calculates the count of the terms in a vector
 * Args: 
 *     data - A vector after being converted from list of words
 * Return: 
 *     Count of the number of terms in the vector
 */
std::vector<double> EmdIntentRecognizer::vecGetTermCount(std::vector<std::vector<double>> vfvData)
{
    assertm(!vfvData.empty(), "Error in vecGetTermCount, Please check the Input and the reference data file");
    
    std::vector<double> term_count(vfvData.at(0).size(), 0);
    for(int i=0; i<vfvData.size(); i++)
    {
        for(int j=0; j<vfvData.at(i).size(); j++)
        {
            auto val = vfvData.at(i).at(j)>1? 1: vfvData.at(i).at(j);
            term_count.at(j)+=val;
        }
    }
    return term_count;
}

/**
 * Generates the Inverse Document Frequecy
 * Args: 
 *     data - A list of vectors after being converted from list of sentences
 */
void EmdIntentRecognizer::vGenIDF(std::vector< std::vector<double>> data)
{
    assertm(!data.empty(), "Error in vGenIDF, Please check the Input and the reference data file");
    
    auto val = vecGetTermCount(data);
    std::vector<double> ret;
    double row = (double)data.size();
    for(auto temp: val)
        ret.push_back(log(row/temp));

    mIDF = ret;
}

/**
 * Calculates the term frequency in a vector
 * Args: 
 *     data - A vector after being converted from list of words
 * Return: 
 *     A vector containing the frequency of terms
 */
std::vector<double> EmdIntentRecognizer::vecGetTf(std::vector<double> data)
{
    assertm(!data.empty(), "Error in vecGetTf, Please check the Input and the reference data file");
    
    double size = 0;
    for(double val: data)
        size+= val;

    std::vector<double> ret;
    for(auto val: data)
        ret.push_back(val/size);

    return ret;
}

/**
 * Multiplies the term frequency with the inverse document frequency
 * Args: 
 *     vecData - A vector after being converted from list of words
 * Return: 
 *     A vector containing the product -> tf*idf
 */
std::vector<double> EmdIntentRecognizer::vecIdfMutiplier(std::vector<double> vecData)
{
    assertm(mIDF.size()==vecData.size(), "Error in vecIdfMutiplier, Please check the Input and the reference data file");
    
    std::vector<double> vecProcessedData;
    for(int i =0; i< vecData.size(); i++)
        vecProcessedData.push_back(vecData[i]*mIDF[i]);
    return vecProcessedData;
}

/**
 * Parse all the sentences to a list of list of words
 *
 * Return: 
 *     A list of list of words after being parsed using vecParseText
 */
std::vector<std::vector<std::string>> EmdIntentRecognizer::vecParseReferenceData()
{  
    std::vector<std::vector<std::string>> vecParsedData;
    for(auto strElem: m_vecReferenceData)
        vecParsedData.push_back( vecParseText(strElem) );

    return vecParsedData;
}

/**
 * A builder method that builds the object to enable tf-idf methodology
 */
void EmdIntentRecognizer::vBuild()
{
    auto processeData = vecParseReferenceData();
    m_vfvDataMat = vfvVector2Mat(processeData);
    vGenIDF(m_vfvDataMat);
}

/**
 * Calculates the tf-idf similarity between 2 strings
 * Args: 
 *     strInp - Input sentence 1
 *     strReference - Input sentence 2
 * Return: 
 *     double - Similarity value calculated by tf-idf methodology using cosine similarity
 */
double EmdIntentRecognizer::dGetSimilarity(std::string strInp, std::string strReference)
{
    assertm(( (!strInp.empty()) && (!strReference.empty())), "Error in dGetSimilarity, Please check the Input and the reference data file");
    
    boost::algorithm::to_lower(strInp);
    boost::algorithm::to_lower(strReference);

    if(mIDF.empty())
        vBuild();

    std::string strIntent;

    auto vecStr = vecParseText(strInp);
    auto vInput = vecGetTf( vecBagOfWords2Vec( vecStr ) );
    vInput = vecIdfMutiplier( vInput );

    vecStr = vecParseText(strReference);
    auto vRef = vecGetTf( vecBagOfWords2Vec(vecStr) );
    vRef = vecIdfMutiplier( vRef );

    auto dSim = dGetCosineSimilarity(vInput, vRef);

    return dSim;
}

/**
 * Detects the intent of the given sentence
 * Args: 
 *     strInput - The Input Sentence/Question
 * Return: 
 *     string - Detected Intent
 */
std::string EmdIntentRecognizer::strGetIntent(std::string strInput)
{
    std::string strIntent = "No Intent Recognised";
    if(strInput.empty())
    {
        std::cout<< "Please input a valid sentence" << std::endl; 
    }
    double sim = 0;
    for(auto & vecStr: m_mapReferenceData)
    {
        for(auto strElem: vecStr.second)
        {
            auto sim_temp = dGetSimilarity(strElem, strInput);
            if(sim_temp>sim)
            {
                sim = sim_temp;
                strIntent = vecStr.first;
            }   
        }

    }
    return strIntent;
}






