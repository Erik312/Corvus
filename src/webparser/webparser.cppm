//
// webparser.cppm - A web text parser 
// version 1.0
// Written by Erik Ramos(erik.ramos315@gmail.com)
// 
//

module;
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>


export module webparser;



//WebParser- used to parse html from raw socket data

export class WebParser{
    public:
        WebParser(){};
        ~WebParser(){};

        int wordFind(std::string targetWord,std::string &dataFile){
            std::string foundWord="";
            for(unsigned long i=0; i < dataFile.size(); i++){
                if(dataFile[i] == targetWord[0]){ // looks for first char that matches the first char of target word
                    int wordStart=i;
                    foundWord=dataFile[i];
                    for(unsigned long j=1; j < targetWord.size(); j++){
                        foundWord+=dataFile[wordStart+j]; // loop and append the rest of the word up to the length of the target word
                        if(foundWord == targetWord){ // On postivie word match return the starting index of the word
                            return wordStart;
                        }
                    }
                }
            
            }
        return -1;
        };

        std::string extractStyle(int targetIndex,std::string &dataFile){
            std::string result;
            int targetCount=targetIndex + 8;// start at end of style tag.
            for(unsigned long i=targetCount; i < dataFile.size(); i++){
                result+=dataFile[i]; // loop and append everything after the style tag
            }
            return result;
        };


        std::string parseWeb(std::string &rawHtml){
            std::string tempRaw=rawHtml;
            std::string parsedData;
            int endWord=wordFind("</body>",tempRaw);
            size_t convWord=endWord;
            bool inTag=false;
            for(size_t i=0; i < tempRaw.size(); i++){ // loop through string searching for html tags.
                if(i == convWord){
                    return parsedData;
                }else{
                    if(tempRaw[i] == '<'){
                        inTag=true;
                    }else if(tempRaw[i] == '>'){
                        inTag=false;
                        parsedData+='\n';
                    }else{
                        if(inTag==false){
                            //std::string currentData;
                            parsedData+=tempRaw[i];
                            // if not inside tag append to string.       
                        }    
                    }
                }
                
            }
            return parsedData; // returned text inside html tags.
        }
                


};