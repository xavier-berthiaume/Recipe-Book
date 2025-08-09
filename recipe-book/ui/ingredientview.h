#ifndef INGREDIENTVIEW_H
#define INGREDIENTVIEW_H

#include "abstractview.h"
#include "ingredientlistmodel.h"

#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class IngredientView;
}

class IngredientView : public AbstractView {
  Q_OBJECT

  void setLoadedCount();
  void checkLoadedStatus();
  void incrementTotalCount();
  void decrementTotalCount();

  Ui::IngredientView *ui;

  IngredientListModel *m_ingredientModel;

  QListView *m_listView;
  QToolButton *m_loadMoreButton;
  QToolButton *m_editButton;
  QToolButton *m_deleteButton;
  QPushButton *m_detailsButton;
  QLabel *m_loadedCountIndicator;
  QLabel *m_totalCountIndicator;

  int m_totalCount = 0;

public:
  explicit IngredientView(QWidget *parent = nullptr);
  ~IngredientView();

  void clearModel() override;

  void handleObjectsCounted(ObjectTypes type, int count) override;
  void handleObjectCreated(ObjectTypes type, Storable *object) override;
  void handleObjectLoaded(ObjectTypes type, Storable *object) override;
  private slots:
  void on_createButton_clicked();
      void on_loadMoreButton_clicked();
  void on_deleteButton_clicked();
      void on_editButton_clicked();
  void on_ingredientListView_clicked(const QModelIndex &index);
      void on_detailsButton_clicked();
};

#endif // INGREDIENTVIEW_H
