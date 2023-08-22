#include <crow.h>

int main(){
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){ 
        return "Hello world"; 
    });

    CROW_ROUTE(app, "/welcome")([](){
        auto page = crow::mustache::load_text("crow-api.html");
        return page;
    });

    CROW_ROUTE(app, "/me/<string>")([](std::string name){ 
        auto page = crow::mustache::load("welcome-you.html"); 
        crow::mustache::context ctx({{"name", name}});    
        return page.render(ctx);                            
    });

    CROW_ROUTE(app, "/you").methods(crow::HTTPMethod::POST)([](){ 
        return "Hello world from post";
    });

    app.port(8080).multithreaded().run(); 
}
