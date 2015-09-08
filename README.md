#BigML-CPlusPlus-Bindings
C++ Bindings for BigML Machine Learning API V1.0.0

Created to be used with the BigML Machine Learning API (https://bigml.com)

<b>created by Robert L. Hudspeth</b>
#How does it work? 

1) Include BigML.hpp

2) Create object of BigML class

3) Set user authentication

4) Declare the functions you want to use

To set user authentication, you have two choices. The first gets the username and API key from environment variables <i>[object.set_user_info();]</i>. The second choice gets the username and API key from string literals <i>[object.set_user_info("username", "api_key");]</i>.

When the functions are declared, a JSON body will be constructed, containing your user authentication and the information passed into the function arguments. For example, to create a remote source, you would call the function <i>[object.create_remote_source("s3://bigml-public/csv/iris.csv", "source");]</i>.

The data within the function arguments will be sent in an HTTP POST request via libcURL, where it will be processed by the BigML API, and a resource will be created. Everything you submit to the API is viewable on the BigML Dashboard. 

To check on the status of the source for its completion, calling the function <i>[object.get_source(object.get_src());]</i> will send an HTTP GET request based on the resource identifier stored in <i>[object.get_src()]</i>. Alternatively, you could call the function as <i>[object.get_source("identifier");]</i>.

The majority of functions follow a similar pattern, building off an existing resource's identifier. To create a dataset, for example, after creating a source, all you have to call is <i>[object.create_dataset(object.get_src());]<i/>.

The only function that behaves differently is <i>[object.create_prediction("model_identifier", "column", number);]</i>, where the prediction is created instantaneously and a confidence for that particular prediction is returned.

Last Update: 09/08/2015
