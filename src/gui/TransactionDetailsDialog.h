// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2018 The Circle Foundation
//  
// Copyright (c) 2018 The Circle Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QDialog>

namespace Ui {
class TransactionDetailsDialog;
}

namespace WalletGui {

class TransactionDetailsDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(TransactionDetailsDialog)

public:
  TransactionDetailsDialog(const QModelIndex &_index, QWidget* _parent);
  ~TransactionDetailsDialog();

private:
  QScopedPointer<Ui::TransactionDetailsDialog> m_ui;
  const QString m_detailsTemplate;
};

}
