#ifndef EMPLOY_SETTINGS_H
#define EMPLOY_SETTINGS_H

#include <employees.h>
#include <iserver.h>
#include <serversetthelper.h>

#include <QString>
#include <QMutex>

class EmploySettings : public EmployBase {
public:
    EmploySettings();
    static std::string name() { return "EmploySettings"; }
    virtual bool init();

    QString getSettString(const std::string &name);
    void setSettString(const std::string &sName, QString sValue);
    QString getSettPassword(const std::string &name);
    void setSettPassword(const std::string &sName, QString sValue);
    int getSettInteger(const std::string &sName);
    void setSettInteger(const std::string &sName, int nValue);
    bool getSettBoolean(const std::string &sName);
    void setSettBoolean(const std::string &sName, bool bValue);

    bool hasSett(const std::string &sName);
    const std::string &getSettType(const std::string &sName);

	const std::map<std::string, ServerSettHelper*> &listSettings();
	void printSettings();
    nlohmann::json toJson();

private:

    void addNewSetting(ServerSettHelper* pServerSettHelper);
    void initSettingDatabase(ServerSettHelper* pServerSettHelper);
    void updateSettingDatabase(ServerSettHelper* pServerSettHelper);

    std::map<std::string, ServerSettHelper*> m_mapSettings;

    QMutex m_mtxServerSettings;
    std::string TAG;
};

#endif // EMPLOY_SETTINGS_H