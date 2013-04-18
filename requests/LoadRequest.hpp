#ifndef QMINE_REQUESTS_LOADREQUEST_HPP
#define QMINE_REQUESTS_LOADREQUEST_HPP

#include <QFile>
#include "ARequest.hpp"

namespace QMine {
  namespace Requests {

	class LoadRequest : public ARequest	{
	public:
	  enum LoadType {
		 Up,
		 Down
	   };

	  LoadRequest(QString path, LoadType type);
	  virtual ~LoadRequest();

	private:
	  QString typeToString();

	  QString path;
	  int size;
	  int line;
	  LoadType loadType;
	  int port;
	  QFile *fileToUpload;
	};

  } // namespace Requests
} // namespace QMine

#endif // QMINE_REQUESTS_LOADREQUEST_HPP
