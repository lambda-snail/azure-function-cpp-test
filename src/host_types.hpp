#pragma once

#include <map>
#include <string>
#include <vector>

namespace function::host
{
    struct identity_info
    {
        std::string AuthenticationType;
        std::string Actor;
        std::string BootstrapContext;
        std::string Label;
        std::string Name;
        std::string NameClaimType;
        std::string RoleClaimType;
        std::vector<std::string> Claims;
        bool IsAuthenticated;
    };

    struct host_request_info
    {
        std::string Url;
        std::string Method;
        std::string Query;
        std::map<std::string, std::string> Headers;
        std::string Params;
        std::vector<identity_info> Identities;
        std::string Body;
    };

    struct host_request_info_wrapper
    {
        host_request_info Req;
    };

    struct host_request_wrapper
    {
        host_request_info_wrapper Data;
        std::string MetaData;
    };


    struct host_response_outputs
    {
        std::string Message;
        host_request_info Res;
        std::vector<std::string> Logs;
        std::string ReturnValue; // What is this?
    };

    struct host_response_wrapper
    {
        host_response_outputs Outputs;
    };
}
