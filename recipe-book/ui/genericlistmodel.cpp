#include "genericlistmodel.h"

template <typename T>
GenericListModel<T>::GenericListModel(QObject *parent)
    : QAbstractListModel(parent) {}

template <typename T>
int GenericListModel<T>::rowCount(const QModelIndex &parent) const {
  return m_modelList.size();
}

template <typename T>
void GenericListModel<T>::populate(const QList<T *> &models) {
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

template <typename T> void GenericListModel<T>::addModel(T *model) {
  if (model == nullptr)
    return;

  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_modelList.append(model);

  connectModelSignals(model);
  endInsertRows();
}

template <typename T> void GenericListModel<T>::removeModel(int index) {
  if (index < 0 || index >= m_modelList.size())
    return;

  beginRemoveRows(QModelIndex(), index, index);
  m_modelList.removeAt(index);
  endRemoveRows();
}
