### software_architecture
# Lab 4 Minieieva

GitHub link: https://github.com/DariaMinieieva/software_architecture/tree/micro_mq

In this task message queue was added for the communication between facade service and messages service.

There is an example of what is received by each of three logging services:

Logging service 1:
![img](images/7.png)

Logging service 2:
![img](images/6.png)

Logging service 3:
![img](images/5.png)

And example of what is received by each of two messages service:

Messages service 1:
![img](images/4.png)

Messages service 2:
![img](images/3.png)

And some of the results of GET request to facade, (in square brackets messages returned by logging service and in round - by messages service).
As we can see, all messages from logging service are returned, but messages service only returns what each instance has:

Example 1:
![img](images/2.png)

Example 2:
![img](images/1.png)

## Usage

To make usage of logging service easier, the port should be passed to it.

So to start logging services you should do the following:

```bash
./logging 8083
./logging 8084
./logging 8085
```

And to start messages service you should do this:

```bash
./messages 8081
./messages 8082
```

Right now these ports are hardcoded.