#include <functional>
#include <QString>
#include <QJsonObject>

#ifndef IREQUEST_HPP
#define IREQUEST_HPP

#define MAX_RQST_SZ 4096

namespace QMine {
	class Window;
	typedef void (Window::*WinRqstFunc)();

	namespace Requests {
		enum RequestType {
			Authenticate,
			Signup,
			Exec,
			Insert,
			Move,
			Backspace,
			Delete,
			Load,
			Shell,
			Sync,
			Response,
			Quit,
			Unknown
		};

		QString genUuidv4();

		class IRequest {
		public:
			virtual ~IRequest() {}

			virtual QString toQString() = 0;
			virtual const char *toString() = 0;
			virtual int length() = 0;
			virtual QString getId() = 0;
			virtual RequestType getType() = 0;
			virtual void response(Window *w, std::function<void()> f, QJsonObject const *o) = 0;
		};
	}
}
#endif // IREQUEST_HPP
