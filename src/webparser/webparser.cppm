//
// webparser.cppm - A web text parser 
// version 1.0
// Written by Erik Ramos(erik.ramos315@gmail.com)
// 
//


module;
#include <iostream>
#include <string>
#include <vector>


export module webparser;



//WebParser- used to parse html from raw socket data

export class WebParser{
    public:
        WebParser(){};
        ~WebParser(){};

        int wordFind(std::string targetWord,std::vector<std::string> &dataFile){
        for(unsigned long i=0; i < dataFile.size(); i++){
            if(dataFile[i][0] == targetWord[0]){ // looks for first char that matches the first char of target word
                int wordStart=i;
                std::string foundWord=dataFile[i];
                if(foundWord == targetWord){ // On postivie word match return the starting index of the word
                    return wordStart;
                }
            }
            
        }
            return -1;
        };

        std::vector<std::string> extractStyle(int targetIndex,std::vector<std::string> &dataFile){
        std::vector<std::string> result;
        int targetCount=targetIndex + 10;// start at end of style tag.
        for(unsigned long i=targetCount; i < dataFile.size(); i++){
            result.push_back(dataFile[i]); // loop and append everything after the style tag
        }
            return result;
        };


        std::vector<std::string> parseWeb(std::vector<std::string> &rawHtml){
        std::vector<std::string> tempRaw=rawHtml;
        std::vector<std::string> parsedData;
        std::string currentData="";
        bool inTag=false;
        for(unsigned long i=0; i < tempRaw.size(); i++){ // loop through string searching for html tags.
            for(unsigned long j=0; j < tempRaw[i].size(); j++)
                if(tempRaw[i][j] == '<'){
                    inTag=true;
                }else if(tempRaw[i][j] == '>'){
                    inTag=false;
                }else{
                    if(inTag==false){
                        //std::string currentData;
                        currentData+=tempRaw[i][j];
                         // if not inside tag append to string.
                    }
                    
                }
                
            

        }
            parsedData.push_back(currentData);
            return parsedData; // returned text inside html tags.
        };

};