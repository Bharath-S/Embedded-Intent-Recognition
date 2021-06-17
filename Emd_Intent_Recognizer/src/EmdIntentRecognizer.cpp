#include "EmdIntentRecognizer.h"

using namespace std;

EmdIntentRecognizer::EmdIntentRecognizer(std::string strFileName)
{
    CsvReader fReferenceData(strFileName);

    m_mapReferenceData = fReferenceData.mapGetReference();
    m_vecReferenceData = fReferenceData.vecGetStrings();
}

std::vector<std::string> EmdIntentRecognizer::textParse(std::string & bigString)
{
    std::vector<std::string> vec;
    boost::tokenizer<> tok(bigString);
    for(boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++ beg)
    {
        vec.push_back(*beg);
    }
    return vec;
}


void EmdIntentRecognizer::createVocabList(std::vector<std::vector<std::string>> rawDataSet)
{
    std::set<std::string> vocabListSet;
    for (std::vector<std::string> document : rawDataSet)
    {
        for (std::string word : document)
            vocabListSet.insert(word);
    }
    std::copy(vocabListSet.begin(), vocabListSet.end(), std::back_inserter(vocabList));
}

std::vector<double> EmdIntentRecognizer::bagOfWords2VecMN(std::vector<std::string> & inputSet)
{
    std::vector<double> returnVec(vocabList.size(), 0);
    for (std::string word : inputSet)
    {
        size_t idx = std::find(vocabList.begin(), vocabList.end(), word) - vocabList.begin();
        if (idx != vocabList.size())
            returnVec.at(idx) += 1;
    }
    return returnVec;
}

auto EmdIntentRecognizer::vec2mat(std::vector<std::vector<std::string>> rawDataSet)
{
    createVocabList(rawDataSet);
    int cnt(0);
    for (auto it = rawDataSet.begin(); it != rawDataSet.end(); ++ it)
    {
        cnt ++;
        std::cout << cnt << "\r";
        //std::cout.flush();
        dataMat.push_back(bagOfWords2VecMN(*it));
    }
    return dataMat;
}

double EmdIntentRecognizer::cosine_similarity(std::vector<double> &v1, std::vector<double> &v2)
{
    double d1, d2, d3 = 0;
    unsigned int len = v1.size();
    for (unsigned int i = 0; i < len; ++i)
    {
        d1 += (v1[i] * v2[i]);
        d2 += (v1[i] * v1[i]);
        d3 += (v2[i] * v2[i]);
    }
    return d1 / (sqrt(d2) * sqrt(d3));
}


std::vector<double> EmdIntentRecognizer::get_term_count(std::vector<std::vector<double>> data)
{
    std::vector<double> term_count(data[0].size(), 0);
    for(int i=0; i<data.size(); i++)
    {
        for(int j=0; j<data[i].size(); j++)
        {
            auto val = data[i][j]>1? 1: data[i][j];
            term_count[j]+=val;
        }
    }
    return term_count;
}

void EmdIntentRecognizer::vGenIDF(std::vector< std::vector<double>> data)
{
    auto val = get_term_count(data);
    std::vector<double> ret;
    double row = (double)data.size();
    for(auto temp: val)
    {
        ret.push_back(log(row/temp));
    }

    mIDF = ret;
}


std::vector<double> EmdIntentRecognizer::get_tf(std::vector<double> data)
{
    double size = 0;
    for(double val: data)
    {
        size+= val;
    } 

    std::vector<double> ret;
    for(auto val: data)
    {
        ret.push_back(val/size);
    }

    return ret;
}


std::vector<double> EmdIntentRecognizer::vecIdfMutiplier(std::vector<double> vecData)
{
    std::vector<double> vecProcessedData;
    if(mIDF.size()!=vecData.size())
    {
        std::cout<<"The input is wrong" << std::endl;
        return vecProcessedData;
    }

    for(int i =0; i< vecData.size(); i++)
    {
        vecProcessedData.push_back(vecData[i]*mIDF[i]);
    }
    return vecProcessedData;
}

std::vector<std::vector<std::string>> EmdIntentRecognizer::vecParseReferenceData()
{
    std::vector<std::vector<std::string>> vecParsedData;
    for(auto strElem: m_vecReferenceData)
    {
        vecParsedData.push_back( textParse(strElem) );
    }

    return vecParsedData;
}

void EmdIntentRecognizer::vBuild()
{
    auto processeData = vecParseReferenceData();
    dataMat = vec2mat(processeData);
    vGenIDF(dataMat);
}

double EmdIntentRecognizer::dGetSimilarity(std::string strInp, std::string strReference)
{
    boost::algorithm::to_lower(strInp);
    boost::algorithm::to_lower(strReference);

    if(mIDF.empty())
    {
        vBuild();
    }

    std::string strIntent;

    auto vecStr = textParse(strInp);
    auto vInput = get_tf( bagOfWords2VecMN( vecStr ) );
    vInput = vecIdfMutiplier( vInput );

    vecStr = textParse(strReference);
    auto vRef = get_tf( bagOfWords2VecMN(vecStr) );
    vRef = vecIdfMutiplier( vRef );

    auto dSim = cosine_similarity(vInput, vRef);

    return dSim;
}

std::string EmdIntentRecognizer::strGetIntent(std::string strInput)
{
    std::string strIntent = "No Intent Recognised";
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






