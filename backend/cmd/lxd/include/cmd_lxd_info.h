#ifndef CMD_LXD_INFO
#define CMD_LXD_INFO

#include <iserver.h>
#include <cmd_handlers.h>

class CmdLXDInfoHandler : public ICmdHandler {

    public:
        CmdLXDInfoHandler();
        virtual std::string cmd();
        virtual std::string description();
        virtual const ModelCommandAccess &access();
        virtual const std::vector<CmdInputDef> &inputs();
        virtual void handle(ModelRequest *pRequest);

    private:
        QString TAG;
        ModelCommandAccess m_modelCommandAccess;
        std::vector<CmdInputDef> m_vInputs;
};

REGISTRY_CMD(CmdLXDInfoHandler)

#endif // CMD_LXD_INFO

