// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QFrame>

#include <IWalletLegacy.h>

namespace Ui {
  class SendFrame;
}

namespace WalletGui {

class TransferFrame;

class SendFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(SendFrame)

public:
  SendFrame(QWidget* _parent);
  ~SendFrame();

  void setAddress(const QString& _address);

private:
  QScopedPointer<Ui::SendFrame> m_ui;
  QList<TransferFrame*> m_transfers;

  void sendTransactionCompleted(CryptoNote::TransactionId _transactionId, bool _error, const QString& _errorText);
  void walletActualBalanceUpdated(quint64 _balance);
  void updateFee();
  static bool isValidPaymentId(const QByteArray& _paymentIdString);

  Q_SLOT void addRecipientClicked();
  Q_SLOT void clearAllClicked();
  Q_SLOT void mixinValueChanged(int _value);
  Q_SLOT void sendClicked();
};

}
