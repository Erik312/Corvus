//
// urlparser.cpp - A simple url parser 
// version 1.0
// Written by Erik Ramos(erikram312@gmail.com)
// 
//
module;
#include <iostream>
#include <string>
#include <map>



// UrlParser - A parser Class with methods that take a url in the form of a std::string and extracts the path,scheme and hostname.

export module urlparser;

export class UrlParser
{
public:
    UrlParser(){};
    ~UrlParser(){};
     // parse_url() - calls parse_path(),parse_hostname() and parse_scheme() to extract information from url string.
     // param: std::map<string,string> arg1, std::string arg2; 
     // return: std::map<string,string>;
     
   

    std::string parse_path(std::string p1){
        int count=0;
        std::string e_path;
        std::string wrk_url=p1;
        for(std::size_t i=0; i < wrk_url.size(); i++){
            if(wrk_url[i] == '/'){
                count+=1;
            }
            if(count==3){
                e_path+=wrk_url[i];
            }

        }
    
        return e_path;
    };

    std::string parse_hostname(std::string h1){
        int count=0;
        std::string e_hostname;
        std::string wrk_url=h1;
        for(std::size_t i=0; i < wrk_url.size(); i++){
            if(wrk_url[i] == '/'){
                count+=1;
            }
            if(count==2 && wrk_url[i] != '/'){
                e_hostname+=wrk_url[i];
            }else if(count==3){
                break;

            }
        }

        return e_hostname;
    };

    std::string parse_scheme(std::string s1){
        int count=0;
        std::string e_scheme;
        std::string wrk_url=s1;
        for(std::size_t i=0; i < wrk_url.size(); i++){
            if(wrk_url[i] == '/'){
                count+=1;
            }
            e_scheme+=wrk_url[i];
            if(count >= 2){
                break;
            }
        }
    
        return e_scheme;

    };


    int parse_url(std::map<std::string,std::string> &m1,std::string url1){
        if(url1==""){
            std::cout << "ERROR: Invalid or empty string" << "\n";
            return -1;
        }
        m1.clear();
        m1["Path"]=parse_path(url1);
        m1["Hostname"]=parse_hostname(url1);
        m1["Scheme"]=parse_scheme(url1);

        std::cout << "Parse url successfully completed!" << "\n";
        return 0;
    };

};