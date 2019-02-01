#include "string"
using namespace std;

// Stores all the IP-addresses in the network - of hosts and interfaces
const string IPaddress = "0.0.0.0, 30.40.50.0, 400.800.700.0, 0.0.1.0, 30.40.50.1, 88.88.88.1, 99.99.99.1, 0.0.2.0, 3.3.3.2, 1.1.1.2, 88.88.88.2, 0.0.3.0, 3.3.3.3, 77.77.77.3, 0.0.4.0, 400.800.700.4, 1.1.1.4, 99.99.99.4, 77.77.77.4, 0.0.0.1, 0.0.1.1, 0.0.2.1, 0.0.3.1, 0.0.3.2, 0.0.4.1, 0.0.4.2";

// "," Seprated fields show the different interface IP-Adresses of the same router
// ";" Seprated fields show the different routers
const string Routers = "0.0.0.0, 30.40.50.0, 400.800.700.0; 0.0.1.0, 30.40.50.1, 88.88.88.1, 99.99.99.1; 0.0.2.0, 3.3.3.2, 1.1.1.2, 88.88.88.2; 0.0.3.0, 3.3.3.3, 77.77.77.3; 0.0.4.0, 400.800.700.4, 1.1.1.4, 99.99.99.4, 77.77.77.4";

// Distance between the interfaces of two routers
const string InterfaceDistance = "(30.40.50.0, 30.40.50.1, 5), (400.800.700.0, 400.800.700.4, 40), (88.88.88.1, 88.88.88.2, 20), (99.99.99.1, 99.99.99.4, 80), (3.3.3.2, 3.3.3.3, 40), (1.1.1.2, 1.1.1.4, 5), (77.77.77.3, 77.77.77.4, 20)";