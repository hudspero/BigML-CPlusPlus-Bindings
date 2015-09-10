#BigML-CPlusPlus-Bindings
C++ Bindings for BigML Machine Learning API V1.0.0

<b>created by Robert L. Hudspeth</b>

Created to be used with the BigML Machine Learning API (https://bigml.com)

# Requirements
*) libcURL (https://curl.haxx.se)

*) cJSON (http://sourceforge.net/projects/cjson/)

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

  -The first gets the username and API key from environment variables <i>[object.set_user_info();]</i>. 
  
  -The second choice gets the username and API key from string literals <i>[object.set_user_info("username", "api_key");]</i>.

When a function is declared, a JSON body will be constructed, containing your user authentication and the information passed into the function arguments. For example, to create a remote source, you would call the function <i>[object.create_remote_source("s3://bigml-public/csv/iris.csv", "source");]</i>, where the URL is a link to a remote source, and "source" is the name.

Once the JSON body is constructed, it will be sent in an HTTP POST request via libcURL, where it will be processed by the BigML API, and a resource will be created. Everything you submit to the API is viewable on the BigML Dashboard. 

In return, you will get a unique resource identifier, which you can use to view on the BigML dashboard, or create a new resource of your choice.

<i>NOTE: To create a resource, you cannot use any random identifier. To learn more, visit (https://bigml.com/developers)</i>

To check on the status of the source for its completion, calling the function <i>[object.get_source(object.get_src());]</i> will send an HTTP GET request based on the resource identifier stored in <i>[object.get_src();]</i>. Alternatively, you could call the function as <i>[object.get_source("identifier");]</i>.

The majority of functions follow a similar pattern, building off an existing resource's identifier. To create a dataset, for example, after creating a source, all you have to call is <i>[object.create_dataset(object.get_src());]</i>.

The only function that behaves differently is <i>[object.create_prediction("model_identifier", "column", number);]</i>, where the prediction is created instantaneously and a confidence for that particular prediction is returned.

Any questions about these Bindings can be sent directly towards me. Anything else is better sent towards BigML (https://github.com/bigmlcom).

Last README Update: 09/09/2015
