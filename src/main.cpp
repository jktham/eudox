#include "app.hpp"

App app;

int main() {
	app.init();
	app.loop();
	app.exit();
	return 0;
}
