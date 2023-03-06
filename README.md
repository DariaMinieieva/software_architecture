### software_architecture
# Lab 1 Daria Minieieva
## POST/GET requests screenshots

Here is example of running POST request with text "msggg1". <br>
![img.png](images/img.png)

And here is example of output to the "logging" console. <br>
![img.png](images/img_2.png)

Example of GET request that returns message from "logging" service and "not implemented yet" from "messages" service. <br>
![img.png](images/img_3.png)

And here is result of GET request after two more POST request with messages "msggg2" and "msggg3". <br>
![img.png](images/img_4.png)

And output of "logging" console. <br>
![img.png](images/img_5.png)

## Libraries

This lab is done on C++ using httpserver (https://github.com/etr/libhttpserver) for http server, cpr (https://github.com/libcpr/cpr) and Boost UUID for UUID generation. Also tbb concurrent hash map is used to store data in logging service.
