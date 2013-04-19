#ifndef QMINE_FILE_HPP
#define QMINE_FILE_HPP

#include <QFile>
#include <QString>
#include <QStringList>

namespace QMine {

  class File {
  public:
	File(QString path);
	~File();

	QString getTitle();
	QString getPath();
	QString getFile();

  private:
	QFile *internFile;
	QString title;
	QString path;
	QStringList file;
  };

} // namespace QMine

#endif // QMINE_FILE_HPP
