#ifndef CMD_CLASSBOOK_PROPOSAL_DELETE_RECORD_HANDLER_H
#define CMD_CLASSBOOK_PROPOSAL_DELETE_RECORD_HANDLER_H

#include <iserver.h>

class CmdClassbookProposalDeleteRecordHandler : public ICmdHandler {

    public:
        CmdClassbookProposalDeleteRecordHandler();
        virtual std::string cmd();
        virtual bool accessUnauthorized();
        virtual bool accessUser();
        virtual bool accessTester();
        virtual bool accessAdmin();
        virtual const std::vector<CmdInputDef> &inputs();
        virtual QString description();
        virtual QStringList errors();
        virtual void handle(QWebSocket *pClient, IWebSocketServer *pWebSocketServer, QString m, QJsonObject obj);

    private:
        QString TAG;
        std::vector<CmdInputDef> m_vInputs;
};

#endif // CMD_CLASSBOOK_PROPOSAL_DELETE_RECORD_HANDLER_H

