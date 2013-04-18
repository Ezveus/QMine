#include <QJsonValue>
#include "AuthenticateRequest.hpp"

QMine::Requests::AuthenticateRequest::AuthenticateRequest(QString name, QString pass) : ARequest() {
  id = ARequest::genUuidv4();
  type = Authenticate;
  this->name = name;
  this->pass = pass;
  this->request = QString("AUTHENTICATE={\"id\":\"") + id + QString("\",\"name\":\"") + this->name + QString("\",\"pass\":\"") +
	  this->pass + QString("\"}");
  if (request.length() > 4096) {
	// TODO : raise an exception
  }
}

QMine::Requests::AuthenticateRequest::~AuthenticateRequest() {
}

QString QMine::Requests::AuthenticateRequest::getName() {
  return name;
}

QString QMine::Requests::AuthenticateRequest::getPass() {
  return pass;
}
