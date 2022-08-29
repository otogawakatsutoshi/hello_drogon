#include "UserCtrl.h"

using namespace demo::v1;

// Add definition of your processing function here

// void UserCtrl::login(const HttpRequestPtr &req,
//                  std::function<void (const HttpResponsePtr &)> &&callback,
//                  std::string &&userId,
//                  const std::string &password)
// {
//     LOG_DEBUG<<"User "<<userId<<" login";
//     //Authentication algorithm, read database, verify, identify, etc...
//     //...
//     Json::Value ret;
//     ret["result"]="ok";
//     ret["token"]=drogon::utils::getUuid();
//     auto resp=HttpResponse::newHttpJsonResponse(ret);
//     callback(resp);
// }
// void UserCtrl::getInfo(const HttpRequestPtr &req,
//                    std::function<void (const HttpResponsePtr &)> &&callback,
//                    std::string userId,
//                    const std::string &token) const
// {
//     LOG_DEBUG<<"User "<<userId<<" get his information";

//     //Verify the validity of the token, etc.
//     //Read the database or cache to get user information
//     Json::Value ret;
//     ret["result"]="ok";
//     ret["user_name"]="Jack";
//     ret["user_id"]=userId;
//     ret["gender"]=1;
//     auto resp=HttpResponse::newHttpJsonResponse(ret);
//     callback(resp);
// }

void UserCtrl::loginGet(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback
                )
{
    // LOG_DEBUG<<"User "<<userId<<" login";
    HttpViewData viewdata;
    viewdata.insert("title", "list parameters");
    viewdata.insert(
        "parameters", 
        req->getParameters()  // Getパラメータはこのように取得
    );
    
    // ListParaView.cspというビューにデータを渡す (詳細は後述)
    auto resp = drogon::HttpResponse::newHttpViewResponse("ListParaView.csp", viewdata);
    //Authentication algorithm, read database, verify, identify, etc...
    //...
    // Json::Value ret;
    // ret["result"]="ok";
    // ret["token"]=drogon::utils::getUuid();
    // auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void UserCtrl::loginPost(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 std::string &&userId,
                 const std::string &password)
{
    LOG_DEBUG<<"User "<<userId<<" login";
    //Authentication algorithm, read database, verify, identify, etc...
    //...
    Json::Value ret;
    ret["result"]="ok";
    ret["token"]=drogon::utils::getUuid();
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}