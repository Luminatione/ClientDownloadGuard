#pragma once

#ifndef BUTTON_CLICK_TO_THIS_CONNECTION(button, function)
#define BUTTON_CLICK_TO_THIS_CONNECTION(button, function) connect(button, SIGNAL(clicked()), this, SLOT(function))
#endif
