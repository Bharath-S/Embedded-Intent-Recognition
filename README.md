# Embedded Intent Recognizer!

Small intent recognition command line tool.
The idea is to be able to ask a set of predefined questions and accurately recognize the intent of the user. The predefined intents are the following:
- What is the weather like today? => Prints (Intent: Get Weather)
- What is the weather like in Paris today? => Prints (Intent: Get Weather City)
- What is the weather like in New York today? => Prints (Intent: Get Weather City)
- Am I free at 13:00 PM tomorrow? ==> Prints (Intent: Check calendar)
- Tell me an interesting fact. => Prints (Intent: Get Fact)



## Algorithms

- TF-IDF -> Term Frequency - Inverse Document Frequency
- Cosine Similarity

## Setup

- Clone the repo and cd into the cloned directory
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `./EmbeddedIntentDetection` -> To execute the main program
- `./utest/uTest` -> To run the unit test cases
- Have fun
