//
//  BigML.cpp
//
//  Created by Robert Lee Hudspeth
//  Last Modified on 9/11/15
//

#include "BigML.hpp"

/******************************/
/*	     PRIVATE	      */
/******************************/

void BigML::validate(string &BIGML_AUTH) {

	init_str(&s);
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	
	request ="https://bigml.io/source?" + BIGML_AUTH;
	
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, request.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		curl_easy_perform(curl);
		
		for (i = 0; i<s.len; i++) {
			if (s.ptr[i] == 'c' && s.ptr[i+1] == 'o' && s.ptr[i+2] == 'd'
			&& s.ptr[i+7] == '4') {
				cout << "ERROR: ";
				i += 7;
				for (j = 0; j<3; j++)
					cout << s.ptr[i+j];
				cout << endl;
				exit(1);}}}
	
	else {
		cout << "cURL failed to connect. Please check your connections." << endl;
		exit(1);}
	
	reset_str(&s);
	curl_easy_cleanup(curl);} //End cURL session

void BigML::get_source_identifier(str *s) {
	
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == 's' && s->ptr[i+1] == 'o' && s->ptr[i+2] == 'u'
		&& s->ptr[i+3] == 'r' && s->ptr[i+4] == 'c' && s->ptr[i+5] == 'e'
		&& s->ptr[i+6] == '/') {
			i += 7;
			for (j = 0; j<24; j++) {
				src += s->ptr[i]; //Copy identifier into string
				i++;}
			break;}}}

void BigML::get_dataset_identifier(str *s) {
			
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == 'd' && s->ptr[i+1] == 'a' && s->ptr[i+2] == 't'
		&& s->ptr[i+3] == 'a' && s->ptr[i+4] == 's' && s->ptr[i+5] == 'e'
		&& s->ptr[i+6] == 't' && s->ptr[i+7] == '/') {
			i += 8;
			for (j = 0; j<24; j++) {
				dts += s->ptr[i]; //Copy identifier into string
				i++;}
			break;}}}
	
void BigML::get_anomaly_identifier(str *s) {
		
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == 'a' && s->ptr[i+1] == 'n' && s->ptr[i+2] == 'o'
		&& s->ptr[i+3] == 'm' && s->ptr[i+4] == 'a' && s->ptr[i+5] == 'l'
		&& s->ptr[i+6] == 'y' && s->ptr[i+7] == '/') {
			i += 8;
			for (j = 0; j<24; j++) {
				ano += s->ptr[i]; //Copy identifier into string
				i++;}
			break;}}}
	
void BigML::get_cluster_identifier(str *s) {
		
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == 'c' && s->ptr[i+1] == 'l' && s->ptr[i+2] == 'u'
		&& s->ptr[i+3] == 's' && s->ptr[i+4] == 't' && s->ptr[i+5] == 'e'
		&& s->ptr[i+6] == 'r' && s->ptr[i+7] == '/') {
			i += 8;
			for (j = 0; j<24; j++) {
				cls += s->ptr[i]; //Copy identifier into string
				i++;}
			break;}}}
	
void BigML::get_ensemble_identifier(str *s) {
		
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == 'e' && s->ptr[i+1] == 'n' && s->ptr[i+2] == 's'
		&& s->ptr[i+3] == 'e' && s->ptr[i+4] == 'm' && s->ptr[i+5] == 'b'
		&& s->ptr[i+6] == 'l' && s->ptr[i+7] == 'e' && s->ptr[i+8] == '/') {
			i += 9;
			for (j = 0; j<24; j++) {
				ens += s->ptr[i]; //Copy identifier into string
				i++;}
			break;}}}

void BigML::get_model_identifier(str *s) {
			
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == 'm' && s->ptr[i+1] == 'o' && s->ptr[i+2] == 'd'
		&& s->ptr[i+3] == 'e' && s->ptr[i+4] == 'l' && s->ptr[i+5] == '/') {
			i += 6;
			for (j = 0; j<24; j++) {
				mod += s->ptr[i]; //Copy identifier into string
				i++;}
			break;}}}

