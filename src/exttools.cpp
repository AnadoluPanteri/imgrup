#include "exttools.h"

Tools::Tools(QObject *parent)
    : QObject(parent)
 {
  }

Tools::~Tools()
{

}

void Tools::share_link(QString linktoshare){

        // thanks matyjas for example on — https://github.com/matyjas/share-bear/
        QString title = "Imgrup";

        QString desc = "uploaded to imgur with N9";


        MDataUri duri;

        duri.setMimeType ("text/x-url");

        duri.setTextData (linktoshare);

        duri.setAttribute ("title", title);

        duri.setAttribute ("description", desc);

        if (duri.isValid() == false) {

            qCritical() << "Invalid URI";

            return;
        }


        QStringList link;

        link << duri.toString();
    ShareUiInterface shareIf("com.nokia.ShareUi");
    shareIf.share(link);

}

void Tools::account_tokens(){
    qDebug("account test");
    Accounts::Account* m_account = 0;
    Accounts::Manager m_manager;
    Accounts::AccountIdList accounts = m_manager.accountList();
    foreach (Accounts::AccountId id, accounts) {

        Accounts::Account* account = m_manager.account(id);


        if (account->providerName() == "twitter") {
            qDebug() << "Accounts found?";
            qDebug() << "    username =" << account->valueAsString("username");
            m_account = account;
            break;
        }
    }

    int credentialsId = 0;
    if (m_account) {
        if (m_account->enabled()) {
            // If there is an enabled tmo account, get corresponding SignOn credentials
            qDebug() << "Accounts: Found account" << m_account->displayName();
            credentialsId = m_account->valueAsInt("CredentialsId");

            qDebug() << "    " << m_account->allKeys();
            qDebug() << "    username =" << m_account->valueAsString("username");
            qDebug() << "    CredentialsId =" << credentialsId;
            qDebug() << "    name =" << m_account->valueAsString("token");
            Accounts::ServiceList services = m_account->services();
            foreach (Accounts::Service* service, services) {
                qDebug() << "    service:" << service->name();
            }
        } else {
            qDebug() << "Accounts: Found disabled account" << m_account->displayName();
        }
    }


}


