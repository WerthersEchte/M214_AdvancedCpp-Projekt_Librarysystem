/*
 * UI.h
 *
 *  Created on: 24 Apr 2016
 *      Author: orobsonpires
 */

#include "Client.cpp"

namespace library {

class UI {
public:
	UI(Client& client);
	virtual ~UI();
	void showMenu();
private:
	void sendCommand();
	Client _client;
};

}