void BigML::get_status(str *s) {
			
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == '"' && s->ptr[i+1] == 's' && s->ptr[i+2] == 't'
		&& s->ptr[i+3] == 'a' && s->ptr[i+4] == 't') {
			code = s->ptr[i+19];}}}
	
void BigML::get_dataset_status(str *s) {
			
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == 'e' && s->ptr[i+1] == '_' && s->ptr[i+2] == 's') {
			code = s->ptr[i+51];}}}

void BigML::get_prediction_info(str *s) {
	
	cout << s->ptr << endl;
	for (i = 0; i<s->len; i++) { //Parse through JSON response
		if (s->ptr[i] == '1' && s->ptr[i+1] == ',' && s->ptr[i+3] == '"' && s->ptr[i+4] == 'c') {
			cout << "Confidence: ";
			i += 17;
			for (j = 0; j<7; j++) {
				cout << s->ptr[i+j];}
			break;}}
	
	cout << endl;}

/******************************/
/*	     PUBLIC	      */
/******************************/


//Return identifiers as "get" member functions to prevent altering of private member variables
string BigML::get_src() {return BigML::src;}

string BigML::get_dts() {return BigML::dts;}

string BigML::get_ano() {return BigML::ano;}

string BigML::get_cls() {return BigML::cls;}

string BigML::get_ens() {return BigML::ens;}

string BigML::get_mod() {return BigML::mod;}


//Set user authentication info through function arguments
void BigML::set_user_info(const string _name, const string _key) {
		
	cout << endl;
			
	//Get info through string literals
	cout << "Gathering Authentication Data From String Literals" << endl;
			
	if ((_name.data() == NULL) || (_key.data() == NULL)) {
		cout << "ERROR: Missing BigML username or API key or both." << endl;
		exit(1);}
	
	else if (_key.length() != 40) {
		cout << "ERROR: API key is not of valid length." << endl;
		exit(1);}
			
	else {
		user_name = _name;
		user_key = _key;
		BIGML_AUTH = "username=" + _name + ";api_key=" + _key;}
	
	validate(BIGML_AUTH);}

/****************************************************************************/

//Set user authentication info through environment variables
void BigML::set_user_info() {
		
	cout << endl;
	
	//Get environment variables
	cout << "Gathering Authentication Data From Environment Variables" << endl;
	
	if((getenv("BIGML_USERNAME") == NULL) || (getenv("BIGML_API_KEY") == NULL) || (getenv("BIGML_AUTH") == NULL)) {
		cout << "ERROR: Could not find proper environment variables." << endl;
		exit(1);}
	
	else {
		user_name = getenv("BIGML_USERNAME");
		user_key = getenv("BIGML_API_KEY");
		BIGML_AUTH = getenv("BIGML_AUTH");
		validate(BIGML_AUTH);}}

/****************************************************************************/

void BigML::create_remote_source(const char* url, const char* title) {
		
	cout << endl;
	cout << "Creating Remote Source." << endl;
	
	//Create request URL
	request = "https://bigml.io/source?" + BIGML_AUTH;
	
	//Creating JSON body
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "remote", url);
	cJSON_AddStringToObject(root, "name", title);
	item = cJSON_GetObjectItem(root, "remote");
	json = cJSON_Print(root);
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	cout << "Initializing cURL" << endl;
	
	init_str(&s); //Initialize memory buffer for storing resource identifier & status code for later use

	if(curl) {
		struct curl_slist *slist = NULL;
		slist = curl_slist_append(slist, "Accept: "); //Specifying headers so that API knows
		slist = curl_slist_append(slist, "Content-Type: application/json"); //I am submitting JSON
		slist = curl_slist_append(slist, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json); //Posting JSON body
		curl_easy_setopt(curl, CURLOPT_URL, request.data()); //To authenticated source site
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);	//Send response code to struct str s
		curl_easy_perform(curl); //Launch request
				
		curl_slist_free_all(slist); //Free headers
		curl_easy_cleanup(curl); //End cURL session
		get_source_identifier(&s);
		cJSON_Delete(root);} //Free JSON root
				
	else {
		cout << "cURL failed to connect. Please check your connections." << endl;
		exit(1);}}

