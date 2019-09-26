#ifndef TCONNECTIONCLIENT_HPP
#define TCONNECTIONCLIENT_HPP

#include "TConnection.hpp"

#include <QHostAddress>

namespace connection {

//----------------------------------------------------------------
/*!
 * \brief Класс для работы с сервером раздающим блоки ключей для подбора
 */
class TConnectionClient: public TConnection
{
public:
    TConnectionClient();

    void seachServer (quint16) ;            // Поиск сервера в локальной сети
    QHostAddress getIpAddressServer () ;    // Получаем адрес найденного сервера

    bool sendData (TConnection::exchangeProtocol, quint64) {;}      // Виртуальный метод передачи данных
    bool receiveData (TConnection::exchangeProtocol*, quint64*) {;} // Виртуальный метод получения данных

private:

    QHostAddress fIpAddressServer = QHostAddress ()  ; // IP адрес сервера
    bool fIsServerExist {false} ;           // флаг нахождения сервера

private slots:
    void slotHostConnected () ; // Слот срабатывающий при нахождении сервера
};

}
#endif // TCONNECTIONCLIENT_HPP
