/*

Entry point of the application.

Copyright (C) 2018, Guillaume Gonnet
License MIT

*/

#include "app/system.h"
#include "app/mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtCore/QCommandLineParser>


// Entry point of the application.
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.setApplicationDescription("A MIPS simulator.");

    parser.addPositionalArgument("program", "The binary program to load.");

    QCommandLineOption debug_option("d", "Enable debug mode.");
    parser.addOption(debug_option);

    QCommandLineOption offset_option("o", "Start cycle offset (default=0).", "number");
    offset_option.setDefaultValue("0");
    parser.addOption(offset_option);

    parser.process(app);
    int offset = parser.value("o").toInt();

    app::MainWindow window;
    app::System system(window, parser.isSet("d"), offset);

    auto args = parser.positionalArguments();

    system.Initialize();
    system.loader().Load(args.value(0));

    window.show();
    system.Start();

    return app.exec();
}