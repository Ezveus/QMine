#include <QJsonValue>
#include "AuthenticateRequest.hpp"

QMine::Requests::AuthenticateRequest::AuthenticateRequest(QString name, QString pass) {
	id = genUuidv4();
	type = Authenticate;
	if (name.length() + pass.length() <= 4002) {
		this->name = name;
		this->pass = pass;
		this->request = QString("AUTHENTICATE={\"id\":\"") + id + QString("\",\"name\":\"") + this->name + QString("\",\"pass\":\"") +
				this->pass + QString("\"}");
	} else {
		// TODO : raise an exception
		this->name = "";
		this->pass = "";
		this->request = "";
	}
}

QMine::Requests::AuthenticateRequest::~AuthenticateRequest() {
}

QString QMine::Requests::AuthenticateRequest::toQString() {
	return request;
}

const char *QMine::Requests::AuthenticateRequest::toString() {
	return request.toStdString().c_str();
}

int QMine::Requests::AuthenticateRequest::length() {
	return request.length();
}

QString QMine::Requests::AuthenticateRequest::getId() {
	return id;
}

QMine::Requests::RequestType QMine::Requests::AuthenticateRequest::getType() {
	return type;
}

/* void QMine::Requests::AuthenticateRequest::response(Window *w, WinRqstFunc f, const QJsonObject *o) {
	if (!o->contains("status") && !o->value("status").isDouble()) {
		// TODO : raise an exception
		return ;
	}
	if (o->value("status").toDouble() != 0) {
		// TODO : raise an exception
		return ;
	}
	(w->*f)();
} */

void QMine::Requests::AuthenticateRequest::response(Window *w, std::function<void()> f, const QJsonObject *o) {
	if (!o->contains("status") && !o->value("status").isDouble()) {
		// TODO : raise an exception
		return ;
	}
	if (o->value("status").toDouble() != 0) {
		// TODO : raise an exception
		return ;
	}
	f();
}

QString QMine::Requests::AuthenticateRequest::getName() {
	return name;
}

QString QMine::Requests::AuthenticateRequest::getPass() {
	return pass;
}
