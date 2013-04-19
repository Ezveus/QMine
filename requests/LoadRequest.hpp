#ifndef QMINE_REQUESTS_LOADREQUEST_HPP
#define QMINE_REQUESTS_LOADREQUEST_HPP

#include <QFile>
#include "ARequest.hpp"
#include "FileUploader.hpp"

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

	  int getPort();
	  QByteArray getFile();
	  void setUploader(FileUploader *fu);
	  void startUpload();

	private:
	  QString typeToString();

	  QString path;
	  int size;
	  int line;
	  LoadType loadType;
	  int port;
	  QFile *fileToUpload;
	  FileUploader *uploader;
	};

  } // namespace Requests
} // namespace QMine

#endif // QMINE_REQUESTS_LOADREQUEST_HPP