/****************************************************************************/

	void BigML::get_source(const string source_iden) {
				
		wait = 1;
		code = ' ';
				
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
	
		init_str(&s);
	
		cout << endl;
		cout << "Your Source Identifier is: " << source_iden << endl;
		cout << endl;
		cout << "Checking of Status of Source Upload." << endl;
		cout << endl;
			
		request = "https://bigml.io/source/" + source_iden + "?" + BIGML_AUTH + ";full=false";
			
		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, request.data());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
						
			while (code != '5') {		  //While request is not completed
				curl_easy_perform(curl);  //Send GET request
				get_status(&s);	 	  //Check status code
				sleep_for(seconds(wait)); //Send delay to prevent throttling server
				reset_str(&s);		  //Clear buffer
				init_str(&s);
				wait++;}		  //Increase delay time
	
			cout << "Your Source with Identifier '" << source_iden << "' Has Been Created." << endl;}
					
		else {
			cout << "cURL failed to connect. Please check your connections" << endl;
			exit(1);}
	
		curl_easy_cleanup(curl); //End cURL session
		reset_str(&s);
		cout << endl;}

/****************************************************************************/

void BigML::create_dataset(const string source_iden) {
        
	cout << endl;
	cout << "Creating Dataset." << endl;
	
	resource = "source/" + source_iden;
	request = "https://bigml.io/dataset?" + BIGML_AUTH;
	
	//Creating JSON body
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "source", resource.data());
	cJSON_AddStringToObject(root, "name", source_iden.data());
	item = cJSON_GetObjectItem(root, "source");
	json = cJSON_Print(root);
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	cout << "Initializing cURL" << endl;
			
	init_str(&s); //Initialize memory buffer for storing resource identifier & status code for later use
			
	if(curl) {
		struct curl_slist *slist = NULL;
		slist = curl_slist_append(slist, "Accept: "); //Specifying headers so that API knows
		slist = curl_slist_append(slist, "Content-Type: application/json"); //I am submitting JSON
		slist = curl_slist_append(slist, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
		curl_easy_setopt(curl, CURLOPT_URL, request.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);	//Send response code to struct str s
		curl_easy_perform(curl);
				
		curl_slist_free_all(slist); //Free headers
		curl_easy_cleanup(curl); //End cURL session

		get_dataset_identifier(&s);
		cJSON_Delete(root);} //Free JSON root
    
	else {
		cout << "cURL failed to connect. Please check your connections" << endl;
		exit(1);}}

/****************************************************************************/

	void BigML::get_dataset(const string dataset_iden) {
				
		wait = 1;
		code = ' ';
					
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		
		reset_str(&s);
		init_str(&s);
			
		cout << endl;
		cout << "Your Dataset Identifier is: " << dataset_iden << endl;
		cout << endl;
		cout << "Checking on Status of Dataset Creation." << endl;
		cout << endl;
				
		request = "https://bigml.io/dataset/" + dataset_iden + "?" + BIGML_AUTH + ";full=false";

		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, request.data());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
			
			while (code != '5') {		  //While request is not completed
				curl_easy_perform(curl);  //Send GET request
				get_dataset_status(&s);	  //Check status code
				sleep_for(seconds(wait)); //Send delay to prevent throttling server
				reset_str(&s);		  //Clear buffer
				init_str(&s);
				wait++;}		  //Increase delay time
		
			cout << "Your Dataset with Identifier '" << dataset_iden << "' Has Been Created." << endl;}
						
		else {
			cout << "cURL failed to connect. Please check your connections" << endl;
			exit(1);}
		
		curl_easy_cleanup(curl); //End cURL session
		reset_str(&s);
		cout << endl;}

/****************************************************************************/

