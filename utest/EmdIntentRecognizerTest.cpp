//#define private public
#include "../header/EmdIntentRecognizer.h"
//#undef private

#include <gtest/gtest.h>

TEST(EmdIntentRecognizerTest, vecParseText) 
{ 
    EmdIntentRecognizer oEIR("../data/Reference.csv");
    std::string strInput = "Testing the parsing function";
    std::vector<std::string> vecProcessedStr = {"Testing","the","parsing","function"};
    std::vector<std::string> vecRet = oEIR.vecParseText(strInput);
    ASSERT_EQ(vecRet, vecProcessedStr);
}

TEST(EmdIntentRecognizerTest, strGetIntent) 
{ 
    EmdIntentRecognizer oEIR("../data/Reference.csv");
    oEIR.vBuild();
    
    ASSERT_EQ("Get Weather", oEIR.strGetIntent("What is the weather like tomorrow?"));
    
    ASSERT_EQ("Get Weather", oEIR.strGetIntent("Is the weather good today?"));
    
    ASSERT_EQ("Get Weather City", oEIR.strGetIntent("What is the weather in Paris tomorrow?"));
    
    ASSERT_EQ("Check calendar", oEIR.strGetIntent("What time is the meeting?"));
    
    ASSERT_EQ("Get Fact", oEIR.strGetIntent("Do you want to hear an interesting fact ?"));
}

TEST(EmdIntentRecognizerTest, vecGetTermCount) 
{ 
    EmdIntentRecognizer oEIR("../data/Reference.csv");
    std::vector<std::vector<double> > vfvInput;
    
    vfvInput.push_back({2.0,1.0,0.0,0.0,1.0});
    vfvInput.push_back({0.0,0.0,0.0,0.0,1.0});
    
    std::vector<double> vecExpOutput = {1,1,0,0,2} ;
    ASSERT_EQ(vecExpOutput, oEIR.vecGetTermCount(vfvInput) );
}

TEST(EmdIntentRecognizerTest, vecParseReferenceData) 
{ 
    EmdIntentRecognizer oEIR("../data/Reference.csv");
    std::vector<std::string> vecProcessedStr = {"what","is","the","weather", "like", "today"};
    ASSERT_EQ(oEIR.m_vecReferenceData.size(), oEIR.vecParseReferenceData().size());
}

TEST(EmdIntentRecognizerTest, vecGetTf) 
{ 
    EmdIntentRecognizer oEIR("../data/Reference.csv");
    std::vector<double> vecInput = {2.0,0.0,0.0,2.0,1.0};
    std::vector<double> vecExp = {0.4,0.0,0.0,0.4,0.2};
    ASSERT_EQ(vecExp, oEIR.vecGetTf(vecInput));
}


int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
