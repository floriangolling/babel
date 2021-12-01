#include "loginPage.hpp"

Login::Login(myWindow *window, std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, std::string username, std::string password, QWidget *parent) : QWidget(parent) {
    QWidget *widget = new QWidget(this);
    widget->setStyleSheet("background-color:#009cd6;border-radius:25px");
    widget->setGeometry(400, 200, 500, 375);
    QPushButton *button = new QPushButton("CONNEXION", this);
    QPushButton *button2 = new QPushButton("S'INSCRIRE", this);
    QSignalMapper *mapper = new QSignalMapper();
    QLabel *connectionLabel = new QLabel(this);
    QFont *font = new QFont(QString("Arial"), 40, QFont::Bold);
    QLineEdit *usernameInput = new QLineEdit("", this);
    QLineEdit *passwordInput = new QLineEdit("", this);

    _errorMessage = new QLabel(this);
    _errorMessage->setGeometry(550, 600, 200, 15);
    _errorMessage->setHidden(true);
    _errorMessage->setStyleSheet("background-color:red");
    _errorMessage->setAlignment(Qt::AlignHCenter);
    _inputPassword = new QLabel(this);
    _inputUsername = new QLabel(this);
    _inputUsername->setText("username is too long");
    _inputPassword->setStyleSheet("background-color:none;color:red");
    _inputUsername->setGeometry(755, 260, 200, 35);
    _inputPassword->setText("password is too long");
    _inputUsername->setStyleSheet("background-color:none;color:red");
    _inputPassword->setGeometry(755, 335, 200, 35);
    _inputPassword->setVisible(false);
    _inputUsername->setVisible(false);
    _fctClickEvent = fctClickEvent;
    _fctTextEvent = fctTextEvent;
    this->_window = window;
    usernameInput->setPlaceholderText("NOM DE COMPTE");
    passwordInput->setPlaceholderText("MOT DE PASSE");
    button2->setStyleSheet("background-color:white");
    button->setStyleSheet("background-color:white");
    passwordInput->setStyleSheet("background-color:white");
    usernameInput->setStyleSheet("background-color:white");
    usernameInput->setText(username.c_str());
    passwordInput->setText(password.c_str());
    connectionLabel->setText("Page de connexion");
    usernameInput->setGeometry(550, 260, 200, 35);
    passwordInput->setGeometry(550, 335, 200, 35);
    passwordInput->setEchoMode(QLineEdit::Password);
    button->setGeometry(550, 410, 200, 35);
    button2->setGeometry(550, 485, 200, 35);
    connectionLabel->setGeometry(400, 0, 550, 200);
    connectionLabel->setFont(*font);
    connect(button2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(button2, goToRegister);
    connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(button, LoginEvent);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleWindowEvents(int)));
    connect(usernameInput, SIGNAL(textChanged(const QString &)), this, SLOT(userInputChange(const QString &)));
    connect(passwordInput, SIGNAL(textChanged(const QString &)), this, SLOT(passwordInputChange(const QString &)));
    userInputChange(usernameInput->text());
    passwordInputChange(passwordInput->text());
}

int Login::handleWindowEvents(int ev) {
    int response = this->_fctClickEvent(ev);
    return (response);
}

void Login::setMessage(const std::string &str) {
    _errorMessage->setText(str.c_str());
    if (_errorMessage->isVisible() == false) {
        _errorMessage->setVisible(true);
        _errorMessage->repaint();
    }
}

void Login::handleTextEvent(const std::string &str, int id) {
    this->_fctTextEvent(str, id);
}

void Login::userInputChange(const QString &str) {
    if (str.toStdString().size() > 20 && _inputUsername->isVisible() == false) {
        _inputUsername->setVisible(true);
        _inputUsername->repaint();
    } else if (str.toStdString().size() <= 20 && _inputUsername->isVisible() == true) {
        _inputUsername->setVisible(false);
    }
    this->handleTextEvent(str.toStdString(), LoginUsernameInput);
}

void Login::passwordInputChange(const QString &str) {
    if (str.toStdString().size() > 20 && _inputPassword->isVisible() == false) {
        _inputPassword->setVisible(true);
        _inputPassword->repaint();
    } else if (str.toStdString().size() <= 20 && _inputPassword->isVisible() == true) {
        _inputPassword->setVisible(false);
    }
    this->handleTextEvent(str.toStdString(), LoginPasswordInput);
}
