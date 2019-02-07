// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2018 The Circle Foundation
//  
// Copyright (c) 2018 The Circle Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <IWalletLegacy.h>

#include "Message.h"

namespace WalletGui {

typedef QPair<CryptoNote::TransactionId, Message> TransactionMessageId;

class MessagesModel : public QAbstractItemModel {
  Q_OBJECT
  Q_ENUMS(Columns)
  Q_ENUMS(Roles)

public:
  enum Columns{
    COLUMN_DATE = 0, COLUMN_TYPE, COLUMN_HEIGHT, COLUMN_MESSAGE, COLUMN_HASH, COLUMN_AMOUNT, COLUMN_MESSAGE_SIZE,
      COLUMN_FULL_MESSAGE, COLUMN_HAS_REPLY_TO
  };

  enum Roles {
    ROLE_DATE = Qt::UserRole, ROLE_TYPE, ROLE_HEIGHT, ROLE_MESSAGE, ROLE_FULL_MESSAGE, ROLE_COLUMN, ROLE_ROW,
      ROLE_HEADER_REPLY_TO, ROLE_HASH, ROLE_AMOUNT, ROLE_MESSAGE_SIZE
  };

  static const QString HEADER_REPLY_TO_KEY;
  static MessagesModel& instance();
  quint64 dayPoolAmount;
  quint64 totalPoolAmount;

  Qt::ItemFlags flags(const QModelIndex& _index) const Q_DECL_OVERRIDE;
  int columnCount(const QModelIndex& _parent = QModelIndex()) const Q_DECL_OVERRIDE;
  int rowCount(const QModelIndex& _parent = QModelIndex()) const Q_DECL_OVERRIDE;

  QVariant headerData(int _section, Qt::Orientation _orientation, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  QVariant data(const QModelIndex& _index, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
  QModelIndex index(int _row, int _column, const QModelIndex& _parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QModelIndex	parent(const QModelIndex& _index) const Q_DECL_OVERRIDE;

private:
  QVector<TransactionMessageId> m_messages;
  QHash<CryptoNote::TransactionId, QPair<quint32, quint32> > m_transactionRow;

  MessagesModel();
  ~MessagesModel();

  QVariant getDisplayRole(const QModelIndex& _index) const;
  QVariant getDecorationRole(const QModelIndex& _index) const;
  QVariant getAlignmentRole(const QModelIndex& _index) const;
  QVariant getUserRole(const QModelIndex& _index, int _role, CryptoNote::TransactionId _transactionId, CryptoNote::WalletLegacyTransaction& _transaction,
    const Message& _message) const;

  void reloadWalletTransactions();
  void resetPoolTotal();
  void appendTransaction(CryptoNote::TransactionId _id, quint32& _row_count);
  void appendTransaction(CryptoNote::TransactionId _id);
  void updateWalletTransaction(CryptoNote::TransactionId _id);
  void lastKnownHeightUpdated(quint64 _height);
  void reset();

Q_SIGNALS:
  void poolEarningsSignal(quint64 _dayPoolAmount, quint64 _totalPoolAmount);

};

}
