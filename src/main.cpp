#include "sirius_logger/log.h"
#include "core/application.h"
#include "sirius_logger/log_level.h"

const int WIDTH = 900;
const int HEIGHT = 900;

int main(int argc, char **argv) {
	sr::init_logger(sr::LogLevel::Info);
	Application app(argc, argv, "Sirius Model Viewer", WIDTH, HEIGHT);
	app.run();
}