void BigML::create_anomalies(const string dataset_iden) {
		
	cout << endl;
	cout << "Launching Anomaly Detector" << endl;
			
	resource = "dataset/" + dataset_iden;
	request = "https://bigml.io/anomaly?" + BIGML_AUTH;
			
	//Creating JSON body
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "dataset", resource.data());
	cJSON_AddStringToObject(root, "name", dataset_iden.data());
	item = cJSON_GetObjectItem(root, "dataset");
	json = cJSON_Print(root);
            
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	cout << "Initializing cURL" << endl;
				
	init_str(&s); //Initialize memory buffer for storing resource identifier & status code for later use
			
	if(curl) {
		struct curl_slist *slist = NULL;
		slist = curl_slist_append(slist, "Accept: "); //Specifying headers so that API knows
		slist = curl_slist_append(slist, "Content-Type: application/json"); //I am submitting JSON
		slist = curl_slist_append(slist, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
		curl_easy_setopt(curl, CURLOPT_URL, request.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);	//Send response code to struct str s
		curl_easy_perform(curl);
					
		curl_slist_free_all(slist); //Free headers
		curl_easy_cleanup(curl); //End cURL session
					
		get_anomaly_identifier(&s); //Retrieve anomaly identifier
		cJSON_Delete(root);} //Free JSON root
					
	else {
		cout << "cURL failed to connect. Please check your connections" << endl;
		exit(1);}}

/****************************************************************************/

	void BigML::get_anomalies(const string anomaly_iden) {
		
		wait = 1;
		code = ' ';

		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
						
		reset_str(&s);
		init_str(&s);
			
		cout << endl;
		cout << "Your Anomaly Identifier is: " << anomaly_iden << endl;
		cout << endl;
		cout << "Checking on Status of Anomaly Detection." << endl;
		cout << "This May Take A While to Complete." << endl;
		cout << endl;
				
		request = "https://bigml.io/anomaly/" + anomaly_iden + "?" + BIGML_AUTH + ";full=false";
				
		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, request.data());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
							
			while (code != '5') {		  //While request is not completed
				curl_easy_perform(curl);  //Send GET request
				get_status(&s);		  //Check status code
				sleep_for(seconds(wait)); //Send delay to prevent throttling server
				reset_str(&s);		  //Clear buffer
				init_str(&s);
				wait++;}		  //Increase delay time
		
			cout << "Your Anomaly Detection with Identifier '" << anomaly_iden << "' is Complete." << endl;
			cout << endl;}
						
		else {
			cout << "cURL failed to connect. Please check your connections" << endl;
			exit(1);}
		
		curl_easy_cleanup(curl); //End cURL session
		reset_str(&s);
		cout << endl;}

/****************************************************************************/

void BigML::create_cluster(const string dataset_iden) {
			
	cout << endl;
	cout << "Building Cluster" << endl;

	resource = "dataset/" + dataset_iden;
	request = "https://bigml.io/cluster?" + BIGML_AUTH;

	//Creating JSON body
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "dataset", resource.data());
	cJSON_AddStringToObject(root, "name", dataset_iden.data());
	item = cJSON_GetObjectItem(root, "dataset");
	json = cJSON_Print(root);

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	cout << "Initializing cURL" << endl;

	init_str(&s); //Initialize memory buffer for storing resource identifier & status code for later use

	if(curl) {
		struct curl_slist *slist = NULL;
		slist = curl_slist_append(slist, "Accept: "); //Specifying headers so that API knows
		slist = curl_slist_append(slist, "Content-Type: application/json"); //I am submitting JSON
		slist = curl_slist_append(slist, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
		curl_easy_setopt(curl, CURLOPT_URL, request.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);	//Send response code to struct str s
		curl_easy_perform(curl);
		
		curl_slist_free_all(slist); //Free headers
		curl_easy_cleanup(curl); //End cURL session
		
		get_cluster_identifier(&s); //Retrieve cluster identifier
		cJSON_Delete(root);} //Free JSON root

	else {
		cout << "cURL failed to connect. Please check your connections" << endl;
		exit(1);}}

