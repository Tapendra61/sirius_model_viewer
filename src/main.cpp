#include "sirius_logger/log.h"
#include "core/application.h"
#include "sirius_logger/log_level.h"

int main(int argc, char **argv) {
	sr::init_logger(sr::LogLevel::Trace);
	
	AppConfig config;
	config.window_title =  "Sirius Model Viewer";
	Application app(argc, argv, config);
	app.run();
}