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

