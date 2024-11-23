#define ASIO_STANDALONE

#include <charconv>
#include <cstdint>
#include <iostream>

#include <crow.h>

#include "host_types.hpp"

static constexpr std::string_view custom_handler_port_str = "FUNCTIONS_CUSTOMHANDLER_PORT=";

/**
 * Extracts the value of an environment variable with a numeric value.
 * @var_string The string of the variable, including the '=' character.
 */
template<typename value_t>
static constexpr bool get_environment_value(std::string_view var_string, char** env_vars, value_t& value)
{
    for(int32_t i = 0; env_vars[i] != nullptr; ++i)
    {
        std::string_view env_var(env_vars[i]);

        if(env_var.starts_with(var_string))
        {
            auto value_str = env_var.substr(var_string.length(), env_var.length());
            if(not value_str.empty())
            {
                if(std::from_chars(env_var.data() + var_string.length(), env_var.data() + env_var.length(), value).ec == std::errc{})
                {
                    return true;
                }
            }
        }
    }

    value = {};
    return false;
};

int main(int32_t argc, char** argv, char** envp)
{
    // The function host exposes certain configurations as environment variables
    // FUNCTIONS_CUSTOMHANDLER_PORT holds the port we are expected to listen to
    uint16_t port{};
    if(not get_environment_value<uint16_t>(custom_handler_port_str, envp, port))
    {
        throw std::runtime_error("Unable to determine port for custom handler");
    }

    std::clog << "[Handler] Listening on port " << port << std::endl;

    crow::SimpleApp app;

    // The function host sends a call to / on startup
    // Not sure what is the appropriate response, but this seems to work
    CROW_ROUTE(app, "/")([]()
    {
        return crow::response(crow::status::OK);
    });

    // If enableForwardingHttpRequest is set,§ the path will be /api/simple-http-trigger
    CROW_ROUTE(app, "/simple-http-trigger").methods("POST"_method)([](crow::request const& req)
    {
        crow::json::rvalue const& json = crow::json::load(req.body);
        crow::json::rvalue const& data = json["Data"];
        crow::json::rvalue const& metadata = json["Metadata"]; // Not MetaData

        crow::json::rvalue const& body = data["req"]["Body"];

        crow::json::wvalue response;
        response["Outputs"]["res"]["body"] = body.s();
        return crow::response(crow::status::OK, response);

        // Echoes the request back to the caller when enableForwardingHttpRequest is set
        // crow::json::wvalue response = crow::json::wvalue::empty_object();
        // for(const auto&[header, value] : req.headers)
        // {
        //     response[header] = value;
        // }
        //
        // crow::response http_response(crow::status::OK, response);
        // http_response.set_header("Content-Type", "application/json");
        //
        // return response;
    });

    app.port(port)/*.multithreaded()*/.run();

    return 0;
}
