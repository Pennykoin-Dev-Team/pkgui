// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2018 The Circle Foundation
//  
// Copyright (c) 2018 The Circle Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QDateTime>

#include "SortedMessagesModel.h"
#include "MessagesModel.h"

namespace WalletGui {

SortedMessagesModel& SortedMessagesModel::instance() {
  static SortedMessagesModel inst;
  return inst;
}

SortedMessagesModel::SortedMessagesModel() : QSortFilterProxyModel() {
  setSourceModel(&MessagesModel::instance());
  setDynamicSortFilter(true);
  sort(MessagesModel::COLUMN_DATE, Qt::DescendingOrder);
}

SortedMessagesModel::~SortedMessagesModel() {
}

bool SortedMessagesModel::lessThan(const QModelIndex& _left, const QModelIndex& _right) const {
  QDateTime leftDate = _left.data(MessagesModel::ROLE_DATE).toDateTime();
  QDateTime rightDate = _right.data(MessagesModel::ROLE_DATE).toDateTime();
  if((rightDate.isNull() || !rightDate.isValid()) && (leftDate.isNull() || !leftDate.isValid())) {
    return _left.row() < _right.row();
  }

  if(leftDate.isNull() || !leftDate.isValid()) {
    return false;
  }

  if(rightDate.isNull() || !rightDate.isValid()) {
    return true;
  }

  return leftDate < rightDate;
}

}
