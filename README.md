# Azure Function in C++

This is a bare-bones example of how to make an Azure function in C++. It contains one function `simple-http-trigger`
that simply returns the http request that was sent to it.

There is no error handling and all http related stuff are hard-coded, as the goal of the
project was to investigate what the minimum amount of work is to make it work locally. The project may be used
further in the future to investigate if it is possible to use other Azure services that are usually
integrated in an Azure function.

Not sure yet if it will work in the cloud as-is, or if you need to e.g. put it in a docker container first.

# How to Run

Requires Azure functions core tools to run locally.

- Compile
- `cd <cmake-folder>`
- `func start`

# Notes

## Port and Other Settings

The function host exposes some settings to our function via environment variables. These are called `FUNCTIONS_*` or `FUNCTIONS_CUSTOMHANDLER_*`.

The port we are supposed to listen to in order to communicate with the host is found in `FUNCTIONS_CUSTOMHANDLER_PORT`.

## Initial Request

On start, the function host will send the following request to the function:

```
GET / HTTP/1.1
Host: 127.0.0.1:44877
```

I'm not sure yet what is the appropriate way to respond to this, but it seems the host is not
unhappy with the current state (echo the request back) since subsequent requests to the function are working.

## Forwarding Requests

If we set the flag `enableForwardingHttpRequest` in host.json the function host will send a copy of incoming requests
to our function, which can come in handy if we only need http triggers. Turning this off adds extra structure to the
requests coming from the function host. This is not handled here as it would need more preparation than this minimal
project, but I may look at this in the future.

# References

- https://learn.microsoft.com/en-us/azure/azure-functions/create-first-function-vs-code-other?tabs=go%2Clinux
  - Official documentation
- https://www.youtube.com/watch?v=2hNdkYInj4g
    - Minimal video demonstrating how to do this in Go
- https://think-async.com/Asio/asio-1.30.2/doc/asio/tutorial/tutdaytime1.html
  - The web server is based on this
