//
//  BigML.hpp
//
//  Created by Robert Lee Hudspeth
//  Last Modified on 9/11/15
//

#ifndef BIGML_HPP
#define BIGML_HPP

#include <iostream>     //cout, cin, endl
#include <cstdlib>      //getenv
#include <string>       //string
#include <chrono>	//For delaying GET requests
#include <thread>	//For delaying GET requests
#include <curl/curl.h>  //Non-Standard; HTTP requests
#include "cJSON.h"	//Non-Standard; Creating JSON body
#include "respbuffer.h" //Non-Standard; Storing JSON response for parsing

//To avoid declaring within standard namespace,
//Doing so can cause issues from user to user
using namespace std::this_thread;
using namespace std::chrono;
using std::cout;
using std::endl;
using std::string;
using std::getenv;

class BigML {

/**********************************************************************************************/

    private:
	
	string user_name, user_key, BIGML_AUTH; //For user authentication
        string request, resource, iden, response; //For building request URLs
	int wait; //For delaying fetch requests
	int code; //For storing status code
	int i, j; //For index variables
	
	CURL *curl; //libcURL easy_handle for easy operations

	cJSON *root, *data, *item; //For submitting JSON body
	char *json;		   //For submitting JSON body
	
	struct str s;			     //For storing JSON response body
	string src, dts, ano, cls, ens, mod; //For storing/fetching resource identifiers
	
	void validate(string &BIGML_AUTH);
	
	void get_source_identifier(str *s);
	void get_dataset_identifier(str *s);
	void get_anomaly_identifier(str *s);
	void get_cluster_identifier(str *s);
	void get_ensemble_identifier(str *s);
	void get_model_identifier(str *s);
	
	void get_status(str *s);
	void get_dataset_status(str *s);
	void get_prediction_info(str *s);
	
/**********************************************************************************************/
	
    public:
	
	//Set user authentication info through function arguments
	void set_user_info(const string str1, const string str2);
	
	//Set user authentication info through environment variables
	void set_user_info();
	
	//Return identifiers as "get" member functions to prevent altering of private member variables
	string get_src();
	string get_dts();
	string get_ano();
	string get_cls();
	string get_ens();
	string get_mod();
	
        void create_remote_source(const char* url, const char* title);
	
		void get_source(const string source_iden);

	void create_dataset(const string source_iden);

		void get_dataset(const string dataset_iden);

	void create_anomalies(const string dataset_iden);
	
		void get_anomalies(const string anomaly_iden);

	void create_cluster(const string dataset_iden);
			
		void get_cluster(const string cluster_iden);
	
	void create_ensemble(const string dataset_iden);
	
		void get_ensemble(const string ensemble_iden);
	
	void create_model(const string dataset_iden);
	
		void get_model(const string model_iden);

        void create_prediction(const string model_iden, const char *col, const float num);
	
/**********************************************************************************************/

};

#endif
