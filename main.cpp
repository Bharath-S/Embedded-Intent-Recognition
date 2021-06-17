/*************************************************************************************************
 *
 * A command line tool to recognize a simple small intent of the question asked
 *
 * Example Questions -> Intent:
 *
 * 1. What is the weather like today? -> Intent: Get Weather
 * 2. What is the weather like in Paris today? -> Intent: Get Weather City
 * 3. Am I free at 13:00 PM tomorrow? -> Intent: Check calendar
 * 4. Tell me an interesting fact -> Intent: Get Fact
 *
 * This program uses cosine similarity along with term frequency and inverse document frequency
 * (TF-IDF) to measure the similary between given sentence and the reference sentence
 *
 * The reference senteces are used for the finding the sentence statistics, 
 * and can be found in the data folder
 *
 *************************************************************************************************/

#include "EmdIntentRecognizer.h"

int main(){
    
    EmdIntentRecognizer oEIR("../data/Reference.csv");
    oEIR.vBuild();
    
    std::cout << "Embedded Intent Detection" << std::endl << std::endl;
    while(true) {
        std::string input_text;
        std::cout<<"Enter a question: ";
        std::getline(std::cin, input_text);
        std::cout<< "Intent: "<< oEIR.strGetIntent(input_text) <<std::endl<<std::endl;
    }  
    return 0;

}

