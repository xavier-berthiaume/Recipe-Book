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

  // Sets the initial view as profile view, loads objects from database,
  // enables/disables certain widgets based on state
  void setupInitialState();

  Ui::MainWindow *ui;

  QProfile *m_selectedUser;

  QStatusBar *m_status;
  QTabWidget *m_viewSelector;
  ProfileView *m_profileView;

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void launchWindow();

public slots:
  void handleObjectsCounted(ObjectTypes type, int count);
  void handleObjectCreated(ObjectTypes type, Storable *object);
  void handleObjectLoaded(ObjectTypes type, Storable *object);

  // Ui related slots are private
private slots:
  void handleProfileSelected(QProfile *profile);

signals:
  void requestObject(ObjectTypes type, const QUuid &id);
  void requestObjects(ObjectTypes type, int offset = 0, int limit = 10);
  void requestObjectsCounted(ObjectTypes type);
  void createObjectRequested(ObjectTypes type, const QVariantMap &data);
  void updateObjectRequested(ObjectTypes type, Storable *object);
  void deleteObjectRequested(ObjectTypes type, Storable *object);
};

#endif // MAINWINDOW_H
