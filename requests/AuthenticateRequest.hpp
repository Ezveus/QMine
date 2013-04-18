#include <QString>
#include "IRequest.hpp"

#ifndef AUTHENTICATEREQUEST_HPP
#define AUTHENTICATEREQUEST_HPP

namespace QMine {
	namespace Requests {
		class AuthenticateRequest : public IRequest {
		public:
			AuthenticateRequest(QString name, QString pass);
			virtual ~AuthenticateRequest();

			virtual QString toQString();
			virtual const char *toString();
			virtual int length();
			virtual QString getId();
			virtual RequestType getType();
			// virtual void response(Window *w, WinRqstFunc f, QJsonObject const *o) override;
			virtual void response(Window *w, std::function<void()> f, QJsonObject const *o) override;

			QString getName();
			QString getPass();

		private:
			AuthenticateRequest();

			QString name;
			QString pass;
			QString request;
			QString id;
			RequestType type;
		};
	}
}

#endif // AUTHENTICATEREQUEST_HPP
