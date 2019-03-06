#include "denglu.h"

denglu::denglu(int count,QWidget *parent)
: QDialog(parent)
{
    N = count;
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *subLayout;
    m_Labels = new QLabel*[N];
    m_LineEdits = new QLineEdit*[N];
    //设计界面
    for(int i=0; i<N; i++)
    {
        subLayout = new QHBoxLayout;
        m_LineEdits[i] = new QLineEdit(this);
        m_Labels[i] = new QLabel(this);
        subLayout->addWidget(m_Labels[i]);
        subLayout->addWidget(m_LineEdits[i]);
        layout->addLayout(subLayout);
    }

    m_OKButton = new QPushButton( tr("OK"), this );
    m_CancelButton = new QPushButton( tr("Cancel"), this );
    subLayout = new QHBoxLayout;
    subLayout->addStretch();
    subLayout->addWidget(m_OKButton);
    subLayout->addWidget(m_CancelButton);
    layout->addLayout(subLayout);
    setLayout(layout);

    connect(m_OKButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_CancelButton, SIGNAL(clicked()), this, SLOT(reject()));

}

denglu::~denglu()
{
    delete m_LineEdits;
    delete m_Labels;
}

void denglu::SetLabelTexts(const QStringList &listText)
{
    for(int i=0; i<listText.size(); i++)
    {
        if( i >= N )
            break;
        m_Labels[i]->setText( listText.at(i) );
    }
}

void denglu::SetOneLabelText(int index, const QString &text)
{
    m_Labels[index]->setText(text);
}

void denglu::SetLabelsWidth(int width)
{
    for(int i=0; i<N; i++)
        m_Labels[i]->setFixedWidth(width);
}


QString denglu::GetOneText(int index)
{
    return m_LineEdits[index]->text();
}


