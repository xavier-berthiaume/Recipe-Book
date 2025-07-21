#ifndef GENERIC_ROOT_VIEW_H
#define GENERIC_ROOT_VIEW_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

template <typename T> class GenericRootView : public QWidget {

protected:
  QList<T *> m_models;
  QLineEdit *m_searchBar;
  QPushButton *m_searchButton;
  QPushButton *m_createButton;
  QGridLayout *m_displayBoxArea;

  GenericRootView(const QList<T *> &models, QWidget *parent = nullptr)
      : m_models(models), QWidget(parent), m_searchBar(new QLineEdit(this)),
        m_searchButton(new QPushButton(tr("Search"), this)),
        m_createButton(new QPushButton(tr("Create"), this)),
        m_displayBoxArea(new QGridLayout(this)) {

    QVBoxLayout *widgetLayout = new QVBoxLayout(this);
    QHBoxLayout *searchLayout = new QHBoxLayout(this);

    searchLayout->addWidget(m_searchBar);
    searchLayout->addWidget(m_searchButton);
    searchLayout->addWidget(m_createButton);

    QWidget *searchWidget = new QWidget(this);
    searchWidget->setLayout(searchLayout);

    QWidget *display = new QWidget(this);
    display->setLayout(m_displayBoxArea);

    widgetLayout->addWidget(searchWidget);
    widgetLayout->addWidget(display);

    setLayout(widgetLayout);
  }

  virtual void displayModels() = 0;
  void addModel(T *model) { m_models->append(model); };
};

#endif
