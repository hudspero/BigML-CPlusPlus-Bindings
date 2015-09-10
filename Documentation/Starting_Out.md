# Research

During my development of these bindings, I kept a journal record as well as many whiteboard drawings of what I believed I had to 
do. When I first started on this project in July 2015, I had no real clue where to begin. I started to look at the established 
Python Bindings (https://github.com/bigmlcom/python), but there were too many files for me that I lost track of where to begin.

Eventually, I discovered BigML's Webinars. These are roughly hour-long videos that demonstrate the capabilities of the BigML 
API, as well as Machine Learning as a whole from the command line by sending POST and GET requests. It was from this Webinar
specifically (https://www.youtube.com/watch?v=JtudB691AQY) that I was able to get the main ideas and break down what I had to do.

# Discovery

The first thing I learned is that the Bindings, in any language, are <b>NOT</b> a recreation of the BigML API. They are an 
<b>interface</b> used to <b>interact</b> with the API directly, without touching any backend code directly.

Going from the previously-linked webinar, as well as many conversations with the senior staff, I nailed down the steps I needed
for each feature's corresponding function:

<b>1)</b> Set the user authentication (get the username and API key that is unique to each user)

<b>2)</b> Get said authentication

<b>3)</b> Get the necessary information for the creation of each resource

<b>4)</b> Construct JSON body for the HTTP POST request

<b>5)</b> Launch the HTTP request

<b>6)</b> Parse the JSON response from each request and get the necessary information

From there, I was able to build a rough outline of the C++ BigML class and its member functions

  <b>-Private member functions would be used for fetching information from the JSON responses.</b>
  
  <b>-Public member functions would be called by the user for creation, fetching, updating, and deletion of resources.</b>
  
# Development

The first tool I got my hands on was libcURL, and thankfully, there were tutorials provided for me to look at and study from
(http://curl.haxx.se/libcurl/c/libcurl-tutorial.html). 
This is how the HTTP requests are launched in the C++ Bindings (since libcURL is a library built in C, I was able
to use it in C++ quite well). I was able to build the request URLs through using string objects and the overloaded + operator 
to concactenate multiple strings together. 

-For resource creation, I have a defined base URL in each function + BIGML_AUTH
-For resource fetching, I have that same base URL + resource_identifier + "?" + BIGML_AUTH

The second tool I got was cJSON and this took some serious work. There were no tutorials or documentation available for me
so I had to resort to Stackoverflow and the libcURL mailing list for an idea of what I was supposed to do. Once I thought I had
a clue, I launched the POST request to the API, only to be returned an "Invalid Format" error. This took many hours of
frustration before I found that my JSON body had to be formatted instead of unformatted.

SEE: (item = cJSON_Print) vs <s>(item = cJSON_PrintUnformatted)</s>

With these two tools in hand, I was able to specify the request URL and post the JSON body. It wouldn't be until the halfway mark
that I would store the JSON response (respbuffer.c) and the private member functions to parse through them. This meant that the 
screen could be less cluttered, and I would get full control over what the user should see.

I developed V1.0.0 of the Bindings over the course of two and a half months. To this day, I am still adding features and I will
continue to support them in the future.
