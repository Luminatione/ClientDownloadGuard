#pragma once

#ifndef BUTTON_CLICK_TO_THIS_CONNECTION(button, function)
#define BUTTON_CLICK_TO_THIS_CONNECTION(button, function) connect(button, SIGNAL(clicked()), this, SLOT(function))
#endif

#ifndef SERVER_RESPONSE_TO_THIS_CONNECTION(reply, onSuccess, onError)
#define SERVER_RESPONSE_TO_THIS_CONNECTION(reply, onSuccess, onError) 	connect(reply, &QIODevice::readyRead, this, &onSuccess);\
																		connect(reply, &QNetworkReply::errorOccurred, this, &onError)
#endif
#ifndef SERVER_RESPONSE_TO_THIS_DISCONNECTION(reply, onSuccess, onError)
#define SERVER_RESPONSE_TO_THIS_DISCONNECTION(reply, onSuccess, onError) 	disconnect(reply, &QIODevice::readyRead, this, &onSuccess);\
																		disconnect(reply, &QNetworkReply::errorOccurred, this, &onError)
#endif