/****************************************************************************/

	void BigML::get_cluster(const string cluster_iden) {

		wait = 1;
		code = ' ';
	
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		
		reset_str(&s);
		init_str(&s);

		cout << endl;
		cout << "Your Cluster Identifier is: " << cluster_iden << endl;
		cout << endl;
		cout << "Checking on Status of Cluster Creation." << endl;
		cout << endl;

		request = "https://bigml.io/cluster/" + cluster_iden + "?" + BIGML_AUTH + ";full=false";

		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, request.data());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
			
			while (code != '5') {		  //While request is not completed
				curl_easy_perform(curl);  //Send GET request
				get_status(&s);		  //Check status code
				sleep_for(seconds(wait)); //Send delay to prevent throttling server
				reset_str(&s);		  //Clear buffer
				init_str(&s);
				wait++;}}		  //Increase delay time
		
		else {
			cout << "cURL failed to connect. Please check your connections" << endl;
			exit(1);}
		
		cout << "Your Cluster Creation with Identifier '" << cluster_iden << "' is Complete." << endl;
		curl_easy_cleanup(curl); //End cURL session
		reset_str(&s);
		cout << endl;}

/****************************************************************************/

void BigML::create_ensemble(const string dataset_iden) {
				
	cout << endl;
	cout << "Building Ensemble" << endl;

	resource = "dataset/" + dataset_iden;
	request = "https://bigml.io/andromeda/ensemble?" + BIGML_AUTH;

	//Creating JSON body
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "dataset", resource.data());
	cJSON_AddStringToObject(root, "name", dataset_iden.data());
	item = cJSON_GetObjectItem(root, "dataset");
	json = cJSON_Print(root);

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	cout << "Initializing cURL" << endl;

	init_str(&s); //Initialize memory buffer for storing resource identifier & status code for later use

	if(curl) {
		struct curl_slist *slist = NULL;
		slist = curl_slist_append(slist, "Accept: "); //Specifying headers so that API knows
		slist = curl_slist_append(slist, "Content-Type: application/json"); //I am submitting JSON
		slist = curl_slist_append(slist, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
		curl_easy_setopt(curl, CURLOPT_URL, request.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);	//Send response code to struct str s
		curl_easy_perform(curl);
		
		curl_slist_free_all(slist); //Free headers
		curl_easy_cleanup(curl); //End cURL session
		
		get_ensemble_identifier(&s);
		cJSON_Delete(root);} //Free JSON root

	else {
		cout << "cURL failed to connect. Please check your connections" << endl;
		exit(1);}}

/****************************************************************************/

	void BigML::get_ensemble(const string ensemble_iden) {
			
		wait = 1;
		code = ' ';
	
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		
		reset_str(&s);
		init_str(&s);

		cout << endl;
		cout << "Your Ensemble Identifier is: " << ensemble_iden << endl;
		cout << endl;
		cout << "Checking on Status of Ensemble Creation." << endl;
		cout << endl;

		request = "https://bigml.io/andromeda/ensemble/" + ensemble_iden + "?" + BIGML_AUTH + ";full=false";

		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, request.data());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
			
			while (code != '5') {		  //While request is not completed
				curl_easy_perform(curl);  //Send GET request
				get_status(&s);		  //Check status code
				sleep_for(seconds(wait)); //Send delay to prevent throttling server
				reset_str(&s);		  //Clear buffer
				init_str(&s);
				wait++;}}		  //Increase delay time
		
		else {
			cout << "cURL failed to connect. Please check your connections" << endl;
			exit(1);}
		
		cout << "Your Ensemble Creation with Identifier '" << ensemble_iden << "' is Complete." << endl;
		curl_easy_cleanup(curl); //End cURL session
		reset_str(&s);
		cout << endl;}

/****************************************************************************/

