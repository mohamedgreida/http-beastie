#include "utils.hpp"

namespace beast = boost::beast;
namespace http = beast::http;

http::response<http::string_body> handle_request(const http::request<http::string_body>& req) {
  http::response<http::string_body> res;

  res.version(req.version());
  res.keep_alive(false);

  res.set(http::field::server, "http-beastie");
  res.set(http::field::content_type, "text/html");

  if (req.method() == http::verb::get) {
    if (req.target() == "/") {
      res.result(http::status::ok);
      res.body() = file_contents("static/index.html");
    } else if(req.target() == "/greida"){
      res.result(http::status::ok);
      res.body() = file_contents("static/greida.html");
    } else {
      res.result(http::status::not_found);
      res.body() = "<h1 style=\"text-align: center;\">404 Not Found</h1>";
    }
  } else {
    res.result(http::status::method_not_allowed);
    res.set(http::field::allow, "GET");
    res.body() = "<h1 style=\"text-align: center;\">405 Method Not Allowed</h1>";
  }

  res.prepare_payload();
  return res;
}
std::string file_contents(std::string filepath){
  std::ifstream file(filepath);
  if(!file){
    std::cout << "File not found\n";
    return "";
  }else{
    std::string line, contents= "";
    while(std::getline(file, line)){
      contents += line + '\n';
    }
    return contents;
  }
}
