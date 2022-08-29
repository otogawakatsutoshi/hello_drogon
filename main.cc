#include <iostream>
#include <exception>
#include <stdexcept>
#include <optional>
#include <argparse/argparse.hpp>
#include <drogon/drogon.h>

// cloud_run環境下かどうか判定
bool is_cloudrun () {

    bool judge = false;
    // K_SERVICEがセットされているかどうかでCloudRun無いかそうでないかをチェック。
    if (std::getenv("K_SERVICE"))
    {
        judge = true;
    }

    return judge;
}

// http 
void http_listener () {

    // 環境変数チェック。
    std::string port = std::getenv("PORT");

    // check port environment 
    if ( port.empty())
    {
        throw "PORT environment assign value";
    }

    for(const char c : port)
    {
    	if(! std::isdigit(c)) {
           throw "PORT only contains numeric";
        }
    }
    std::cout << "start http listener." << std::endl;
    // http connection
    drogon::app().addListener(
        std::getenv("BIND"),
        std::stoi(port)
    );
}

// https
void https_listener (const std::string& keyfile, const std::string& certfile) {
    // 環境変数チェック。
    std::string port = std::getenv("PORT");

    // check port environment 
    if ( port.empty())
    {
        throw "PORT environment assign value";
    }

    for(const char c : port)
    {
    	if(! std::isdigit(c)) {
           throw "PORT only contains numeric";
        }
    }
    std::cout << "start https listener." << std::endl;
    // https connection
    drogon::app().addListener(
        std::getenv("BIND"),
        std::stoi(port),
        true,
        certfile,
        keyfile
    );
}

//Load config file
void load_config () {
    //drogon::app().loadConfigFile("../config.json");
}

// describe command parameter
void describe (argparse::ArgumentParser& program) {
    program.add_argument("--keyfile")
        .default_value(std::string(""))
        .help("keyFile for ssl");

    program.add_argument("--certfile")
        .default_value(std::string(""))
        .help("certfile for ssl");

    program.add_description("drogon init args for ");
    program.add_epilog("Possible things include betingalw, chiz, and res.");
}

// parse 処理
void parse (argparse::ArgumentParser& program, const int& argc, const char *argv[]) {
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
}

// invoke
void invoke (const int& argc, const char *argv[]) {

    argparse::ArgumentParser program("program_name");

    describe(program);

    parse(program, argc, argv);
    
    // 割当
    const std::string keyfile = program.get<std::string>("--keyfile");
    const std::string certfile = program.get<std::string>("--certfile");

    // keyfileで処理分け。
    if (keyfile.empty() ^ certfile.empty())
    {
        std::cerr << "both certfile and keyfile assined value." << std::endl;
        std::exit(1);
    } else if (keyfile.empty() && certfile.empty()) {
        http_listener();
    } else {
        https_listener(keyfile, certfile);
    }
}

int main(const int argc,const char *argv[]) {

    invoke(argc, argv);
    load_config();
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
