#include "pixie-application.hpp"

int main(int argc, char *argv[]) {
    Pixie::Application app;
    int status = app.run(argc, argv);
    return status;
}
