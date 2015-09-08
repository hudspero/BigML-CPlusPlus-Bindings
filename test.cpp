/**************************************************/
//			    TEST.CPP						                  
//												                        
// Created to test the C++ Bindings for BigML API 
// Created by Robert L. Hudspeth				          
//												                        
// Last Modified: September 4th, 2015			        
/**************************************************/

#include "BigML.hpp"

int main() {

	//Create object of BigML class
	BigML object;
	
	//Get user authentication from environment variables
	object.set_user_info();
	
	//		NOTE					     
	// You can also authenticate through entering    
	// your username and API key via string literals 
	// object.set_user_info("username", "api_key");  
	
	//Create a source from remote URL and give it a name
	object.create_remote_source("https://static.bigml.com/csv/iris.csv", "source");
	
		//Check on status for completion from source identifier
		object.get_source(object.get_src());
	
	//Create a dataset from the identifier source identifier
	object.create_dataset(object.get_src());
	
		//Check on status for completion from dataset identifier
		object.get_dataset(object.get_dts());
	
	//Create an anomaly detection from dataset identifier
	object.create_anomalies(object.get_dts());
	
		//Check on status for completion from anomaly identifier
		object.get_anomalies(object.get_ano());
	
	//Create a cluster grouping from dataset identifier
	object.create_cluster(object.get_dts());
	
		//Check on status for completion from cluster identifier
		object.get_cluster(object.get_cls());
	
	//Create an ensemble from dataset identifier
	object.create_ensemble(object.get_dts());
	
		//Check on status for completion from ensemble identifier
		object.get_ensemble(object.get_ens());
		
	//Create a model from dataset identifier
	object.create_model(object.get_dts());
	
		//Check on status for completion from model identifier
		object.get_model(object.get_mod());
		
	//Create a prediction from model identifier, and which
	object.create_prediction(object.get_mod(), "000000", 4.3);
	    
    return 0;

}
