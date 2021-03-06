#ifndef TCOMMONSERVER_H
#define TCOMMONSERVER_H

#include <QtGlobal>
#include <QHostAddress>
#include <QDateTime>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "TConnectionServer.hpp"
#include "TCommonDefine.hpp"
#include "TClientDescr.hpp"

using namespace connection ;

namespace server {

namespace commonDefineServer {

static std::condition_variable cvLog ;                      ///< Условная переменная для синхронизации доступа к модели отображения лога работы
static std::condition_variable cvKey ;                      ///< Условная переменная для синхронизации доступа к модели отображения лога подбора ключей
static std::atomic <bool> isLogBlock (false) ;              ///< Флаг добавления записи в контейнер модели лога работы
static std::atomic <bool> isKeyBlock (false) ;              ///< Флаг добавления записи в контейнер модели лога подбора ключей

static std::mutex mutexNewConnection  ;                     ///< mutex для синхронизации доступа к контейнеру содержащий список всех новых подключений
static std::mutex mutexLog  ;                               ///< mutex для синхронизации доступа к контейнеру содержащему лог (т.к. там vector)
static std::mutex mutexKey  ;                               ///< mutex для синхронизации доступа к контейнеру содержащему лог по подбру ключей (т.к. там vector)
//-----------------------------------------------------------------------------

const static qint32 timerLogRefresh {1000} ;                ///< Период срабатывания таймера для обновления логов

const static QString toolTipRun {"Запуск подбора ключей"} ; // Подсказки выводимые на кнопках
const static QString toolTipPause {"Временная приостановка подбора ключей"} ;
const static QString toolTipExit {"Завершение приложения"} ;
const static QString toolTipStop {"Завершение подбора ключей"} ;
//-------------------------------------------------------------------------------------
typedef std::shared_ptr <TClientDescr> tdPtrClientDescr ;   ///< typedef для указателя на описание подключения клиента

                    /// Структура данных для одной итерации подбора
struct brutForceItem {
    tdPtrClientDescr ptrClientDesvt {nullptr} ;                     ///< Указатель на хост которому передан блок
    QString keyFound {""} ;                                         ///< Найденный ключ
} ;
//-------------------------------------------------------------------------------------
typedef std::shared_ptr <QTcpSocket> tdTcpSocket ; ///< typedef указателя на QTcpSocket
                    /// Описание подключения клиента
struct clientDescr {
    QDateTime dateTime {QDateTime::currentDateTime()};        ///< Время выполнения последней операции
    TConnection::state clientState {TConnection::stUnknown} ; ///< Состояние клиента/сервера. Например, для завершения работы очереди threadClient устанавливается состояние stAppClose
    tdTcpSocket ptrTcpSocket ;                                ///< Указатель на сокет обрабатывающий работу с удаленным клиентом

    bool operator () (const clientDescr& inFirst, const clientDescr& inSecond)  const { return (inFirst.ptrTcpSocket -> peerAddress().toIPv4Address() < inSecond.ptrTcpSocket ->peerAddress().toIPv4Address()) ; }
} ;
typedef std::shared_ptr <clientDescr> tdClientDescr ;   ///< typedef для указателя на описание клиента
//--------------------------------------------------------------------------------------
                    /// Описание структуры записи в лог
struct logItem {
    QTime itemTime {QTime::currentTime()} ; ///< Время события
    QString host {""} ;                     ///< Хост с которым выполняется обмен данными
    TConnection::exchangeProtocol command ; ///< Выполненная команда
    qint64 date ;                           ///< Данные передаваемые/получаемые
    QString comments {""} ;                 ///< Комментарии
} ;
typedef std::shared_ptr <logItem> tdLogItem ;   ///< typedef для указателя на запись в лог
                                            // Заголовки колонок лога
static QString logItemHeaderTime {"Время"} ;
static QString logItemHeaderHost {"Хост"} ;
static QString logItemHeaderCommand {"Команда"} ;
static QString logItemHeaderData {"Данные"} ;
static QString logItemHeaderComment {"Комментарий"} ;

                    /// Описание структуры записи в лог по подбру ключей
struct keyItem {
    QTime itemTime {QTime::currentTime()} ; ///< Время события
    QString host {""} ;                     ///< Хост с которым выполняется обмен данными
    QString key {""} ;                      ///< Найденный ключ
    QString result {""};                    ///< Результат проверки ключа
} ;
typedef std::shared_ptr <keyItem> tdKeyItem ;   ///< typedef для указателя на запись в лог по подбру ключей
                                            // Заголовки колонок лога по обработке найденных ключей
static QString keyItemHeaderTime {"Время"} ;
static QString keytemHeaderHost {"Хост"} ;
static QString keyItemHeaderKey {"Найденный ключ"} ;
static QString keyItemHeaderResult {"Результат проверки"} ;




//-----------------------------------------------------------------------------

}
}
#endif // TCOMMONSERVER_H
