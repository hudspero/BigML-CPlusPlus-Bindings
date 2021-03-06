#BigML-CPlusPlus-Bindings
C++ Bindings for BigML Machine Learning API

<b>created by Robert L. Hudspeth</b>

Created to be used with the <a href="https://bigml.com">BigML Machine Learning API</a>

# Requirements
*) <a href="https://curl.haxx.se">libcURL</a>

*) <a href="http://sourceforge.net/projects/cjson/">cJSON</a>

*) GCC 4.2.1+

#How does it work? 

<b>1)</b> Get the required tools

<b>2)</b> Download the files in this repo in the same directory as your main file

<b>3)</b> Include "BigML.hpp"

<b>4)</b> Create object of BigML class

<b>5)</b> Set user authentication

<b>6)</b> Declare the functions you want to use

<b>7)</b> When compiling, <b>BE SURE TO INCLUDE THE -lcurl FLAG! WITHOUT THIS, IT WILL NOT COMPILE!</b>

# What Is Happening?

To set user authentication, you have two choices. 

  -The first gets the username and API key from environment variables 
  
      object.set_user_info(); 
  
  -The second choice gets the username and API key from string literals 
  
      object.set_user_info("username", "api_key");

If your username or API key are invalid, you will receive a 401 Error. If you don't have enough credits, you will receive a 402 Error. More info on bad status codes can be found <a href="https://bigml.com/developers/status_codes">here</a>.

When a function is declared, a JSON body will be constructed, containing your user authentication and the information passed into the function arguments. For example, to create a remote source, you would call the function 

    object.create_remote_source("s3://bigml-public/csv/iris.csv", "source");
    
where the URL is a link to a remote source, and "source" is the name.

Once the JSON body is constructed, it will be sent in an HTTP POST request via libcURL, where it will be processed by the BigML API, and a resource will be created. Everything you submit to the API is viewable on the BigML Dashboard. 

In return, you will get a unique resource identifier, which you can use to view on the BigML dashboard, or create a new resource of your choice.

<i>NOTE: To create a resource, you cannot use any random identifier. To learn more, visit <a href="https://bigml.com/developers">here</a></i>.

To check on the status of the source for its completion, calling the function 

    object.get_source(object.get_src());
    
will send an HTTP GET request based on the resource identifier stored in 

    object.get_src();
    
Alternatively, you could call the function as 

    object.get_source("identifier");
    
The majority of functions follow a similar pattern, building off an existing resource's identifier. To create a dataset, for example, after creating a source, all you have to call is 

    object.create_dataset(object.get_src());

The only function that behaves differently is 

    object.create_prediction("model_identifier", "column", number);
    
where the prediction is created instantaneously and a confidence for that particular prediction is returned.

Any questions about these Bindings can be sent directly towards me. Anything else is better sent towards <a href="https://github.com/bigmlcom">BigML</a>.

# What Can You Do?

As of 9/10/15, the current list of features are:

-Create a Remote Source

-Build a Dataset

-Detect a Anomalies

-Build a Cluster

-Build an Ensemble

-Build a Model

-Develop a Prediction

Last README Update: 04/07/2017
