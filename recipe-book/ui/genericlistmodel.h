#ifndef GENERICLISTMODEL_H
#define GENERICLISTMODEL_H

#include <QAbstractListModel>
#include <QModelIndex>

template <typename T> class GenericListModel : public QAbstractListModel {
protected:
  QList<T *> m_modelList;
  virtual void connectModelSignals(T *model) const = 0;

public:
  explicit GenericListModel(QObject *parent = nullptr)
      : QAbstractListModel(parent) {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    return m_modelList.size();
  }

  void populate(const QList<T *> &models) {
    if (models.empty())
      return;

    if (!m_modelList.isEmpty()) {
      beginResetModel();
      qDeleteAll(m_modelList);
      m_modelList.clear();
      endResetModel();
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + models.size() - 1);
    for (T *model : models) {
      m_modelList.append(model);
      connectModelSignals(model);
    }
    endInsertRows();
  }

  void addModel(T *model) {
    if (model == nullptr)
      return;

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_modelList.append(model);
    connectModelSignals(model);
    endInsertRows();
  }

  void removeModel(int index) {
    if (index < 0 || index >= m_modelList.size())
      return;

    beginRemoveRows(QModelIndex(), index, index);
    m_modelList.removeAt(index);
    endRemoveRows();
  }

  virtual void modifyModel(int index, const QVariant &data, int role) = 0;
};

#endif
