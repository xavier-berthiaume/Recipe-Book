#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include "abstractview.h"
#include "profilelistmodel.h"

#include <QListView>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class ProfileView;
}

class ProfileView : public AbstractView {
  Q_OBJECT

  Ui::ProfileView *ui;

  ProfileListModel *m_profileModel;
  QListView *m_listView;
  QToolButton *m_editButton;
  QToolButton *m_deleteButton;
  QPushButton *m_loginButton;

public:
  explicit ProfileView(QWidget *parent = nullptr);
  ~ProfileView();

  void handleObjectCreated(ObjectTypes type, Storable *object) override;
  void handleObjectLoaded(ObjectTypes type, Storable *object) override;

private slots:
  void on_createButton_clicked();
  void on_profileListView_clicked(const QModelIndex &index);
  void on_deleteButton_clicked();
  void on_editButton_clicked();
};

#endif // PROFILEVIEW_H
