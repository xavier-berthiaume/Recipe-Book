#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../models.h"
#include "../objecttypes.h"
#include "profileview.h"

#include <QMainWindow>
#include <QVariantMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  Ui::MainWindow *ui;

  QProfile *m_selectedUser;

  QTabWidget *m_viewSelector;
  ProfileView *m_profileView;

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void handleObjectCreated(ObjectTypes type, Storable *object);
  void handleObjectLoaded(ObjectTypes type, Storable *object);

  // Ui related slots are private
private slots:

signals:
  void requestObject(ObjectTypes type, const QUuid &id);
  void requestObjects(ObjectTypes type, int offset = 0, int limit = 10);
  void createObjectRequested(ObjectTypes type, const QVariantMap &data);
  void updateObjectRequested(ObjectTypes type, Storable *object);
  void deleteObjectRequested(ObjectTypes type, Storable *object);
};

#endif // MAINWINDOW_H
