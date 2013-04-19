#ifndef QMINE_REQUESTS_LOADREQUEST_HPP
#define QMINE_REQUESTS_LOADREQUEST_HPP

#include <QFile>
#include "ARequest.hpp"
#include "FileUploader.hpp"

namespace QMine {
  namespace Requests {

	/*
	 ** This request represents a LOAD request
	 */
	class LoadRequest : public ARequest	{
	public:
	  /*
	   ** It represents the two types of LOAD request
	   */
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
	  QString getPath();

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
