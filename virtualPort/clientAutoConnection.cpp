// add this to connect the client when you press "connect" on tino

std::ifstream inTino;
inTino.open("/home/yourUserName/.tino/clientPort.txt");
std::string portnameString;
getline(inTino, portnameString);
QString qportnameString = QString::fromStdString(portnameString);

mbDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                 qportnameString);

