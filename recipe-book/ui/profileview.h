#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include "abstractview.h"
#include "profilelistmodel.h"

#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class ProfileView;
}

class ProfileView : public AbstractView {
  Q_OBJECT

  void selectProfile(const QModelIndex &index = QModelIndex());

  Ui::ProfileView *ui;

  QProfile *m_selectedProfile;
  ProfileListModel *m_profileModel;
  QListView *m_listView;
  QToolButton *m_loadMoreButton;
  QToolButton *m_editButton;
  QToolButton *m_deleteButton;
  QPushButton *m_loginButton;
  QLabel *m_loadedCountIndicator;
  QLabel *m_totalCountIndicator;

  int m_totalCount;

public:
  explicit ProfileView(QWidget *parent = nullptr);
  ~ProfileView();

  void handleObjectsCounted(ObjectTypes type, int count) override;
  void handleObjectCreated(ObjectTypes type, Storable *object) override;
  void handleObjectLoaded(ObjectTypes type, Storable *object) override;

  void setLoadedCount();
  void incrementTotalCount();
  void decrementTotalCount();

private slots:
  void on_createButton_clicked();
  void on_profileListView_clicked(const QModelIndex &index);
  void on_deleteButton_clicked();
  void on_editButton_clicked();
  void on_loginButton_clicked();

  void on_loadMoreButton_clicked();

  signals:
  void requestProfileCount(ObjectTypes type);
  void selectedProfileChanged(QProfile *profile);
};

#endif // PROFILEVIEW_H
