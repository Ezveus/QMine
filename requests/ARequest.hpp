#include <functional>
#include <QString>
#include <QJsonObject>

#ifndef AREQUEST_HPP
#define AREQUEST_HPP

#define MAX_RQST_SZ 4096 // Maximum size the server reads
#define SUCCESSFULL_REQUEST 0 // Status of a successfull request

namespace QMine {
  class Window;
  typedef void (Window::*WinRqstFunc)();

  namespace Requests {

	/*
	 ** All types of requests
	 */
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

	/*
	 ** ARequest : Abstract class representing a request
	 */
	class ARequest {
	public:
	  virtual ~ARequest() {}

	  virtual QString toQString();
	  virtual const char *toString();
	  virtual QByteArray toByteArray();
	  virtual int length();
	  virtual QString getId();
	  virtual RequestType getType();
	  virtual void response(QJsonObject const *o, std::function<void(const QJsonObject *)> f);

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
