#include <functional>
#include <QString>
#include <QJsonObject>

#ifndef AREQUEST_HPP
#define AREQUEST_HPP

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

	class ARequest {
	public:
	  virtual ~ARequest() {}

	  virtual QString toQString();
	  virtual const char *toString();
	  virtual int length();
	  virtual QString getId();
	  virtual RequestType getType();
	  virtual void response(QJsonObject const *o, std::function<void()> f);

	  static QString genUuidv4();

	protected:
	  ARequest();
	  ARequest(ARequest const&);
	  ARequest& operator=(ARequest const&);

	  QString request;
	  QString id;
	  RequestType type;
	};
  }
}
#endif // AREQUEST_HPP
