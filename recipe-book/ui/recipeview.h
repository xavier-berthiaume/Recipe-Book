#ifndef RECIPEVIEW_H
#define RECIPEVIEW_H

#include "abstractview.h"
#include "recipelistmodel.h"

#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class RecipeView;
}

class RecipeView : public AbstractView {
  Q_OBJECT

  void setLoadedCount();
  void checkLoadedStatus();
  void incrementTotalCount();
  void decrementTotalCount();

  Ui::RecipeView *ui;

  RecipeListModel *m_recipeModel;

  QListView *m_listView;
  QToolButton *m_loadMoreButton;
  QToolButton *m_editButton;
  QToolButton *m_deleteButton;
  QToolButton *m_detailsButton;
  QLabel *m_loadedCountIndicator;
  QLabel *m_totalCountIndicator;

  int m_totalCount = 0;

public:
  explicit RecipeView(QWidget *parent = nullptr);
  ~RecipeView();

  void clearModel() override;

  void handleObjectsCounted(ObjectTypes type, int count) override;
  void handleObjectCreated(ObjectTypes type, Storable *object) override;
  void handleObjectLoaded(ObjectTypes type, Storable *object) override;

private slots:
};

#endif // RECIPEVIEW_H
