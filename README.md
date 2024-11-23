# Azure Function in C++

This is a bare-bones example of how to make an Azure function in C++. It contains one function `simple-http-trigger`
that simply returns the http request that was sent to it.

The example uses crow to set up the web server for simplicity. The project may be used
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

On start, the function host will send the following request to the worker/handler:

```
GET / HTTP/1.1
Host: 127.0.0.1:XXX
```

I'm not sure yet what is the appropriate way to respond to this, but currently the example is returning an empty OK response
and it seems the host is accepting this.

## Forwarding Requests

If we set the flag `enableForwardingHttpRequest` in host.json the function host will send a copy of incoming requests
to our function, which can come in handy if we only need http triggers. Turning this off adds extra structure to the
requests coming from the function host.

The initial version of this test made use of the `enableForwardingHttpRequest`. Note that the route changes when using this setting.

# References

- https://learn.microsoft.com/en-us/azure/azure-functions/create-first-function-vs-code-other?tabs=go%2Clinux
  - Official documentation
- https://www.youtube.com/watch?v=2hNdkYInj4g
    - Minimal video demonstrating how to do this in Go
- https://think-async.com/Asio/asio-1.30.2/doc/asio/tutorial/tutdaytime1.html
  - The web server is based on this
