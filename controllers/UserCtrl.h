#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace demo
{
namespace v1
{
class UserCtrl : public drogon::HttpController<UserCtrl>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(UserCtrl::get, "/{2}/{1}", Get); // path is /UserCtrl/{arg2}/{arg1}
    // METHOD_ADD(UserCtrl::your_method_name, "/{1}/{2}/list", Get); // path is /UserCtrl/{arg1}/{arg2}/list
    // ADD_METHOD_TO(UserCtrl::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    // methodとルーティング両方表示
    // METHOD_ADD(UserCtrl::login,"/token?userId={1}&passwd={2}",Post);
    // METHOD_ADD(UserCtrl::getInfo,"/{1}/info?token={2}",Get);
    METHOD_ADD(UserCtrl::loginGet,"/user/login",Get);
    METHOD_ADD(UserCtrl::loginPost,"/user/login/aa",Post);
    // METHOD_ADD(UserCtrl::getInfo,"/{1}/info?token={2}",Get);
    METHOD_LIST_END

    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    // void login(const HttpRequestPtr &req,
    //            std::function<void (const HttpResponsePtr &)> &&callback,
    //            std::string &&userId,
    //            const std::string &password);
    // void getInfo(const HttpRequestPtr &req,
    //              std::function<void (const HttpResponsePtr &)> &&callback,
    //              std::string userId,
    //              const std::string &token) const;
    void loginGet(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback
    );
    void loginPost(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string &&userId,
               const std::string &password);
};
}
}