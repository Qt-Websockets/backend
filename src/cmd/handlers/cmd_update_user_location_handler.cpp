#include "../headers/cmd_update_user_location_handler.h"
#include "../../tasks/update_user_location_task.h"
#include <QJsonArray>
#include <QThreadPool>

CmdUpdateUserLocationHandler::CmdUpdateUserLocationHandler(){
}

QString CmdUpdateUserLocationHandler::cmd(){
	return "updateuserlocation";
}

bool CmdUpdateUserLocationHandler::accessUnauthorized(){
	return false;
}

bool CmdUpdateUserLocationHandler::accessUser(){
	return false;
}

bool CmdUpdateUserLocationHandler::accessTester(){
	return false;
}

bool CmdUpdateUserLocationHandler::accessAdmin(){
	return true;
}

const QVector<CmdInputDef> &CmdUpdateUserLocationHandler::inputs(){
	return m_vInputs;
};

QString CmdUpdateUserLocationHandler::description(){
	return "This method will be try update user location by lastip";
}

QStringList CmdUpdateUserLocationHandler::errors(){
	QStringList	list;
	return list;
}

void CmdUpdateUserLocationHandler::handle(QWebSocket *pClient, IWebSocketServer *pWebSocketServer, QJsonObject obj){
	IUserToken *pUserToken = pWebSocketServer->getUserToken(pClient);
	
	if(pUserToken == NULL){
		pWebSocketServer->sendMessageError(pClient, cmd(), Errors::NotAuthorizedRequest());
		return;
	}

	if(!pUserToken->isAdmin()){
		pWebSocketServer->sendMessageError(pClient, cmd(), Errors::AllowedOnlyForAdmin());
		return;
	}

	QJsonValueRef vUserID = obj["userid"];
	// bool bConvert = false;
	
	if(!vUserID.isDouble()){
		pWebSocketServer->sendMessageError(pClient, cmd(), Errors::QuestIDMustBeInteger());
		return;
	}

	int userid = vUserID.toInt();
	if(userid == 0){
		pWebSocketServer->sendMessageError(pClient, cmd(), Errors::QuestIDMustBeNotZero());
		return;
	}

	QSqlDatabase db = *(pWebSocketServer->database());
	QString lastip = "";
	{
		QSqlQuery query(db);
		query.prepare("SELECT * FROM users WHERE id = :userid");
		query.bindValue(":userid", userid);
		query.exec();
		if (query.next()) {
			QSqlRecord record = query.record();
			lastip = record.value("last_ip").toString();
		}
	}
	
	if(lastip == "" || lastip == NULL){
		QSqlQuery query(db);
		query.prepare("SELECT * FROM users_ips WHERE userid = :userid ORDER BY id DESC");
		query.bindValue(":userid", userid);
		query.exec();
		if (query.next()) {
			QSqlRecord record = query.record();
			lastip = record.value("ip").toString();
		}
	}

	qDebug() << "lastip: " << lastip;
	qDebug() << "userid: " << userid;

	UpdateUserLocationTask *pUpdateUserLocationTask = new UpdateUserLocationTask(pWebSocketServer, userid, lastip);
	QThreadPool::globalInstance()->start(pUpdateUserLocationTask);

	QJsonObject jsonData;
	jsonData["cmd"] = QJsonValue(cmd());
	jsonData["result"] = QJsonValue("DONE");
	pWebSocketServer->sendMessage(pClient, jsonData);
}