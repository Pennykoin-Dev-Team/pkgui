// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2015-2016 XDN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QDialog>

namespace Ui {
class AboutDialog;
}

namespace WalletGui {

class AboutDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(AboutDialog)

public:
  AboutDialog(QWidget* _parent);
  ~AboutDialog();

private:
  QScopedPointer<Ui::AboutDialog> m_ui;
};

}