void BigML::create_model(const string dataset_iden) {
            
	cout << endl;
	cout << "Creating Model." << endl;
	
	resource = "dataset/" + dataset_iden;
	request = "https://bigml.io/model?" + BIGML_AUTH;
	
	//Creating JSON body
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "dataset", resource.data());
	cJSON_AddStringToObject(root, "name", dataset_iden.data());
	item = cJSON_GetObjectItem(root, "dataset");
	json = cJSON_Print(root);
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	cout << "Initializing cURL" << endl;
	
	init_str(&s); //Initialize memory buffer for storing resource identifier & status code for later use
	
	if(curl) {
		struct curl_slist *slist = NULL;
		slist = curl_slist_append(slist, "Accept: "); //Specifying headers so that API knows
		slist = curl_slist_append(slist, "Content-Type: application/json"); //I am submitting JSON
		slist = curl_slist_append(slist, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
		curl_easy_setopt(curl, CURLOPT_URL, request.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);	//Send response code to struct str s
		curl_easy_perform(curl);
		
		curl_slist_free_all(slist); //Free headers
		curl_easy_cleanup(curl); //End cURL session
		get_model_identifier(&s);
		cJSON_Delete(root);} //Free JSON root

	else {
		cout << "cURL failed to connect. Please check your connections" << endl;
		exit(1);}}

/****************************************************************************/

	void BigML::get_model(const string model_iden) {
				
		wait = 1;
		code = ' ';
	
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		
		reset_str(&s);
		init_str(&s);

		cout << endl;
		cout << "Your Model Identifier is: " << model_iden << endl;
		cout << endl;
		cout << "Checking on Status of Model Creation." << endl;
		cout << endl;

		request = "https://bigml.io/model/" + model_iden + "?" + BIGML_AUTH + ";full=false";

		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, request.data());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
			
			while (code != '5') {		  //While request is not completed
				curl_easy_perform(curl);  //Send GET request
				get_status(&s);		  //Check status code
				sleep_for(seconds(wait)); //Send delay to prevent throttling server
				reset_str(&s);		  //Clear buffer
				init_str(&s);
				wait++;}}		  //Increase delay time
		
		else {
			cout << "cURL failed to connect. Please check your connections" << endl;
			exit(1);}
		
		cout << "Your Model with Identifier '" << model_iden << "' Has Been Created." << endl;
		curl_easy_cleanup(curl); //End cURL session
		reset_str(&s);
		cout << endl;}

/****************************************************************************/

void BigML::create_prediction(const string model_iden, const char *col, const float num) {
			
	cout << endl;
	cout << "Creating Prediction." << endl;
	cout << endl;

	cJSON *item1, *item2; //For submitting JSON body
	char *info;	      //For submitting JSON body
	
	resource = "model/" + model_iden;
	request = "https://bigml.io/prediction?" + BIGML_AUTH;
	
	//Creating main JSON body
	root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "model", resource.data());
	cJSON_AddItemToObject(root, "input_data", data = cJSON_CreateObject());
	
	//Creating data JSON body
	cJSON_AddNumberToObject(data, col, num);
	item2 = cJSON_GetObjectItem(data, "data");
	info = cJSON_PrintUnformatted(data);
	cout << "Creating a prediction for the following info:" << endl;
	cout << info << endl;
	cout << endl;
	
	//Getting main JSON body
	item1 = cJSON_GetObjectItem(root, "model");
	json = cJSON_Print(root);
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	cout << "Initializing cURL" << endl;
	
	init_str(&s); //Initialize memory buffer for storing resource identifier & status code for later use
	
	if(curl) {
		struct curl_slist *slist = NULL;
		slist = curl_slist_append(slist, "Accept: "); //Specifying headers so that API knows
		slist = curl_slist_append(slist, "Content-Type: application/json"); //I am submitting JSON
		slist = curl_slist_append(slist, "charsets: utf-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);
		curl_easy_setopt(curl, CURLOPT_URL, request.data());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc); //Get JSON response code using writefunc
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);	//Send response code to struct str s
		curl_easy_perform(curl);
		
		cout << endl;
		cout << "Your Prediction Has Been Created." << endl;
		cout << endl;
		get_prediction_info(&s);
		cout << endl;
		
		curl_slist_free_all(slist); //Free headers
		curl_easy_cleanup(curl); //End cURL session
		cJSON_Delete(root);} //Free JSON root

	else {
		cout << "cURL failed to connect. Please check your connections" << endl;
		exit(1);}}
