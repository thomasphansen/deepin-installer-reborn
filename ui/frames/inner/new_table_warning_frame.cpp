// Copyright (c) 2016 LiuLang. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/frames/inner/new_table_warning_frame.h"

#include <QEvent>
#include <QLabel>
#include <QVBoxLayout>

#include "base/file_util.h"
#include "ui/frames/consts.h"
#include "ui/widgets/comment_label.h"
#include "ui/widgets/nav_button.h"
#include "ui/widgets/title_label.h"
#include "ui/utils/widget_util.h"

namespace installer {

NewTableWarningFrame::NewTableWarningFrame(QWidget* parent) : QFrame(parent) {
  this->setObjectName("new_table_warning_frame");

  this->initUI();
  this->initConnections();
}

void NewTableWarningFrame::changeEvent(QEvent* event) {
  if (event->type() == QEvent::LanguageChange) {
    title_label_->setText(tr("Format Disk"));
    comment_label_->setText(tr("All data will be erased on that disk!"));
    cancel_button_->setText(tr("Cancel"));
    confirm_button_->setText(tr("Continue"));
  } else {
    QFrame::changeEvent(event);
  }
}

void NewTableWarningFrame::initConnections() {
  connect(cancel_button_, &QPushButton::clicked,
          this, &NewTableWarningFrame::canceled);
  connect(confirm_button_, &QPushButton::clicked,
          this, &NewTableWarningFrame::confirmed);
}

void NewTableWarningFrame::initUI() {
  QLabel* warning_label = new QLabel();
  QPixmap warning_pixmap(":/images/warning.png");
  warning_label->setPixmap(warning_pixmap);
  title_label_ = new TitleLabel(tr("Format Disk"));
  title_label_->setStyleSheet(ReadFile(":/styles/new_table_warning_frame.css"));

  QHBoxLayout* title_layout = new QHBoxLayout();
  title_layout->setContentsMargins(0, 0, 0, 0);
  title_layout->setSpacing(0);
  title_layout->addStretch();
  title_layout->addWidget(warning_label);
  title_layout->addSpacing(8);
  title_layout->addWidget(title_label_);
  title_layout->addStretch();

  comment_label_ = new CommentLabel(
      tr("All data will be erased on that disk!"));
  QHBoxLayout* comment_layout = new QHBoxLayout();
  comment_layout->setContentsMargins(0, 0, 0, 0);
  comment_layout->setSpacing(0);
  comment_layout->addWidget(comment_label_);

  cancel_button_ = new NavButton(tr("Cancel"));
  confirm_button_ = new NavButton(tr("Continue"));

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(kMainLayoutSpacing);
  layout->addStretch();
  layout->addLayout(title_layout);
  layout->addLayout(comment_layout);
  layout->addStretch();
  layout->addWidget(cancel_button_, 0, Qt::AlignHCenter);
  layout->addSpacing(kNavButtonVerticalSpacing);
  layout->addWidget(confirm_button_, 0, Qt::AlignHCenter);

  this->setLayout(layout);
  this->setContentsMargins(0, 0, 0, 0);
}

}  // namespace installer