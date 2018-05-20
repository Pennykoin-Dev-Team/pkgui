// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QFrame>
#include <QStyledItemDelegate>

namespace Ui {
class OverviewFrame;
}

namespace WalletGui {

class RecentTransactionsModel;

class OverviewFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(OverviewFrame)

public:
  OverviewFrame(QWidget* _parent);
  ~OverviewFrame();

private:
  QScopedPointer<Ui::OverviewFrame> m_ui;
  QSharedPointer<RecentTransactionsModel> m_transactionModel;

  void transactionsInserted(const QModelIndex& _parent, int _first, int _last);
  void transactionsRemoved(const QModelIndex& _parent, int _first, int _last);
  void layoutChanged();
  void actualBalanceUpdated(quint64 _balance);
  void pendingBalanceUpdated(quint64 _balance);
  void actualDepositBalanceUpdated(quint64 _balance);
  void pendingDepositBalanceUpdated(quint64 _balance);
  void reset();
};

}
