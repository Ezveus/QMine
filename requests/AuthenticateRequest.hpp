#include <QString>
#include "ARequest.hpp"

#ifndef AUTHENTICATEREQUEST_HPP
#define AUTHENTICATEREQUEST_HPP

namespace QMine {
  namespace Requests {
    class AuthenticateRequest : public ARequest {
    public:
      AuthenticateRequest(QString name, QString pass);
      virtual ~AuthenticateRequest();

      QString getName();
      QString getPass();

    private:
      AuthenticateRequest();
      AuthenticateRequest(AuthenticateRequest const&);
      AuthenticateRequest& operator=(AuthenticateRequest const&);

      QString name;
      QString pass;
    };
  }
}

#endif // AUTHENTICATEREQUEST_HPP
