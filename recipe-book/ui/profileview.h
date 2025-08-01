#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include "abstractview.h"

namespace Ui {
class ProfileView;
}

class ProfileView : public AbstractView {
  Q_OBJECT

public:
  explicit ProfileView(QWidget *parent = nullptr);
  ~ProfileView();

  void handleObjectCreated(ObjectTypes type, Storable *object) override;
  void handleObjectLoaded(ObjectTypes type, Storable *object) override;

  private slots:
  void on_createButton_clicked();

  private:
  Ui::ProfileView *ui;
};

#endif // PROFILEVIEW_H
